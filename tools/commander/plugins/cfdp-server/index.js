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

const Parser = require( 'binary-parser' ).Parser;
var fs = require( 'fs' );
var convict = require( 'convict' );
var path = require( 'path' );
const autoBind = require('auto-bind');
//var CfdpLib = require( './build/Release/cfdp' );
var config = require( './config.js' );
const CdrGroundPlugin = require(path.join(global.CDR_INSTALL_DIR, '/commander/classes/CdrGroundPlugin')).CdrGroundPlugin;
const XState = require('xstate');



const PDUTypeEnum = Object.freeze({
    'FileDirective'  :  0, 
    'FileData'       :  1});

const DirectionEnum = Object.freeze({
    'ToFileReceiver' :  0, 
    'ToFileSender'   :  1});

const CrcFlagEnum = Object.freeze({
    'NotPresent'     :  0, 
    'Present'        :  1});

const DirectiveCodeEnum = Object.freeze({
    'EOF'            :  4, 
    'FIN'            :  5, 
    'ACK'            :  6, 
    'METADATA'       :  7, 
    'NAK'            :  8, 
    'PROMPT'         :  9, 
    'KEEPALIVE'      : 10});

const ConditionCodeEnum = Object.freeze({
    'NoError'                 :  0, 
    'PositiveAckLimitReached' :  1, 
    'KeepAliveLimitReached'   :  2, 
    'InvalidTransMode'        :  3, 
    'FilestoreRejection'      :  4, 
    'FileChecksumFailure'     :  5, 
    'FileSizeError'           :  6, 
    'NAKLimitReached'         :  7, 
    'InactivityDetected'      :  8, 
    'InvalidFileStructure'    :  9, 
    'CheckLimitReached'       : 10, 
    'SuspendRequestReceived'  : 14, 
    'CancelRequestReceived'   : 15});

const EndSystemStatusEnum = Object.freeze({
    'GeneratedByWaypoint'     :  0, 
    'GeneratedByEndSystem'    :  1});

const DeliveryCodeEnum = Object.freeze({
    'DataComplete'            :  0, 
    'DataIncomplete'          :  1});

const FileStatusEnum = Object.freeze({
    'DiscardedDeliberately'   :  0, 
    'DiscardedDueToReject'    :  1, 
    'SuccessfullyRetained'    :  2, 
    'StatusUnreported'        :  3});

const SegCtrlEnum = Object.freeze({
    'BoundariesRespected'     :  0, 
    'BoundariesNotRespected'  :  1});

const ResponseRequiredEnum = Object.freeze({
    'NAK'                     :  0, 
    'Keepalive'               :  1});

const ActionCodeEnum = Object.freeze({
    'CreateFile'              :  0, 
    'DeleteFile'              :  1, 
    'RenameFile'              :  2, 
    'AppendFile'              :  3, 
    'ReplaceFile'             :  4, 
    'CreateDirectory'         :  5, 
    'RemoveDirectory'         :  6, 
    'DenyFile'                :  7, 
    'DenyDirectory'           :  8});

const HandlerCodeEnum = Object.freeze({
    'Cancel'                  :  0, 
    'Suspend'                 :  1, 
    'IgnoreError'             :  2, 
    'AppendFile'              :  3, 
    'Abandon'                 :  4});



class CFDPServer extends CdrGroundPlugin {
    constructor(configObj) {
        configObj.webRoot = path.join( __dirname, 'web');  
        super(configObj);
        
    	autoBind(this);
    	
    	this.Transactions = {
    	    RX: {
    	    	Active:    {},
    	    	Completed: {},
    	    },
    	    TX: {
    	        Queued:    {},
    	        Active:    {},
    	        Completed: {},
    	    }
    	};
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

        /* Initialize CFDP server. */
        this.initServer();
        
        /* Initial the file server. */
        this.initFileServer();

        this.logInfo( 'Initialized' );
    };
    
    
    
    getActiveRXTransaction(transID) {
        return this.Transactions.RX.Active[transID];
    }
    
    
    
    allocActiveRXTransaction(transID, rxConfig) {
    	var newTransaction = undefined;
    	
        if(typeof this.Transactions.RX.Active[transID] === 'undefined') {
            newTransaction = {};
        	
            newTransaction.stateMachine = this.allocClass1RXStateMachine(rxConfig);
            newTransaction.service = XState.interpret(newTransaction.stateMachine).start();
        	
            this.Transactions.RX.Active[transID] = newTransaction;
        }
        
        return newTransaction;
    }
    
    
    
