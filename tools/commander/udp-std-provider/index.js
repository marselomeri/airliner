/*******************************************************************************
 * 
 * Copyright (c) 2018 Windhover Labs, L.L.C. All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer. 2. Redistributions in
 * binary form must reproduce the above copyright notice, this list of
 * conditions and the following disclaimer in the documentation and/or other
 * materials provided with the distribution. 3. Neither the name Windhover Labs
 * nor the names of its contributors may be used to endorse or promote products
 * derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 * 
 ******************************************************************************/

'use strict';

const net = require( 'net' );
var events = require( 'events' );
const Emitter = require( 'events' ).EventEmitter;
var convict = require( 'convict' );
const dgram = require( 'dgram' );
var convict = require( 'convict' );
var path = require( 'path' );

const CdrGroundPlugin = require(path.join(global.CDR_INSTALL_DIR, '/commander/classes/CdrGroundPlugin')).CdrGroundPlugin;

/**
 * Event id's
 * 
 * @type {Object}
 */
var EventEnum = Object.freeze( {
    'INITIALIZED': 1,
    'UDP_ERROR': 2,
    'UDP_CONNECTOR_LISTENING': 3
} );

var emit = Emitter.prototype.emit;

exports.events = [];

/**
 * Count listeners
 * 
 * @type {Function}
 */
var listenerCount = Emitter.listenerCount ||
function( emitter, type ) {
    return emitter.listeners( type ).length
}

/**
 * Constructor for UdpStdProvider
 * 
 * @param {String}
 *                configFile path to UdpStdProvider-config.json
 * @constructor
 */
class UdpStdProvider extends CdrGroundPlugin {
    constructor(configObj) {
        // urlBase
        configObj.webRoot = path.join( __dirname, 'web');  
        super(configObj);

        this.sender = dgram.createSocket( 'udp4' );
        var self = this;

        /**
         * Define varibale server schema
         * 
         * @type {Object}
         */
        this.config = convict( {
            env: {
                doc: 'The application environment.',
                format: [ 'production', 'development', 'test' ],
            default: 'development',
            env: 'NODE_ENV'
            },
            inPort: {
                doc: 'Input port.',
                format: 'int',
            default: 0
            },
            outPort: {
                doc: 'Output port.',
                format: 'int',
            default: 0
            },
            outAddress: {
                doc: 'Output IP address.',
                format: 'ipaddress',
            default: '127.0.0.1'
            },
            outputStreamID: {
                doc: 'Output binary stream from binary data provider to the encoder/decoder.',
                format: String,
            default: ''
            },
            inputStreamID: {
                doc: 'Input binary stream from encoder/decoder to binary data provider.',
                format: String,
            default: ''
            }
        } );

        /* Load environment dependent configuration */
        this.config.loadFile( configObj.configFile );

        /* Perform validation */
        this.config.validate( {
            allowed: 'strict'
        } );
        
        this.hk = {
            opsPath: '/' + configObj.name + '/hk',
            content: {
                cmdAcceptCount: 0,
                cmdRejectCount: 0,
                inPort: this.config.get( 'inPort' ),
                outPort: this.config.get( 'outPort' ),
                outAddress: this.config.get( 'outAddress' ),
                msgSentCount: 0,
                msgRecvCount: 0,
                inputStreamID: this.config.get( 'inputStreamID' ),
                outputStreamID: this.config.get( 'outputStreamID' )
            }
        };
        
        this.startListener();
        
        var content = {};
        content[configObj.name] = {
            shortDescription: 'Standard UDP Provider (' + configObj.name + ')',
            longDescription: 'Standard UDP Provider (' + configObj.name + ')',
            nodes: {
                main: {
                    type: CdrGroundPlugin.ContentType.LAYOUT,
                    shortDescription: 'Main',
                    longDescription: 'Main BAT.',
                    filePath: '/main_layout.lyt'
                },
                hk: {
                    type: CdrGroundPlugin.ContentType.PANEL,
                    shortDescription: 'Housekeeping',
                    longDescription: 'Housekeeping',
                    filePath: '/hk.pug'
                }
            }
        }

        this.addContent(content);
        
        var cmdSetInput = [
            {
                opsPath: '/' + configObj.name + '/setInput',
                args: [
                    {
                        name:    'Port',
                        type:    'uint16',
                        bitSize: 16
                    }
                ]
            }
        ];
        this.addCommands(cmdSetInput, function(cmd) {
            var port = parseInt(cmd.args.Port);
            if(isNaN(port)) {
                self.hk.content.cmdRejectCount++;
                self.logError('Invalid data type for port.  Must be a number.');
            } else if(port < 1024 || port > 65535) {
                self.hk.content.cmdRejectCount++;
                self.logError('Invalid port.  Must be between 1024 and 65535.');
            } else {
                self.logInfo('Commanded to bind to port ' + port);
                self.listener.close(function () {
                    self.hk.content.inPort = port;
                    if(self.startListener()) {
                        self.hk.content.cmdAcceptCount++;
                    } else {
                        self.hk.content.cmdRejectCount++;
                    }
                });
            }
        });
        
        var cmdSetOutput = [
            {
                opsPath: '/' + configObj.name + '/setOutput',
                args: [
                    {
                        name:    'Port',
                        type:    'uint16',
                        bitSize: 16
                    },{
                        name:    'Address',
                        type:    'char',
                        bitSize: 1024
                    }
                ]
            }
        ];
        this.addCommands(cmdSetOutput, function(cmd) {
            var port = parseInt(cmd.args.Port);
            if(isNaN(port)) {
                self.hk.content.cmdRejectCount++;
                self.logError('Invalid data type for port.  Must be a number.');
            } else if(port < 1024 || port > 65535) {
                self.hk.content.cmdRejectCount++;
                self.logError('Invalid port.  Must be between 1024 and 65535.');
            } else {
                self.logInfo('Commanded to set output to \'' + cmd.args.Address + ':' + port + '\'');
                self.hk.content.outPort = port;
                self.hk.content.outAddress = cmd.args.Address;
                self.hk.content.cmdAcceptCount++;
            }
        });

        this.addTelemetry([this.hk]);

        this.namespace.emitter.on( this.config.get( 'inputStreamID' ), function( buffer ) {
            self.hk.content.msgSentCount++;
            self.sender.send( buffer, 0, buffer.length, self.hk.content.outPort, self.hk.content.outAddress);
        } );

        this.logInfo( 'Initialized' );
    };
    
    startListener() {
        try {
            var self = this;
            
            this.listener = dgram.createSocket( {type: 'udp4', reuseAddr: true} );
    
            this.listener.on( 'listening', () => {
                const listenerAddress = self.listener.address();
                self.logInfo(`UDP connector listening ${listenerAddress.address}:${listenerAddress.port}` );
            } );
            
            this.listener.bind( this.hk.content.inPort, () => {            
                self.listener.on( 'message', ( msg, rinfo ) => {
                    self.hk.content.msgRecvCount++;
                    self.namespace.emit( self.hk.content.outputStreamID, msg );
                } );
    
                self.listener.on( 'error', ( err ) => {
                    self.logError( `UDP connector error:\n${err}.` );
                } );
            });   
            
            return true;
        } catch(err) {
            this.logError('Failed to bind.  ' + err);
            return false;
        }
    }
}



exports = module.exports = UdpStdProvider;