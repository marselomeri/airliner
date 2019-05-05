'use strict';

var path = require('path');
const dgram = require( 'dgram' );

const CdrFlightAppsPlugin = require(path.join(global.CDR_INSTALL_DIR, '/commander/classes/CdrFlightAppsPlugin')).CdrFlightAppsPlugin;

module.exports = class CfeCdrFlightAppsPlugin extends CdrFlightAppsPlugin {
    constructor(config) {
        config.name = 'vc';
        config.webRoot = path.join( __dirname, 'web');  
        super(config);
        
        this.config = config;
        
    	var self = this;
        
        /* Initialize server side housekeeping telemetry that we'll publish 
         * later. */
        this.initTelemetry();

        /* Initialize client side interface. */
        this.initClientInterface();

        /* Initialize server side commands. */
        this.initCommands();
        
        /* Initialize video server. */
        this.initServer();
    };

  
    getServerApp(commander) {
	    var videoServer = new VideoServer(commander);
	
	    return {name:'video-server', obj:videoServer};
    }
    
    
    initTelemetry() {
        this.hk = {
            opsPath: '/' + this.config.name + '/hk',
            content: {
                cmdAcceptCount: 0,
                cmdRejectCount: 0,
                framesReceived: 0,
                serverEnabled: 0
            }
        };
        this.addTelemetry(this.hk, 1000);
    }

    
    initClientInterface() {        
    	var content = {
            vc: {    	
                shortDescription: 'Video Control',
                longDescription: 'Video Control Manager.',
                nodes: {
                    main: {
                        type: CdrFlightAppsPlugin.ContentType.LAYOUT,
                        shortDescription: 'Main',
                        longDescription: 'Main VC.',
                        filePath: 'main.lyt'
                    },
                    cdh: {
                        type: CdrFlightAppsPlugin.ContentType.PANEL,
                        shortDescription: 'Command and Data Handling',
                        longDescription: 'Command counters.',
                        filePath: 'cdh.pug'
                    },
                    viewer: {
                        type: CdrFlightAppsPlugin.ContentType.PANEL,
                        shortDescription: 'Viewer',
                        longDescription: 'Video viewer.',
                        filePath: 'viewer.pug'
                    }
                }
            }
        };
        
      	this.addContent(content);
    }
    
    
    initCommands() {
    	var self = this;
    	
        var cmdReset = {
            opsPath: '/' + this.config.name + '/reset',
            args: []
        }
        this.addCommand(cmdReset, function(cmd) {
        	self.hk.content.cmdAcceptCount = 0;
        	self.hk.content.cmdRejectCount = 0;
        	self.hk.content.framesReceived = 0;
        });
    }
    
  
    initServer() {
        this.socket = dgram.createSocket( 'udp4' );

        this.socket.on( 'error', ( err ) => {
          console.log( `server error:\n${err.stack}` );
          this.socket.close();
        } );

        this.socket.on( 'message', ( frame, info ) => {
          var imageObject = {
            image: true,
            buffer: frame.toString( 'base64' )
          }
          this.namespace.emit( 'video-stream', imageObject );

          //socket.volatile.emit( 'stream', {
          //  image: true,
          //  buffer: msg.toString( 'base64' )
          //} );
        } );

        this.socket.bind( 3001 );

        global.NODE_APP.videoServer = this.socket;

        this.namespace.emit( 'advertise-stream', 'video-stream' );
    }
};