    allocClass1RXStateMachine(rxConfig) {
    	var newSM = new XState.Machine(
    		{
    		    id: 'Class1Receiver',
    		    initial: 'WaitForMetaData',
    		    strict: true,
    		    context: {
    		    	config:  rxConfig,
    		    	TempDir: this.TempDir
    		    },
    		    states: {
    		        WaitForMetaData: {
    		            type: 'atomic',
    		            on: {
    		                ABANDON: {
    		                    target: 'Shutdown', actions: ['issueAbandoned']
    		                },
    		                CANCEL: {
    		                    target: 'Shutdown', actions: ['issueTransactionFinished']
    		                },
    		                RX_METADATA: {
    		                    /* Issue Metadata-Recv */
    		                    target: 'WaitForEOF', actions: ['storeMetadata']
    		                },
    		                RX_EOF: {
    		                    /* Let the User know that the transaction completed without
    		                     * any Metadata being received.  
    		                     * Issue Transaction-Finished */
    		                    target: 'Shutdown', actions: ['issueTransactionFinished']
    		                },
    		                INACTIVITY_TIMEOUT: {
    		                    target: 'Shutdown' 
    		                },
    		                RX_CANCEL_RQUEST: {
    		                    target: 'Shutdown', actions: ['issueTransactionFinished']
    		                }
    		            }
    		        },
    		        WaitForEOF: {
    		            type: 'atomic',
    		            on: {
    		                ABANDON: {
    		                    target: 'Shutdown', actions: ['issueAbandoned']
    		                },
    		                CANCEL: {
    		                    target: 'Shutdown', actions: ['retainTempFile','issueTransactionFinished']
    		                },
    		                RX_FILEDATA: {
    		                    target: 'WaitForEOF', actions: ['storeFileData']
    		                },
    		                RX_EOF: {
    		                    target: 'Shutdown', cond: 'isFileTransfer', actions: ['completeFile', 'issueTransactionFinished']
    		                },
    		                INACTIVITY_TIMEOUT: {
    		                    target: 'Shutdown' 
    		                },
    		                RX_CANCEL_RQUEST: {
    		                    target: 'Shutdown', actions: ['issueTransactionFinished']
    		                }
    		            }
    		        },
    		        Shutdown: {
    		            type: 'final'
    		        }
    		    }
    		},{
    		    actions: {
    		        startFile: (context, event) => {
    		            /* Try to open the file. */
    		            console.log('startFile');
    		        },
    		        copyTempFileToDest: (context, event) => {
    		            /* Copy the temporary file to the destination directory/file */
    		            console.log('copyTempFileToDest');
    		        },    
    		        execFilestoreRequests: (context, event) => {
    		            console.log('execFilestoreRequests');
    		        },
    		        issueTransactionFinished: (context, event) => {
    		            console.log('issueTransactionFinished');
    		        },
    		        issueAbandoned: (context, event) => {
    		            console.log('issueTransactionFinished');
    		        },
    		        issueTransactionFinished: (context, event) => {
    		            console.log('issueTransactionFinished');
    		        },
    		        issueMetadataRecv: (context, event) => {
    		            console.log('issueMetadataRecv');
    		        },
    		        issueReport: (context, event) => {
    		            console.log('issueReport');
    		        },
    		        retainTempFile: (context, event) => {
    		            console.log('retainTempFile');
    		        },
    		        storeFileData: (context, event) => {
                            console.log('storeFileData');
    		        },
    		        updateFileSize: (context, event) => {
    		            console.log('updateFileSize');
    		        },
    		        storeFileData: (context, event) => {
    		            fs.writeSync(context.fd, event.pdu.data, 0, event.pdu.data.length, event.pdu.dataOffset);
    		        },
    		        storeMetadata: (context, event) => {
                            console.log('*** storeMetadata ***');
                            context.srcFileName = event.pdu.meta.srcFileName;
                            context.dstFileName = event.pdu.meta.destFileName;
                            context.tmpFileName = path.join(this.TempDir, context.dstFileName);

                            this.createSubDirectories(context.tmpFileName);
    		        	
                            context.fd = fs.openSync(context.tmpFileName, 'w');
    		        },
    		        completeFile: (context, event) => {
    		            console.log('*** completeFile ***');
    		            var self = this;
    		            fs.closeSync(context.fd);
    		            context.absDstFileName = path.join(context.config.PhyBasePath, context.dstFileName);
    		            this.createSubDirectories(context.absDstFileName);
    		            
    		            var readStream = fs.createReadStream(context.tmpFileName);
    		            var writeStream = fs.createWriteStream(context.absDstFileName);
    		            
    		            readStream.pipe(writeStream);
    		            
    		            readStream.on('close', function () {
    		                fs.unlink(context.tmpFileName);
    		            });
    		            
    		            writeStream.on('close', function () {
                                self.hk.content.fileRxCount++;

                                self.reportFileReceived(context.absDstFileName, context.dstFileName);
    		            })
    		        
    		        },
    		    },
    		    guards: {
    		        isFileTransfer: (context, event) => {
    		            return true;
    		        },
    		        isFileOpen: (context, event) => {
    		            return true;
    		        }
    		    }
    		}
        );
    	
    	return newSM;
    }
    
    
    
