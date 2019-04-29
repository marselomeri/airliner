'use strict';

var path = require('path');

const CdrFlightAppsPlugin = require(path.join(global.CDR_INSTALL_DIR, '/commander/classes/CdrFlightAppsPlugin')).CdrFlightAppsPlugin;

module.exports = class CfeCdrFlightAppsPlugin extends CdrFlightAppsPlugin {
    constructor() {
        super(path.join(__dirname, 'web'));

        var content = {
            ci: {
                shortDescription: 'Command Ingest',
                longDescription: 'Command Ingest.',
                nodes: {
				    main: {
					    type: CdrFlightAppsPlugin.ContentType.LAYOUT,
    					shortDescription: 'Main',
	                    longDescription: 'Main AMC.',
					    filePath: 'main_layout.lyt'
				    },
				    cdh: {
					    type: CdrFlightAppsPlugin.ContentType.PANEL,
					    shortDescription: 'Command and Data Handling',
					    longDescription: 'Command counters.',
					    filePath: 'cdh.pug'
				    },
				    hk: {
					    type: CdrFlightAppsPlugin.ContentType.PANEL,
					    shortDescription: 'CI Housekeeping',
					    longDescription: 'Command Ingest Housekeeping.',
					    filePath: 'hk.pug'
				    }
                }
            }
        };

    	this.addContent(content);
    }
};
