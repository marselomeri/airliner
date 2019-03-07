'use strict';

var path = require( 'path' );

const CdrPlugin = require( path.join( global.CDR_INSTALL_DIR, '/commander/classes/CdrPlugin' ) ).CdrPlugin;

module.exports = class CfeCdrPlugin extends CdrPlugin {
  constructor( urlBase ) {
    super( 'lc', path.join( __dirname, 'web', urlBase ) );
  }

  getContent() {
    var result = {
      shortDescription: 'Limit Checker',
      longDescription: 'Limit Checker.',
      nodes: {
        main: {
          type: CdrPlugin.ContentType.LAYOUT,
          shortDescription: 'Main',
          longDescription: 'Main LC.',
          filePath: '/main.lyt'
        },
        cdh: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'Command and Data Handling',
          longDescription: 'Command counters.',
          filePath: '/cdh.pug'
        },
        lc_0_24: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'LC ( 0 - 24 )',
          longDescription: 'Limit Checker - WP Results ( 0 - 24 ).',
          filePath: '/lc_0_24.pug'
        },
        lc_25_49: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'LC ( 25 - 49 )',
          longDescription: 'Limit Checker - WP Results ( 25 - 49 ).',
          filePath: '/lc_25_49.pug'
        },
        lc_50_74: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'LC ( 50 - 74 )',
          longDescription: 'Limit Checker - WP Results ( 50 - 74 ).',
          filePath: '/lc_50_74.pug'
        },
        lc_75_99: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'LC ( 75 - 99 )',
          longDescription: 'Limit Checker - WP Results ( 75 - 99 ).',
          filePath: '/lc_75_99.pug'
        },
        lc_100_124: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'LC ( 100 - 124 )',
          longDescription: 'Limit Checker - WP Results ( 100 - 124 ).',
          filePath: '/lc_100_124.pug'
        },
        lc_125_149: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'LC ( 125 - 149 )',
          longDescription: 'Limit Checker - WP Results ( 125 - 149 ).',
          filePath: '/lc_125_149.pug'
        },
        lc_150_174: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'LC ( 150 - 174 )',
          longDescription: 'Limit Checker - WP Results ( 150 - 174 ).',
          filePath: '/lc_150_174.pug'
        },
      }
    };

    return result;
  }
};

//var plugin = new CfeCdrPlugin();

//let CfeCdrPlugin = new class extends CdrPlugin {
