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
const emitter = require( 'events' );
const util = require( 'util' );
const convict = require( 'convict' );
const jp = require( 'jsonpath' );
const config = require( './config.js' );
const Sparkles = require( 'sparkles' );
const uuidV1 = require( 'uuid/v1' );
const path = require( 'path' );
const autoBind = require('auto-bind');
const CdrGroundPlugin = require(path.join(global.CDR_INSTALL_DIR, '/commander/classes/CdrGroundPlugin')).CdrGroundPlugin;


class VariableServer extends CdrGroundPlugin {
    /**
     * Constructor for variable server
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

        /* Initialize the configuration. */
        this.initConfig(configObj.name, configObj.configFile);
        
        /* Initialize server side housekeeping telemetry that we'll publish 
         * later. */
        this.initTelemetry();

        /* Initialize client side interface. */
        this.initClientInterface();

        /* Initialize server side commands. */
        this.initCommands();
        
        this.vars = {};
        this.subscribers = {};
        this.prevMsgRecv = 0;
        this.prevParamsUpdated = 0;
        this.prevParamsForwarded = 0;
        
        setInterval(function () {
        	self.hk.content.msgRecvPerSecond = self.hk.content.msgRecvCount - self.prevMsgRecv;
        	self.prevMsgRecv = self.hk.content.msgRecvCount;

        	self.hk.content.paramsUpdatedPerSecond = self.hk.content.paramsUpdated - self.prevParamsUpdated;
        	self.prevParamsUpdated = self.hk.content.paramsUpdated;

        	self.hk.content.paramsForwardedPerSecond = self.hk.content.paramsForwarded - self.prevParamsForwarded;
        	self.prevParamsForwarded = self.hk.content.paramsForwarded;
        }, 1000);

        
        this.namespace.recv( config.get( 'jsonInputStreamID' ), function( message ) {
            var vars = self.getVariablesFromMsgOpsName( message.opsPath );
            
            self.hk.content.msgRecvCount++;
            
            if ( self.isEmpty( vars ) == false ) {
                /* We have variables either persisted or subscribed to in this message.  Iterate through
                 * each variable that we're looking for.
                 */
                var currentDateAndTime = new Date();
                var subscribersToUpdate = {};

                var msgRoot = message.content;

                for ( var itemID in vars ) {
                    var variable = vars[ itemID ];
                    var varOpName = self.getVariableOpsName( itemID );
                    var valueObj = jp.query( msgRoot, '$.' + varOpName );

                    if ( self.isEmpty( valueObj ) == true ) {
                        self.logError('OpName ' + itemID + ' not found.' );
                    } else {
                        var value = valueObj[ 0 ];

                        self.hk.content.paramsUpdated++;
                        
                        /* Update the current value. */
                        if ( variable.hasOwnProperty( 'sample' ) == false ) {
                            variable.sample = [];
                        }
                        variable.sample.push( {
                            value: value,
                            msgTime: message.msgTime,
                            gndTime: currentDateAndTime
                        } );

                        /* Get the persistence value and set the array of retained values accordingly. */
                        var persistenceCount = self.getVariablePersistence( itemID );

                        if ( variable.sample.length > persistenceCount ) {
                            /* The array is too big.  We need to take the oldest sample out. */
                            variable.sample.shift();
                        }

                        /* Now loop through all the subscribers, if any. */
                        for ( var subscriberID in variable.subscribers ) {
                            /* First make sure this subscriber callback still exists. */
                            if ( subscribersToUpdate.hasOwnProperty( subscriberID ) == false ) {
                                /* This is the first time in this function call that we've
                                 * processed a variable for this particular subscriber.
                                 * Create a new subscriber record in this temporary
                                 * object.
                                 */
                                subscribersToUpdate[ subscriberID ] = {};
                            }
                            
                            subscribersToUpdate[subscriberID][itemID] = {sample: [ variable.sample[ variable.sample.length - 1 ] ]};
                            
                            self.hk.content.paramsForwarded++;
                        }
                    }
                }

                /* Lastly, loop through all the subscriptions to update, and send them
                 * an array of updates.
                 */
                for ( var subscriberID in subscribersToUpdate ) {
                	var callback = self.subscribers[subscriberID];
                	
                    /* Make sure this callback still exists. */
                    if ( typeof callback === 'function' ) {
                        callback( subscribersToUpdate[ subscriberID ]);                        
                    } else {
                        /* TODO:  Release this subscriber. */
                    }
                }
            }
            self.instanceEmit( config.get( 'outputEventsStreamID' ), 'message-received' );
        } );

        this.namespace.recv( config.get( 'varDefReqStreamID' ), function( req, cb ) {
            self.getTlmDefinitions( req, cb );
        } );

