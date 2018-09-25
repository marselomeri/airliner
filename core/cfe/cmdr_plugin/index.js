'use strict';

var path = require('path');

const CdrPlugin = require('/home/users/mbenson/git/airliner/tools/commander/commander/classes/CdrPlugin');
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
			nodes: [
				{
					text: 'Essential Services',
					nodes: [
						{
							text: 'Main',
							filePath: '/es/main.pug',
							urlPath: '/cfe/es/main.pug',
				        },
						{
							text: 'Application Control',
							filePath: '/es/appctrl.pug',
							urlPath: '/cfe/es/appctrl.pug',
				        },
						{
							text: 'Console',
							filePath: '/es/console.pug',
							urlPath: '/cfe/es/console.pug',
				        },
						{
							text: 'Memory',
							filePath: '/es/memory.pug',
							urlPath: '/cfe/es/memory.pug',
				        },
						{
							text: 'Performance Monitor',
							filePath: '/es/perfmon.pug',
							urlPath: '/cfe/es/perfmon.pug',
				        }
			        ]
			    },{
					text: 'Software Bus',
					nodes: [
						{
							text: 'Main',
							filePath: '/sb/main.pug',
							urlPath: '/cfe/sb/main.pug',
				        }
					]
			    },{
					text: 'Table Services',
					nodes: [
						{
							text: 'Main',
							filePath: '/tbl/main.pug',
							urlPath: '/cfe/tbl/main.pug',
				        }
					]
			    },{
					text: 'Time Services',
					nodes: [
						{
							text: 'Main',
							filePath: '/time/main.pug',
							urlPath: '/cfe/time/main.pug',
				        }
					]
			    },{
					text: 'Event Services',
					nodes: [
						{
							text: 'Main',
							filePath: '/evs/main.pug',
							urlPath: '/cfe/evs/main.pug',
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
