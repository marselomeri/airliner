"use strict";

var path = require( 'path' );

const CdrPlugin = require(path.join(global.CDR_INSTALL_DIR, '/commander/classes/CdrPlugin')).CdrPlugin;

/**
 * Commander Ground plugin
 */
class CdrGroundPlugin extends CdrPlugin {
	
    /**
     * Constructor for commander plugin
     * @param {String} name    directory name
     * @param {String} webRoot directory path
     * @param {String} urlBase base url
     */
    constructor(webRoot) {
	    super(webRoot);
    }

    getContent() { 
        var result = {
            ground: {
	            shortDescription: 'Ground',
	            longDescription: 'Ground Systems.',
	            nodes: {}
            }
	    };

	    return result;
	}
  
}



module.exports = {
  CdrGroundPlugin: CdrGroundPlugin
}