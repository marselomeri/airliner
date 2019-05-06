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

const events = require( 'events' );
const emitter = require( 'events' ).EventEmitter;
const path = require( 'path' );
const convict = require( global.CDR_INSTALL_DIR + '/node_modules/convict' );
const CdrGroundPlugin = require(path.join(global.CDR_INSTALL_DIR, '/commander/classes/CdrGroundPlugin')).CdrGroundPlugin;


class PanelDisplay extends CdrGroundPlugin {
    constructor(configObj) {
        configObj.webRoot = path.join( __dirname, 'web');  
        super(configObj);
        
    	var self = this;

        /* Initialize the configuration. */
        this.initConfig(configObj.name, configObj.configFile);
        
        /* Initialize server side housekeeping telemetry that we'll publish 
         * later. */
        this.initTelemetry();

        /* Initialize client side interface. */
        this.initClientInterface();

        /* Initialize server side commands. */
        this.initCommands();
        
        /* Start listening for data to send out the socket. */
        this.namespace.emitter.on( this.config.get( 'inputStreamID' ), function( buffer ) {
            self.hk.content.msgSentCount++;
            self.sender.send( buffer, 0, buffer.length, self.hk.content.outPort, self.hk.content.outAddress);
        } );

        this.logInfo( 'Initialized' );
    };
    
    startListener() {
        try {
            var self = this;
                       
            return true;
        } catch(err) {
            this.logError('Failed to bind.  ' + err);
            return false;
        }
    }
    
    
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
                inPort: this.config.get( 'inPort' ),
                outPort: this.config.get( 'outPort' ),
                outAddress: this.config.get( 'outAddress' ),
                msgSentCount: 0,
                msgRecvCount: 0,
                inputStreamID: this.config.get( 'inputStreamID' ),
                outputStreamID: this.config.get( 'outputStreamID' )
            }
        };
        this.addTelemetry(this.hk, 1000);
    }
    
    
    
    initClientInterface() {
        var content = {};
        
        content[this.config.name] = {
            shortDescription: 'Panel Display',
            longDescription: 'Panel Display',
            nodes: {
                main: {
                    type: CdrGroundPlugin.ContentType.LAYOUT,
                    shortDescription: 'Main',
                    longDescription: 'Main Layout.',
                    filePath: '/main.lyt',
                    handlebarsContext: {
                        pluginName: this.config.name
                    }
                },
                f1: {
                    type: CdrGroundPlugin.ContentType.PANEL,
                    shortDescription: 'F1 Panel',
                    longDescription: 'F1 Panel',
                    filePath: '/f1.pug',
                    handlebarsContext: {
                        pluginName: this.config.name
                    }
                },
                f2: {
                    type: CdrGroundPlugin.ContentType.PANEL,
                    shortDescription: 'F2 Panel',
                    longDescription: 'F2 Panel',
                    filePath: '/f2.pug',
                    handlebarsContext: {
                        pluginName: this.config.name
                    }
                },
                f3: {
                    type: CdrGroundPlugin.ContentType.PANEL,
                    shortDescription: 'F3 Panel',
                    longDescription: 'F3 Panel',
                    filePath: '/f3.pug',
                    handlebarsContext: {
                        pluginName: this.config.name
                    }
                },
                f4: {
                    type: CdrGroundPlugin.ContentType.PANEL,
                    shortDescription: 'F4 Panel',
                    longDescription: 'F4 Panel',
                    filePath: '/f4.pug',
                    handlebarsContext: {
                        pluginName: this.config.name
                    }
                },
                f5: {
                    type: CdrGroundPlugin.ContentType.PANEL,
                    shortDescription: 'F5 Panel',
                    longDescription: 'F5 Panel',
                    filePath: '/f1.pug',
                    handlebarsContext: {
                        pluginName: this.config.name
                    }
                },
                f6: {
                    type: CdrGroundPlugin.ContentType.PANEL,
                    shortDescription: 'F6 Panel',
                    longDescription: 'F6 Panel',
                    filePath: '/f6.pug',
                    handlebarsContext: {
                        pluginName: this.config.name
                    }
                },
                f7: {
                    type: CdrGroundPlugin.ContentType.PANEL,
                    shortDescription: 'F7 Panel',
                    longDescription: 'F7 Panel',
                    filePath: '/f7.pug',
                    handlebarsContext: {
                        pluginName: this.config.name
                    }
                }
            }
        }
        
        this.addContent(content);
    }
    
    
    initCommands() {
        var cmdSetInput = {
            opsPath: '/' + this.config.name + '/setInput',
            args: [
                {
                    name:    'Port',
                    type:    'uint16',
                    bitSize: 16
                }
            ]
        }
        this.addCommand(cmdSetInput, this.setInput);

        var cmdSetOutput = {
            opsPath: '/' + this.config.name + '/setOutput',
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
        };
        this.addCommand(cmdSetOutput, this.setOutput);
    }
    
    
    setInput(cmd) {
    	if(cmd.hasOwnProperty('args') == false) {
            this.logError('Invalid arguments.  Port is required.');
    	} else {
            var port = parseInt(cmd.args.Port);
            if(isNaN(port)) {
                this.hk.content.cmdRejectCount++;
                this.logError('Invalid data type for port.  Must be a number.');
            } else if(port < 1024 || port > 65535) {
        	    this.hk.content.cmdRejectCount++;
        	    this.logError('Invalid port.  Must be between 1024 and 65535.');
            } else {
        	    this.logInfo('Commanded to bind to port ' + port);
        	    this.listener.close(function () {
        		    this.hk.content.inPort = port;
                    if(this.startListener()) {
                	    this.hk.content.cmdAcceptCount++;
                    } else {
                	    this.hk.content.cmdRejectCount++;
                    }
                });
            }
    	}
    };
    
    
    setOutput(cmd) {
    	if(cmd.hasOwnProperty('args') == false) {
            this.logError('Invalid arguments.  Port is required.');
    	} else {
            var port = parseInt(cmd.args.Port);
            if(isNaN(port)) {
                this.hk.content.cmdRejectCount++;
                this.logError('Invalid data type for port.  Must be a number.');
            } else if(port < 1024 || port > 65535) {
                this.hk.content.cmdRejectCount++;
                this.logError('Invalid port.  Must be between 1024 and 65535.');
            } else {
                this.logInfo('Commanded to set output to \'' + cmd.args.Address + ':' + port + '\'');
                this.hk.content.outPort = port;
                this.hk.content.outAddress = cmd.args.Address;
                this.hk.content.cmdAcceptCount++;
            }
    	}
    }
}



exports = module.exports = PanelDisplay;