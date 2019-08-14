'use strict';

var path = require( 'path' );

const CdrFlightAppsPlugin = require( path.join( global.CDR_INSTALL_DIR, '/commander/classes/CdrFlightAppsPlugin' ) ).CdrFlightAppsPlugin;

module.exports = class CfeCdrFlightAppsPlugin extends CdrFlightAppsPlugin {
    constructor(config) {
        config.name = 'mpc';
        config.webRoot = path.join( __dirname, 'web');  
        super(config);

        var content = {
            mpc: {
                shortDescription: 'Multicopter Position Control',
                longDescription: 'Multicopter Position Control.',
                nodes: {
                    main: {
                        type: CdrFlightAppsPlugin.ContentType.LAYOUT,
                        shortDescription: 'Main',
                        longDescription: 'Main MPC.',
                        filePath: '/main_layout.lyt'
                    },
                    hk: {
                        type: CdrFlightAppsPlugin.ContentType.PANEL,
                        shortDescription: 'HK',
                        longDescription: 'MPC Housekeeping.',
                        filePath: '/hk.pug'
                    },
                    cs: {
                        type: CdrFlightAppsPlugin.ContentType.PANEL,
                        shortDescription: 'Control State',
                        longDescription: 'MPC Control State',
                        filePath: '/cs.pug'
                    },
                    vs: {
                        type: CdrFlightAppsPlugin.ContentType.PANEL,
                        shortDescription: 'Vehicle State',
                        longDescription: 'MPC Vehicle State',
                        filePath: '/vs.pug'
                    },
                    pid: {
                        type: CdrFlightAppsPlugin.ContentType.PANEL,
                        shortDescription: 'PID',
                        longDescription: 'MPC PIDs Tunint',
                        filePath: '/pid.pug'
                    },
                    tv: {
                        type: CdrFlightAppsPlugin.ContentType.PANEL,
                        shortDescription: 'Table Values',
                        longDescription: 'MPC Table Values',
                        filePath: '/tv.pug'
                    }
                }
            }
        };
        
        this.addContent(content);
    };
};