        this.namespace.recv( config.get( 'reqSubscribeStreamID' ), function( req, cb ) {
            if ( req.cmd === 'addSubscription' ) {
                if ( typeof req.opsPath === 'string' || req.opsPath instanceof String ) {
                    self.addSubscription( req.subscriberID, req.opsPath );
                } else if ( Array.isArray( req.opsPath ) ) {
                    for ( var i = 0; i < req.opsPath.length; ++i ) {
                        self.addSubscription( req.subscriberID, req.opsPath[ i ] );
                    }
                } else {
                    self.logError('Subscription request invalid. \'' + req + '\'' );
                }
            } else if ( req.cmd === 'removeSubscription' ) {
                if ( typeof req.opsPath === 'string' || req.opsPath instanceof String ) {
                    self.removeSubscription( req.subscriberID, req.opsPath, cb );
                } else if ( Array.isArray( req.opsPath ) ) {
                    for ( var i = 0; i < req.opsPath.length; ++i ) {
                        self.removeSubscription( req.subscriberID, req.opsPath[ i ], cb );
                    }
                } else {
                    self.logError( 'Unsubscribe request invalid. \'' + req + '\'' );
                }
            } else if ( req.cmd === 'addSubscriber' ) {
                var id = uuidV1();
                self.subscribers[ id ] = req.cb;
                cb( id );
                self.hk.content.subscribers++;
            } else if ( req.cmd === 'removeSubscriber' ) {
                self.hk.content.subscribers--;
                delete self.subscribers[ req.subscriberID ];
            } else {
                self.logError( 'Request invalid. \'' + req + '\'' );
            }
        } );

        var variables = config.get( 'variables' );
        if ( typeof variables !== 'undefined' ) {
            for ( var i = 0; i < variables.length; ++i ) {
                if ( typeof variables[ i ].persistence !== 'undefined' ) {
                    this.setVariablePersistence( variables[ i ].name, variables[ i ].persistence.count );
                }
            }
        }

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
    	
    	

