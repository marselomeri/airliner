'use strict';

var path = require( 'path' );

const CdrPlugin = require( path.join( global.CDR_INSTALL_DIR, '/commander/classes/CdrPlugin' ) ).CdrPlugin;

module.exports = class CfeCdrPlugin extends CdrPlugin {
  constructor( urlBase ) {
    super( 'sc', path.join( __dirname, 'web', urlBase ) );
  }

  getContent() {
    var result = {
      shortDescription: 'Stored Command',
      longDescription: 'Stored Command.',
      nodes: {
        main: {
          type: CdrPlugin.ContentType.LAYOUT,
          shortDescription: 'Main',
          longDescription: 'Main VM.',
          filePath: '/main.lyt'
        },
        cdh: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'Command and Data Handling',
          longDescription: 'Command counters.',
          filePath: '/cdh.pug'
        },
        gen: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'General',
          longDescription: 'General',
          filePath: '/gen.pug'
        },
        ats: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'ATS',
          longDescription: 'ATS General.',
          filePath: '/ats.pug'
        },
        rts: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'RTS',
          longDescription: 'RTS General.',
          filePath: '/rts.pug'
        },
        rts_1_32: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'RTS Status (1-32)',
          longDescription: 'RTS Status.',
          filePath: '/rts_1_32.pug'
        },
        rts_33_64: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'RTS Status (33-64)',
          longDescription: 'RTS Status.',
          filePath: '/rts_33_64.pug'
        }
      }
    };

    return result;
  }
};

//var plugin = new CfeCdrPlugin();

//let CfeCdrPlugin = new class extends CdrPlugin {
