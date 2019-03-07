'use strict';

var path = require('path');

const CdrPlugin = require(path.join(global.CDR_INSTALL_DIR, '/commander/classes/CdrPlugin')).CdrPlugin;

module.exports = class CfeCdrPlugin extends CdrPlugin {
  constructor(urlBase) {
    super('fm', path.join(__dirname, 'web', urlBase));
  }

  getContent() {
    var result = {
      shortDescription: 'File Management',
      longDescription: 'File Management',
      nodes: {
				main: {
					type: CdrPlugin.ContentType.LAYOUT,
					shortDescription: 'Main',
					longDescription: 'Main FM.',
					filePath: '/main_layout.lyt'
				},
				hk: {
					type: CdrPlugin.ContentType.PANEL,
					shortDescription: 'FM Housekeeping',
					longDescription: 'FM Housekeeping',
					filePath: '/hk.pug'
				},
				freespace: {
					type: CdrPlugin.ContentType.PANEL,
					shortDescription: 'FM Free Space',
					longDescription: 'FM Free Space',
					filePath: '/freespace.pug'
				},
				openfiles: {
					type: CdrPlugin.ContentType.PANEL,
					shortDescription: 'FM Open Files',
					longDescription: 'FM Open Files',
					filePath: '/openfiles.pug'
				},
				fileinfo: {
					type: CdrPlugin.ContentType.PANEL,
					shortDescription: 'FM File Info',
					longDescription: 'FM File Info',
					filePath: '/fileinfo.pug'
				},
				dirlist: {
					type: CdrPlugin.ContentType.PANEL,
					shortDescription: 'FM Directory Listing',
					longDescription: 'FM Directory Listing',
					filePath: '/dirlist.pug'
				}
      }
    };

    return result;
  }
};

//var plugin = new CfeCdrPlugin();

//let CfeCdrPlugin = new class extends CdrPlugin {
