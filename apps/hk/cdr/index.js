'use strict';

var path = require('path');

const CdrFlightAppsPlugin = require(path.join(global.CDR_INSTALL_DIR, '/commander/classes/CdrFlightAppsPlugin')).CdrFlightAppsPlugin;

module.exports = class CfeCdrFlightAppsPlugin extends CdrFlightAppsPlugin {
    constructor(urlBase) {
        super(path.join(__dirname, 'web'));

        var content = {
        	hk: {
                shortDescription: 'Housekeeping',
                longDescription: 'Housekeeping',
                nodes: {
				    main: {
					    type: CdrFlightAppsPlugin.ContentType.LAYOUT,
					    shortDescription: 'Main',
					    longDescription: 'Main HK.',
					    filePath: 'main_layout.lyt'
				    },
				    hk: {
					    type: CdrFlightAppsPlugin.ContentType.PANEL,
					    shortDescription: 'HK HK',
					    longDescription: 'Housekeeping Housekeeping',
					    filePath: 'hk.pug'
				    }
                }
            }
        };
        
      	this.addContent(content);
    }
};
