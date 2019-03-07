'use strict';

var path = require('path');

const CdrPlugin = require(path.join(global.CDR_INSTALL_DIR, '/commander/classes/CdrPlugin')).CdrPlugin;

module.exports = class CfeCdrPlugin extends CdrPlugin {
  constructor(urlBase) {
    super('to', path.join(__dirname, 'web', urlBase));
  }
  
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

  getContent() {
    var result = {
      shortDescription: 'Telemetry Output',
      longDescription: 'Telemetry Output',
      nodes: {
				main: {
					type: CdrPlugin.ContentType.LAYOUT,
					shortDescription: 'Main',
					longDescription: 'Main AMC.',
					filePath: '/main_layout.lyt'
				},
				cdh: {
					type: CdrPlugin.ContentType.PANEL,
					shortDescription: 'TO Command Counters',
					longDescription: 'Telemetry Output Command and Data Handling',
					filePath: '/cdh.pug'
				},
				hk: {
					type: CdrPlugin.ContentType.PANEL,
					shortDescription: 'TO Housekeeping',
					longDescription: 'Telemetry Output Housekeeping.',
					filePath: '/hk.pug'
				},
				diag: {
					type: CdrPlugin.ContentType.PANEL,
					shortDescription: 'TO Diagnostic',
					longDescription: 'Telemetry Output Diagnostic.',
					filePath: '/diag.pug'
				},
				diag_msg_flow: {
					type: CdrPlugin.ContentType.PANEL,
					shortDescription: 'TO Diagnostic - Message Flows',
					longDescription: 'Telemetry Output Diagnostic - Message Flows.',
					filePath: '/diag_msg_flow.pug'
				},
				diag_pqueue: {
					type: CdrPlugin.ContentType.PANEL,
					shortDescription: 'TO Diagnostic - Priority Queues',
					longDescription: 'Telemetry Output Diagnostic - Priority Queues.',
					filePath: '/diag_pqueue.pug'
				},
				diag_oqueue: {
					type: CdrPlugin.ContentType.PANEL,
					shortDescription: 'TO Diagnostic - Output Queue',
					longDescription: 'Telemetry Output Diagnostic - Output Queue.',
					filePath: '/diag_oqueue.pug'
				},
				tlm_app: {
					type: CdrPlugin.ContentType.PANEL,
					shortDescription: 'Tlm Ctrl',
					longDescription: 'Telemetry Control',
					filePath: '/tlm_app.pug'
				}
      }
    };

    return result;
  }
};

//var plugin = new CfeCdrPlugin();

//let CfeCdrPlugin = new class extends CdrPlugin {
