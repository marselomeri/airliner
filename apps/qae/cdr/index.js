'use strict';

var path = require('path');

const CdrFlightAppsPlugin = require(path.join(global.CDR_INSTALL_DIR, '/commander/classes/CdrFlightAppsPlugin')).CdrFlightAppsPlugin;

module.exports = class CfeCdrFlightAppsPlugin extends CdrFlightAppsPlugin {
    constructor(config) {
        config.name = 'qae';
        config.webRoot = path.join( __dirname, 'web');  
        super(config);

        var content = {
            qae: {    		
                shortDescription: 'Attitude Estimator',
                longDescription: 'Attitude Estimator',
                nodes: {
				    main: {
					    type: CdrFlightAppsPlugin.ContentType.LAYOUT,
					    shortDescription: 'Main',
					    longDescription: 'Main AMC.',
					    filePath: 'main_layout.lyt'
				    },
				    hk: {
					    type: CdrFlightAppsPlugin.ContentType.PANEL,
					    shortDescription: 'AE HK',
					    longDescription: 'Attitude Estimator Housekeeping',
					    filePath: 'hk.pug'
				    },
				    va: {
					    type: CdrFlightAppsPlugin.ContentType.PANEL,
					    shortDescription: 'Vehicle Attitude',
					    longDescription: 'Attitude Estimator Vehicle Attitude',
					    filePath: 'va.pug'
				    },
				    va_plot: {
					    type: CdrFlightAppsPlugin.ContentType.PANEL,
					    shortDescription: 'Vehicle Attitude (plot)',
					    longDescription: 'Attitude Estimator Vehicle Attitude data plot',
					    filePath: 'va_plot.pug'
				    },
				    cs: {
					    type: CdrFlightAppsPlugin.ContentType.PANEL,
					    shortDescription: 'Control State',
					    longDescription: 'Attitude Estimator Control State',
					    filePath: 'cs.pug'
				    }
                }
            }
        };
        
      	this.addContent(content);
    };
};
