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

var Parser = require( "binary-parser" ).Parser;
const net = require( 'net' );
var fs = require( 'fs' );
const util = require( 'util' );
var mergeJSON = require( 'merge-json' );
var convict = require( 'convict' );
var path = require( 'path' );
var jp = require( 'jsonpath' );
var path = require( 'path' );
const autoBind = require('auto-bind');
const CdrGroundPlugin = require(path.join(global.CDR_INSTALL_DIR, '/commander/classes/CdrGroundPlugin')).CdrGroundPlugin;


class ConfigDatabase extends CdrGroundPlugin {
    /**
     * Constructor for configuring databse
     * @param       {String} workspace  path to commander workspace
     * @param       {string} configFile path to config-database-config.json
     * @constructor
     */
    constructor( configObj ) {
        configObj.webRoot = path.join( __dirname, 'web');  
        super(configObj)
        
        autoBind(this);

        var self = this;
        this.defs;
        this.workspace = configObj.workspace;
        this.instanceEmitter;

        /* Initialize the configuration. */
        this.initConfig(configObj.name, configObj.configFile);
        
        /* Initialize server side housekeeping telemetry that we'll publish 
         * later. */
        this.initTelemetry();

        /* Initialize client side interface. */
        this.initClientInterface();
        
        this.namespace.recv( this.config.get( 'queryConfigStreamID' ), function( query, cb ) {
            var result = jp.query( self.defs, query );
            cb( result );
        } );

        /* Initialize server side commands. */
        this.initCommands();
        
        this.logInfo( 'Initialized' );
    };
    
    
    
    initConfig(name, configFile) {  
        var config;
        
        this.config = convict( {
            env: {
              doc: 'The application environment.',
              format: [ 'production', 'development', 'test' ],
              default: 'development',
              env: 'NODE_ENV'
            },
            CFE_SB_PACKET_TIME_FORMAT: {
                doc: 'CFE SB time format.',
                format: [ 'CFE_SB_TIME_32_16_SUBS', 'CFE_SB_TIME_32_32_SUBS', 'CFE_SB_TIME_32_32_M_20' ],
                default: 'CFE_SB_TIME_32_16_SUBS'
            },
            CFE_TIME_EPOCH_YEAR: {
                doc: 'CFE Time epoch year.',
                format: 'int',
                default: 1980
            },
            CFE_TIME_EPOCH_DAY: {
                doc: 'CFE Time epoch year.',
                format: 'int',
                default: 1
            },
            CFE_TIME_EPOCH_HOUR: {
                doc: 'CFE Time epoch year.',
                format: 'int',
                default: 0
            },
            CFE_TIME_EPOCH_MINUTE: {
                doc: 'CFE Time epoch year.',
                format: 'int',
                default: 0
            },
            CFE_TIME_EPOCH_SECOND: {
                doc: 'CFE Time epoch year.',
                format: 'int',
                default: 0
            },
            msgDefs: [ {
              file: {
                doc: 'Input file.',
                format: String,
                default: ''
              }
            } ],
            queryConfigStreamID: {
              doc: 'Stream ID for configuration queries',
              format: String,
              default: ''
            }
          } );

        /* Load environment dependent configuration */
        this.config.loadFile( configFile );

        /* Perform validation */
        this.config.validate( {
            allowed: 'strict'
        } );

        var inMsgDefs = this.config.get( 'msgDefs' );

        for ( var i = 0; i < inMsgDefs.length; ++i ) {
            if ( typeof process.env.AIRLINER_MSG_DEF_PATH === 'undefined' ) {
                var fullPath = path.join( this.workspace, config.get( 'msgDefPath' ), inMsgDefs[ i ].file );
            } else {
                var fullPath = path.join( process.env.AIRLINER_MSG_DEF_PATH, inMsgDefs[ i ].file );
            }
            var msgDefInput = JSON.parse( fs.readFileSync( fullPath, 'utf8' ) );
            this.defs = mergeJSON.merge( this.defs, msgDefInput );
        }
        
        this.config.name = name;
    }
        

    
    initCommands() {
        var cmdGetMessageIDFromOpsName = {
            opsPath: '/' + this.config.name + '/getMessageIDFromOpsName',
            returnType: 'uint16',
            args: [
                {
                    name:    'OpsName',
                    type:    'char',
                    bitSize: 2048
                }
            ]
        }
        this.addCommand(cmdGetMessageIDFromOpsName, this.getMessageIDFromOpsName);

        var cmdGetPerfIDs = {
            opsPath: '/' + this.config.name + '/cmdGetPerfIDs',
            returnType: 'object'
        }
        this.addCommand(cmdGetPerfIDs, this.cmdGetPerfIDs);
    };


    
    getMessageIDFromOpsName(cmd, cb) {
        var self = this;

        if(typeof cb !== 'function') {
            var errorText = 'Callback is required.';
            this.logError(errorText);
            this.hk.content.cmdRejectCount++;
        } else if(cmd.hasOwnProperty('args') == false) {
            var errorText = 'Invalid arguments.  OpsName is required.';
            this.logError(errorText);
            this.hk.content.cmdRejectCount++;
            cb(errrorText);
        } else {
            var opsName = cmd.args[0].value;
            this.hk.content.cmdAcceptCount++;
            
            var app = this.getAppFromPath(opsName);
            var opName = this.getOperationFromPath(opsName);
            
            var opObj = self.defs.Airliner.apps[app];
            
            if(self.defs.Airliner.apps.hasOwnProperty(app) == false) {
                var errorText = 'App \'' + app + '\' not found';
                this.logError(errorText);
                this.hk.content.cmdRejectCount++;
                cb(errorText);
            } else {
                if(self.defs.Airliner.apps[app].operations.hasOwnProperty(opName) == false) {
                    var errorText = 'Message \'' + opName + '\' not found';
                    this.logError(errorText);
                    this.hk.content.cmdRejectCount++;
                    cb(errorText);
                } else {
                    cb(undefined, parseInt(self.defs.Airliner.apps[app].operations[opName].airliner_mid));
                    this.hk.content.cmdAcceptCount++;
                }
            }
        }
    };
    
    
    