    DeleteFolderRecursive(inPath) {
    	var self = this;
        if (fs.existsSync(inPath)) {
    	    fs.readdirSync(inPath).forEach(function(file, index){
    	        var curPath = inPath + '/' + file;
    	        if (fs.lstatSync(curPath).isDirectory()) { // recurse
    	        	self.DeleteFolderRecursive(curPath);
    	        } else { // delete file
      	            fs.unlinkSync(curPath);
    	        }
    	    });
    	    fs.rmdirSync(inPath);
    	  }
    };
    
    
    
    initConfig(name, configFile) {
        /* Load environment dependent configuration */
        config.loadFile( configFile );

        /* Perform validation */
        config.validate( {
            allowed: 'strict'
        } );
        
        config.name = name;        
        
        /* Create the temporary and base directories. */
        this.TempDir = path.join(global.CDR_WORKSPACE, config.get('TempDir'));
        if (!fs.existsSync(this.TempDir)) {
            this.createSubDirectoriesFull(this.TempDir);
        } else {
            this.DeleteFolderRecursive(this.TempDir);
        }
    	
    	this.rxConfigs = config.get('RX');
    	for(var i = 0; i < this.rxConfigs.length; ++i) {
    	    var rxConfig = this.rxConfigs[i];
    	    rxConfig.PhyBasePath = path.join(global.CDR_WORKSPACE, rxConfig.PhyBasePath);
    	    if (!fs.existsSync(rxConfig.PhyBasePath)) {
    	    	this.createSubDirectoriesFull(rxConfig.PhyBasePath);
    	    }
    	}
    	
    	this.txConfigs = config.get('TX');
    	for(var i = 0; i < this.txConfigs.length; ++i) {
            var txConfig = this.txConfigs[i];
            txConfig.PhyBasePath = path.join(global.CDR_WORKSPACE, txConfig.PhyBasePath);
    	    if (!fs.existsSync(txConfig.PhyBasePath)) {
    	    	this.createSubDirectoriesFull(txConfig.PhyBasePath);
    	    }
    	}
    }
    
    
    
    createSubDirectoriesFull(usrPath) {
    	var pathElements = path.parse(usrPath);
    	var location = '/';
        pathElements.dir.split(path.sep).forEach (function (item) {
            location = path.join(location, item);
            if (!fs.existsSync(location)) {
                fs.mkdirSync(location);
            }
        });

        if (!fs.existsSync(usrPath)) {
            fs.mkdirSync(usrPath);
        }
    }
    
    
    
    createSubDirectories(usrPath) {
    	var pathElements = path.parse(usrPath);
    	var location = '/';
        pathElements.dir.split(path.sep).forEach (function (item) {
            location = path.join(location, item);
            if (!fs.existsSync(location)) {
                fs.mkdirSync(location);
            }
        });
    }
    
    
    
    initTelemetry() {
        this.hk = {
            opsPath: '/' + config.name + '/hk',
            content: {
                cmdAcceptCount: 0,
                cmdRejectCount: 0,
                pduInCount: 0,
                pduOutCount: 0,
                fileRxCount: 0,
                fileTxCount: 0,
                inputStreamID: config.get( 'CfdpInputStream' )
            }
        };
        this.addTelemetry(this.hk, 1000);
    }
    
    
    
    getRxConfig(dstPath) {
        var rxConfig = undefined;
        
    	/* Find the configuration. */
    	for(var i = 0; i < this.rxConfigs.length; ++i) {
    	    if(dstPath.startsWith(this.rxConfigs[i].DestBasePath)) {
    		rxConfig = this.rxConfigs[i];
    	    }
    	}
    	
        return rxConfig;
    }
    
    
    
    getTxConfig(dstPath) {
        var txConfig = undefined;

        ///* Find the configuration. */
        //for(var i = 0; i < txConfigs.length; ++i) {
        //        if(dstPath.startsWith(txConfigs[i].DestBasePath)) {
        //                txConfig = txConfigs[i];
        //        }
        //}
        
        return txConfig;
    }
    
    
    
    initClientInterface() {
        var content = {};
        
        content[config.name] = {
            shortDescription: 'CFDP Server (' + config.name + ')',
            longDescription: 'CFDP Server (' + config.name + ')',
            nodes: {
                main: {
                    type: CdrGroundPlugin.ContentType.LAYOUT,
                    shortDescription: 'Main',
                    longDescription: 'Main.',
                    filePath: '/main_layout.lyt',
                    handlebarsContext: {
                        pluginName: config.name
                    }
                },
                hk: {
                    type: CdrGroundPlugin.ContentType.PANEL,
                    shortDescription: 'Housekeeping',
                    longDescription: 'Housekeeping',
                    filePath: '/hk.pug',
                    handlebarsContext: {
                        pluginName: config.name
                    }
                },
                rx_browser: {
                    type: CdrGroundPlugin.ContentType.PANEL,
                    shortDescription: 'RX File Browser',
                    longDescription: 'RX File Browser',
                    filePath: '/rx_file_browser.pug',
                    handlebarsContext: {
                        pluginName: config.name
                    }
                },
                tx_browser: {
                    type: CdrGroundPlugin.ContentType.PANEL,
                    shortDescription: 'TX File Browser',
                    longDescription: 'TX File Browser',
                    filePath: '/tx_file_browser.pug',
                    handlebarsContext: {
                        pluginName: config.name
                    }
                },
                temp_browser: {
                    type: CdrGroundPlugin.ContentType.PANEL,
                    shortDescription: 'Temp File Browser',
                    longDescription: 'Temp File Browser',
                    filePath: '/temp_file_browser.pug',
                    handlebarsContext: {
                        pluginName: config.name
                    }
                }
            }
        }
        
        this.addContent(content);
    }
    
    
    
