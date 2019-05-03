"use strict";

var path = require( 'path' );

const CdrPlugin = require(path.join(global.CDR_INSTALL_DIR, '/commander/classes/CdrPlugin')).CdrPlugin;

/**
 * Commander Flight plugin
 */
class CdrGroundPlugin extends CdrPlugin {
        
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
            flight: {
                shortDescription: 'Ground',
                longDescription: 'Ground Systems.',
                nodes: content
            }
        };
                
        super.addContent(newContent);
    }
}



module.exports = {
        CdrGroundPlugin: CdrGroundPlugin
}