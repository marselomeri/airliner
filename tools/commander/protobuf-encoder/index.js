/****************************************************************************
 *
 *   Copyright (c) 2018 Windhover Labs, L.L.C. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name Windhover Labs nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 *****************************************************************************/

'use strict';

var Parser = require( 'binary-parser' ).Parser;
const net = require( 'net' );
const Emitter = require( 'events' );
var fs = require( 'fs' );
const util = require( 'util' );
var protobuf = require( 'protobufjs' );
var Promise = require( 'promise' );
var mergeJSON = require( 'merge-json' );
var convict = require( 'convict' );
var config = require( './config.js' );
const Sparkles = require( 'sparkles' );
var path = require( 'path' );
var dot = require( 'dot-object' );
var Long = require( 'long' );
var path = require( 'path' );
const CdrGroundPlugin = require(path.join(global.CDR_INSTALL_DIR, '/commander/classes/CdrGroundPlugin')).CdrGroundPlugin;

/**
 * Event id's
 * @type {Object}
 */
var EventEnum = Object.freeze( {
    'INITIALIZED': 1,
    'OPS_PATH_NOT_FOUND': 2,
    'MSG_OPS_PATH_NOT_FOUND': 3,
    'MSG_DEF_NOT_FOUND': 4,
    'APP_NOT_FOUND': 5,
    'UNHANDLED_EXCEPTION ': 6
} );

var emit = Emitter.prototype.emit;

exports.events = [
    'connect',
    'close',
    'error'
    ];


/**
 * Count listeners
 * @type {Function}
 */
var listenerCount = Emitter.listenerCount ||
function( emitter, type ) {
    return emitter.listeners( type ).length
}

class ProtobufEncoder extends CdrGroundPlugin {
    /**
     * Constructor for protobuf encoder
     * @param       {String} workspace  path to workspace
     * @param       {String} configFile path to protobuf-encoder-config.json
     * @constructor
     */
    constructor( configObj ) {
        super(configObj);
        
        this.parsers = {};
        this.defs = {};
        this.workspace = configObj.workspace;
        
        var self = this;

        /* Load environment dependent configuration */
        config.loadFile( configObj.configFile );

        /* Perform validation */
        config.validate( {
            allowed: 'strict'
        } );

        this.ccsdsPriHdr = new Parser()
            .endianess( 'big' )
            .bit3( 'version' )
            .bit1( 'pktType' )
            .bit1( 'secHdr' )
            .bit11( 'apid' )
            .bit2( 'segment' )
            .bit14( 'sequence' )
            .uint16( 'length' );

        this.ccsdsCmdSecHdr = new Parser()
            .endianess( 'little' )
            .bit1( 'reserved' )
            .bit7( 'code' )
            .uint8( 'checksum' );

        switch ( config.get( 'CFE_SB_PACKET_TIME_FORMAT' ) ) {
            case 'CFE_SB_TIME_32_16_SUBS':
                this.ccsdsTlmSecHdr = new Parser()
                    .endianess( 'little' )
                    .uint32( 'seconds' )
                    .uint16( 'subseconds' );
                this.tlmHeaderLength = 96;
                break;

            case 'CFE_SB_TIME_32_32_SUBS':
                this.ccsdsTlmSecHdr = new Parser()
                    .endianess( 'little' )
                    .uint32( 'seconds' )
                    .uint32( 'subseconds' );
                    this.tlmHeaderLength = 98;
                break;

            case 'CFE_SB_TIME_32_32_M_20':
                this.ccsdsTlmSecHdr = new Parser()
                    .endianess( 'little' )
                    .uint32( 'seconds' )
                    .uint32( 'subseconds' );
                this.tlmHeaderLength = 98;
                break;

            default:
                break;
        }

        this.ccsds = new Parser()
            .endianess( 'little' )
            .nest( 'PriHdr', {
                type: this.ccsdsPriHdr
            } )
            .choice( 'SecHdr', {
                tag: 'PriHdr.pktType',
                choices: {
                    0: this.ccsdsTlmSecHdr,
                    1: this.ccsdsCmdSecHdr
                }
            } )
            .buffer( 'payload', {
                readUntil: 'eof'
            } );
        
        var inMsgDefs = config.get( 'msgDefs' )
        for ( var i = 0; i < inMsgDefs.length; ++i ) {
            if ( typeof process.env.AIRLINER_MSG_DEF_PATH === 'undefined' ) {
                var fullPath = path.join( this.workspace, config.get( 'msgDefPath' ), inMsgDefs[ i ].file );
            } else {
                var fullPath = path.join( process.env.AIRLINER_MSG_DEF_PATH, inMsgDefs[ i ].file );
            }

            var msgDefInput = JSON.parse( fs.readFileSync( fullPath, 'utf8' ) );
            this.defs = mergeJSON.merge( this.defs, msgDefInput );
        }

        if ( typeof process.env.AIRLINER_PROTO_PATH === 'undefined' ) {
            var fullPath = path.join( this.workspace, config.get( 'protobufDirectory' ) );
        } else {
            var fullPath = process.env.AIRLINER_PROTO_PATH;
        }
        var protoFiles = self.recFindByExt( fullPath, 'proto' );

        for ( var i = 0; i < protoFiles.length; i++ ) {
            this.parseProtoFile( protoFiles[ i ] );
        }

        this.namespace.emitter.on( config.get( 'jsonInputStreamID' ), function( message ) {
            try {
                var tlmDef = self.getTlmDefByPath( message.opsPath );
                if ( typeof tlmDef === 'undefined' ) {
                    self.logDebug( 'tlmDef is undefined for  \'' + message.opsPath + '\'' );
                    return undefined;
                } else {
                    var msgDef = self.getMsgDefByName( tlmDef.airliner_msg );

                    if ( typeof msgDef === 'undefined' ) {
                        self.logError( 'msgDef is undefined for  \'' + message.opsPath + '\'' );
                        return undefined;
                    } else {
                        if ( msgDef.hasOwnProperty( 'proto_root' ) ) {
                            var symbolName = message.symbol; //self.getSymbolNameFromOpsPath( message.opsPath );
                            var msgID = message.msgID; //tlmDef.airliner_mid;


                            if ( typeof symbolName !== 'undefined' ) {

                                var pbMsgDef = msgDef.proto_root.lookupType( symbolName + '_pb' );
                                var pbMsg = pbMsgDef.create( message.content );

                                var pbBuffer = pbMsgDef.encode( pbMsg ).finish();

                                var hdrBuffer = new Buffer( 12 )
                                hdrBuffer.writeUInt16BE( msgID, 0 );
                                hdrBuffer.writeUInt16BE( 1, 2 );
                                hdrBuffer.writeUInt16BE( pbBuffer.length - 1, 4 );
                                hdrBuffer.writeUInt16BE( 0, 6 );
                                hdrBuffer.writeUInt16BE( 0, 8 );
                                hdrBuffer.writeUInt16BE( 0, 10 );

                                var msgBuffer = Buffer.concat( [ hdrBuffer, pbBuffer ] );

                                self.namespace.emit( config.get( 'binaryOutputStreamID' ), msgBuffer );
                            }
                        }
                    }
                }
            } catch ( err ) {
                self.logError('Input JSON: Unhandled exception. \'' + err + '\'' );
            }
        } );
        
        this.logInfo( 'Initialized' );
    };

