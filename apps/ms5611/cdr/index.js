'use strict';

var path = require('path');

const CdrFlightAppsPlugin = require(path.join(global.CDR_INSTALL_DIR, '/commander/classes/CdrFlightAppsPlugin')).CdrFlightAppsPlugin;

module.exports = class Ms5611CdrFlightAppsPlugin extends CdrFlightAppsPlugin {
    constructor(config) {
        config.name = 'ms5611';
        config.webRoot = path.join( __dirname, 'web');  
        super(config);
    	
        var content = {
            shortDescription: 'MS5611 Barometric Altimeter',
        	longDescription: 'MS5611 Barometric Altimeter Driver.',
        	nodes: {
        	    main: {
        	        type: CdrFlightAppsPlugin.ContentType.LAYOUT,
        	        shortDescription: 'Main',
        	        longDescription: 'Main MS5611.',
        	        filePath: '/main.lyt'
        	    },
        	    cdh: {
        	        type: CdrFlightAppsPlugin.ContentType.PANEL,
        	        shortDescription: 'Command and Data Handling',
        	        longDescription: 'Command counters.',
        	        filePath: '/cdh.pug'
        	    },
        	    cfg: {
        	        type: CdrFlightAppsPlugin.ContentType.PANEL,
        	        shortDescription: 'Configuration',
        	        longDescription: 'Configuration Diagnostic Message.',
        	        filePath: '/cfg.pug'
        	    },
        	    meas: {
        	        type: CdrFlightAppsPlugin.ContentType.PANEL,
        	        shortDescription: 'Measurement',
        	        longDescription: 'Measurement Diagnostic Message.',
        	        filePath: '/meas.pug'
        	    }
        	}
        };
    	
    	this.addContent(content);
    }
};