    initCommands() {
//        var cmdSetInput = {
//            opsPath: '/' + config.name + '/setInput',
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
    
    
    
    BufferToPDU(inBuffer) {
        var pdu = this.pduHdrDef.parse(inBuffer);
        
        /* Check to see if the CRC is included. */
        if(pdu.crc == CrcFlagEnum.Present) {
            /* It is present.  Verify that the CRC is correct. */
            /* TODO */
            console.log('The CRC is present.')
        }
        
        /* The byte offset after the 'transSeqnumLength' field. */
        var offset = 4;

        /* Add 1 to the entity ID length because the field is the actual length - 1 */
        pdu.entityIDLength++;
        /* Add 1 to the transaction sequence number length because the field is the actual 
         * length - 1 */
        pdu.transSeqNumLength++;
        
        pdu.transSeqNum = 0;
        pdu.srcEntityID = '';
        pdu.destEntityID = '';
        
        for(var i = 0; i < pdu.entityIDLength; ++i) { 
        	pdu.srcEntityID = pdu.srcEntityID + inBuffer[offset++].toString(10) + '.';
        }
        pdu.srcEntityID = pdu.srcEntityID.substring(0, pdu.srcEntityID.length-1);
        
        var value = 0;
        for(var i = pdu.transSeqNumLength-1; i >= 0; --i) {
        	value = value + (inBuffer[offset++] * Math.pow(10, i));
        }
        pdu.transSeqNum = value;
        
        for(var i = 0; i < pdu.entityIDLength; ++i) { 
        	pdu.destEntityID = pdu.destEntityID + inBuffer[offset++].toString(10) + '.';
        }
        pdu.destEntityID = pdu.destEntityID.substring(0, pdu.destEntityID.length-1);
        
        if(pdu.pduType == 0) {
        	pdu.directiveCode = inBuffer.readUInt8(offset++);
        	
        	switch(pdu.directiveCode) {
        	    /* EOF */
        	    case DirectiveCodeEnum.EOF: {
        	    	pdu.eof = {};
        	    	pdu.eof.condCode = (inBuffer.readUInt8(offset++) >> 4) & 0x0f;
        	    	pdu.eof.fileChecksum = inBuffer.readUInt32BE(offset);
        	    	offset = offset + 4;
        	    	pdu.eof.fileSize = inBuffer.readUInt32BE(offset);
        	    	offset = offset + 4;
        	    	
        	    	/* Omitted if condition code is ‘No error’.  Otherwise, entity ID in the 
        	    	 * TLV is the ID of the entity at which transaction cancellation was 
        	    	 * initiated. */ 
        	    	if(pdu.eof.condCode != 0) {
        	    		/* The Type of the Entity ID TLV shall be 06 hex; the Value shall 
        	    		 * be an Entity ID as discussed in 5.1. */
        	    	    pdu.eof.faultLocation = {};
        	    	    pdu.eof.faultLocation.Type = inBuffer.readUInt8(offset++);
        	    	    pdu.eof.faultLocation.Length = inBuffer.readUInt8(offset++);
        	    	    pdu.eof.faultLocation.Value = [];
        	    	    for(var i = 0; i < pdu.faultLocation.Length; ++i) {
            	    	    pdu.eof.faultLocation.Value.push(inBuffer.readUInt8(offset++));
        	    	    }
        	    	}
        	    	break;
        	    }
        	    
        	    /* Finished */
        	    case DirectiveCodeEnum.FIN: {
        	    	pdu.finished = {};
        	    	
        	    	var tempByte   = inBuffer.readUInt8(offset++);
        	    	pdu.finished.condCode   = (tempByte >> 4) & 0x0f;
        	    	pdu.finished.endSysStat = (tempByte >> 3) & 0x01;
        	    	pdu.finished.delCode    = (tempByte >> 2) & 0x01;
        	    	pdu.finished.fileStat   = (tempByte >> 0) & 0x03;
        	    	pdu.finished.endSysStat = (tempByte >> 3) & 0x01;

        	    	/* The Type of the Entity ID TLV shall be 06 hex; the Value shall 
        	    	 * be an Entity ID as discussed in 5.1. */
        	    	pdu.finished.filestoreResponse = {};
        	    	tempByte = inBuffer.readUInt8(offset++);
        	    	pdu.finished.filestoreResponse.actionCode = (tempByte >> 4) & 0x0f;
        	    	pdu.finished.filestoreResponse.statusCode = tempByte & 0x0f;
        	    	
        	    	pdu.finished.filestoreResponse.firstFileName = {};
        	    	pdu.finished.filestoreResponse.firstFileName.Length = inBuffer.readUInt8(offset++);
        	    	pdu.finished.filestoreREsponse.firstFileName.Value = inBuffer.toString('utf8', offset, offset + pdu.filestoreResponse.firstFileName.Length);
        	    	offset = offset + pdu.filestoreResponse.firstFileName.Length;
        	    	
        	    	pdu.finished.filestoreResponse.secondFileName = {};
        	    	pdu.finished.filestoreResponse.secondFileName.Length = inBuffer.readUInt8(offset++);
        	    	pdu.finished.filestoreREsponse.secondFileName.Value = inBuffer.toString('utf8', offset, offset + pdu.filestoreResponse.secondFileName.Length);
        	    	offset = offset + pdu.filestoreResponse.secondFileName.Length;
        	    	
        	    	pdu.finished.filestoreResponse.filestoreMessage = {};
        	    	pdu.finished.filestoreResponse.filestoreMessage.Length = inBuffer.readUInt8(offset++);
        	    	pdu.finished.filestoreResponse.filestoreMessage.Value = inBuffer.toString('utf8', offset, offset + pdu.finished.filestoreResponse.filestoreMessage.Length);
        	    	offset = offset + pdu.finished.filestoreResponse.filestoreMessage.Length;
        	    	break;
        	    }
        	    
        	    /* ACK */
        	    case DirectiveCodeEnum.ACK: {
        	    	pdu.ack = {};
        	    	
        	    	var tempByte   = inBuffer.readUInt8(offset++);
        	    	pdu.ack.directiveCode   = (tempByte >> 4) & 0x0f;
        	    	pdu.ack.directiveSubCode = tempByte & 0x0f;
        	    	tempByte   = inBuffer.readUInt8(offset++);
        	    	pdu.ack.condCode = (tempByte >> 4) & 0x0f;
        	    	pdu.ack.transStatus = tempByte & 0x03;
        	    	break;
        	    }
        	    
        	    /* Metadata */
        	    case DirectiveCodeEnum.METADATA: {
        	    	pdu.meta = {};
        	    	var length = 0;
        	    	        	    	
        	    	pdu.meta.segCtrl = inBuffer.readUInt8(offset++) & 0x01;
        	    	pdu.meta.fileSize = inBuffer.readUInt32BE(offset);
        	    	offset = offset + 4;
        	    	
        	    	length = inBuffer.readUInt8(offset++);
        	    	pdu.meta.srcFileName = path.join('/', inBuffer.toString('utf8', offset, offset + length));
        	    	offset = offset + length;
        	    	
        	    	length = inBuffer.readUInt8(offset++);
        	    	pdu.meta.destFileName = path.join('/', inBuffer.toString('utf8', offset, offset + length));
        	    	offset = offset + length;

        	    	if(inBuffer.length >= (offset + 2)) {
            	    	    pdu.meta.option.type = inBuffer.readUInt8(offset++);
            	    	    pdu.meta.option.Length = inBuffer.readUInt8(offset++);
            	    	    if(inBuffer.length >= (offset + pdu.meta.option.Length)) {
            	    	        pdu.meta.option.Value = inBuffer.toString('utf8', offset, offset + pdu.meta.option.Length);
            	    	        offset = offset + pdu.meta.option.Length;
            	    	    }
        	    	}
                        
        	    	break;
        	    }
        	    
        	    /* NAK */
        	    case DirectiveCodeEnum.NAK: {
        	    	pdu.nak = {};
        	    	
        	    	pdu.nak.startOfScope = inBuffer.readUInt32BE(offset);
        	    	offset = offset + 4;
        	    	pdu.nak.endOfScope = inBuffer.readUInt32BE(offset);
        	    	offset = offset + 4;
        	    	/* TODO */
        	    	break;
        	    }
        	    
        	    /* Prompt */
        	    case DirectiveCodeEnum.PROMPT: {
        	    	pdu.prompt = {};
        	    	
        	    	pdu.prompt.responseRequired = inBuffer.readUInt8(offset++) & 0x01;
        	    	
        	    	break;
        	    }
        	    
        	    /* Keep Alive */
        	    case DirectiveCodeEnum.KEEPALIVE: {
        	    	pdu.keepAlive = {};
        	    	
        	    	pdu.keepAlive.progress = inBuffer.readUInt32BE(offset++);
        	    	
        	    	break;
        	    }
        	}
        } else {
        	pdu.dataOffset = inBuffer.readUInt32BE(offset);
        	offset = offset + 4;
        	
        	var startOffset = offset;
        	var endOffset = pdu.dataOffset + pdu.dataFieldLength;
        	pdu.data = inBuffer.slice(startOffset);
        }
        
        return pdu;
    }
    
    
    
    MessageToPDU(inMessage) {
    	var pdu = undefined;
    	    	
    	if(inMessage.msgID == 0x1FFE) {
    	    this.hk.content.pduInCount++;
            pdu = this.BufferToPDU(inMessage.content.payload);
    	}
    	
    	return pdu;
    };
    
    
    
    initServer() {
    	var self = this;
    	
        this.pduHdrDef = new Parser()
            .endianess( 'big' )
            .bit3( 'version' )
            .bit1( 'pduType' )
            .bit1( 'direction' )
            .bit1( 'transMode' )
            .bit1( 'crc' )
            .bit1( 'spare1' )
            .uint16( 'dataFieldLength' )
            .bit1( 'spare2' )
            .bit3( 'entityIDLength' )
            .bit1( 'spare3' )
            .bit3( 'transSeqNumLength' );

        this.namespace.recv( config.get( 'CfdpInputStream' ), this.ProcessIncomingMessage);
        
    	this.logInfo( 'Initialized engine' );
    };
    
    
    
    ProcessIncomingMessage(message) {
    	var pdu = this.MessageToPDU(message);
    	
    	if(typeof pdu !== 'undefined') {
    		var transID = this.getTransactionIDFromPDU(pdu);
    	    
    	    var transaction = this.getActiveRXTransaction(transID);
    	    
    	    if(typeof transaction === 'undefined') {
    	    	/* This is a new transaction.  Get the RX configuration and allocate a new 
    	    	 * transaction object. */
    	    	if((pdu.pduType == PDUTypeEnum.FileDirective) && (pdu.directiveCode == DirectiveCodeEnum.METADATA)) {
    	    	    var dstPath = pdu.meta.destFileName;
    	    	    var config = this.getRxConfig(dstPath);
    	    	
    	    	    if(typeof config === 'undefined') {
    	    		    /* TODO */
    	    		    console.log('Destination path not defined.');
    	    	    } else {
    	    	        transaction = this.allocActiveRXTransaction(transID, config);
    	    	    }
    	    	}
    	    	/* TODO: Log this and update metrics. */
    	    } else {
    	    	/* TODO: Log this and update metrics. */
    	    }
    	    
    	    if(typeof transaction !== 'undefined') {
		    	switch(pdu.pduType) {
		    	    case PDUTypeEnum.FileDirective: {
		    	    	switch(pdu.directiveCode) {
		    	    		case DirectiveCodeEnum.EOF: {
		    	    	    	transaction.service.send({type: 'RX_EOF', pdu: pdu});
		    	    			break;
		    	    		}
	
		    	    		case DirectiveCodeEnum.FIN: {
		    	    	    	transaction.service.send({type: 'RX_FIN', pdu: pdu});
		    	    			break;
		    	    		}
	
		    	    		case DirectiveCodeEnum.ACK: {
		    	    	    	transaction.service.send({type: 'RX_ACK', pdu: pdu});
		    	    			break;
		    	    		}
	
		    	    		case DirectiveCodeEnum.METADATA: {
		    	    	    	transaction.service.send({type: 'RX_METADATA', pdu: pdu});
		    	    			break;
		    	    		}
	
		    	    		case DirectiveCodeEnum.NAK: {
		    	    	    	transaction.service.send({type: 'RX_NAK', pdu: pdu});
		    	    			break;
		    	    		}
	
		    	    		case DirectiveCodeEnum.PROMPT: {
		    	    	    	transaction.service.send({type: 'RX_PROMPT', pdu: pdu});
		    	    			break;
		    	    		}
	
		    	    		case DirectiveCodeEnum.KEEPALIVE: {
		    	    	    	transaction.service.send({type: 'RX_KEEPALIVE', pdu: pdu});
		    	    			break;
		    	    		}
		    	    	}
		    	        break;	
		    	    }
	
		    	    case PDUTypeEnum.FileData: {
		    	    	transaction.service.send({type: 'RX_FILEDATA', pdu: pdu});
		    	        break;	
		    	    }
		    	}
    	    }
    	}
    }
    
    
    
    getTransactionIDFromPDU(pdu) {
        return pdu.srcEntityID + '_' + pdu.transSeqNum;
    }
    
    
    
    getPhysicalRxPath(logicalPath) {
        var rxConfig = this.getRxConfig(logicalPath);
        
        var physicalPath = path.join(rxConfig.PhyBasePath, logicalPath);
        
        return physicalPath;
    }
    
    
    
    getPhysicalTxPath(logicalPath) {
        var txConfig = this.getTxConfig(logicalPath);
        
        var physicalPath = path.join(txConfig.PhyBasePath, logicalPath);
        
        return physicalPath;
    }
    
    
    
    getPhysicalTempPath(logicalPath) {
        var physicalPath = path.join(this.TempDir, logicalPath);
        
        return physicalPath;
    }
    
    
    
    reportFileReceived(physicalPath, virtualPath) {
        this.namespace.send('file-received', {physicalPath: physicalPath, virtualPath: virtualPath, gndTime: new Date()});
    }
    
    
    
    initFileServer() {
        var self = this;
        global.NODE_APP.get('/plugin/' + config.name + '/rx_files', function(req, res) {
            var start = 0;
            var idxFile = 0;
            var length = -1;
            var fileList = [];
          
            if(req.hasOwnProperty('query') == true) {  
                var requestedPath = req.query.path || '/';
                var physicalPath = self.getPhysicalRxPath(requestedPath);
                
                fs.readdir(physicalPath, (err, files) => {      
                    if (err) {
                        throw err;
                    }
                    
                    var data = [];

                    if(requestedPath !== '/') {
                        data.push({ Name : '..', IsDirectory: true, Path : path.join(requestedPath, '..')  });
                    }
                    
                    for(var i = 0; i < files.length; ++i) {
                        try {
                            //console.log("processingile);
                            var isDirectory = fs.statSync(path.join(physicalPath, files[i])).isDirectory();
                            if (isDirectory) {
                                data.push({ Name : files[i], IsDirectory: true, Path : path.join(requestedPath, files[i])  });
                            } else {
                                var ext = path.extname(files[i]);

                                data.push({ Name : files[i], Ext : ext, IsDirectory: false, Path : path.join(requestedPath, files[i]) });
                            }
                        } catch(e) {
                            console.log(e); 
                        } 
                    }

                    res.json(data);
                });
            } 
        });

        global.NODE_APP.get('/plugin/' + config.name + '/tx_files', function(req, res) {
            var start = 0;
            var idxFile = 0;
            var length = -1;
            var fileList = [];
          
            if(req.hasOwnProperty('query') == true) {  
                var requestedPath = req.query.path || '/';
                var physicalPath = self.getPhysicalTxPath(requestedPath);
                
                fs.readdir(physicalPath, (err, files) => {      
                    if (err) {
                        throw err;
                    }
                    
                    var data = [];

                    if(requestedPath !== '/') {
                        data.push({ Name : '..', IsDirectory: true, Path : path.join(requestedPath, '..')  });
                    }
                    
                    for(var i = 0; i < files.length; ++i) {
                        try {
                            //console.log("processingile);
                            var isDirectory = fs.statSync(path.join(physicalPath, files[i])).isDirectory();
                            if (isDirectory) {
                                data.push({ Name : files[i], IsDirectory: true, Path : path.join(requestedPath, files[i])  });
                            } else {
                                var ext = path.extname(files[i]);

                                data.push({ Name : files[i], Ext : ext, IsDirectory: false, Path : path.join(requestedPath, files[i]) });
                            }
                        } catch(e) {
                            console.log(e); 
                        } 
                    }

                    res.json(data);
                });
            } 
        });
        global.NODE_APP.get('/plugin/' + config.name + '/temp_files', function(req, res) {
            var start = 0;
            var idxFile = 0;
            var length = -1;
            var fileList = [];
          
            if(req.hasOwnProperty('query') == true) {  
                var requestedPath = req.query.path || '/';
                var physicalPath = self.getPhysicalTempPath(requestedPath);
                
                fs.readdir(physicalPath, (err, files) => {      
                    if (err) {
                        throw err;
                    }
                    
                    var data = [];

                    if(requestedPath !== '/') {
                        data.push({ Name : '..', IsDirectory: true, Path : path.join(requestedPath, '..')  });
                    }
                    
                    for(var i = 0; i < files.length; ++i) {
                        try {
                            var isDirectory = fs.statSync(path.join(physicalPath, files[i])).isDirectory();
                            if (isDirectory) {
                                data.push({ Name : files[i], IsDirectory: true, Path : path.join(requestedPath, files[i])  });
                            } else {
                                var ext = path.extname(files[i]);

                                data.push({ Name : files[i], Ext : ext, IsDirectory: false, Path : path.join(requestedPath, files[i]) });
                            }
                        } catch(e) {
                            console.log(e); 
                        } 
                    }

                    res.json(data);
                });
            } 
        });
    }

    
    
    handleClientRequest( obj ) {
        var self = this;
        var outObj = {
            msg: 'FAILIURE',
            value: undefined
        }

        if ( obj.query.length == 0 ) {
            obj.cb( outObj );
            return;
        }

        switch ( obj.query ) {
            case 'GET_MIB':
                obj.cb( self.GetMibParams( outObj, obj.data ) );
                break;

            case 'SET_MIB':
                obj.cb( self.SetMibParams( outObj, obj.data ) );
                break;

            case 'RESTART_ENGINE':
                obj.cb( self.RestartEngine( outObj, obj.data ) );
                break;

            case 'STOP_ENGINE':
                obj.cb( self.StopEngine( outObj, obj.data ) );
                break;

            case 'SEND_FROM_GND':
                obj.cb( self.SendFromGnd( outObj, obj.data ) );
                break;

            case 'GET_TRANS_STATUS':
                obj.cb( self.GetTransactionStatus( outObj, obj.data ) );
                break;

            case 'GET_SUMMARY_STATUS':
                obj.cb( self.GetSummaryStatus( outObj, obj.data ) );
                break;

            case 'REG_PDU_OPEN_CB':
                if ( obj.cb == undefined ) {
                    self.logError( 'EventEnum.IMPROPER_REQ, "No callback found"' );
                    break;
                }
                cf.RegisterCallbackOn( 'pduOutputOpen', obj.cb );
                break;

            case 'REG_PDU_READY_CB':
                if ( obj.cb == undefined ) {
                    self.logError( 'EventEnum.IMPROPER_REQ, "No callback found"' );
                    break;
                }
                cf.RegisterCallbackOn( 'pduOutputReady', obj.cb );
                break;

            case 'REG_TRANS_STATUS_CB':
                if ( obj.cb == undefined ) {
                    self.logError( 'EventEnum.IMPROPER_REQ, "No callback found"' );
                    break;
                }
                cf.RegisterCallbackOn( 'showTransactionStatus', obj.cb );
                break;

            case 'REG_INDICATION_CB':
                if ( obj.cb == undefined ) {
                    self.logError( 'EventEnum.IMPROPER_REQ, "No callback found"' );
                    break;
                }
                cf.RegisterCallbackOn( 'indication', obj.cb );
                break;

            case 'MAKE_TEST_CASES':
                self.makeTestCases();
                break;

            case 'RUN_TEST':
                self.runTest();
                break;

            case 'VALIDATE_TEST':
                if ( obj.cb == undefined ) {
                    self.logError( 'EventEnum.IMPROPER_REQ, "No callback found"' );
                    break;
                }
                obj.cb( self.valTest() );
                break;

            default:
                self.logError( 'EventEnum.IMPROPER_REQ, "Unknown Query"' );
                break;
        }
    }
    
    

    /**
     * Makes necessary files to perform uplink test
     */
    makeTestCases() {
        var self = this;
        var fileCount = 0

        while ( fileCount < self.testkit.numberOfFilesGenerated ) {
            if ( fs.existsSync( self.testkit.originPath ) ) {
                if ( fileCount == 0 ) {
                    fs.readdir( self.testkit.originPath, ( err, files ) => {
                        // if ( err ) throw err;
                        for ( const file of files ) {
                            fs.unlink( path.join( self.testkit.originPath, file ), err => {
                                // if ( err ) throw err;
                            });
                        }
                    });
                }

                var fileContent = "";
                var fileSize = 0;
                var fileCapacity = self.testkit.fileSizeSpectrum[ Math.floor( Math.random() * self.testkit.fileSizeSpectrum.length ) ];
                var maxFileSize = 5;
                var tempStr = "";
                var genName = "";

                if ( fileCapacity == "b" ) {
                    maxFileSize = Math.floor( Math.random() * 900 )
                }

                if ( fileCapacity == "kb" ) {
                    maxFileSize = Math.floor( Math.random() * ( 900 * 1000 ) )
                }

                while ( fileSize < maxFileSize ) {
                    tempStr = stringGen( Math.floor( Math.random() * 15 ) ) + " ";
                    fileSize += tempStr.length;
                    fileContent += tempStr
                }
                genName = self.testkit.originPath + "/" + fileCapacity + "_" + fileSize + "_" + fileCapacity + ".txt";

                if ( genName != "" ) {
                    fs.writeFile( genName, fileContent, ( err ) => {
                        if ( err ) {
                            this.logError( 'The file failed to save!' );
                        } else {
                            this.logInfo( 'The file was succesfully saved.' );
                        }
                    });
                }
                fileCount += 1
            } else {
                fs.mkdir( self.testkit.originPath, {
                    recursive: true
                }, ( err ) => {
                    if ( err ) {
                        this.logError( 'Failed to make directory `' + self.testkit.originPath + '`' );
                        fileCount = self.testkit.numberOfFilesGenerated;
                    }
                });
            }
        }
    }

    
    
    /**
     * Run a test to check cdfp ground node work
     */
    runTest() {
        var self = this;
        self.testkit.genFileList = [];
        fs.readdir( self.testkit.originPath, ( err, files ) => {
            if ( err ) throw err;

            for ( const file of files ) {
                cf.RequestPdu( 1, "0.24", path.join( self.testkit.originPath, file ), path.join( self.testkit.destPath, file ) );
                self.testkit.genFileList.push( path.join( self.testkit.destPath, file ) );
            }
        });
    }

    
    
    /**
     * Validates the test that ran in this instance
     */
    valTest() {
        var self = this;
        var Status = 'SUCCESS'
        for ( var i in self.testkit.genFileList ) {
            if ( !fs.existsSync( self.testkit.genFileList[ i ] ) ) {
                Status = 'FAILIURE'
            }
        }
        return {
            msg: Status
        }
    }
}



exports = module.exports = CFDPServer;