    /**
     * Generates an array of paths of files that are located in the
     * base directory which matches the extention passed into parameters.
     * @param  {String} base   base directory path
     * @param  {String} ext    file extention
     * @param  {Object} files  file read object or undefined
     * @param  {Object} result empty array or undefined
     * @return {Object}        array of matching paths
     */
    recFindByExt( base, ext, files, result ) {
        var self = this

        result = result || []
        try {
            files = files || fs.readdirSync( base )
            files.forEach(
                    function( file ) {
                        var newbase = path.join( base, file )
                        if ( fs.statSync( newbase ).isDirectory() ) {
                            result = self.recFindByExt( newbase, ext, fs.readdirSync( newbase ), result )
                        } else {
                            if ( file.substr( -1 * ( ext.length + 1 ) ) == '.' + ext ) {
                                result.push( newbase )
                            }
                        }
                    }
            )
        } catch ( e ) {
            self.logError( 'recFindByExt | unknown error  \'' + e.message + '\'' );
        }
        return result
    }

    /**
     * Gets telemetry operations path from full telemetry path
     * @param  {String} opsPath telemetry path
     * @return {String}         telemetry operation path
     */
    getMsgOpsPathFromFullOpsPath( opsPath ) {
        var appName = this.getAppNameFromPath( opsPath );
        var opName = this.getOperationFromPath( opsPath );
        if ( appName != undefined & opName != undefined ) {
            var msgOpsPath = '/' + appName + '/' + opName;
            return msgOpsPath;
        } else {
            return undefined
        }
    }


    /**
     * Gets telemetry symbol name from operation path
     * @param  {String} opsPath operation path
     * @return {string}         symbol name
     */
    getSymbolNameFromOpsPath( opsPath ) {
        var msgOpsPath = this.getMsgOpsPathFromFullOpsPath( opsPath );

        if ( typeof msgOpsPath === 'undefined' ) {
            this.logError( 'getSymbolNameFromOpsPath: Ops path not found.' );
        } else {
            var msgDef = this.getTlmDefByPath( msgOpsPath );

            if ( typeof msgDef === 'undefined' ) {
                this.logError( 'getSymbolNameFromOpsPath: Message ops path not found.' );
                return undefined;
            } else {
                return msgDef.airliner_msg;
            }
        }
        return undefined;
    }


