'use strict';

var path = require('path');

const CdrFlightAppsPlugin = require(path.join(global.CDR_INSTALL_DIR, '/commander/classes/CdrFlightAppsPlugin')).CdrFlightAppsPlugin;

module.exports = class CfeCdrFlightAppsPlugin extends CdrFlightAppsPlugin {
    constructor() {
        super(path.join(__dirname, 'web'));

        var content = {
            vm: {    		
                shortDescription: 'Vehicle Manager',
                longDescription: 'Vehicle State Manager.',
                nodes: {
                    main: {
                        type: CdrFlightAppsPlugin.ContentType.LAYOUT,
                        shortDescription: 'Main',
                        longDescription: 'Main VM.',
                        filePath: 'main.lyt'
                    },
                    cdh: {
                        type: CdrFlightAppsPlugin.ContentType.PANEL,
                        shortDescription: 'Command and Data Handling',
                        longDescription: 'Command counters.',
                        filePath: 'cdh.pug'
                    },
                    vs: {
                        type: CdrFlightAppsPlugin.ContentType.PANEL,
                        shortDescription: 'Vehicle State',
                        longDescription: 'Arming and Navigation States',
                        filePath: 'vs.pug'
                    }
                }
            }
        };
  
	    this.addContent(content);
    };
};