    /**
     * Checks if a object is empty
     * @param  {Object}  obj object
     * @return {Boolean}     true if empty otherwise false
     */
    isEmpty( obj ) {
        if ( obj.length != undefined & typeof obj != 'string' ) {
            if ( obj.length == 0 ) {
                return true;
            } else {
                return false;
            }
        } else if ( typeof obj === 'object' ) {
            for ( var key in obj ) {
                if ( obj.hasOwnProperty( key ) )
                    return false;
            }
            return true;
        } else {
            return undefined;
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
    getOpNameFromPath( path ) {
        if ( typeof path === 'string' ) {
            var splitName = path.split( '/' );
            return splitName[ 2 ];
        }
        
        return undefined;
    }


    /**
     * Returns message operation path
     * @param  {String} path telemetry path
     * @return {String}      message operation path
     */
    getMessageOpsPath( path ) {
        var appName = this.getAppNameFromPath( path );
        var opName = this.getOpNameFromPath( path );
        if ( appName != undefined & opName != undefined ) {
            var msgOpsPath = '/' + appName + '/' + opName;
            return msgOpsPath;
        } else {
            return undefined
        }

    }


    /**
     * Parse and return variable operation name
     * @param  {String} path telemetry path
     * @return {String}      variable operation name
     */
    getVariableOpsName( path ) {
        if ( typeof path === 'string' ) {
            var splitName = path.split( '/' );
            return splitName[ 3 ];
        }
        return undefined;
    }


    /**
     * Parse and return varibles from message operation name
     * @param  {String} opsName operation name
     * @return {Object}         output variables
     */
    getVariablesFromMsgOpsName( opsName ) {
        var self = this;
        var outVars = {};
        for ( var opsPath in self.vars ) {
            var msgOpsName = self.getMessageOpsPath( opsPath );
            if ( msgOpsName == opsName ) {
                outVars[ opsPath ] = self.vars[ opsPath ];
            }
        }
        return outVars;
    }
    

    /**
     * Checks if varName is an array
     * @param  {String} varName variable name
     * @return {Boolean}        true if variable name is a array otherwise false
     */
    isVarNameAnArray( varName ) {
        if ( typeof varName == 'string' ) {
            var start = varName.indexOf( '[' );

            if ( start > 0 ) {
                var end = varName.indexOf( ']' );

                if ( end > start ) {
                    return true;
                }
            }
        }
        return false;
    }

    /**
     * Gets telemetry definitions and calls callback function on it
     * @param  {Object}   req telemetry definition request object
     * @param  {Function} cb  callback
     */
    getTlmDefinitions( req, cb ) {
        var self = this;
        this.instanceEmit( config.get( 'tlmDefReqStreamID' ), req, function( tlmDefs ) {
            if ( typeof tlmDefs === 'undefined' ) {
                cb( undefined );
            } else {
                if ( typeof tlmDefs.length === 'number' ) {
                    /* This must be an array. */
                    var outTlmDefs = [];
                    for ( var i = 0; i < tlmDefs.length; ++i ) {
                        var outTlmDef = tlmDefs[ i ];
                        outTlmDef.persistence = {};
                        outTlmDef.persistence.count = self.getVariablePersistence( tlmDefs[ i ].opsPath );
                        outTlmDef.timeout = self.getVariableTimeout( tlmDefs[ i ].opsPath );
                        outTlmDefs.push( outTlmDef );
                    }
                    cb( outTlmDefs );
                } else {
                    /* This is a single request. */
                    var outTlmDef = tlmDefs;
                    outTlmDef.persistence = {};
                    outTlmDef.persistence.count = self.getVariablePersistence( tlmDefs.opsPath );
                    outTlmDef.timeout = self.getVariableTimeout( tlmDefs.opsPath );
                    cb( outTlmDef );
                }
            }
        } );
    };


    /**
     * Add subscribers to variable (opsPath)
     * @param  {String}   opsPath operation path
     * @param  {Function} cb      callback
     */
    addSubscription( subscriberID, opsPath ) {
        if ( this.vars.hasOwnProperty( opsPath ) == false ) {
            /* We have not received this variable yet and it does
             * not already have a predefinition.  Create a new record. */
            var variable = {
                    opsPath: opsPath,
                    arrayIndices: {}
            };
            this.vars[ opsPath ] = variable;
        } else {
            /* We've already received this or have a predefinition. */
            var variable = this.vars[ opsPath ];

            /* Send however many values are currently persisted. */
            var outVar = {};
            outVar[ opsPath ] = {};
            
            /* Do we already have persisted values to send back? */
            if(variable.sample !== undefined) {
                if(variable.sample.legnth > 0) {
                    /* Yes.  Send all the persisted values of the value */
                    outVar[ opsPath ].sample = variable.sample;

                    this.subscribers[ subscriberID ]( outVar );
                }
            }
        }

        if ( variable.hasOwnProperty( 'subscribers' ) == false ) {
            variable[ 'subscribers' ] = {};
        }

        variable.subscribers[subscriberID] = subscriberID;
        this.hk.content.subscriptions++;
    }


    /**
     * Sets a persistence value to variable (opsPath)
     * @param  {String} opsPath operation path
     * @param  {Number} count   persistence count
     */
    setVariablePersistence( opsPath, count ) {
        if ( this.vars.hasOwnProperty( opsPath ) == false ) {
            /* We have not received this variable yet and it does
             * not already have a predefinition.  Create a new record. */
            var variable = {
                    opsPath: opsPath
            };
            this.vars[ opsPath ] = variable;
        } else {
            /* We've already received this or have a predefinition. */
            var variable = this.vars[ opsPath ];
        }

        if ( variable.hasOwnProperty( 'persistence' ) == false ) {
            /* We have not the persistence for this variable yet. */
            variable.persistence = {};
        }

        variable.persistence = {
                count: count
        };
    }


    /**
     * Gets a persistence value to variable (opsPath)
     * @param  {String} opsPath operation path
     */
    getVariablePersistence( opsPath ) {
        if ( this.vars.hasOwnProperty( opsPath ) == false ) {
            /* We have not received this variable yet and it does
             * not already have a predefinition.  Return the default of 1. */
            return 1;
        } else {
            /* We've already received this or have a predefinition. */
            if ( typeof this.vars[ opsPath ].persistence === 'undefined' ) {
                /* Persistence is not set.  Return the default of 1. */
                return 1;
            } else {
                return this.vars[ opsPath ].persistence.count;
            }
        }
    }


    /**
     * Sets a timeout value to variable (opsPath)
     * @param  {String} opsPath operation path
     * @param  {Number} timeout timeout value
     */
    setVariableTimeout( opsPath, timeout ) {
        if ( this.vars.hasOwnProperty( opsPath ) == false ) {
            /* We have not received this variable yet and it does
             * not already have a predefinition.  Create a new record. */
            var variable = {
                    opsPath: opsPath
            };
            this.vars[ opsPath ] = variable;
        } else {
            /* We've already received this or have a predefinition. */
            var variable = this.vars[ opsPath ];
        }

        if ( variable.hasOwnProperty( 'timeout' ) == false ) {
            /* We have not the timeout for this variable yet. */
            variable.timeout = {};
        }

        variable.timeout = timeout;
    }


    /**
     * Gets a timeout value to variable (opsPath)
     * @param  {String} opsPath operation path
     */
    getVariableTimeout( opsPath ) {
        if ( this.vars.hasOwnProperty( opsPath ) == false ) {
            /* We have not received this variable yet and it does
             * not already have a predefinition.  Return the default of 0. */
            return 0;
        } else {
            /* We've already received this or have a predefinition. */
            if ( typeof this.vars[ opsPath ].timeout === 'undefined' ) {
                /* Timeout is not set.  Return the default of 0. */
                return 0;
            } else {
                return this.vars[ opsPath ].timeout;
            }
        }
    }


    /**
     * Remove subscription for variable (opsPath) for associated callback
     * @param  {string}   opsPath operation path
     * @param  {Function} cb      callback function
     */
    removeSubscription( subscriberID, opsPath, cb ) {
        var variable = this.vars[ opsPath ];

        variable.subscribers[subscriberID] = undefined;
            
        /* TODO - Remove the callbacks. */
        //this.subscribers[ subscriberID ]( outVar );
    }


    /**
     * Emit data
     * @param  {String}   streamID stream id
     * @param  {String}   msg      emit message
     * @param  {Function} cb       callback
     */
    instanceEmit( streamID, msg, cb ) {
        this.namespace.send( streamID, msg, cb );
    }
    
    
    initTelemetry() {
        this.hk = {
            opsPath: '/' + config.name + '/hk',
            content: {
                cmdAcceptCount: 0,
                cmdRejectCount: 0,
                msgRecvCount: 0,
                msgRecvPerSecond: 0,
                paramsUpdated: 0,
                paramsUpdatedPerSecond: 0,
                subscribers: 0,
                subscriptions: 0,
                paramsForwarded: 0,
                paramsForwardedPerSecond: 0,
                inputStreamID: config.get( 'jsonInputStreamID' ),
                outputEventsStreamID: config.get( 'outputEventsStreamID' ),
                varDefReqStreamID: config.get( 'varDefReqStreamID' ),
                tlmDefReqStreamID: config.get( 'tlmDefReqStreamID' ),
                reqSubscribeStreamID: config.get( 'reqSubscribeStreamID' )
            }
        };
        this.addTelemetry(this.hk, 1000);
    }
    
    
    
    initClientInterface() {
        var content = {};
        
        content[config.name] = {
            shortDescription: 'Variable Server (' + config.name + ')',
            longDescription: 'Variable Server (' + config.name + ')',
            nodes: {
                main: {
                    type: CdrGroundPlugin.ContentType.LAYOUT,
                    shortDescription: 'Main',
                    longDescription: 'Main BAT.',
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
                subscriptions: {
                    type: CdrGroundPlugin.ContentType.PANEL,
                    shortDescription: 'Subscriptions',
                    longDescription: 'Subscriptions',
                    filePath: '/subscriptions.pug',
                    handlebarsContext: {
                        pluginName: config.name
                    }
                }
            }
        }
        
        this.addContent(content);
    }
    
    
    initCommands() {
    	var self = this;
    	
        var cmdResetDef = {
            opsPath: '/' + config.name + '/reset',
            args: []
        }
        this.addCommand(cmdResetDef, this.cmdReset);
        
        var cmdGetSubscribersDef = {
            opsPath: '/' + config.name + '/getSubscribers',
            returnType: 'Array',
            args: []
        }
        this.addCommand(cmdGetSubscribersDef, this.cmdGetSubscribers);
        
        var cmdGetSubscriptionsDef = {
            opsPath: '/' + config.name + '/getSubscriptions',
            returnType: 'Array',
            args: [
                {
                    name:    'SubscriberID',
                    type:    'char',
                    bitSize: 400
                }
            ]
        }
        this.addCommand(cmdGetSubscriptionsDef, this.cmdGetSubscriptions);
    }
    
    
    cmdReset(cmd) {
    	this.hk.content.cmdAcceptCount   = 0;
    	this.hk.content.cmdRejectCount   = 0;
    	this.hk.content.msgRecvCount     = 0;
    	this.hk.content.paramsUpdated    = 0;
    	this.hk.content.paramsForwarded  = 0;
    };
    
    
    cmdGetSubscribers(cmd, cb) {
    	var outSubscribers = [];
    	for(var subID in this.subscribers) {
    		outSubscribers.push(subID);
    	}
    	cb(outSubscribers)
    }
    
    
    cmdGetSubscriptions(cmd, cb) {
    	var outSubscriptions = [];

        for(var itemID in this.vars) {
        	for(var subscriberID in this.vars[itemID].subscribers) {
        		if(subscriberID === cmd.args.SubscriberID) {
            		outSubscriptions.push(itemID);
        		}
        	}
        }
    	
    	cb(outSubscriptions);
    }
};


exports = module.exports = VariableServer;