    getOperationFromPath( path ) {
        if ( typeof path === 'string' ) {
            var splitName = path.split( '/' );
            return splitName[ 2 ];
        }
        return undefined;
    }
    
    
    
    getAppFromPath( path ) {
        if ( typeof path === 'string' ) {
            var splitName = path.split( '/' );
            return splitName[ 1 ];
        }
        return undefined;
    }
    
    
    
    initTelemetry() {
        this.hk = {
            opsPath: '/' + this.config.name + '/hk',
            content: {
                cmdAcceptCount: 0,
                cmdRejectCount: 0,
                queryConfigStreamID: this.config.get( 'queryConfigStreamID' )
            }
        };
        this.addTelemetry(this.hk, 1000);
    }
    
    
    
    initClientInterface() {
        var content = {};
        
        content[this.config.name] = {
            shortDescription: 'Config Database (' + this.config.name + ')',
            longDescription: 'Config Database (' + this.config.name + ')',
            nodes: {
                main: {
                    type: CdrGroundPlugin.ContentType.LAYOUT,
                    shortDescription: 'Main',
                    longDescription: 'Main BAT.',
                    filePath: '/main_layout.lyt',
                    handlebarsContext: {
                        pluginName: this.config.name
                    }
                },
                hk: {
                    type: CdrGroundPlugin.ContentType.PANEL,
                    shortDescription: 'Housekeeping',
                    longDescription: 'Housekeeping',
                    filePath: '/hk.pug',
                    handlebarsContext: {
                        pluginName: this.config.name
                    }
                }
            }
        }
        
        this.addContent(content);
    }


    
    cmdGetPerfIDs(cmd, cb) {
        var self = this;
        var perfIDs = undefined;
        
        console.log('Executing cmdGetPerfIDs');

        if(typeof cb !== 'function') {
            var errorText = 'Callback is required.';
            this.logError(errorText);
            this.hk.content.cmdRejectCount++;
            return 
        } else if(cmd.hasOwnProperty('args') == true) {
        	var errText = 'Invalid arguments.  No arguments are required for this command.';
            this.logError(errText);
            cb(errText, null);
      	} else {
            perfIDs = self.defs.Airliner.common.performance;
            cb(null, perfIDs);
      	}
    }
}


exports = module.exports = ConfigDatabase;