'use strict';

var path = require('path');

const CdrFlightAppsPlugin = require(path.join(global.CDR_INSTALL_DIR, '/commander/classes/CdrFlightAppsPlugin')).CdrFlightAppsPlugin;

module.exports = class BatCdrFlightAppsPlugin extends CdrFlightAppsPlugin {
    constructor() {
	    super(path.join( __dirname, 'web'));
    	
        var content = {
        	bat: {
                shortDescription: 'Battery',
        	    longDescription: 'Battery.',
        	    nodes: {
        	        main: {
        		        type: CdrFlightAppsPlugin.ContentType.LAYOUT,
        		        shortDescription: 'Main',
        		        longDescription: 'Main BAT.',
        	 	        filePath: '/main_layout.lyt'
        	        },
        	        hk: {
        		        type: CdrFlightAppsPlugin.ContentType.PANEL,
        		        shortDescription: 'Battery Housekeeping',
        		        longDescription: 'Battery Housekeeping',
        		        filePath: '/hk.pug'
        	        }
        	    }
        	}
        };
        
        this.addContent(content);
    }
};