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
var EventEmitter = require( 'events' );
var fs = require( 'fs' );
const dgram = require( 'dgram' );
const util = require( 'util' );
var protobuf = require( 'protobufjs' );
var mergeJSON = require( 'merge-json' );
var convict = require( 'convict' );
var socket_io = require( 'socket.io' );
var CommanderInstance = require( './commander_instance.js' );
var CommanderApp = require( './commander_app.js' );
var path = require( 'path' );
const http = require( 'http' );
const autoBind = require('auto-bind');
const ContentTypeEnum = require( './classes/CdrPlugin.js' ).ContentTypeEnum;
const { createLogger, format, transports } = require('winston');
const { combine, timestamp, label, printf } = format;

var emit = EventEmitter.prototype.emit;

/**
 * Count listeners
 * @type {Function}
 */
var listenerCount = EventEmitter.listenerCount ||
  function( emitter, type ) {
    return emitter.listeners( type ).length
  }

var publicFunctions = [
  'getDirectoryListing',
  'getCmdDef',
  'getTlmDefs',
  'sendCommand',
  'getPanels',
  'getLayouts',
  'getWidgets',
  'getDefaultLayout',
  'getADSBJson',
  'queryConfigDB'
];

var config = require( './config.js' );

const ROOT_INSTANCE_NAME = 'ROOT';


/**
 * Constructor for commander
 * @param       {String} workspace  path to commander workspace
 * @param       {String} configFile path to commander-config.json
 * @constructor
 */

