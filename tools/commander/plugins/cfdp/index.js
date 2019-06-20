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


class CFDPServer extends CdrGroundPlugin {
    constructor(configObj) {
        configObj.webRoot = path.join( __dirname, 'web');  
        super(configObj);
        
    	autoBind(this);
    	
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

        this.logInfo( 'Initialized' );
    };
    
    
    initConfig(name, configFile) {
        /* Load environment dependent configuration */
        config.loadFile( configFile );

        /* Perform validation */
        config.validate( {
            allowed: 'strict'
        } );
        
        config.name = name;
    }
    
    
    initTelemetry() {
        this.hk = {
            opsPath: '/' + config.name + '/hk',
            content: {
                cmdAcceptCount: 0,
                cmdRejectCount: 0
            }
        };
        this.addTelemetry(this.hk, 1000);
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

        this.namespace.recv( config.get( 'CfdpInputStream' ), function( message ) {
        	if(message.msgID == 0x1FFE) {                
                var pdu = self.pduHdrDef.parse(message.content.payload);
                
                /* The byte offset after the 'transSeqnumLength' field. */
                var offset = 4;

                /* Add 1 to the entity ID length because the field is the actual length - 1 */
                pdu.entityIDLength++;
                /* Add 1 to the transaction sequence number length because the field is the actual 
                 * length - 1 */
                pdu.transSeqNumLength++;
                
                pdu.srcEntityID = [];
                pdu.transSeqNum = [];
                pdu.destEntityID = [];
                
                for(var i = 0; i < pdu.entityIDLength; ++i) { 
                	pdu.srcEntityID.push(message.content.payload[offset++]);
                }
                
                for(var i = 0; i < pdu.transSeqNumLength; ++i) {
                	pdu.transSeqNum.push(message.content.payload[offset++]);
                }
                
                for(var i = 0; i < pdu.entityIDLength; ++i) {                	
                	pdu.destEntityID.push(message.content.payload[offset++]);
                }
                
                if(pdu.pduType == 0) {
                	pdu.directiveCode = message.content.payload.readUInt8(offset++);
                	
                	switch(pdu.directiveCode) {
                	    /* EOF */
                	    case 4: {
                	    	pdu.eof = {};
                	    	pdu.eof.condCode = (message.content.payload.readUInt8(offset++) >> 4) & 0x0f;
                	    	pdu.eof.fileChecksum = message.content.payload.readUInt32BE(offset);
                	    	offset = offset + 4;
                	    	pdu.eof.fileSize = message.content.payload.readUInt32BE(offset);
                	    	offset = offset + 4;
                	    	
                	    	/* Omitted if condition code is ‘No error’.  Otherwise, entity ID in the 
                	    	 * TLV is the ID of the entity at which transaction cancellation was 
                	    	 * initiated. */ 
                	    	if(pdu.eof.condCode != 0) {
                	    		/* The Type of the Entity ID TLV shall be 06 hex; the Value shall 
                	    		 * be an Entity ID as discussed in 5.1. */
                	    	    pdu.eof.faultLocation = {};
                	    	    pdu.eof.faultLocation.Type = message.content.payload.readUInt8(offset++);
                	    	    pdu.eof.faultLocation.Length = message.content.payload.readUInt8(offset++);
                	    	    pdu.eof.faultLocation.Value = [];
                	    	    for(var i = 0; i < pdu.faultLocation.Length; ++i) {
                    	    	    pdu.eof.faultLocation.Value.push(message.content.payload.readUInt8(offset++));
                	    	    }
                	    	}
                	    	break;
                	    }
                	    
                	    /* Finished */
                	    case 5: {
                	    	pdu.finished = {};
                	    	
                	    	var tempByte   = message.content.payload.readUInt8(offset++);
                	    	pdu.finished.condCode   = (tempByte >> 4) & 0x0f;
                	    	pdu.finished.endSysStat = (tempByte >> 3) & 0x01;
                	    	pdu.finished.delCode    = (tempByte >> 2) & 0x01;
                	    	pdu.finished.fileStat   = (tempByte >> 0) & 0x03;
                	    	pdu.finished.endSysStat = (tempByte >> 3) & 0x01;

                	    	/* The Type of the Entity ID TLV shall be 06 hex; the Value shall 
                	    	 * be an Entity ID as discussed in 5.1. */
                	    	pdu.finished.filestoreResponse = {};
                	    	tempByte = message.content.payload.readUInt8(offset++);
                	    	pdu.finished.filestoreResponse.actionCode = (tempByte >> 4) & 0x0f;
                	    	pdu.finished.filestoreResponse.statusCode = tempByte & 0x0f;
                	    	
                	    	pdu.finished.filestoreResponse.firstFileName = {};
                	    	pdu.finished.filestoreResponse.firstFileName.Length = message.content.payload.readUInt8(offset++);
                	    	pdu.finished.filestoreREsponse.firstFileName.Value = message.content.payload.toString('utf8', offset, offset + pdu.filestoreResponse.firstFileName.Length);
                	    	offset = offset + pdu.filestoreResponse.firstFileName.Length;
                	    	
                	    	pdu.finished.filestoreResponse.secondFileName = {};
                	    	pdu.finished.filestoreResponse.secondFileName.Length = message.content.payload.readUInt8(offset++);
                	    	pdu.finished.filestoreREsponse.secondFileName.Value = message.content.payload.toString('utf8', offset, offset + pdu.filestoreResponse.secondFileName.Length);
                	    	offset = offset + pdu.filestoreResponse.secondFileName.Length;
                	    	
                	    	pdu.finished.filestoreResponse.filestoreMessage = {};
                	    	pdu.finished.filestoreResponse.filestoreMessage.Length = message.content.payload.readUInt8(offset++);
                	    	pdu.finished.filestoreResponse.filestoreMessage.Value = message.content.payload.toString('utf8', offset, offset + pdu.finished.filestoreResponse.filestoreMessage.Length);
                	    	offset = offset + pdu.finished.filestoreResponse.filestoreMessage.Length;
                	    	break;
                	    }
                	    
                	    /* ACK */
                	    case 6: {
                	    	pdu.ack = {};
                	    	
                	    	var tempByte   = message.content.payload.readUInt8(offset++);
                	    	pdu.ack.directiveCode   = (tempByte >> 4) & 0x0f;
                	    	pdu.ack.directiveSubCode = tempByte & 0x0f;
                	    	tempByte   = message.content.payload.readUInt8(offset++);
                	    	pdu.ack.condCode = (tempByte >> 4) & 0x0f;
                	    	pdu.ack.transStatus = tempByte & 0x03;
                	    	break;
                	    }
                	    
                	    /* Metadata */
                	    case 7: {
                	    	pdu.meta = {};
                	    	
                	    	pdu.meta.segCtrl = message.content.payload.readUInt8(offset++) & 0x01;
                	    	pdu.meta.fileSize = message.content.payload.readUInt32BE(offset);
                	    	offset = offset + 4;
                	    	
                	    	pdu.meta.srcFileName = {};
                	    	pdu.meta.srcFileName.Length = message.content.payload.readUInt8(offset++);
                	    	pdu.meta.srcFileName.Value = message.content.payload.toString('utf8', offset, offset + pdu.meta.srcFileName.Length);
                	    	offset = offset + pdu.meta.srcFileName.Length;
                	    	
                	    	pdu.meta.destFileName = {};
                	    	pdu.meta.destFileName.Length = message.content.payload.readUInt8(offset++);
                	    	pdu.meta.destFileName.Value = message.content.payload.toString('utf8', offset, offset + pdu.meta.destFileName.Length);
                	    	offset = offset + pdu.meta.destFileName.Length;

                	    	/* TODO */
                	    	//pdu.meta.options = {};
                	    	//pdu.meta.options.filestoreRequest = {};
                	    	//pdu.meta.options.destFileName.Length = message.content.payload.readUInt8(offset++);
                	    	//pdu.meta.options.destFileName.Value = message.content.payload.toString('utf8', offset, offset + pdu.meta.options.destFileName.Length);
                	    	//offset = offset + pdu.meta.options.destFileName.Length;
                	    	break;
                	    }
                	    
                	    /* NAK */
                	    case 8: {
                	    	pdu.nak = {};
                	    	
                	    	pdu.nak.startOfScope = message.content.payload.readUInt32BE(offset);
                	    	offset = offset + 4;
                	    	pdu.nak.endOfScope = message.content.payload.readUInt32BE(offset);
                	    	offset = offset + 4;
                	    	/* TODO */
                	    	break;
                	    }
                	    
                	    /* Prompt */
                	    case 9: {
                	    	pdu.prompt = {};
                	    	
                	    	pdu.prompt.responseRequired = message.content.payload.readUInt8(offset++) & 0x01;
                	    	
                	    	break;
                	    }
                	    
                	    /* Keep Alive */
                	    case 12: {
                	    	pdu.keepAlive = {};
                	    	
                	    	pdu.keepAlive.progress = message.content.payload.readUInt32BE(offset++);
                	    	
                	    	break;
                	    }
                	}
                	
                	console.log(pdu);
                } else {
                	pdu.dataOffset = message.content.payload.readUInt32BE(offset);
                	offset = offset + 4;
                	
                	pdu.data = [];
                	var startOffset = offset;
                	var endOffset = pdu.dataOffset + pdu.dataFieldLength;
                	
                    for(var i = 0; i < pdu.dataFieldLength; ++i) {
                    	pdu.data.push(message.content.payload[offset++]);
                    }
                }
        	}
        });
        
//    	/* Set CFDP API configuration */
//    	//CfdpLib.SetConfig( config.get( 'config' ) );
//
//    	/* Register Required Callbacks */
//    	/* End users may not be able to alter following callbacks */
//    	CfdpLib.RegisterCallbackOn( 'info', ( value ) => {
//    	    this.logInfo( 'EventEnum.LOG_EVENTS, value' );
//    	} );
//
//    	CfdpLib.RegisterCallbackOn( 'debug', ( value ) => {
//    	    this.logDebug( 'EventEnum.LOG_EVENTS, value' );
//    	} );
//
//    	CfdpLib.RegisterCallbackOn( 'error', ( value ) => {
//    	    this.logError( 'EventEnum.LOG_EVENTS, value' );
//    	} );
//
//    	CfdpLib.RegisterCallbackOn( 'warning', ( value ) => {
//    	    this.logInfo( 'EventEnum.LOG_EVENTS, value' );
//    	} );
//
//    	CfdpLib.RegisterCallbackOn( 'pduOutputOpen', () => {} );
//    	CfdpLib.RegisterCallbackOn( 'pduOutputReady', () => {} );
//    	CfdpLib.RegisterCallbackOn( 'indication', () => {} );
//
//        CfdpLib.RegisterCallbackOn( 'pduOutputSend', ( bufferObj ) => {
//
//   	    var buffer = new Buffer( self.outGoingFileChunkSize );
//    	    buffer.fill( 0x00 );
//    	    /* CCSDS MSG ID for sending pdu to space - 4093*/
//    	    buffer.writeUInt16BE( 4093, 0 );
//    	    /* Sequence Number */
//    	    buffer.writeUInt16BE( 1, 2 );
//    	    /* Pdu length*/
//    	    buffer.writeUInt16BE( self.outGoingFileChunkSize - 7, 4 );
//    	    /* Has no command code and sub code */
//    	    buffer.writeUInt8( 0, 6 );
//    	    buffer.writeUInt8( 0, 7 );
//
//    	    /* Copy buffer */
//    	    for ( var i = 0; i < bufferObj.length; i++ ) {
//    	      buffer.writeUInt8( bufferObj.pdu[ i ], 12 + i );
//    	    }
//
//    	    //this.instanceEmit( config.get( 'cfdpOutputStream' ), buffer );
//    	    this.logDebug( 'EventEnum.PDU_EVENTS, buffer' );
//        } );
//
//    	/* Init CFDP Engine */
//    	CfdpLib.AppInit();
//
//    	/* Set MIB parmeters from default config */
//    	//var mibParams = config.get( 'mibParameters' );
//    	//for ( var key in mibParams ) {
//    	//	  CfdpLib.SetMibParams( key, mibParams[ key ] );
//    	//}
//
//    	//this.instanceEmitter.on( config.get( 'CfdpClientStreamID' ), function( obj ) {
//    	//    self.handleClientRequest( obj );
//    	//  } );
//
//    	// this.instanceEmitter.on( config.get( 'cfdpInputStream' ), function( msg ) {
//    	    /* Send buffer to ground cfdp engine */
//    		//  CfdpLib.GivePdu( msg.payload, msg.payload.length );
//    	//} );
//
//    	/* Start Cycling Trasactions */
//    	CfdpLib.StartCycle();
//    	this.TransCycleStarted = true;
    	this.logInfo( 'Initialized engine' );
    };

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
     * Gets value of MIB parameter
     * @param  {Object} outData default response object
     * @param  {Objext} inData  input object
     * @return {Object}         response object
     */
    GetMibParams(outData, inData) {
        /* inData  is a list of arguments */
        if ( inData.length == 1 ) {
            if ( typeof( inData[ 0 ] ) == 'string' ) {
                outData.msg = "SUCCESS";
                outData.value = {}
                outData.value.mib_name = ( inData[ 0 ].toUpperCase() );
                outData.value.mib_value = cf.GetMibParams( inData[ 0 ] );
                if ( outData.value.mib_value == '' ) {
                    outData.msg = "FAILIURE";
                    outData.value.mib_value = undefined;
                }
            }
        }
        return outData;
    }

