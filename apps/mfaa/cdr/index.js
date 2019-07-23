'use strict';

var path = require('path');

/* Inherit from CdrFlightAppsPlugin to get the "Flight->Apps" path in the 
 * navigation pane.
 */
const CdrFlightAppsPlugin = require(path.join(global.CDR_INSTALL_DIR, '/commander/classes/CdrFlightAppsPlugin')).CdrFlightAppsPlugin;

module.exports = class CfeCdrFlightAppsPlugin extends CdrFlightAppsPlugin {
    constructor(config) {
        config.name = 'mfaa';
        config.webRoot = path.join( __dirname, 'web');  
        super(config);

        var content = {
            mfaa: {    	
                shortDescription: 'My First App A',
                longDescription: 'My First App A',
                nodes: {
                    main: {
                        type: CdrFlightAppsPlugin.ContentType.LAYOUT,
                        shortDescription: 'Main',
                        longDescription: 'Main MFAA.',
                        filePath: 'main_layout.lyt'
                    },
                    hk: {
                        type: CdrFlightAppsPlugin.ContentType.PANEL,
                        shortDescription: 'HK',
                        longDescription: 'Housekeeping',
                        filePath: 'hk.pug'
                    }
                }
            }
        };
        
      	this.addContent(content);
    };
};
