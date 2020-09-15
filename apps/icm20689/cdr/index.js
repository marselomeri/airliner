'use strict';

var path = require('path');

const CdrFlightAppsPlugin = require(path.join(global.CDR_INSTALL_DIR, '/commander/classes/CdrFlightAppsPlugin')).CdrFlightAppsPlugin;

module.exports = class Icm20689CdrFlightAppsPlugin extends CdrFlightAppsPlugin {
    constructor(config) {
        config.name = 'icm20689';
        config.webRoot = path.join( __dirname, 'web');  
        super(config);
    	
        var content = {
            shortDescription: 'ICM20689 Inertial Measurement Unit',
        	longDescription: 'ICM20689 Inertial Measurement Unit Driver.',
        	nodes: {
        	    main: {
        	        type: CdrFlightAppsPlugin.ContentType.LAYOUT,
        	        shortDescription: 'Main',
        	        longDescription: 'Main ICM20689.',
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
        	        longDescription: 'ICM20689 Diagnostic Message',
        	        filePath: '/diag.pug'
        	    }
        	}
        };
    	
    	this.addContent(content);
    }
};
