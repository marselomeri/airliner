'use strict';

var path = require( 'path' );

const CdrPlugin = require( path.join( global.CDR_INSTALL_DIR, '/commander/classes/CdrPlugin' ) ).CdrPlugin;
//var express = require('express');
//var router = express.Router();
//var path = require('path');
//var url = require('url');

//var workspace = path.join(__dirname + '/..', '/workspace/web');
//
///* GET home page. */
//router.get('/*', function(req, res, next) {
//	var translatedPath = path.join(workspace, req.url);
//
//	switch(path.extname(req.url)) {
//	    case '.pug':
//	        res.render(translatedPath, { title: 'Express' });
//	        break;
//
//	    default:
//	    	var options = {};
//	    	res.sendFile(translatedPath, options, function(error) {
//	    		if (error) {
//                    res.writeHead(500);
//                    res.end();
//	    		}
//	    	});
//	    	break;
//    };
//});


module.exports = class CfeCdrPlugin extends CdrPlugin {
  constructor( urlBase ) {
    super( path.basename( __dirname ), path.join( __dirname, 'web', urlBase ) );
  }

  getContent() {
    var result = {
      shortDescription: 'Core Flight Executive',
      longDescription: 'Core Flight Executive services.',
      nodes: {
        es: {
          shortDescription: 'Essential Services',
          longDescription: 'Core essential services.',
          nodes: {
            main: {
              type: CdrPlugin.ContentType.LAYOUT,
              shortDescription: 'Main',
              longDescription: 'Main Essential Services.',
              filePath: '/es/main_layout.lyt'
            },
            appctrl: {
              type: CdrPlugin.ContentType.PANEL,
              shortDescription: 'Application Control',
              longDescription: 'Application start, stop, restart, and reload.',
              filePath: '/es/appctrl.pug'
            },
            cdh: {
              type: CdrPlugin.ContentType.PANEL,
              shortDescription: 'Command and Data Handling',
              longDescription: 'Command counters.',
              filePath: '/es/cdh.pug'
            },
            console: {
              type: CdrPlugin.ContentType.PANEL,
              shortDescription: 'Console',
              longDescription: 'System console.',
              filePath: '/es/console.pug'
            },
            logging: {
              type: CdrPlugin.ContentType.PANEL,
              shortDescription: 'Logging',
              longDescription: 'Essential Services logging status and control.',
              filePath: '/es/logging.pug'
            },
            memory: {
              type: CdrPlugin.ContentType.PANEL,
              shortDescription: 'Memory',
              longDescription: 'Memory and memory pool status and monitoring.',
              filePath: '/es/memory.pug'
            },
            reset: {
              type: CdrPlugin.ContentType.PANEL,
              shortDescription: 'Reset',
              longDescription: 'Core reset and restart.',
              filePath: '/es/reset.pug'
            },
            version: {
              type: CdrPlugin.ContentType.PANEL,
              shortDescription: 'Version',
              longDescription: 'Core versions.',
              filePath: '/es/version.pug'
            }
          }
        },
        evs: {
          shortDescription: 'Event Services',
          longDescription: 'Core event services.',
          nodes: {
            main: {
              type: CdrPlugin.ContentType.LAYOUT,
              shortDescription: 'Main',
              longDescription: 'Main Event Services.',
              filePath: '/evs/main_layout.lyt'
            },
            hk: {
              type: CdrPlugin.ContentType.PANEL,
              shortDescription: 'Housekeeping',
              filePath: '/evs/hk.pug'
            },
            efltr: {
              type: CdrPlugin.ContentType.PANEL,
              shortDescription: 'Event Filter (Generic)',
              filePath: '/evs/efltr.pug'
            },
            sch: {
              type: CdrPlugin.ContentType.PANEL,
              shortDescription: 'Scheduler',
              filePath: '/evs/sch.pug'
            },
            stats: {
              type: CdrPlugin.ContentType.PANEL,
              shortDescription: 'Stats',
              filePath: '/evs/stats.pug'
            }
          }
        },
        sb: {
          shortDescription: 'Software Bus',
          longDescription: 'Core software bus services.',
          nodes: {
            main: {
              type: CdrPlugin.ContentType.LAYOUT,
              shortDescription: 'Main',
              longDescription: 'Main Software Bus Services.',
              filePath: '/sb/main_layout.lyt'
            },
            hk: {
              type: CdrPlugin.ContentType.PANEL,
              shortDescription: 'Housekeeping',
              filePath: '/sb/hk.pug'
            },
            stats: {
              type: CdrPlugin.ContentType.PANEL,
              shortDescription: 'Statistics Summary',
              filePath: '/sb/stats.pug'
            },
            pipestats: {
              type: CdrPlugin.ContentType.PANEL,
              shortDescription: 'Pipe Statistics',
              filePath: '/sb/pipestats.pug'
            }
          }
        },
        tbl: {
          shortDescription: 'Table Services',
          longDescription: 'Core table services.',
          nodes: {
            main: {
              type: CdrPlugin.ContentType.LAYOUT,
              shortDescription: 'Main',
              longDescription: 'Main Table Services.',
              filePath: '/tbl/main_layout.lyt'
            },
            general: {
              type: CdrPlugin.ContentType.PANEL,
              shortDescription: 'General',
              filePath: '/tbl/general.pug'
            },
            registry: {
              type: CdrPlugin.ContentType.PANEL,
              shortDescription: 'Registry',
              filePath: '/tbl/registry.pug'
            }
          }
        },
        time: {
          shortDescription: 'Time Services',
          longDescription: 'Core time services.',
          nodes: {
            main: {
              type: CdrPlugin.ContentType.LAYOUT,
              shortDescription: 'Main',
              longDescription: 'Main time services.',
              filePath: '/time/main_layout.lyt'
            },
            hk: {
              type: CdrPlugin.ContentType.PANEL,
              shortDescription: 'Housekeeping',
              filePath: '/time/hk.pug'
            },
            diag_full: {
              type: CdrPlugin.ContentType.PANEL,
              shortDescription: 'Diagnostic (Full Message)',
              filePath: '/time/diag_full.pug'
            },
            diag_1: {
              type: CdrPlugin.ContentType.PANEL,
              shortDescription: 'Diagnostic (Partial - 1)',
              filePath: '/time/diag_1.pug'
            },
            diag_2: {
              type: CdrPlugin.ContentType.PANEL,
              shortDescription: 'Diagnostic (Partial - 2)',
              filePath: '/time/diag_2.pug'
            },
            diag_3: {
              type: CdrPlugin.ContentType.PANEL,
              shortDescription: 'Diagnostic (Partial - 3)',
              filePath: '/time/diag_3.pug'
            }
          }
        },
        pilot: {
          shortDescription: 'Pilot',
          longDescription: 'Pilot Services',
          nodes: {
            main: {
              type: CdrPlugin.ContentType.LAYOUT,
              shortDescription: 'PFD',
              longDescription: 'Primary Flight Dispaly',
              filePath: '/pilot/main_layout.lyt'
            },
            vm: {
              type: CdrPlugin.ContentType.PANEL,
              shortDescription: 'Vehicle Manager',
              filePath: '/pilot/vm.pug'
            },
            indicator: {
              type: CdrPlugin.ContentType.PANEL,
              shortDescription: 'Indicators',
              filePath: '/pilot/indicator.pug'
            },
            position: {
              type: CdrPlugin.ContentType.PANEL,
              shortDescription: 'Vehicle Position',
              filePath: '/pilot/position.pug'
            },
            misc: {
              type: CdrPlugin.ContentType.PANEL,
              shortDescription: 'Miscellaneous',
              filePath: '/pilot/misc.pug'
            },
            vitals: {
              type: CdrPlugin.ContentType.PANEL,
              shortDescription: 'Vitals',
              filePath: '/pilot/vitals.pug'
            },
            display: {
              type: CdrPlugin.ContentType.PANEL,
              shortDescription: 'Display',
              filePath: '/pilot/display.pug'
            },
            testwgt: {
              type: CdrPlugin.ContentType.WIDGET,
              shortDescription: 'Test Widget',
              filePath: '/pilot/testwgt.pug'
            }
          }
        }
      }
    };

    return result;
  }

  getLayouts() {
    var result = {
      name: 'cfe',
      text: 'Core Flight Executive',
      description: 'Core Flight Executive services.',
      nodes: [ {
        name: 'es',
        text: 'Essential Services',
        description: 'Core essential services.',
        nodes: [ {
          name: 'main',
          text: 'Main',
          filePath: '/es/main_layout.json',
          urlPath: '/cfe/es/main_layout.json',
          description: 'Main Essential Services.'
        } ]
      } ]
    };

    return result;
  }



  getPanels() {
    var result = {
      name: 'cfe',
      text: 'Core Flight Executive',
      description: 'Core Flight Executive services.',
      nodes: [ {
        name: 'es',
        text: 'Essential Services',
        description: 'Core essential services.',
        nodes: [ {
            name: 'appctrl',
            text: 'Application Control',
            filePath: '/es/appctrl.pug',
            urlPath: '/cfe/es/appctrl.pug',
            description: 'Application start, stop, restart, and reload.'
          },
          {
            name: 'cdh',
            text: 'Command and Data Handling',
            filePath: '/es/cdh.pug',
            urlPath: '/cfe/es/cdh.pug',
            description: 'Command counters.'
          },
          {
            name: 'console',
            text: 'Console',
            filePath: '/es/console.pug',
            urlPath: '/cfe/es/console.pug',
            description: 'System console.'
          },
          {
            name: 'logging',
            text: 'Logging',
            filePath: '/es/logging.pug',
            urlPath: '/cfe/es/logging.pug',
            description: 'Essential Services logging status and control.'
          },
          {
            name: 'memory',
            text: 'Memory',
            filePath: '/es/memory.pug',
            urlPath: '/cfe/es/memory.pug',
            description: 'Memory and memory pool status and monitoring.'
          },
          {
            name: 'reset',
            text: 'Reset',
            filePath: '/es/reset.pug',
            urlPath: '/cfe/es/reset.pug',
            description: 'Core reset and restart.'
          },
          {
            name: 'version',
            text: 'Version',
            filePath: '/es/version.pug',
            urlPath: '/cfe/es/version.pug',
            description: 'Core versions.'
          }
        ]
      }, {
        name: 'evs',
        text: 'Event Services',
        description: 'Core event services.',
        nodes: [ {
          name: 'main',
          text: 'Main',
          filePath: '/evs/main.pug',
          urlPath: '/cfe/evs/main.pug',
          description: ''
        } ]
      }, {
        name: 'sb',
        text: 'Software Bus',
        description: 'Core software bus services.',
        nodes: [ {
          name: 'main',
          text: 'Main',
          filePath: '/sb/main.pug',
          urlPath: '/cfe/sb/main.pug',
          description: ''
        } ]
      }, {
        name: 'tbl',
        text: 'Table Services',
        description: 'Core table services.',
        nodes: [ {
          name: 'main',
          text: 'Main',
          filePath: '/tbl/main.pug',
          urlPath: '/cfe/tbl/main.pug',
          description: ''
        } ]
      }, {
        name: 'time',
        text: 'Time Services',
        description: 'Core time services.',
        nodes: [ {
          name: 'main',
          text: 'Main',
          filePath: '/time/main.pug',
          urlPath: '/cfe/time/main.pug',
          description: ''
        } ]
      } ]
    };

    return result;
  };
};

//var plugin = new CfeCdrPlugin();

//let CfeCdrPlugin = new class extends CdrPlugin {