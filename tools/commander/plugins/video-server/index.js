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
const convict = require( 'convict' );
const path = require( 'path' );
const autoBind = require('auto-bind');
const dgram = require( 'dgram' );
const CdrGroundPlugin = require(path.join(global.CDR_INSTALL_DIR, '/commander/classes/CdrGroundPlugin')).CdrGroundPlugin;


class VideoServer extends CdrGroundPlugin {
	/**
	 * Constructor for VideoServer
	 * 
	 * @param {Object}
	 *                configObj configuration object containing mandatory and
	 *                optional parameters.  
	 *                {
	 *                    namespace: 'airliner', 
	 *                    name:      'fsw-connector', 
	 *                    workspace:  global.CDR_WORKSPACE, 
	 *                    configFile: `${global.CDR_WORKSPACE}/etc/udpstdprovider-config.json`}
	 *                }
	 *                
	 * @constructor
	 */
    constructor(configObj) {
        configObj.webRoot = path.join( __dirname, 'web');  
        super(configObj);
        
    	autoBind(this);
    	
    	var self = this;
    	this.events = [];

        /* Initialize the configuration. */
        this.initConfig(configObj.name, configObj.configFile);
        
        /* Initialize server side housekeeping telemetry that we'll publish 
         * later. */
        this.initTelemetry();

        /* Initialize client side interface. */
        this.initClientInterface();

        /* Initialize server side commands. */
        this.initCommands();
        
        /* Start video server. */
        this.initVideoServer();

        this.logInfo( 'Initialized' );
    };
    
    
    initConfig(name, configFile) {
    	var config;
    	
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
            port: {
                doc: 'UDP port.',
                format: 'int',
                default: 3001
            },
            tlmStreamID: {
                doc: 'Input JSON stream from binary decoder.',
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
        
        this.config.name = name;
    }
    
    
    initTelemetry() {
        this.hk = {
            opsPath: '/' + this.config.name + '/hk',
            content: {
                cmdAcceptCount: 0,
                cmdRejectCount: 0,
                framesReceived: 0,
                serverState: 'DISABLED',
                port: this.config.get('port')
            }
        };
        this.addTelemetry(this.hk, 1000);
    }
    
    
    
    initClientInterface() {
        var content = {};
        
        content[this.config.name] = {
            shortDescription: 'Video Server (' + this.config.name + ')',
            longDescription: 'Video Server (' + this.config.name + ')',
            nodes: {
                main: {
                    type: CdrGroundPlugin.ContentType.LAYOUT,
                    shortDescription: 'Main',
                    longDescription: 'Main.',
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
                },
                viewer: {
                    type: CdrGroundPlugin.ContentType.PANEL,
                    shortDescription: 'Video Viewer',
                    longDescription: 'Video Viewer',
                    filePath: '/video_viewer.pug',
                    handlebarsContext: {
                        pluginName: this.config.name
                    }
                }
            }
        }
        
        this.addContent(content);
    }
    
    
    initCommands() {
//        var cmdSetInput = {
//            opsPath: '/' + this.config.name + '/setInput',
//            args: [
//                {
//                    name:    'Port',
//                    type:    'uint16',
//                    bitSize: 16
//                }
//            ]
//        }
//        this.addCommand(cmdSetInput, this.setInput);
    }
    
    
//    setInput(cmd) {
//        var self = this;
//        
//    	if(cmd.hasOwnProperty('args') == false) {
//            this.logError('Invalid arguments.  Port is required.');
//    	} else {
//            var port = parseInt(cmd.args.Port);
//            if(isNaN(port)) {
//                this.hk.content.cmdRejectCount++;
//                this.logError('Invalid data type for port.  Must be a number.');
//            } else if(port < 1024 || port > 65535) {
//        	    this.hk.content.cmdRejectCount++;
//        	    this.logError('Invalid port.  Must be between 1024 and 65535.');
//            } else {
//        	    this.logInfo('Commanded to bind to port ' + port);
//        	    this.listener.close(function () {
//        	        self.hk.content.inPort = port;
//                    if(self.startListener()) {
//                        self.hk.content.cmdAcceptCount++;
//                    } else {
//                        self.hk.content.cmdRejectCount++;
//                    }
//                });
//            }
//    	}
//    };
    
    
    
    initVideoServer() {
        var self = this;
        this.socket = dgram.createSocket( 'udp4' );

        this.hk.content.serverState = 'LISTENING';
        
        this.socket.on( 'error', ( err ) => {
            self.logError(`server error:\n${err.stack}` );
            self.hk.content.serverState = 'FAILED';
            self.socket.close();
        } );

        this.socket.on( 'message', ( frame, info ) => {
            self.hk.content.framesReceived++;
            var imageObject = {
                image: true,
                buffer: frame.toString( 'base64' )
            }
            self.namespace.send( 'video-stream', imageObject );

            //socket.volatile.emit( 'stream', {
            //  image: true,
            //  buffer: msg.toString( 'base64' )
            //} );
        } );

        this.socket.bind( this.hk.content.port );

        global.NODE_APP.videoServer = this.socket;

        this.namespace.send( 'advertise-stream', 'video-stream' );
    }
}



exports = module.exports = VideoServer;
