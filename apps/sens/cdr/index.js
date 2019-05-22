'use strict';

var path = require('path');

const CdrFlightAppsPlugin = require(path.join(global.CDR_INSTALL_DIR, '/commander/classes/CdrFlightAppsPlugin')).CdrFlightAppsPlugin;

module.exports = class CfeCdrFlightAppsPlugin extends CdrFlightAppsPlugin {
    constructor(config) {
        config.name = 'sens';
        config.webRoot = path.join( __dirname, 'web');  
        super(config);

        var content = {
            sens: {    	
                shortDescription: 'Sensor Combined',
                longDescription: 'Sensor Combined Message.',
                nodes: {
                    main: {
                        type: CdrFlightAppsPlugin.ContentType.LAYOUT,
                        shortDescription: 'Main',
                        longDescription: 'Main SENS.',
                        filePath: 'main.lyt'
                   },
                   cdh: {
                       type: CdrFlightAppsPlugin.ContentType.PANEL,
                       shortDescription: 'Command and Data Handling',
                       longDescription: 'Command counters.',
                       filePath: 'cdh.pug'
                   }
               }
            }
        };
        
      	this.addContent(content);
    };
};
