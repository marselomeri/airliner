'use strict';

var path = require('path');
var VideoServer = require('./video_server');

const CdrFlightAppsPlugin = require(path.join(global.CDR_INSTALL_DIR, '/commander/classes/CdrFlightAppsPlugin')).CdrFlightAppsPlugin;

module.exports = class CfeCdrFlightAppsPlugin extends CdrFlightAppsPlugin {
    constructor(config) {
        config.name = 'ak8963';
        config.webRoot = path.join( __dirname, 'web');  
        super(config);

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
    };

  
    getServerApp(commander) {
	    var videoServer = new VideoServer(commander);
	
	    return {name:'video-server', obj:videoServer};
    }
};
