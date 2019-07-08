'use strict';

var path = require('path');

const CdrFlightAppsPlugin = require(path.join(global.CDR_INSTALL_DIR, '/commander/classes/CdrFlightAppsPlugin')).CdrFlightAppsPlugin;

module.exports = class CfeCdrFlightAppsPlugin extends CdrFlightAppsPlugin {
    constructor(config) {
        config.name = 'sc';
        config.webRoot = path.join( __dirname, 'web');  
        super(config);

        var content = {
            sc: {    		
                shortDescription: 'Stored Command',
                longDescription: 'Stored Command.',
                nodes: {
                    main: {
                        type: CdrFlightAppsPlugin.ContentType.LAYOUT,
                        shortDescription: 'Main',
                        longDescription: 'Main VM.',
                        filePath: '/main_layout.lyt'
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
                        longDescription: 'General',
                        filePath: '/gen.pug'
                    },
                    ats: {
                        type: CdrFlightAppsPlugin.ContentType.PANEL,
                        shortDescription: 'ATS',
                        longDescription: 'ATS General.',
                        filePath: '/ats.pug'
                    },
                    rts: {
                        type: CdrFlightAppsPlugin.ContentType.PANEL,
                        shortDescription: 'RTS',
                        longDescription: 'RTS General.',
                        filePath: '/rts.pug'
                    },
                    rts_1_32: {
                        type: CdrFlightAppsPlugin.ContentType.PANEL,
                        shortDescription: 'RTS Status (1-32)',
                        longDescription: 'RTS Status.',
                        filePath: '/rts_1_32.pug'
                    },
                    rts_33_64: {
                        type: CdrFlightAppsPlugin.ContentType.PANEL,
                        shortDescription: 'RTS Status (33-64)',
                        longDescription: 'RTS Status.',
                        filePath: '/rts_33_64.pug'
				    }
                }
            }
        };
      
        this.addContent(content);
    };
};
