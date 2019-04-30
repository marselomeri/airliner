'use strict';

var path = require('path');

const CdrFlightAppsPlugin = require(path.join(global.CDR_INSTALL_DIR, '/commander/classes/CdrFlightAppsPlugin')).CdrFlightAppsPlugin;

module.exports = class CfeCdrFlightAppsPlugin extends CdrFlightAppsPlugin {
    constructor() {
        super(path.join(__dirname, 'web'));
        
        var content = {
        	sch: {
                shortDescription: 'Scheduler',
                longDescription: 'Scheduler.',
                nodes: {
                    main: {
                        type: CdrFlightAppsPlugin.ContentType.LAYOUT,
                        shortDescription: 'Main',
                        longDescription: 'Main SCH.',
                        filePath: '/main_layout.lyt'
                    },
                    hk: {
                        type: CdrFlightAppsPlugin.ContentType.PANEL,
                        shortDescription: 'Housekeeping (SCH)',
                        longDescription: 'Scheduler housekeeping telemetry.',
                        filePath: '/hk.pug'
                    },
                    sch: {
                        type: CdrFlightAppsPlugin.ContentType.PANEL,
                        shortDescription: 'Schedule Control (General)',
                        longDescription: 'Schedule control.',
                        filePath: '/sch.pug'
                    },
                    diag: {
                        type: CdrFlightAppsPlugin.ContentType.PANEL,
                        shortDescription: 'Schedule Diagnostics',
                        longDescription: 'Schedule Diagnostics.',
                        filePath: '/diag.pug'
                    },
                    app_sch: {
                        type: CdrFlightAppsPlugin.ContentType.PANEL,
                        shortDescription: 'SCH Ctrl',
                        longDescription: 'Application specific scheduling data.',
                        filePath: '/app-sch.pug'
                    }
                }
            }
        };
    
        this.addContent(content);
    };
        
  

  getMessageIDsAndMacros( args, cb ) {
    var msgs = [];
    var queryString = '$.Airliner.apps';
    global.COMMANDER.queryConfigDB( queryString, function( apps ) {
      for ( var appName in apps[ 0 ] ) {
        var operations = apps[ 0 ][ appName ].operations;
        for ( var msgName in operations ) {
          var msg = operations[ msgName ];
          if ( msg.hasOwnProperty( 'macro' ) ) {
            if ( msg.hasOwnProperty( 'airliner_mid' ) ) {
              var msgID = parseInt( msg.airliner_mid );
              var duplicate = false;

              for ( var i = 0; i < msgs.length; ++i ) {
                if ( msgs[ i ].msgID === msgID ) {
                  duplicate = true;
                }
              }

              if ( !duplicate ) {
                msgs.push( {
                  msgID: msgID,
                  macro: msg.macro
                } );
              }
            }
          }
        }
      }
      cb( msgs );
    } );

  }
  getMessageIDsAndMacrosFromMsgName( args, cb ) {
    var msgs = [];




    if ( args.hasOwnProperty( 'opsPaths' ) ) {
      for ( var i in args.opsPaths ) {

        var reqAppName = undefined;
        var reqMsgName = undefined;

        var opsPathArr = args.opsPaths[ i ].split( '/' );
        reqAppName = opsPathArr[ 1 ] === '' ? undefined : opsPathArr[ 1 ];
        reqMsgName = opsPathArr[ 2 ] === '' ? undefined : opsPathArr[ 2 ];
        var queryString = '$.Airliner.apps';
        if ( reqAppName != undefined ) {
          queryString = queryString + '.' + reqAppName;
        }
        global.COMMANDER.queryConfigDB( queryString, function( apps ) {
          if ( apps[ 0 ].hasOwnProperty( 'operations' ) ) {
            var operations = apps[ 0 ].operations;
            if ( operations.hasOwnProperty( reqMsgName ) ) {
              var msg = operations[ reqMsgName ];
              if ( msg.hasOwnProperty( 'macro' ) && msg.hasOwnProperty( 'airliner_mid' ) ) {
                var msgID = parseInt( msg.airliner_mid );
                var msgMacro = msg.macro;
                var duplicate = false;
                for ( var i = 0; i < msgs.length; ++i ) {
                  if ( msgs[ i ].msgID === msgID ) {
                    duplicate = true;
                  }
                }
                if ( !duplicate ) {
                  msgs.push( {
                    msgID: msgID,
                    macro: msgMacro
                  } );
                }
              }
            }
          }
        } );
      }
    }

    cb( msgs );

  }

  getFunctions() {
    var result = [
      this.getMessageIDsAndMacros,
      this.getMessageIDsAndMacrosFromMsgName
    ];

    return result;
  }

};

//var plugin = new CfeCdrPlugin();

//let CfeCdrPlugin = new class extends CdrPlugin {