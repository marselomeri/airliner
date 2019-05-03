'use strict';

var path = require('path');

const CdrFlightAppsPlugin = require(path.join(global.CDR_INSTALL_DIR, '/commander/classes/CdrFlightAppsPlugin')).CdrFlightAppsPlugin;

module.exports = class CfeCdrFlightAppsPlugin extends CdrFlightAppsPlugin {
    constructor(config) {
        config.name = 'ea';
        config.webRoot = path.join( __dirname, 'web');  
        super(config);
        
        var content = {
            ea: {
                shortDescription: 'External Application',
                longDescription: 'External Application',
                nodes: {
				    main: {
					    type: CdrFlightAppsPlugin.ContentType.LAYOUT,
					    shortDescription: 'Main',
					    longDescription: 'Main AMC.',
					    filePath: 'main_layout.lyt'
				    },
				    hk: {
					    type: CdrFlightAppsPlugin.ContentType.PANEL,
					    shortDescription: 'EA HK',
					    longDescription: 'External Application Housekeeping',
					    filePath: 'hk.pug'
				    }
                }
            }
        };

      	this.addContent(content);
    }
};