    /**
     * Sets MIB parameter
     * @param  {Object} outData default response object
     * @param  {Objext} inData  input object
     * @return {Object}         response object
     */
    SetMibParams(outData, inData) {
        if ( inData.length == 2 ) {
            if ( typeof( inData[ 0 ] ) == 'string' & typeof( inData[ 1 ] ) == 'string' ) {
                var resp = cf.SetMibParams( inData[ 0 ], inData[ 1 ] );
                if ( resp == 'PASS' ) {
                    outData.msg = "SUCCESS";
                } else {
                    outData.msg = "FAILIURE"
                }
            }
        }
        return outData;
    }

    /**
     * Restarts Transaction Cycle
     * @param  {Object} outData default response object
     * @param  {Objext} inData  input object
     * @return {Object}         response object
     */
    RestartEngine(outData, inData) {
        var self = this;
        if ( !self.TransCycleStarted ) {
            cf.StopCycle();
            cf.StartCycle();
            outData.msg = "SUCCESS";
            self.TransCycleStarted = true;
        } else {
            outData.msg = "FAILIURE";
        }
        return outData;
    }

    /**
     * Stops Transaction Cycle
     * @param  {Object} outData default response object
     * @param  {Objext} inData  input object
     * @return {Object}         response object
     */
    StopEngine( outData, inData ) {
        cf.StopCycle();
        self.TransCycleStarted = false;
        outData.msg = "SUCCESS";
        return outData;
    }