module.exports = class Commander extends EventEmitter {
    constructor(workspace, configFile) {
        super();
        
        autoBind(this);
        
        this.workspace = workspace;
        this.instances = {};
        var self = this;
        this.registeredFunctions = [];
        this.registeredStreams = [];
        
        const LoggerConsoleFormat = printf(function({ level, namespace, plugin, message, data, timestamp }) {
            var output = '';

            output += `${timestamp} [`;
            
            if(typeof namespace !== 'undefined') {
                output += `${namespace}`;
            }
            
            output += `:`;
            
            if(typeof plugin !== 'undefined') {
                output += `${plugin}`;
            }
            
            output += `] ${level}: `;
            
            if(typeof data !== 'undefined') {
                output += `<DATA> `;
            }
            
            if(typeof message !== 'undefined') {
                output += `${message}`;
            }
            
            return output;
        });
        
        this.Logger = createLogger({
            level: 'info',
            format: format.combine(
                format.timestamp({
                    format: 'YYYY-MM-DD HH:mm:ss'
                }),
                format.errors({ stack: true }),
                format.splat()
            ),
            defaultMeta: { 
            },
            transports: [
                //
                // - Write to all logs with level `info` and below to `combined.log`
                // - Write all logs error (and below) to `error.log`.
                //
                new transports.File({ filename: 'quick-start-error.log', level: 'error' }),
                new transports.File({ filename: 'quick-start-combined.log' })
            ]
        });

        //
        // If we're not in production then **ALSO** log to the `console`
        // with the colorized simple format.
        //
        if (process.env.NODE_ENV !== 'production') {
            this.Logger.add(new transports.Console({
                format: format.combine(
                    format.colorize(),
                    LoggerConsoleFormat
                )
            }));
        }

        /* Load environment dependent configuration */
        config.loadFile( configFile );

        /* Perform validation */
        config.validate( {
            allowed: 'strict'
        } );

        /* Add the root instance. */
        this.addInstance( ROOT_INSTANCE_NAME );

        var cfgInstances = config.get( 'instances' );

        for ( var i = 0; i < cfgInstances.length; ++i ) {
            this.instances[ cfgInstances[ i ].name ] = new CommanderInstance( this, cfgInstances[ i ] );
        }

        //Socket.io
        var io = socket_io();
        global.NODE_APP.io = io;

        io.on( 'connection', function( socket ) {
            socket.enabledStreams = [];

            self.subscribe( updateTelemetry, function( subscriberID ) {
                socket.subscriberID = subscriberID;
            } );


            socket.on( 'connect_error', function( err ) {
                self.Logger.log({
                    level:              'debug',
                    message:             message
                });
                self.Logger.info( 'SocketIO: Socket connect error.  \'' + err + '\'' );
            } );

            socket.on( 'connect_timeout', function() {
                self.logError( 'SocketIO: Socket timeout.' );
            } );

            socket.on( 'reconnect', function( num ) {
                self.Logger.info( 'SocketIO: Socket successfully reconnected on attempt # \'' + num + '\'.' );
            } );

            socket.on( 'reconnect_attempt', function() {
                self.Logger.info( 'SocketIO: Socket reconnect attempt.' );
            } );

            socket.on( 'reconnecting', function( num ) {
                self.Logger.info( 'SocketIO: Socket reconnecting attempt # \'' + num + '\'.' );
            } );
        
            socket.on( 'reconnect_error', function( err ) {
                self.Logger.error( 'SocketIO: Socket reconnect error.  \'' + err + '\'.' );
            } );

            socket.on( 'reconnect_failed', function() {
                self.Logger.error( 'SocketIO: Socket reconnect failed.' );
            } );
        
            socket.on( 'disconnect', function( err ) {
                self.Logger.info( 'SocketIO: Socket ' + socket.id + ' disconnected.' );
                socket.removeAllListeners();
                self.removeSubscriber( socket.subscriberID );
                socket.disconnect( true );
            } );
        
            socket.on( 'ping', function() {
                self.Logger.debug( 'SocketIO: Socket ping.' );
            } );
        
            socket.on( 'pong', function( latency ) {
                self.Logger.debug( 'SocketIO: Socket pong (' + latency + ' ms).' );
            } );
        
            socket.on( 'subscribe', function( opsPaths ) {
                self.addSubscription( socket.subscriberID, opsPaths );
            } );
        
            socket.on( 'unsubscribe', function( opsPaths ) {
                self.removeSubscription( socket.subscriberID, opsPaths );
            } );
        
            socket.on( 'enable-stream', function( streamName ) {
                socket.enabledStreams[ streamName ] = true;
            } );
        
            socket.on( 'disable-stream', function( streamName ) {
                socket.enabledStreams[ streamName ] = false;
            } );
        
            socket.on( 'sendCmd', function( cmdObj, cb ) {
                self.sendCmd( cmdObj, cb);              
            } );
        
            socket.on( 'PING', function( startTime ) {
                socket.emit( 'PONG', startTime );
            } );
        
            socket.on( 'pluginFunction', function( pluginName, funcName, args, cb ) {
                for ( var i in self.registeredFunctions ) {
                    if ( self.registeredFunctions[ i ].pluginName === pluginName ) {
                        if ( self.registeredFunctions[ i ].funcName === funcName ) {
                            if ( typeof self.registeredFunctions[ i ].cb === 'function' ) {
                                self.registeredFunctions[ i ].cb( args, function( results ) {
                                    cb( results );
                                } );
                            }
                        }
                    }
                }
            } );
            
            var onevent = socket.onevent;
            socket.onevent = function (packet) {
                var args = packet.data || {};
                onevent.call(this, packet);
                packet.data = ['*'].concat(args);
                onevent.call(this, packet);
            }
        
            socket.on( '*', function( funcName, args, cb ) {    	
                for ( var i in self.registeredFunctions ) {
                    if ( self.registeredFunctions[ i ].funcName === funcName ) {
                        if ( typeof self.registeredFunctions[ i ].cb === 'function' ) {
                            self.registeredFunctions[ i ].cb( args, function( results ) {
                                cb( results );
                                      } );
                        };
                    }
                }
            });
        
        
            function updateTelemetry( update ) {
                socket.emit( 'telemetry-update', update );
            }

            for ( var i in self.registeredStreams ) {
                var streamName = self.registeredStreams[ i ].streamName;
                self.defaultInstance.recv( streamName, function( newData ) {
                    var stream = socket.enabledStreams[ streamName ];
                    if ( typeof stream === 'boolean' ) {
                        if ( stream === true ) {
                            socket.volatile.emit( streamName, newData );
                        }
                    }
                } );
            };
        
            for ( var i in publicFunctions ) {
                ( function( funcName ) {
                    socket.on( funcName, function() {
                        var cb = arguments[ arguments.length - 1 ];
                        self.Logger.debug( 'SocketIO: ' + funcName );
                        if ( typeof self[ funcName ] !== 'function' ) {
                            self.Logger.error( 'Invalid function' );
                        } else {
                            self[ funcName ].apply( self, arguments );
                        }
                    } );
                } )( publicFunctions[ i ] );
            }
        });
        
        self.Logger.info('Commander initialized');
    }


    /**
     * Sets a default commander instance
     * @param  {Object} instance instance object
     */
    setDefaultInstance( instance ) {
        var self = this;
        this.defaultInstance = instance;

        this.defaultInstance.recv( 'advertise-stream', function( streamName ) {
            self.registeredStreams.push( {
                streamName: streamName
            } );
        } );
    }

    /**
     * Get panels by path
     * @param  {String} paths     directory path
     * @param  {Object} panelsObj panel object
     */
    getPanelsByPath( paths, panelsObj ) {
        if ( paths.length == 1 ) {
            var targetPath = paths[ 0 ];
            if ( targetPath === '' ) {
                return panelsObj;
            } else {
                var targetObj = panelsObj[ targetPath ];
                if ( typeof targetObj === 'object' ) {
                    var nodes = targetObj.nodes;
                    var outNodes = {};
                    for ( var nodeID in nodes ) {
                        if ( typeof nodes[ nodeID ].type !== 'undefined' ) {
                            if ( nodes[ nodeID ].type === ContentTypeEnum.PANEL ) {
                                outNodes[ nodeID ] = nodes[ nodeID ];
                            }
                        } else {
                            outNodes[ nodeID ] = nodes[ nodeID ];
                            }
                    }
                    return outNodes;
                }
            }
        } else {
            var targetPath = paths[ 0 ];
            var targetObj = panelsObj[ targetPath ];
            if ( typeof targetObj === 'object' ) {
                var nodes = targetObj.nodes;
                paths.shift();
                return this.getPanelsByPath( paths, nodes );
            }
        }
    }


    registerFunction( pluginName, cb ) {
        this.registeredFunctions.push( {
            pluginName: pluginName,
            funcName: cb.name,
            cb: cb
        } );
    }


    registerStreams( streamName ) {
        this.registeredStreams.push( {
            streamName: streamName
        } );
    }


    /**
     * Get layout by path
     * @param  {String} paths     directory path
     * @param  {Object} layoutsObj layout object
     */
    getLayoutsByPath( paths, layoutsObj ) {
        if ( paths.length == 1 ) {
            var targetPath = paths[ 0 ];
            if ( targetPath === '' ) {
                return layoutsObj;
            } else {
                var targetObj = layoutsObj[ targetPath ];
                if ( typeof targetObj === 'object' ) {
                    var nodes = targetObj.nodes;
                    var outNodes = {};
                    for ( var nodeID in nodes ) {
                        if ( typeof nodes[ nodeID ].type !== 'undefined' ) {
                            if ( nodes[ nodeID ].type === ContentTypeEnum.LAYOUT ) {
                                outNodes[ nodeID ] = nodes[ nodeID ];
                            }
                        } else {
                            outNodes[ nodeID ] = nodes[ nodeID ];
                        }
                    }
                    return outNodes;
                }
            }
        } else {
            var targetPath = paths[ 0 ];
            var targetObj = layoutsObj[ targetPath ];
            if ( typeof targetObj === 'object' ) {
                var nodes = targetObj.nodes;
                paths.shift();
                return this.getLayoutsByPath( paths, nodes );
            }
        }
    }

    /**
     * Get panels by widget
     * @param  {String} paths     directory path
     * @param  {Object} panelsObj panel object
     */
    getWidgetsByPath( paths, panelsObj ) {
        if ( paths.length == 1 ) {
            var targetPath = paths[ 0 ];
            
            if ( targetPath === '' ) {
                return panelsObj;
            } else {
                var targetObj = panelsObj[ targetPath ];
                if ( typeof targetObj === 'object' ) {
                    var nodes = targetObj.nodes;
                    var outNodes = {};
                    for ( var nodeID in nodes ) {
                        if ( typeof nodes[ nodeID ].type !== 'undefined' ) {
                            if ( nodes[ nodeID ].type === ContentTypeEnum.WIDGET ) {
                                outNodes[ nodeID ] = nodes[ nodeID ];
                            }
                        } else {
                            outNodes[ nodeID ] = nodes[ nodeID ];
                        }
                    }
                    return outNodes;
                }
            }
        } else {
            var targetPath = paths[ 0 ];
            var targetObj = panelsObj[ targetPath ];
            if ( typeof targetObj === 'object' ) {
                var nodes = targetObj.nodes;
                paths.shift();
                return this.getWidgetsByPath( paths, nodes );
            }
        }
    }

    /**
     * Gets panels
     * @param  {String}   inPath input path
     * @param  {Function} cb     callback
     */
    getPanels( inPath, cb ) {
        var outObj = {};

        var paths = inPath.split( '/' );

        paths.shift();
        var content = this.getPanelsByPath( paths, global.CONTENT_TREE );

        cb( content );
    }

    /**
     * Gets default layout configuration
     * @param  {Function} cb callback on response
     */
    getDefaultLayout( cb ) {
        /* is a stub needs to go in some configuration */
        var layout = fs.readFileSync( global.CDR_WORKSPACE + '/plugins/cfe/web/pilot/main_layout.lyt' );
        cb( JSON.parse( layout ) );
    }

    /******************* STUBS ********************************************/
    /**
     * Gets ADSB data in JSON (stub)
     * @param  {Function} cb Callback
     */
    getADSBJson( cb ) {
        http.get( 'http://127.0.0.1:8080/dump1090/data.json', function(resp) {
            var data = ''
                resp.on( 'data', function(chunk) {
                    data += chunk;
                } );
            resp.on( 'end', function() {
                cb( JSON.parse( data ) );
            } );
        } ).on( 'error', function(e) {
            this.logError( `${e.message}` );
        } );
    }

    /******************* STUBS ********************************************/
    /**
     * Gets layout
     * @param  {String}   inPath input path
     * @param  {Function} cb     callback
     */
    getLayouts( inPath, cb ) {
        var outObj = {};

        var paths = inPath.split( '/' );

        paths.shift();

        var content = this.getLayoutsByPath( paths, global.CONTENT_TREE );

        cb( content );
    }

    /**
     * Gets widget
     * @param  {String}   inPath input path
     * @param  {Function} cb     callback
     */
    getWidgets( inPath, cb ) {
        var outObj = {};

        var paths = inPath.split( '/' );

        paths.shift();

        var content = this.getWidgetsByPath( paths, global.CONTENT_TREE );

        cb( content );
    }

    /**
     * Query configuration database
     * @param  {String}   inPath input path
     * @param  {Function} cb     callback
     */
    queryConfigDB( inPath, cb ) {
        if ( typeof this.defaultInstance.send === 'function' & typeof inPath == 'string' ) {
            this.defaultInstance.send( config.get( 'queryConfigStreamID' ), inPath, function( resp ) {
                cb( resp );
            } );
        };
    }


    /**
     * Gets command definition
     * @param  {Object}   cmdObj command object
     * @param  {Function} cb     callback
     */
    getCmdDef( cmdObj, cb ) {
        if ( typeof this.defaultInstance.send === 'function' ) {
            if ( typeof cmdObj == 'object' && cmdObj.hasOwnProperty( 'name' ) ) {
                this.defaultInstance.send( config.get( 'cmdDefReqStreamID' ), {
                    opsPath: cmdObj.name
                }, function( resp ) {
                    cb( resp );
                } );
            }
        };
    }

    /**
     * Gets telemetry definitions
     * @param  {Object}   tlmObjs telemetry object
     * @param  {Function} cb      callback
     */
    getTlmDefs( tlmObjs, cb ) {
        if ( typeof this.defaultInstance.send === 'function' && typeof tlmObjs == 'object' ) {
            this.defaultInstance.send( config.get( 'varDefReqStreamID' ), tlmObjs, function( resp ) {
                cb( resp );
            } );
        };
    }

    /**
     * Passes 'sendCommand' string into callback
     * @param  {Function} cb callback
     */
    sendCommand( cb ) {
        cb( 'sendCommand' );
    }
    

    /**
     * Sends command name and arguments
     * @param  {String} cmdName command name
     * @param  {Object} args    argument object
     */
    sendCmd( cmdName, cb ) {
        if ( cmdName.hasOwnProperty( 'ops_path' ) ) {
            this.defaultInstance.send( config.get( 'cmdSendStreamID' ), cmdName, cb );
        }
    }


    /**
     * Subscribe to telemetry server
     * @param  {String}   varName telemetry name
     * @param  {Function} cb      callback
     */
    subscribe( updateCallback, cb ) {
        var self = this;
        this.defaultInstance.send( config.get( 'reqSubscribeStreamID' ), {
            cmd: 'addSubscriber',
            cb: updateCallback
        }, function( subscriberID ) {
            cb( subscriberID );
        } );
    }


    /**
     * Subscribe to telemetry
     * @param  {String}   varName telemetry name
     * @param  {Function} cb      callback
     */
    addSubscription( subscriberID, varName ) {
        var self = this;
        if ( typeof varName == 'object' ) {
            this.defaultInstance.send( config.get( 'reqSubscribeStreamID' ), {
                cmd: 'addSubscription',
                subscriberID: subscriberID,
                opsPath: varName
            } );
        }
    }


    /**
     * Unsubscribe from telemetryCommanderInstance
     * @param  {String}   varName telemetry name
     * @param  {Function} cb      callback
     */
    removeSubscription( subscriberID, varName ) {
        var self = this;
        if ( typeof varName == 'object' ) {
            this.defaultInstance.send( config.get( 'reqSubscribeStreamID' ), {
                cmd: 'removeSubscription',
                subscriberID: subscriberID,
                opsPath: varName
            } );
        }
    }


    /**
     * Unsubscribe from telemetry server
     * @param  {String}   varName telemetry name
     * @param  {Function} cb      callback
     */
    removeSubscriber( subscriberID ) {
        var self = this;
        this.defaultInstance.send( config.get( 'reqSubscribeStreamID' ), {
            cmd: 'removeSubscriber',
            subscriberID: subscriberID
        } );
    }


    /**
     * Add instance to commander
     * @param  {String}   name instance name
     * @param  {Function} cb   callback
     */
    addInstance( name, cb ) {
        this.instances[ name ] = new CommanderInstance( name, this );

        if ( typeof cb === 'function' ) {
            cb( this.instances[ name ] );
        };
    }

    

    /**
     * Log error events
     * @param  {String} text    text
     */
    logError(namespace, plugin, message, data) {        
        this.Logger.log({
            level:      'error',
            message:    message,
            namespace:  namespace,
            plugin:     plugin, 
            data:       data
        });
    }


    /**
     * Log warn events
     * @param  {String} text    text
     */
    logWarn(namespace, plugin, message, data) {
        this.Logger.log({
            level:      'warn',
            message:    message,
            namespace:  namespace,
            plugin:     plugin, 
            data:       data
        });
    }


    /**
     * Log info events
     * @param  {String} text    text
     */
    logInfo(namespace, plugin, message, data) {
        this.Logger.log({
            level:      'info',
            message:    message,
            namespace:  namespace,
            plugin:     plugin, 
            data:       data
        });
    }


    /**
     * Log verbose events
     * @param  {String} text    text
     */
    logVerbose(namespace, plugin, message, data) {
        this.Logger.log({
            level:      'verbose',
            message:    message,
            namespace:  namespace,
            plugin:     plugin, 
            data:       data
        });
    }


    /**
     * Log debug events
     * @param  {String} text    text
     */
    logDebug(namespace, plugin, message, data) {
        this.Logger.log({
            level:      'debug',
            message:    message,
            namespace:  namespace,
            plugin:     plugin, 
            data:       data
        });
    }
}