'use strict';

var path = require('path');

const CdrFlightAppsPlugin = require(path.join(global.CDR_INSTALL_DIR, '/commander/classes/CdrFlightAppsPlugin')).CdrFlightAppsPlugin;

module.exports = class CfeCdrFlightAppsPlugin extends CdrFlightAppsPlugin {
    constructor() {
        super(path.join(__dirname, 'web'));
        
        var content = {
            nav: {   
                shortDescription: 'Navigation',
                longDescription: 'Vehicle Navigation Manager.',
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
                    als: {
                        type: CdrFlightAppsPlugin.ContentType.PANEL,
                        shortDescription: 'Auto Land Status',
                        longDescription: 'Auto Land Status',
                        filePath: 'als.pug'
                    },
                    cms: {
                        type: CdrFlightAppsPlugin.ContentType.PANEL,
                        shortDescription: 'Current Mission Status',
                        longDescription: 'Current Mission Status',
                        filePath: 'cms.pug'
                    },
                    rtls: {
                        type: CdrFlightAppsPlugin.ContentType.PANEL,
                        shortDescription: 'RTL Status',
                        longDescription: 'RTL Status',
                        filePath: 'rtls.pug'
                    }
                }
            }
        };
        
      	this.addContent(content);
    };
};


//var plugin = new CfeCdrPlugin();

//let CfeCdrPlugin = new class extends CdrPlugin {
