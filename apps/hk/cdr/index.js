'use strict';

var path = require('path');

const CdrPlugin = require(path.join(global.CDR_INSTALL_DIR, '/commander/classes/CdrPlugin')).CdrPlugin;

module.exports = class CfeCdrPlugin extends CdrPlugin {
  constructor(urlBase) {
    super('hk', path.join(__dirname, 'web', urlBase));
  }

  getContent() {
    var result = {
      shortDescription: 'Housekeeping',
      longDescription: 'Housekeeping',
      nodes: {
				main: {
					type: CdrPlugin.ContentType.LAYOUT,
					shortDescription: 'Main',
					longDescription: 'Main HK.',
					filePath: '/main_layout.lyt'
				},
				hk: {
					type: CdrPlugin.ContentType.PANEL,
					shortDescription: 'HK HK',
					longDescription: 'Housekeeping Housekeeping',
					filePath: '/hk.pug'
				}
      }
    };

    return result;
  }
};

//var plugin = new CfeCdrPlugin();

//let CfeCdrPlugin = new class extends CdrPlugin {
