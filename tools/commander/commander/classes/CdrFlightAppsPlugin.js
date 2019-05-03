"use strict";

var path = require( 'path' );
const util = require('util');

const CdrFlightPlugin = require(path.join(global.CDR_INSTALL_DIR, '/commander/classes/CdrFlightPlugin')).CdrFlightPlugin;

/**
 * Commander Flight plugin
 */
class CdrFlightAppsPlugin extends CdrFlightPlugin {
	
    /**
     * Constructor for commander plugin
     * @param {String} name    directory name
     * @param {String} webRoot directory path
     * @param {String} urlBase base url
     */
    constructor(config) {
        super(config);
    }
    
    addContent(content) {
    	var newContent = {
            apps: {
                shortDescription: 'Apps',
                longDescription: 'Applications.',
                nodes: content
            }
    	};
        
        super.addContent(newContent);
    }
}



module.exports = {
  CdrFlightAppsPlugin: CdrFlightAppsPlugin
}