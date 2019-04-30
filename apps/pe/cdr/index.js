'use strict';

var path = require('path');

const CdrFlightAppsPlugin = require(path.join(global.CDR_INSTALL_DIR, '/commander/classes/CdrFlightAppsPlugin')).CdrFlightAppsPlugin;

module.exports = class CfeCdrFlightAppsPlugin extends CdrFlightAppsPlugin {
    constructor() {
        super(path.join(__dirname, 'web'));

        var content = {
            pe: {    	
                shortDescription: 'Position Estimator',
                longDescription: 'Position Estimator',
                nodes: {
				    main: {
					    type: CdrFlightAppsPlugin.ContentType.LAYOUT,
					    shortDescription: 'Main',
					    longDescription: 'Main PE.',
					    filePath: 'main_layout.lyt'
				    },
				    hk: {
					    type: CdrFlightAppsPlugin.ContentType.PANEL,
					    shortDescription: 'PE HK',
					    longDescription: 'Position Estimator Housekeeping',
					    filePath: 'hk.pug'
				    },
				    gps: {
					    type: CdrFlightAppsPlugin.ContentType.PANEL,
					    shortDescription: 'PE GPS',
					    longDescription: 'Position Estimator GPS',
					    filePath: 'gps.pug'
				    },
				    baro: {
					    type: CdrFlightAppsPlugin.ContentType.PANEL,
					    shortDescription: 'PE Baro',
					    longDescription: 'Position Estimator Barometric Altimeter',
					    filePath: 'baro.pug'
				    },
				    dist: {
					    type: CdrFlightAppsPlugin.ContentType.PANEL,
					    shortDescription: 'PE Distance',
					    longDescription: 'Position Estimator Distance Sensor',
					    filePath: 'dist.pug'
				    },
				    land: {
					    type: CdrFlightAppsPlugin.ContentType.PANEL,
					    shortDescription: 'PE Landingr',
					    longDescription: 'Position Estimator Landing Sensor',
					    filePath: 'land.pug'
				    },
				    flow: {
					    type: CdrFlightAppsPlugin.ContentType.PANEL,
					    shortDescription: 'PE Flow',
					    longDescription: 'Position Estimator Flow Sensor',
					    filePath: 'flow.pug'
				    }
				}
            }
        };
        
      	this.addContent(content);
    };
};
