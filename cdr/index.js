'use strict';

var path = require('path');

const CdrPlugin = require(path.join(global.CDR_INSTALL_DIR, '/commander/classes/CdrPlugin')).CdrPlugin;

module.exports = class CfeCdrPlugin extends CdrPlugin {
  constructor(urlBase) {
    super('gps', path.join(__dirname, 'web', urlBase));
  }

  getContent() {
    var result = {
      shortDescription: 'GPS Driver',
      longDescription: 'GPS Driver.',
      nodes: {
				main: {
					type: CdrPlugin.ContentType.LAYOUT,
					shortDescription: 'Main',
					longDescription: 'Main GPS.',
					filePath: '/main_layout.lyt'
				},
				cdh: {
					type: CdrPlugin.ContentType.PANEL,
					shortDescription: 'Command and Data Handling',
					longDescription: 'Command counters.',
					filePath: '/cdh.pug'
				},
                gps: {
                    type: CdrPlugin.ContentType.PANEL,
                    shortDescription: 'Vehicle GPS',
                    longDescription: 'Vehicle Global Position',
                    filePath: '/gps.pug'
                },
      }
    };

    return result;
  }
};
