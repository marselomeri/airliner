'use strict';

var path = require('path');

const CdrFlightAppsPlugin = require(path.join(global.CDR_INSTALL_DIR, '/commander/classes/CdrFlightAppsPlugin')).CdrFlightAppsPlugin;

module.exports = class CfeCdrFlightAppsPlugin extends CdrFlightAppsPlugin {
    constructor(config) {
        config.name = 'VC';
        config.webRoot = path.join( __dirname, 'web');  
        super(config);
        
        this.config = config;
        
    	var self = this;

        /* Initialize client side interface. */
        this.initClientInterface();
    };

  
    getServerApp(commander) {
        var videoServer = new VideoServer(commander);
	
        return {name:'video-server', obj:videoServer};
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
                    }
                }
            }
        };
        
      	this.addContent(content);
    }    
};