    /**
     * Adds operation paths to passed json
     * @param  {Object} inJSON input json
     * @return {Object}        output json
     */
    convertJsonToProtoJson( inJSON ) {
        var outJSON = {};

        for ( var itemID in inJSON ) {
            var msgOpsPath = this.getMsgOpsPathFromFullOpsPath( itemID );
            if ( msgOpsPath != undefined ) {
                var updatedItemID = itemID.replace( msgOpsPath + '/', '' );
                updatedItemID = updatedItemID.replace( '/', '.' );

                outJSON[ updatedItemID ] = inJSON[ itemID ].value;
            }
        }

        dot.object( outJSON );
        return outJSON;
    }


    /**
     * Gets message definition by message name
     * @param  {String} msgName message name
     * @return {Object}         message definition
     */
    getMsgDefByName( msgName ) {
        for ( var appID in this.defs.Airliner.apps ) {
            var app = this.defs.Airliner.apps[ appID ];
            for ( var protoID in app.proto_msgs ) {
                var protomsg = app.proto_msgs[ protoID ];
                if ( protoID == msgName ) {
                    return protomsg;
                }
            }
        }
        return undefined;
    }


    /**
     * Parses protobuf file and get schema specific protobuf object
     * @param  {String} filePath protobuf file path
     */
    parseProtoFile( filePath ) {
        var self = this;
        try {
            var fileName = filePath.replace( /^.*[\\\/]/, '' );
            var structureName = fileName.replace( /\.[^/.]+$/, '' );

            var msgDef = this.getMsgDefByName( structureName );

            if ( typeof msgDef === 'undefined' ) {
                this.logError( 'parseProtoFile (' + filePath + '): Message definition not found.' + structureName + '.' );
            } else {
                msgDef.proto_root = new protobuf.Root();

                protobuf.loadSync( filePath, msgDef.proto_root );
            }
        } catch ( e ) {
            this.logError( 'parseProtoFile parse error \'' + e.message + '\'' );
        }

    }


    /**
     * Parse and return app name
     * @param  {String} path telemetry path
     * @return {String}      App name
     */
    getAppNameFromPath( path ) {
        if ( typeof path === 'string' ) {
            var splitName = path.split( '/' );
            return splitName[ 1 ];
        }
        return undefined;
    }


    /**
     * Parse and return operation name
     * @param  {String} path telemetry path
     * @return {String}      Operation name
     */
    getOperationFromPath( path ) {
        if ( typeof path === 'string' ) {
            var splitName = path.split( '/' );
            return splitName[ 2 ];
        }
        return undefined;
    }


    /**
     * Gets application definition by application name
     * @param  {String} appName application name
     * @return {Object}         application definition object
     */
    getAppDefinition( appName ) {
        for ( var appID in this.defs.Airliner.apps ) {
            var app = this.defs.Airliner.apps[ appID ];
            if ( app.app_name == appName ) {
                return app;
            }
        }
    }


    /**
     * Gets message definition by telemetry path name
     * @param  {String} path telemetry path name
     * @return {Object}      telemetry definition object
     */
    getMsgDefByPath( path ) {
        var tlmDef = this.getTlmDefByPath( path );
        if ( typeof tlmDef === 'undefined' ) {
            this.logError( 'getMsgDefByPath:  Ops path not found. \'' + path + '\'.' );
            return undefined;
        } else {
            return tlmDef.airliner_msg;
        }
    }


    /**
     * Gets telemetry definition by path name
     * @param  {String} path telemetry path name
     * @return {Object}      telemetry definition object
     */
    getTlmDefByPath( path ) {
        var appName = this.getAppNameFromPath( path );
        if ( typeof appName === 'undefined' ) {
            this.logDebug( 'getTlmDefByPath:  App not found in path. \'' + path + '\'.' );
            return undefined;
        } else {
            var operationName = this.getOperationFromPath( path );
            if ( typeof operationName === 'undefined' ) {
                this.logError( 'getTlmDefByPath:  Ops path not found. \'' + path + '\'.' );
                return undefined;
            } else {
                var appDefinition = this.getAppDefinition( appName );
                if ( typeof appDefinition === 'undefined' ) {
                    this.logDebug( 'getTlmDefByPath:  App not found. \'' + appName + '\'.' );
                    return undefined;
                } else {
                    return appDefinition.operations[ operationName ];
                }
            }
        }
    }
};


exports = module.exports = ProtobufEncoder;