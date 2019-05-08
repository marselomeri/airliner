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
const SerialPort = require( global.CDR_INSTALL_DIR + '/node_modules/serialport');
var Enum = require( global.CDR_INSTALL_DIR + '/node_modules/enum');

var ParserState = new Enum({
	'WAITING_FOR_HEADER':        1, 
	'WAITING_FOR_RESPONSE_TYPE': 2, 
	'WAITING_FOR_ID1':           3, 
	'WAITING_FOR_ID2':           4, 
	'WAITING_FOR_STATE1':        5, 
	'WAITING_FOR_STATE2':        6, 
	'WAITING_FOR_STATE3':        7, 
	'WAITING_FOR_STATE4':        8, 
	'WAITING_FOR_CHECKSUM1':     9, 
	'WAITING_FOR_CHECKSUM2':    10, 
	'WAITING_FOR_CHECKSUM3':    11, 
	'WAITING_FOR_CHECKSUM4':    12, 
	'WAITING_FOR_FOOTER':       13, 
	'WAITING_FOR_FINAL_FOOTER': 14
});


class PanelDisplay extends CdrGroundPlugin {
    constructor(configObj) {
        configObj.webRoot = path.join( __dirname, 'web');  
        super(configObj);
        
    	var self = this;
    	
    	this.startTime = 0;
    	this.stopTime = 0;

        /* Initialize the configuration. */
        this.initConfig(configObj.name, configObj.configFile);
        
        /* Initialize server side housekeeping telemetry that we'll publish 
         * later. */
        this.initTelemetry();

        /* Initialize client side interface. */
        this.initClientInterface();

        /* Initialize server side commands. */
        this.initCommands();
        
        /* Open serial port */
        this.serialPort = new SerialPort('/dev/ttyACM0', {
            baudRate: 115200
        });
        
        this.currentParserState = ParserState.WAITING_FOR_HEADER.value;
        
        var group = 0;
        
        setInterval(function() {
            var commandCode = 1;
            var checksum = commandCode + group;
            var command = '<' + commandCode;
            if(group < 10) {
                command += '000' + group;
            } else if(group < 100) {
            	command += '00' + group;
            } else if(group < 1000) {
            	command += '0' + group;
            } else {
            	command += group;
            }
                	
            if(checksum < 10) {
            	command += '000' + checksum;
            } else if(checksum < 100){
            	command += '00' + checksum;
            } else if(checksum < 1000){
                command += '0' + checksum;
            } else {
                command += checksum;
            }
                	
            command += '>';
                	
            self.serialPort.write(command);
            self.hk.content.card1MsgSentCount++;
            
            group++;
            
            if(group >= 40) {
            	group = 0;
            }
        }, 25);

        this.serialPort.on('data', function (data) {
        	var id = 0;
        	var responseType = 0;
        	var state = 0;
        	var checksum = 0;
            
        	for(var i = 0; i < data.length; ++i) {
        		var byteRead = data[i];
        		var charRead = String.fromCharCode(byteRead);
        		
                switch(self.currentParserState)
                {
                    case ParserState.WAITING_FOR_HEADER.value: {
                        if(charRead == '<') {
                            self.currentParserState = ParserState.WAITING_FOR_RESPONSE_TYPE.value;
                        }
                        break;
        	        }

                    case ParserState.WAITING_FOR_RESPONSE_TYPE.value:
                    {
                        if(charRead == '0' || charRead == '1' || charRead == '2' )
                        {
                        	self.currentParserState = ParserState.WAITING_FOR_ID1.value;
                            responseType = byteRead - 48;
                        }
                        else
                        {
                        	self.logError('Unknown response type.');
                        	self.currentParserState = ParserState.WAITING_FOR_HEADER.value;
                        }
                        break;
                    }

                    case ParserState.WAITING_FOR_ID1.value:
                    {
                        if(charRead == '0' || charRead == '1' || charRead == '2'
                          || charRead == '3' || charRead == '4' || charRead == '5'
                          || charRead == '6' || charRead == '7' || charRead == '8'
                          || charRead == '9')
                        {
                        	self.currentParserState = ParserState.WAITING_FOR_ID2.value;
                            id = (byteRead - 48) * 10;
                        }
                        else
                        {
                        	self.logError('Unknown ID1.');
                        	self.currentParserState = ParserState.WAITING_FOR_HEADER.value;
                        }
                        break;
                    }

                    case ParserState.WAITING_FOR_ID2.value:
                    {
                        if(charRead == '0' || charRead == '1' || charRead == '2'
                          || charRead == '3' || charRead == '4' || charRead == '5'
                          || charRead == '6' || charRead == '7' || charRead == '8'
                          || charRead == '9')
                        {
                        	self.currentParserState = ParserState.WAITING_FOR_STATE1.value;
                            id += (byteRead - 48);
                        }
                        else
                        {
                        	self.logError('Unknown ID2.');
                        	self.currentParserState = ParserState.WAITING_FOR_HEADER.value;
                        }
                        break;
                    }

                    case ParserState.WAITING_FOR_STATE1.value:
                    {
                        if(charRead == '0' || charRead == '1' || charRead == '2'
                          || charRead == '3' || charRead == '4' || charRead == '5'
                          || charRead == '6' || charRead == '7' || charRead == '8'
                          || charRead == '9')
                        {
                        	self.currentParserState = ParserState.WAITING_FOR_STATE2.value;
                            state = (byteRead - 48) * 1000;
                        }
                        else
                        {
                        	self.logError('Unknown STATE1.');
                        	self.currentParserState = ParserState.WAITING_FOR_HEADER.value;
                        }
                        break;
                    }

                    case ParserState.WAITING_FOR_STATE2.value:
                    {
                        if(charRead == '0' || charRead == '1' || charRead == '2'
                          || charRead == '3' || charRead == '4' || charRead == '5'
                          || charRead == '6' || charRead == '7' || charRead == '8'
                          || charRead == '9')
                        {
                        	self.currentParserState = ParserState.WAITING_FOR_STATE3.value;
                            state += (byteRead - 48) * 100;
                        }
                        else
                        {
                        	self.logError('Unknown STATE2.');
                        	self.currentParserState = ParserState.WAITING_FOR_HEADER.value;
                        }
                        break;
                    }

                    case ParserState.WAITING_FOR_STATE3.value:
                    {
                        if(charRead == '0' || charRead == '1' || charRead == '2'
                          || charRead == '3' || charRead == '4' || charRead == '5'
                          || charRead == '6' || byteRead == '7' || charRead == '8'
                          || charRead == '9')
                        {
                        	self.currentParserState = ParserState.WAITING_FOR_STATE4.value;
                            state += (byteRead - 48) * 10;
                        }
                        else
                        {
                        	self.logError('Unknown STATE3.');
                        	self.currentParserState = ParserState.WAITING_FOR_HEADER.value;
                        }
                        break;
                    }

                    case ParserState.WAITING_FOR_STATE4.value:
                    {
                        if(charRead == '0' || charRead == '1' || charRead == '2'
                          || charRead == '3' || charRead == '4' || charRead == '5'
                          || charRead == '6' || charRead == '7' || charRead == '8'
                          || charRead == '9')
                        {
                        	self.currentParserState = ParserState.WAITING_FOR_CHECKSUM1.value;
                            state += (byteRead - 48);
                        }
                        else
                        {
                        	self.logError('Unknown STATE4.');
                        	self.currentParserState = ParserState.WAITING_FOR_HEADER.value;
                        }
                        break;
                    }


                    case ParserState.WAITING_FOR_CHECKSUM1.value:
                    {
                        if(charRead == '0' || charRead == '1' || charRead == '2'
                          || charRead == '3' || charRead == '4' || charRead == '5'
                          || charRead == '6' || charRead == '7' || charRead == '8'
                          || charRead == '9')
                        {
                        	self.currentParserState = ParserState.WAITING_FOR_CHECKSUM2.value;
                            checksum = 1000 * (byteRead - 48); 
                        }
                        else
                        {
                        	self.logError('Unknown CHECKSUM1.');
                        	self.currentParserState = ParserState.WAITING_FOR_HEADER.value;
                        }
                        break;
                    }
                    
                    case ParserState.WAITING_FOR_CHECKSUM2.value:
                    {
                        if(charRead == '0' || charRead == '1' || charRead == '2'
                          || charRead == '3' || charRead == '4' || charRead == '5'
                          || charRead == '6' || charRead == '7' || charRead == '8'
                          || charRead == '9')
                        {
                        	self.currentParserState = ParserState.WAITING_FOR_CHECKSUM3.value;
                            checksum += (100 * (byteRead - 48)); 
                        }
                        else
                        {
                        	self.logError('Unknown CHECKSUM2.');
                        	self.currentParserState = ParserState.WAITING_FOR_HEADER.value;
                        }
                        break;
                    }

                    case ParserState.WAITING_FOR_CHECKSUM3.value:
                    {
                        if(charRead == '0' || charRead == '1' || charRead == '2'
                          || charRead == '3' || charRead == '4' || charRead == '5'
                          || charRead == '6' || charRead == '7' || charRead == '8'
                          || charRead == '9')
                        {
                        	self.currentParserState = ParserState.WAITING_FOR_CHECKSUM4.value;
                            checksum += (10 * (byteRead - 48)); 
                        }
                        else
                        {
                        	self.logError('Unknown CHECKSUM3.');
                            currentParserState = ParserState.WAITING_FOR_HEADER.value;
                        }
                        break;
                    }
                
                    case ParserState.WAITING_FOR_CHECKSUM4.value:
                    {
                        if(charRead == '0' || charRead == '1' || charRead == '2'
                          || charRead == '3' || charRead == '4' || charRead == '5'
                          || charRead == '6' || charRead == '7' || charRead == '8'
                          || charRead == '9')
                        {
                        	self.currentParserState = ParserState.WAITING_FOR_FOOTER.value;
                            checksum += (byteRead - 48); 
                        }
                        else
                        {
                            self.logError('Unknown CHECKSUM4.');
                            self.currentParserState = ParserState.WAITING_FOR_HEADER.value;
                        }
                        break;
                    }

                    case ParserState.WAITING_FOR_FOOTER.value:
                    {
                        if(charRead == '>')
                        { 
                            var calculatedChecksum = responseType + id + state;
                            if(calculatedChecksum == checksum) {
                                //std::cout << "SwitchType: " << responseType << "   ID: " << id << "   State: " << state << std::endl;
                                //self.logError('Received message');
                            	if(responseType == 2) {
                                	self.hk.content.card1MsgRecvCount++;
                            	} else {
                            		if(responseType == 0) {
                            			self.swStatus.content.digital[id] = state;
                            		} else if(responseType == 1 ) {
                            			self.swStatus.content.analog[id] = state;
                            		};
                            	}
                            }
                            else
                            {
                                self.logError('Invalid checksum.  ResponseType: ' + responseType + '  ID: ' + id + '  State: ' + state + '  Expected Checksum: ' + checksum + '  Calculated Checksum: ' + calculatedChecksum);
                            }
                        }
                        else
                        {
                            self.logError('Unknown footer');
                        }
                        self.currentParserState = ParserState.WAITING_FOR_HEADER.value;
                        break;
                    }

                    default:
                    {
                        self.logError('Parser in unknown state. ' + self.currentParserState);
                        self.currentParserState = ParserState.WAITING_FOR_HEADER.value;
                        break;
                    }                    
                }
        	}
        });
        
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
                card1DevicePath: '',
                card2DevicePath: '',
                card3DevicePath: '',
                card1MsgRecvCount: 0,
                card2MsgRecvCount: 0,
                card3MsgSentCount: 0,
                card1MsgSentCount: 0,
                card2MsgSentCount: 0,
                card3MsgSentCount: 0
            }
        };
        this.addTelemetry(this.hk, 1000);

        this.swStatus = {
            opsPath: '/' + this.config.name + '/swStatus',
            content: {
                digital: [
                	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                ],
                analog: [0, 0, 0, 0, 0, 0, 0]
            }
        };
        this.addTelemetry(this.swStatus, 10);
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
                hk: {
                    type: CdrGroundPlugin.ContentType.PANEL,
                    shortDescription: 'HK',
                    longDescription: 'Housekeeping',
                    filePath: '/hk.pug',
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
                    filePath: '/f5.pug',
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
    	var self = this;
    	
        var cmdReset = {
            opsPath: '/' + this.config.name + '/Reset',
            args: []
        }
        this.addCommand(cmdReset, function () {
        	self.hk.content.cmdAcceptCount    = 0;
        	self.hk.content.cmdRejectCount    = 0;
        	self.hk.content.card1MsgRecvCount = 0,
        	self.hk.content.card2MsgRecvCount = 0,
        	self.hk.content.card3MsgRecvCount = 0,
        	self.hk.content.card1MsgSentCount = 0,
        	self.hk.content.card2MsgSentCount = 0,
        	self.hk.content.card3MsgSentCount = 0
        });

        var cmdReadSwitch = {
            opsPath: '/' + this.config.name + '/ReadSwitch',
            args: [
                {
                    name:    'Card',
                    type:    'uint8',
                    bitSize: 8
                },{
                    name:    'Group',
                    type:    'uint8',
                    bitSize: 8
                }
            ]
        };
        this.addCommand(cmdReadSwitch, function(cmd) {
        	if(cmd.hasOwnProperty('args') == false) {
                self.logError('Invalid arguments.  MinorCard, MajorCard, and Pin required.');
        	} else {
                var card = parseInt(cmd.args.Card);
                var group = parseInt(cmd.args.Group);
                if(isNaN(card)) {
                	self.hk.content.cmdRejectCount++;
                	self.logError('Invalid data type for Card.  Must be a number.');
                } else if(isNaN(group)) {
                	self.hk.content.cmdRejectCount++;
                	self.logError('Invalid data type for Group.  Must be a number.');
                } else if(card < 0 || card > 2) {
                	self.hk.content.cmdRejectCount++;
                	self.logError('Invalid card.  Must be between 0 and 2.');
                } else if(group < 0 || group > 63) {
                	self.hk.content.cmdRejectCount++;
                	self.logError('Invalid Group.  Must be between 0 and 39.');
                } else {
                	self.logInfo('Querying switch ' + card + ':' + group);
                	
                	var commandCode = 1;
                	var checksum = commandCode + group;
                	var command = '<' + commandCode;
                	if(group < 10) {
                		command += '000' + group;
                	} else if(group < 100) {
                		command += '00' + group;
                	} else if(group < 1000) {
                		command += '0' + group;
                	} else {
                		command += group;
                	}
                	
                	if(checksum < 10) {
                		command += '000' + checksum;
                	} else if(checksum < 100){
                		command += '00' + checksum;
            	    } else if(checksum < 1000){
            		    command += '0' + checksum;
            	    } else {
            		    command += checksum;
            	    }
                	
                	command += '>';
                	
                	self.serialPort.write(command);
                	self.hk.content.cmdAcceptCount++;
                	self.hk.content.card1MsgSentCount++;
                	
//            	    this.listener.close(function () {
//            		    this.hk.content.inPort = port;
//                        if(this.startListener()) {
//                    	    this.hk.content.cmdAcceptCount++;
//                        } else {
//                    	    this.hk.content.cmdRejectCount++;
//                        }
//                    });
                }
        	}
        });

        var cmdSetLED = {
            opsPath: '/' + this.config.name + '/SetLED',
            args: [
                {
                    name:    'MajorCard',
                    type:    'uint8',
                    bitSize: 8
                },{
                    name:    'MinorCard',
                    type:    'uint8',
                    bitSize: 8
                },{
                    name:    'Pin',
                    type:    'uint8',
                    bitSize: 8
                },{
                    name:    'State',
                    type:    'uint8',
                    bitSize: 8
                }
            ]
        };
        this.addCommand(cmdSetLED, this.setLED);
    }
    
    
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