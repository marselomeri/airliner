"use strict";

var path = require( 'path' );

const CdrPlugin = require(path.join(global.CDR_INSTALL_DIR, '/commander/classes/CdrPlugin')).CdrPlugin;

/**
 * Commander Flight plugin
 */
class CdrFlightPlugin extends CdrPlugin {
	
    /**
     * Constructor for commander plugin
     * @param {String} name    directory name
     * @param {String} webRoot directory path
     * @param {String} urlBase base url
     */
    constructor(webRoot) {
	    super(webRoot);
    }
    
    addContent(content) {
    	var newContent = {
            flight: {
                shortDescription: 'Flight',
                longDescription: 'Flight Systems.',
                nodes: content
        	}
    	};
        
        super.addContent(newContent);
    }
  
}



module.exports = {
  CdrFlightPlugin: CdrFlightPlugin
}