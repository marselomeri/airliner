'use strict';

var path = require('path');

const CdrFlightAppsPlugin = require(path.join(global.CDR_INSTALL_DIR, '/commander/classes/CdrFlightAppsPlugin')).CdrFlightAppsPlugin;

module.exports = class CfeCdrFlightAppsPlugin extends CdrFlightAppsPlugin {
    constructor() {
        super(path.join(__dirname, 'web'));

        var content = {
            ak8963: {    		
                shortDescription: 'AK8963',
                longDescription: 'AK8963 Driver.',
                nodes: {
				    main: {
					    type: CdrFlightAppsPlugin.ContentType.LAYOUT,
					    shortDescription: 'Main',
					    longDescription: 'AK8963 Main.',
					    filePath: 'main.lyt'
				    },
				    hk: {
					    type: CdrFlightAppsPlugin.ContentType.PANEL,
					    shortDescription: 'AK8963 HK',
					    longDescription: 'AK8963 Housekeeping.',
					    filePath: 'hk.pug'
				    },
				    diag: {
					    type: CdrFlightAppsPlugin.ContentType.PANEL,
					    shortDescription: 'AK8963 Diagnostics',
					    longDescription: 'AK8963 Diagnostics.',
					    filePath: 'diag.pug'
				    }
                }
            }
        };
        
      	this.addContent(content);
    };
};
