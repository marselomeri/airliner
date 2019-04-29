'use strict';

var path = require( 'path' );

const CdrFlightAppsPlugin = require( path.join( global.CDR_INSTALL_DIR, '/commander/classes/CdrFlightAppsPlugin' ) ).CdrFlightAppsPlugin;

module.exports = class CfeCdrFlightAppsPlugin extends CdrFlightAppsPlugin {
    constructor() {
        super(path.join( __dirname, 'web'));

        var content = {
            mpc: {
                shortDescription: 'Multicopter Position Control',
                longDescription: 'Multicopter Position Control.',
                nodes: {
                    main: {
                        type: CdrFlightAppsPlugin.ContentType.LAYOUT,
                        shortDescription: 'Main',
                        longDescription: 'Main MPC.',
                        filePath: '/main.lyt'
                    },
                    cdh: {
                        type: CdrFlightAppsPlugin.ContentType.PANEL,
                        shortDescription: 'Command and Data Handling',
                        longDescription: 'Command counters.',
                        filePath: '/cdh.pug'
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