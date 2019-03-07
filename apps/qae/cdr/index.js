'use strict';

var path = require('path');

const CdrPlugin = require(path.join(global.CDR_INSTALL_DIR, '/commander/classes/CdrPlugin')).CdrPlugin;

module.exports = class CfeCdrPlugin extends CdrPlugin {
  constructor(urlBase) {
    super('qae', path.join(__dirname, 'web', urlBase));
  }

  getContent() {
    var result = {
      shortDescription: 'Attitude Estimator',
      longDescription: 'Attitude Estimator',
      nodes: {
				main: {
					type: CdrPlugin.ContentType.LAYOUT,
					shortDescription: 'Main',
					longDescription: 'Main AMC.',
					filePath: '/main_layout.lyt'
				},
				hk: {
					type: CdrPlugin.ContentType.PANEL,
					shortDescription: 'AE HK',
					longDescription: 'Attitude Estimator Housekeeping',
					filePath: '/hk.pug'
				},
				va: {
					type: CdrPlugin.ContentType.PANEL,
					shortDescription: 'Vehicle Attitude',
					longDescription: 'Attitude Estimator Vehicle Attitude',
					filePath: '/va.pug'
				},
				cs: {
					type: CdrPlugin.ContentType.PANEL,
					shortDescription: 'Control State',
					longDescription: 'Attitude Estimator Control State',
					filePath: '/cs.pug'
				}
      }
    };

    return result;
  }
};

//var plugin = new CfeCdrPlugin();

//let CfeCdrPlugin = new class extends CdrPlugin {
