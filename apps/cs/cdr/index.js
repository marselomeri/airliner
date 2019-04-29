'use strict';

var path = require('path');

const CdrFlightAppsPlugin = require(path.join(global.CDR_INSTALL_DIR, '/commander/classes/CdrFlightAppsPlugin')).CdrFlightAppsPlugin;

module.exports = class CfeCdrFlightAppsPlugin extends CdrFlightAppsPlugin {
    constructor() {
        super(path.join(__dirname, 'web'));
        
        var content = {
        	cs: {
                shortDescription: 'Checksum Services',
                longDescription: 'Checksum Services',
                nodes: {
				    main: {
					    type: CdrFlightAppsPlugin.ContentType.LAYOUT,
					    shortDescription: 'CS Main',
					    longDescription: 'Checksum Services Main',
					    filePath: 'main_layout.lyt'
				    },
				    apps: {
					    type: CdrFlightAppsPlugin.ContentType.PANEL,
					    shortDescription: 'CS Applications',
					    longDescription: 'Checksum Services Applications',
					    filePath: 'apps.pug'
				    },
				    hk: {
					    type: CdrFlightAppsPlugin.ContentType.PANEL,
					    shortDescription: 'CS Housekeeping',
					    longDescription: 'Checksum Services Housekeeping',
					    filePath: 'hk.pug'
				    },
				    cfecore: {
					    type: CdrFlightAppsPlugin.ContentType.PANEL,
					    shortDescription: 'CS CFE Core',
					    longDescription: 'Checksum Services CFE Core',
					    filePath: 'cfecore.pug'
				    },
				    eeprom: {
					    type: CdrFlightAppsPlugin.ContentType.PANEL,
					    shortDescription: 'CS EEPROM',
					    longDescription: 'Checksum Services EEPROM',
					    filePath: 'eeprom.pug'
				    },
				    memory: {
					    type: CdrFlightAppsPlugin.ContentType.PANEL,
					    shortDescription: 'CS Memory',
					    longDescription: 'Checksum Services Memory',
					    filePath: 'memory.pug'
				    },
				    os: {
					    type: CdrFlightAppsPlugin.ContentType.PANEL,
					    shortDescription: 'CS OS',
					    longDescription: 'Checksum Services OS',
					    filePath: 'os.pug'
				    },
				    tables: {
					    type: CdrFlightAppsPlugin.ContentType.PANEL,
					    shortDescription: 'CS Tables',
					    longDescription: 'Checksum Services Tables',
					    filePath: '/tables.pug'
				    }
                }
            }
        };
            
      	this.addContent(content);
    }
};
