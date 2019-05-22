'use strict';

var path = require('path');

const CdrFlightAppsPlugin = require(path.join(global.CDR_INSTALL_DIR, '/commander/classes/CdrFlightAppsPlugin')).CdrFlightAppsPlugin;

module.exports = class CfeCdrFlightAppsPlugin extends CdrFlightAppsPlugin {
    constructor(config) {
        config.name = 'to';
        config.webRoot = path.join( __dirname, 'web');  
        super(config);

        var content = {
            to: {         
            	shortDescription: 'Telemetry Output',
                longDescription: 'Telemetry Output',
                nodes: {
          		    main: {
          				type: CdrFlightAppsPlugin.ContentType.LAYOUT,
          				shortDescription: 'Main',
          				longDescription: 'Main AMC.',
          				filePath: '/main_layout.lyt'
          			},
          			cdh: {
          				type: CdrFlightAppsPlugin.ContentType.PANEL,
          				shortDescription: 'TO Command Counters',
          				longDescription: 'Telemetry Output Command and Data Handling',
          				filePath: '/cdh.pug'
          			},
          			hk: {
          				type: CdrFlightAppsPlugin.ContentType.PANEL,
          				shortDescription: 'TO Housekeeping',
          				longDescription: 'Telemetry Output Housekeeping.',
          				filePath: '/hk.pug'
          			},
          			diag: {
          				type: CdrFlightAppsPlugin.ContentType.PANEL,
          				shortDescription: 'TO Diagnostic',
          				longDescription: 'Telemetry Output Diagnostic.',
          				filePath: '/diag.pug'
          			},
          			diag_msg_flow: {
          				type: CdrFlightAppsPlugin.ContentType.PANEL,
          				shortDescription: 'TO Diagnostic - Message Flows',
          				longDescription: 'Telemetry Output Diagnostic - Message Flows.',
          				filePath: '/diag_msg_flow.pug'
          			},
          			diag_pqueue: {
          				type: CdrFlightAppsPlugin.ContentType.PANEL,
          				shortDescription: 'TO Diagnostic - Priority Queues',
          				longDescription: 'Telemetry Output Diagnostic - Priority Queues.',
          				filePath: '/diag_pqueue.pug'
          			},
          			diag_oqueue: {
          				type: CdrFlightAppsPlugin.ContentType.PANEL,
          				shortDescription: 'TO Diagnostic - Output Queue',
          				longDescription: 'Telemetry Output Diagnostic - Output Queue.',
          				filePath: '/diag_oqueue.pug'
          			},
          			tlm_app: {
          				type: CdrFlightAppsPlugin.ContentType.PANEL,
          				shortDescription: 'Tlm Ctrl',
          				longDescription: 'Telemetry Control',
          				filePath: '/tlm_app.pug'
          			}
                }
            }
        };
        
      	this.addContent(content);
    };
  
  getMessageIDsAndMacros(args, cb) {
      var msgs = [];
      var queryString = '$.Airliner.apps';
      global.COMMANDER.queryConfigDB(queryString, function (apps) {
          for(var appName in apps[0]) {
              var operations = apps[0][appName].operations;
              for(var msgName in operations) {
                  var msg = operations[msgName];
                  if(msg.hasOwnProperty('macro')) {
                      if(msg.hasOwnProperty('airliner_mid')) {
                          var msgID = parseInt(msg.airliner_mid);
                          var duplicate = false;
                                                    
                          for(var i = 0; i < msgs.length; ++i) {
                              if(msgs[i].msgID === msgID) {
                                  duplicate = true;
                              }
                          }
                          
                          if(!duplicate) {
                              msgs.push({msgID: msgID, macro: msg.macro});
                          }
                      }
                  }
              }
          }
          cb(msgs);
      });
      
  }
  
  getFunctions() {
      var result = [
          this.getMessageIDsAndMacros
      ];
      
      return result;
  }


};

//var plugin = new CfeCdrPlugin();

//let CfeCdrPlugin = new class extends CdrPlugin {
