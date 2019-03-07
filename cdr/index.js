'use strict';

var path = require( 'path' );

const CdrPlugin = require( path.join( global.CDR_INSTALL_DIR, '/commander/classes/CdrPlugin' ) ).CdrPlugin;

module.exports = class CfeCdrPlugin extends CdrPlugin {
  constructor( urlBase ) {
    super( 'mac', path.join( __dirname, 'web', urlBase ) );
  }

  getContent() {
    var result = {
      shortDescription: 'Multicopter Attitude Control',
      longDescription: 'Multicopter Attitude Control.',
      nodes: {
        main: {
          type: CdrPlugin.ContentType.LAYOUT,
          shortDescription: 'Main',
          longDescription: 'Main AMC.',
          filePath: '/main.lyt'
        },
        cdh: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'Command and Data Handling',
          longDescription: 'Command counters.',
          filePath: '/cdh.pug'
        }
      }
    };

    return result;
  }
};

//var plugin = new CfeCdrPlugin();

//let CfeCdrPlugin = new class extends CdrPlugin {
