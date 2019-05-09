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
        'RESYNCING_TO_HEADER':       1, 
	'WAITING_FOR_HEADER':        2, 
	'WAITING_FOR_RESPONSE_TYPE': 3, 
	'WAITING_FOR_ID1':           4, 
	'WAITING_FOR_ID2':           5, 
	'WAITING_FOR_STATE1':        6, 
	'WAITING_FOR_STATE2':        7, 
	'WAITING_FOR_STATE3':        8, 
	'WAITING_FOR_STATE4':        9, 
	'WAITING_FOR_CHECKSUM1':    10, 
	'WAITING_FOR_CHECKSUM2':    11, 
	'WAITING_FOR_CHECKSUM3':    12, 
	'WAITING_FOR_CHECKSUM4':    13, 
	'WAITING_FOR_FOOTER':       14, 
	'WAITING_FOR_FINAL_FOOTER': 15
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
        
        /* Open serial ports */
        this.serial1Port = new SerialPort('/dev/ttyACM0', {
            baudRate: 115200
        });
        this.serial2Port = new SerialPort('/dev/ttyACM1', {
            baudRate: 115200
        });
        this.serial3Port = new SerialPort('/dev/ttyACM2', {
            baudRate: 115200
        });
        
        this.currentParserState = [];
        
        this.currentParserState[0] = ParserState.WAITING_FOR_HEADER.value;
        this.currentParserState[1] = ParserState.WAITING_FOR_HEADER.value;
        
        var group = 0;
        
        this.responseType = [];
        this.id = [];
        this.state = [];
        this.checksum = [];
        
        setInterval(function() {
            var commandCode = 1;
            var checksum = commandCode + group;
            var command = '<' + commandCode + '0';
            if(group < 10) {
                command += '00' + group;
            } else if(group < 100) {
            	command += '0' + group;
            };
            
            command += '0000';
            
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
                	
            self.serial1Port.write(command);
            self.hk.content.card1MsgSentCount++;
            
            self.serial2Port.write(command);
            self.hk.content.card2MsgSentCount++;
            
            group++;
            
            if(group >= 40) {
            	group = 0;
            }
        }, 25);
        

        this.tmpString = [];
        this.tmpString.push('');
        this.tmpString.push('');

        this.serial1Port.on('data', function (data) {
            self.processSerialPortData(0, data);
        });    

        this.serial2Port.on('data', function (data) {            
            self.processSerialPortData(1, data);
        });    
        
        
        /* Start listening for data to send out the socket. */
        this.namespace.emitter.on( this.config.get( 'inputStreamID' ), function( buffer ) {
            //self.hk.content.msgSentCount++;
            //self.sender.send( buffer, 0, buffer.length, self.hk.content.outPort, self.hk.content.outAddress);
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
    
    
    processSerialPortData (cardID, data) {    
        
        for(var i = 0; i < data.length; ++i) {
            var byteRead = data[i];
            var charRead = String.fromCharCode(byteRead);
            this.tmpString[cardID] += charRead;
                    
            switch(this.currentParserState[cardID])
            {
                case ParserState.RESYNCING_TO_HEADER.value: {
                    if(charRead == '<') {
                        this.logError('Received "' + this.tmpString[cardID] + '" while resyncing.');
                        this.tmpString[cardID] = charRead;
                        this.currentParserState[cardID] = ParserState.WAITING_FOR_RESPONSE_TYPE.value;
                    } 
                    break;
                }
                
                case ParserState.WAITING_FOR_HEADER.value: {
                    if(charRead == '<') {
                        this.currentParserState[cardID] = ParserState.WAITING_FOR_RESPONSE_TYPE.value;
                        this.tmpString[cardID] = charRead;
                    }
                    break;
                }

                case ParserState.WAITING_FOR_RESPONSE_TYPE.value:
                {
                    if(charRead == '0' || charRead == '1' || charRead == '2' || charRead == '4')
                    {
                        this.currentParserState[cardID] = ParserState.WAITING_FOR_ID1.value;
                        this.responseType[cardID] = byteRead - 48;
                    }
                    else
                    {
                        this.logError('Unknown response type.');
                        this.currentParserState[cardID] = ParserState.RESYNCING_TO_HEADER.value;
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
                        this.currentParserState[cardID] = ParserState.WAITING_FOR_ID2.value;
                        this.id[cardID] = (byteRead - 48) * 10;
                    }
                    else
                    {
                        this.logError('Unknown ID1.');
                        this.currentParserState[cardID] = ParserState.RESYNCING_TO_HEADER.value;
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
                        this.currentParserState[cardID] = ParserState.WAITING_FOR_STATE1.value;
                        this.id[cardID] += (byteRead - 48);
                    }
                    else
                    {
                        this.logError('Unknown ID2.');
                        this.currentParserState[cardID] = ParserState.RESYNCING_TO_HEADER.value;
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
                        this.currentParserState[cardID] = ParserState.WAITING_FOR_STATE2.value;
                        this.state[cardID] = (byteRead - 48) * 1000;
                    }
                    else
                    {
                        this.logError('Unknown STATE1.');
                        this.currentParserState[cardID] = ParserState.RESYNCING_TO_HEADER.value;
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
                        this.currentParserState[cardID] = ParserState.WAITING_FOR_STATE3.value;
                        this.state[cardID] += (byteRead - 48) * 100;
                    }
                    else
                    {
                        this.logError('Unknown STATE2.');
                        this.currentParserState[cardID] = ParserState.RESYNCING_TO_HEADER.value;
                    }
                    break;
                }

                case ParserState.WAITING_FOR_STATE3.value:
                {
                    if(charRead == '0' || charRead == '1' || charRead == '2'
                      || charRead == '3' || charRead == '4' || charRead == '5'
                      || charRead == '6' || charRead == '7' || charRead == '8'
                      || charRead == '9')
                    {
                        this.currentParserState[cardID] = ParserState.WAITING_FOR_STATE4.value;
                        this.state[cardID] += (byteRead - 48) * 10;
                    }
                    else
                    {
                        this.logError('Unknown STATE3.');
                        this.currentParserState[cardID] = ParserState.RESYNCING_TO_HEADER.value;
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
                        this.currentParserState[cardID] = ParserState.WAITING_FOR_CHECKSUM1.value;
                        this.state[cardID] += (byteRead - 48);
                    }
                    else
                    {
                        this.logError('Unknown STATE4.');
                        this.currentParserState[cardID] = ParserState.RESYNCING_TO_HEADER.value;
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
                        this.currentParserState[cardID] = ParserState.WAITING_FOR_CHECKSUM2.value;
                        this.checksum[cardID] = 1000 * (byteRead - 48); 
                    }
                    else
                    {
                        this.logError('Unknown CHECKSUM1.');
                        this.currentParserState[cardID] = ParserState.RESYNCING_TO_HEADER.value;
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
                        this.currentParserState[cardID] = ParserState.WAITING_FOR_CHECKSUM3.value;
                        this.checksum[cardID] += (100 * (byteRead - 48)); 
                    }
                    else
                    {
                        this.logError('Unknown CHECKSUM2.');
                        this.currentParserState[cardID] = ParserState.RESYNCING_TO_HEADER.value;
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
                        this.currentParserState[cardID] = ParserState.WAITING_FOR_CHECKSUM4.value;
                        this.checksum[cardID] += (10 * (byteRead - 48)); 
                    }
                    else
                    {
                        this.logError('Unknown CHECKSUM3.');
                        this.currentParserState[cardID] = ParserState.RESYNCING_TO_HEADER.value;
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
                        this.currentParserState[cardID] = ParserState.WAITING_FOR_FOOTER.value;
                        this.checksum[cardID] += (byteRead - 48); 
                    }
                    else
                    {
                        this.logError('Unknown CHECKSUM4.');
                        this.currentParserState[cardID] = ParserState.RESYNCING_TO_HEADER.value;
                    }
                    break;
                }

                case ParserState.WAITING_FOR_FOOTER.value:
                {
                    if(charRead == '>')
                    { 
                        var calculatedChecksum = this.responseType[cardID] + this.id[cardID] + this.state[cardID];
                        if(calculatedChecksum == this.checksum[cardID]) {
                            switch(cardID) {
                                case 0:
                                    if(this.responseType[cardID] == 4) {
                                        this.hk.content.card1MsgRecvCount++;
                                    } else {
                                        if(this.responseType[cardID] == 0) {
                                            this.sw1Status.content.digital[this.id[cardID]] = this.state[cardID];
                                        } else if(this.responseType[cardID] == 1 ) {
                                            this.sw1Status.content.analog[this.id[cardID]] = this.state[cardID];
                                        }
                                    };
                                    break;
                                
                                case 1:
                                    if(this.responseType[cardID] == 4) {
                                        this.hk.content.card2MsgRecvCount++;
                                    } else {
                                        if(this.responseType[cardID] == 0) {
                                            this.sw2Status.content.digital[this.id[cardID]] = this.state[cardID];
                                        } else if(this.responseType[cardID] == 1 ) {
                                            this.sw2Status.content.analog[this.id[cardID]] = this.state[cardID];
                                        }
                                    };
                                    break;
                                    
                                default:
                                    this.logError('Invalid card ID of ', cardID);
                                    break;
                            }
                        }
                        else
                        {
                            this.logError('Invalid checksum.  ResponseType: ' + this.responseType[cardID] + '  ID: ' + this.id[cardID] + '  State: ' + this.state[cardID] + '  Expected Checksum: ' + this.checksum[cardID] + '  Calculated Checksum: ' + calculatedChecksum);
                        }
                    }
                    else
                    {
                        this.logError('Unknown footer');
                    }
                    this.currentParserState[cardID] = ParserState.WAITING_FOR_HEADER.value;
                    break;
                }

                default:
                {
                    this.logError('Parser in unknown state. ' + this.currentParserState[cardID]);
                    this.currentParserState[cardID] = ParserState.WAITING_FOR_HEADER.value;
                    break;
                }                    
            }
        }
    };
    
    
    initTelemetry() {
        this.hk = {
            opsPath: '/' + this.config.name + '/hk',
            content: {
                cmdAcceptCount:    0,
                cmdRejectCount:    0,
                card1DevicePath:  '',
                card2DevicePath:  '',
                card3DevicePath:  '',
                card1MsgRecvCount: 0,
                card2MsgRecvCount: 0,
                card3MsgSentCount: 0,
                card1MsgSentCount: 0,
                card2MsgSentCount: 0,
                card3MsgSentCount: 0
            }
        };
        this.addTelemetry(this.hk, 1000);

        this.sw1Status = {
            opsPath: '/' + this.config.name + '/sw1Status',
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
        this.addTelemetry(this.sw1Status, 10);

        this.sw2Status = {
            opsPath: '/' + this.config.name + '/sw2Status',
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
        this.addTelemetry(this.sw2Status, 10);
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
        
        var cmdSetLED = {
            opsPath: '/' + this.config.name + '/SetLED',
            args: [
                {
                    name:    'Board',
                    type:    'uint8',
                    bitSize: 8
                },{
                    name:    'Lamp',
                    type:    'uint32',
                    bitSize: 32
                },{
                    name:    'Intensity',
                    type:    'uint32',
                    bitSize: 32
                }
            ]
        }
        this.addCommand(cmdSetLED, function (cmd) {
            var checksum = 2 + cmd.args.Board + cmd.args.Lamp + cmd.args.Intensity;
            
            /* board = arg1, lamp = arg2, intensity = arg3 */
            var command = '<2' + cmd.args.Board;

            if(cmd.args.Lamp < 10) {
                command += '00' + cmd.args.Lamp;
            } else if(cmd.args.Lamp < 100) {
                command += '0' + cmd.args.Lamp;
            } else {
                command += cmd.args.Lamp;
            }
            
            if(cmd.args.Intensity < 10) {
                command += '000' + cmd.args.Intensity;
            } else if(cmd.args.Intensity < 100) {
                command += '00' + cmd.args.Intensity;
            } else if(cmd.args.Intensity < 1000) {
                command += '0' + cmd.args.Intensity;
            } else {
                command += cmd.args.Intensity;
            }
            
            if(checksum < 10) {
                command += '000' + checksum;
            } else if(checksum < 100) {
                command += '00' + checksum;
            } else if(checksum < 1000) {
                command += '0' + checksum;
            } else {
                command += checksum;
            }
            
            command += '>';
            
            console.log(command);

            self.serial3Port.write(command);
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
    
    
    setLED(board, lamp, intensity) {
        var checksum = 2 + board + lamp + intensity;
        
        /* board = arg1, lamp = arg2, intensity = arg3 */
        var command = '<2' + board;

        if(lamp < 10) {
            command += '00' + lamp;
        } else if(lamp < 100) {
            command += '0' + lamp;
        } else {
            command += lamp;
        }
        
        if(intensity < 10) {
            command += '000' + intensity;
        } else if(intensity < 100) {
            command += '00' + intensity;
        } else if(intensity < 1000) {
            command += '0' + intensity;
        } else {
            command += intensity;
        }
        
        if(checksum < 10) {
            command += '000' + checksum;
        } else if(checksum < 100) {
            command += '00' + checksum;
        } else if(checksum < 1000) {
            command += '0' + checksum;
        } else {
            command += checksum;
        }
        
        command += '>';
        
        console.log(command);

        this.serial3Port.write(command);
    }
    
    cmdAllLEDs(intensity) {
        var board = 3;
        var lamp = 2;
        //for(var board = 0; board < 4; board++) {
        //    for(var lamp = 0; lamp < 8; lamp++) {
                this.setLED(board, lamp, intensity);
        //    }
        //}
    }
}



exports = module.exports = PanelDisplay;