'use strict';

var path = require( 'path' );

const CdrFlightAppsPlugin = require( path.join( global.CDR_INSTALL_DIR, '/commander/classes/CdrFlightAppsPlugin' ) ).CdrFlightAppsPlugin;

module.exports = class CfeCdrFlightAppsPlugin extends CdrFlightAppsPlugin {
    constructor(config) {
        config.name = 'mm';
        config.webRoot = path.join( __dirname, 'web');  
        super(config);
    
        var content = {
        	mm: {
                shortDescription: 'Memory Manager',
                longDescription: 'Memory Manager.',
                nodes: {
                    main: {
                        type: CdrFlightAppsPlugin.ContentType.LAYOUT,
                        shortDescription: 'Main',
                        longDescription: 'Main MM.',
                        filePath: 'main.lyt'
                    },
                    cdh: {
                        type: CdrFlightAppsPlugin.ContentType.PANEL,
                        shortDescription: 'Command and Data Handling',
                        longDescription: 'Command counters.',
                        filePath: '/cdh.pug'
                    },
                    gen: {
                        type: CdrFlightAppsPlugin.ContentType.PANEL,
                        shortDescription: 'General',
                        longDescription: 'General.',
                        filePath: '/gen.pug'
                    }
                }
        	}
        };
        
      	this.addContent(content);
    };
};
