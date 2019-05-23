'use strict';

var path = require('path');

const CdrFlightAppsPlugin = require(path.join(global.CDR_INSTALL_DIR, '/commander/classes/CdrFlightAppsPlugin')).CdrFlightAppsPlugin;

module.exports = class Mpu9250CdrFlightAppsPlugin extends CdrFlightAppsPlugin {
    constructor(config) {
        config.name = 'mpu9250';
        config.webRoot = path.join( __dirname, 'web');  
        super(config);
    	
        var content = {
            shortDescription: 'MPU9250 Inertial Measurement Unit',
        	longDescription: 'MPU9250 Inertial Measurement Unit Driver.',
        	nodes: {
        	    main: {
        	        type: CdrFlightAppsPlugin.ContentType.LAYOUT,
        	        shortDescription: 'Main',
        	        longDescription: 'Main MPU9250.',
        	        filePath: '/main.lyt'
        	    },
        	    cdh: {
        	        type: CdrFlightAppsPlugin.ContentType.PANEL,
        	        shortDescription: 'Command and Data Handling',
        	        longDescription: 'Command counters.',
        	        filePath: '/cdh.pug'
        	    },
        	    diag: {
        	        type: CdrFlightAppsPlugin.ContentType.PANEL,
        	        shortDescription: 'Diagnostic',
        	        longDescription: 'MPU9250 Diagnostic Message',
        	        filePath: '/diag.pug'
        	    }
        	}
        };
    	
    	this.addContent(content);
    }
};
