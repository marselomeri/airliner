'use strict';

var path = require('path');

/* Inherit from CdrFlightAppsPlugin to get the "Flight->Apps" path in the 
 * navigation pane.
 */
const CdrFlightAppsPlugin = require(path.join(global.CDR_INSTALL_DIR, '/commander/classes/CdrFlightAppsPlugin')).CdrFlightAppsPlugin;

module.exports = class CfeCdrFlightAppsPlugin extends CdrFlightAppsPlugin {
    constructor(config) {
        config.name = 'mfab';
        config.webRoot = path.join( __dirname, 'web');  
        super(config);

        var content = {
            mfab: {    	
                shortDescription: 'My First App B',
                longDescription: 'My First App B',
                nodes: {
                    main: {
                        type: CdrFlightAppsPlugin.ContentType.LAYOUT,
                        shortDescription: 'Main',
                        longDescription: 'Main MFAB.',
                        filePath: 'main_layout.lyt'
                    },
                    hk: {
                        type: CdrFlightAppsPlugin.ContentType.PANEL,
                        shortDescription: 'HK',
                        longDescription: 'Housekeeping',
                        filePath: 'hk.pug'
                    },
                    raw: {
                        type: CdrFlightAppsPlugin.ContentType.PANEL,
                        shortDescription: 'Raw',
                        longDescription: 'Raw Value',
                        filePath: 'raw.pug'
                    }
                }
            }
        };
        
      	this.addContent(content);
    };
};