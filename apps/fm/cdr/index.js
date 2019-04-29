'use strict';

var path = require('path');

const CdrFlightAppsPlugin = require(path.join(global.CDR_INSTALL_DIR, '/commander/classes/CdrFlightAppsPlugin')).CdrFlightAppsPlugin;

module.exports = class CfeCdrFlightAppsPlugin extends CdrFlightAppsPlugin {
    constructor() {
        super(path.join(__dirname, 'web'));
    
        var content = {
        	fm: {
                shortDescription: 'File Management',
                longDescription: 'File Management',
                nodes: {
				    main: {
					    type: CdrFlightAppsPlugin.ContentType.LAYOUT,
					    shortDescription: 'Main',
					    longDescription: 'Main FM.',
					    filePath: 'main_layout.lyt'
				    },
				    hk: {
					    type: CdrFlightAppsPlugin.ContentType.PANEL,
					    shortDescription: 'FM Housekeeping',
					    longDescription: 'FM Housekeeping',
					    filePath: 'hk.pug'
				    },
				    freespace: {
					    type: CdrFlightAppsPlugin.ContentType.PANEL,
					    shortDescription: 'FM Free Space',
					    longDescription: 'FM Free Space',
					    filePath: 'freespace.pug'
				    },
				    openfiles: {
					    type: CdrFlightAppsPlugin.ContentType.PANEL,
					    shortDescription: 'FM Open Files',
					    longDescription: 'FM Open Files',
					    filePath: 'openfiles.pug'
				    },
				    fileinfo: {
					    type: CdrFlightAppsPlugin.ContentType.PANEL,
					    shortDescription: 'FM File Info',
					    longDescription: 'FM File Info',
					    filePath: 'fileinfo.pug'
				    },
				    dirlist: {
					    type: CdrFlightAppsPlugin.ContentType.PANEL,
					    shortDescription: 'FM Directory Listing',
					    longDescription: 'FM Directory Listing',
					    filePath: 'dirlist.pug'
				    }
                }
        	}
        }
        
      	this.addContent(content);
    }
};
