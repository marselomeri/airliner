'use strict';

var path = require('path');

const CdrFlightAppsPlugin = require(path.join(global.CDR_INSTALL_DIR, '/commander/classes/CdrFlightAppsPlugin')).CdrFlightAppsPlugin;

module.exports = class AmcCdrFlightAppsPlugin extends CdrFlightAppsPlugin {
    constructor(config) {
        config.name = 'amc';
        config.webRoot = path.join( __dirname, 'web');  
        super(config);
    	
        var content = {
            amc: {
                shortDescription: 'Actuator and Motor Control',
                longDescription: 'Actuator and Motor Control.',
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
                    ao: {
                        type: CdrFlightAppsPlugin.ContentType.PANEL,
                        shortDescription: 'Actuator Outputs',
                        longDescription: 'Actuator Outputs',
                        filePath: 'ao.pug'
                    }
                }
            }
        };
    	
    	this.addContent(content);
    }
};
