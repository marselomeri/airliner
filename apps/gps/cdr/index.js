'use strict';

var path = require('path');

const CdrFlightAppsPlugin = require(path.join(global.CDR_INSTALL_DIR, '/commander/classes/CdrFlightAppsPlugin')).CdrFlightAppsPlugin;

module.exports = class CfeCdrFlightAppsPlugin extends CdrFlightAppsPlugin {
    constructor() {
        super(path.join(__dirname, 'web'));

        var content = {
        	gps: {
                shortDescription: 'GPS Driver',
                longDescription: 'GPS Driver.',
                nodes: {
				    main: {
					    type: CdrFlightAppsPlugin.ContentType.LAYOUT,
					    shortDescription: 'Main',
					    longDescription: 'Main GPS.',
					    filePath: 'main_layout.lyt'
				    },
				    cdh: {
					    type: CdrFlightAppsPlugin.ContentType.PANEL,
					    shortDescription: 'Command and Data Handling',
					    longDescription: 'Command counters.',
					    filePath: 'cdh.pug'
				    },
                    gps: {
                        type: CdrFlightAppsPlugin.ContentType.PANEL,
                        shortDescription: 'Vehicle GPS',
                        longDescription: 'Vehicle Global Position',
                        filePath: 'gps.pug'
                    }
                }
        	}
        };
        
      	this.addContent(content);
    }
};
