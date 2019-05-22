'use strict';

var path = require('path');

const CdrFlightAppsPlugin = require(path.join(global.CDR_INSTALL_DIR, '/commander/classes/CdrFlightAppsPlugin')).CdrFlightAppsPlugin;

module.exports = class CfeCdrFlightAppsPlugin extends CdrFlightAppsPlugin {
    constructor(config) {
        config.name = 'ms5607';
        config.webRoot = path.join( __dirname, 'web');  
        super(config);

        var content = {
            ms5607: {   
                shortDescription: 'MS5607',
                longDescription: 'MS5607 Driver',
                nodes: {
				    main: {
					    type: CdrFlightAppsPlugin.ContentType.LAYOUT,
			            shortDescription: 'Main',
					    longDescription: 'Main MS5607.',
					    filePath: 'main.lyt'
				    },
				    hk: {
					    type: CdrFlightAppsPlugin.ContentType.PANEL,
					    shortDescription: 'HK',
					    longDescription: 'MS5607 Housekeeping',
					    filePath: 'hk.pug'
				    },
                    diag: {
                        type: CdrFlightAppsPlugin.ContentType.PANEL,
                        shortDescription: 'Diag',
                        longDescription: 'MS5607 Diag',
                        filePath: 'diag.pug'
                    }
                }
            }
        };
        
      	this.addContent(content);
    };
};