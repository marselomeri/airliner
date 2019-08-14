'use strict';

var path = require( 'path' );

const CdrFlightAppsPlugin = require( path.join( global.CDR_INSTALL_DIR, '/commander/classes/CdrFlightAppsPlugin' ) ).CdrFlightAppsPlugin;

module.exports = class CfeCdrFlightAppsPlugin extends CdrFlightAppsPlugin {
    constructor(config) {
        config.name = 'mac';
        config.webRoot = path.join( __dirname, 'web');  
        super(config);

        var content = {
        	mac: {
                shortDescription: 'Multicopter Attitude Control',
                longDescription: 'Multicopter Attitude Control.',
                nodes: {
                    main: {
                        type: CdrFlightAppsPlugin.ContentType.LAYOUT,
                        shortDescription: 'Main',
                        longDescription: 'Main MAC.',
                        filePath: 'main_layout.lyt'
                    },
                    hk: {
                        type: CdrFlightAppsPlugin.ContentType.PANEL,
                        shortDescription: 'HK',
                        longDescription: 'MAC Housekeeping.',
                        filePath: 'hk.pug'
                    }
                }
        	}
        };
        
      	this.addContent(content);
    };
};