    /**
     * Sends files from ground to space
     * @param  {Object} outData default response object
     * @param  {Objext} inData  input object
     * @return {Object}         response object
     */
    SendFromGnd( outData, inData ) {
        if ( inData.length == 4 ) {
            if ( inData[ 0 ] <= 2 & typeof( inData[ 1 ] ) == 'string' & typeof( inData[ 2 ] ) == 'string' & typeof( inData[ 3 ] ) == 'string' ) {
                cf.RequestPdu( inData[ 0 ], inData[ 1 ], inData[ 2 ], inData[ 3 ] );
                outData.msg = "SUCCESS";
            }
        }
        return outData;
    }

    /**
     * Get Status Summary
     * @param  {Object} outData default response object
     * @param  {Objext} inData  input object
     * @return {Object}         response object
     */
    CGetSummaryStatus( outData, inData ) {
        outData.msg = "SUCCESS";
        outData.value = cf.GetSummaryStatus();
        return outData;
    }

    /**
     * Signals engine to send transaction status on callback.
     * @param  {Object} outData default response object
     * @param  {Objext} inData  input object
     * @return {Object}         response object
     */
    GetTransactionStatus( outData, inData ) {
        outData.msg = "FAILIURE";
        if ( inData.length == 2 ) {
            if ( typeof( inData[ 0 ] ) == "number" & typeof( inData[ 1 ] ) == "string" ) {
                var transIDObj = cf.GetIdFromString( inData[ 1 ] );
                cf.GetTransactionStatus( inData[ 0 ], transIDObj.length, new Buffer( transIDObj.value ) );
                outData.msg = "SUCCESS";
            }
        }
        return outData;
    }

    /**
     * Given a length will generate a string or a paragraph of that length
     * @param  {Number} len length of the requested string
     * @return {String}     response string
     */
    stringGen( len ) {
        var text = "";

        var charset = "abcdefghijklmnopqrstuvwxyz0123456789 \n\r";

        for ( var i = 0; i < len; i++ )
            text += charset.charAt( Math.floor( Math.random() * charset.length ) );

        return text;
    }

    /**
     * Makes necessary files to perform uplink test
     */
    makeTestCases() {
        var self = this;
        var fileCount = 0
        // console.log( 'heloo', self.testkit.numberOfFilesGenerated )

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
