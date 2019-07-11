'use strict';

var path = require('path');

const CdrFlightAppsPlugin = require(path.join(global.CDR_INSTALL_DIR, '/commander/classes/CdrFlightAppsPlugin')).CdrFlightAppsPlugin;

module.exports = class CfeCdrFlightAppsPlugin extends CdrFlightAppsPlugin {
    constructor(config) {
        config.name = 'vm';
        config.webRoot = path.join( __dirname, 'web');  
        super(config);

        var content = {
            vm: {    		
                shortDescription: 'Vehicle Manager',
                longDescription: 'Vehicle State Manager.',
                nodes: {
                    main: {
                        type: CdrFlightAppsPlugin.ContentType.LAYOUT,
                        shortDescription: 'Main',
                        longDescription: 'Main VM.',
                        filePath: 'main_layout.lyt'
                    },
                    hk: {
                        type: CdrFlightAppsPlugin.ContentType.PANEL,
                        shortDescription: 'HK',
                        longDescription: 'Vehicle Manager Housekeeping',
                        filePath: 'hk.pug'
                    },
                    vs: {
                        type: CdrFlightAppsPlugin.ContentType.PANEL,
                        shortDescription: 'Vehicle State',
                        longDescription: 'Arming and Navigation States',
                        filePath: 'vs.pug'
                    }
                }
            }
        };
  
	    this.addContent(content);
    };
};