'use strict';

var path = require('path');

const CdrFlightAppsPlugin = require(path.join(global.CDR_INSTALL_DIR, '/commander/classes/CdrFlightAppsPlugin')).CdrFlightAppsPlugin;

module.exports = class Hmc5883CdrFlightAppsPlugin extends CdrFlightAppsPlugin {
    constructor(config) {
        config.name = 'hmc5883';
        config.webRoot = path.join( __dirname, 'web');  
        super(config);
    	
        var content = {
            amc: {
                shortDescription: 'HMC5883 Driver',
                longDescription: 'HMC5883 Driver',
                nodes: {
    				main: {
    					type: CdrFlightAppsPlugin.ContentType.LAYOUT,
    					shortDescription: 'Main',
    					longDescription: 'Main HMC5883.',
    					filePath: '/main_layout.lyt'
    				},
    				hk: {
    					type: CdrFlightAppsPlugin.ContentType.PANEL,
    					shortDescription: 'HMC5883 HK',
    					longDescription: 'HMC5883 Housekeeping',
    					filePath: '/hk.pug'
    				},
                    diag: {
                        type: CdrFlightAppsPlugin.ContentType.PANEL,
                        shortDescription: 'HMC5883 Diag',
                        longDescription: 'HMC5883 Diagnostics',
                        filePath: '/diag.pug'
                    }
                }
            }
        };
    	
    	this.addContent(content);
    }
};
