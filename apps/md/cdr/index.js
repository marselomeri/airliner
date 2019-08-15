'use strict';

var path = require( 'path' );

const CdrFlightAppsPlugin = require( path.join( global.CDR_INSTALL_DIR, '/commander/classes/CdrFlightAppsPlugin' ) ).CdrFlightAppsPlugin;

module.exports = class CfeCdrFlightAppsPlugin extends CdrFlightAppsPlugin {
    constructor(config) {
        config.name = 'md';
        config.webRoot = path.join( __dirname, 'web');  
        super(config);
    
        var content = {
        	md: {
                shortDescription: 'Memory Dwell',
                longDescription: 'Memory Dwell.',
                nodes: {
                    main: {
                        type: CdrFlightAppsPlugin.ContentType.LAYOUT,
                        shortDescription: 'Main',
                        longDescription: 'Main VM.',
                        filePath: 'main_layout.lyt'
                    },
                    cdh: {
                        type: CdrFlightAppsPlugin.ContentType.PANEL,
                        shortDescription: 'Command and Data Handling',
                        longDescription: 'Command counters.',
                        filePath: 'cdh.pug'
                    },
                    stats: {
                        type: CdrFlightAppsPlugin.ContentType.PANEL,
                        shortDescription: 'Stats',
                        longDescription: 'MD Stats.',
                        filePath: 'stats.pug'
                    }
                }
        	}
        };
        
      	this.addContent(content);
    };
};
