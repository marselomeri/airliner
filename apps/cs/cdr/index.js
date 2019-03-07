'use strict';

var path = require('path');

const CdrPlugin = require(path.join(global.CDR_INSTALL_DIR, '/commander/classes/CdrPlugin')).CdrPlugin;

module.exports = class CfeCdrPlugin extends CdrPlugin {
  constructor(urlBase) {
    super('cs', path.join(__dirname, 'web', urlBase));
  }

  getContent() {
    var result = {
      shortDescription: 'Checksum Services',
      longDescription: 'Checksum Services',
      nodes: {
				main: {
					type: CdrPlugin.ContentType.LAYOUT,
					shortDescription: 'CS Main',
					longDescription: 'Checksum Services Main',
					filePath: '/main_layout.lyt'
				},
				hk: {
					type: CdrPlugin.ContentType.PANEL,
					shortDescription: 'CS Housekeeping',
					longDescription: 'Checksum Services Housekeeping',
					filePath: '/hk.pug'
				},
				cfecore: {
					type: CdrPlugin.ContentType.PANEL,
					shortDescription: 'CS CFE Core',
					longDescription: 'Checksum Services CFE Core',
					filePath: '/cfecore.pug'
				},
				eeprom: {
					type: CdrPlugin.ContentType.PANEL,
					shortDescription: 'CS EEPROM',
					longDescription: 'Checksum Services EEPROM',
					filePath: '/eeprom.pug'
				},
				memory: {
					type: CdrPlugin.ContentType.PANEL,
					shortDescription: 'CS Memory',
					longDescription: 'Checksum Services Memory',
					filePath: '/memory.pug'
				},
				os: {
					type: CdrPlugin.ContentType.PANEL,
					shortDescription: 'CS OS',
					longDescription: 'Checksum Services OS',
					filePath: '/os.pug'
				},
				tables: {
					type: CdrPlugin.ContentType.PANEL,
					shortDescription: 'CS Tables',
					longDescription: 'Checksum Services Tables',
					filePath: '/tables.pug'
				}
      }
    };

    return result;
  }
};

//var plugin = new CfeCdrPlugin();

//let CfeCdrPlugin = new class extends CdrPlugin {
