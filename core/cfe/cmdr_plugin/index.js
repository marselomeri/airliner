'use strict';

var path = require('path');

const CdrPlugin = require(path.join(global.CDR_INSTALL_DIR, '/commander/classes/CdrPlugin'));
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
	constructor(urlBase) {
		super(path.join(__dirname, 'web', urlBase));	
	}
	
	getPanels() {
		var result = {
			text: 'Core Flight Executive',
			description: 'Core Flight Executive services.',
			nodes: [
				{
					text: 'Essential Services',
					description: 'Core essential services.',
					nodes: [
						{
							text: 'Application Control',
							filePath: '/es/appctrl.pug',
							urlPath: '/cfe/es/appctrl.pug',
							description: 'Application start, stop, restart, and reload.'
				        },
						{
							text: 'Command and Data Handling',
							filePath: '/es/cdh.pug',
							urlPath: '/cfe/es/cdh.pug',
							description: 'Command counters.'
				        },
                        {
                            text: 'Console',
                            filePath: '/es/console.pug',
                            urlPath: '/cfe/es/console.pug',
                            description: 'System console.'
                        },
						{
							text: 'Logging',
							filePath: '/es/logging.pug',
							urlPath: '/cfe/es/logging.pug',
							description: 'Essential Services logging status and control.'
				        },
                        {
                            text: 'Memory',
                            filePath: '/es/memory.pug',
                            urlPath: '/cfe/es/memory.pug',
                            description: 'Memory and memory pool status and monitoring.'
                        },
						{
							text: 'Reset',
							filePath: '/es/reset.pug',
							urlPath: '/cfe/es/reset.pug',
							description: 'Core reset and restart.'
				        },
						{
							text: 'Version',
							filePath: '/es/version.pug',
							urlPath: '/cfe/es/version.pug',
							description: 'Core versions.'
				        }
			        ]
			    },{
                    text: 'Event Services',
                    description: 'Core event services.',
                    nodes: [
                        {
                            text: 'Main',
                            filePath: '/evs/main.pug',
                            urlPath: '/cfe/evs/main.pug',
                            description: ''
                        }
                    ]
                },{
					text: 'Software Bus',
                    description: 'Core software bus services.',
					nodes: [
						{
							text: 'Main',
							filePath: '/sb/main.pug',
							urlPath: '/cfe/sb/main.pug',
                            description: ''
				        }
					]
			    },{
					text: 'Table Services',
                    description: 'Core table services.',
					nodes: [
						{
							text: 'Main',
							filePath: '/tbl/main.pug',
							urlPath: '/cfe/tbl/main.pug',
                            description: ''
				        }
					]
			    },{
					text: 'Time Services',
                    description: 'Core time services.',
					nodes: [
						{
							text: 'Main',
							filePath: '/time/main.pug',
							urlPath: '/cfe/time/main.pug',
                            description: ''
				        }
					]
			    }
		    ]
		};
		
		return result;
	};
};

//var plugin = new CfeCdrPlugin();

//let CfeCdrPlugin = new class extends CdrPlugin {
