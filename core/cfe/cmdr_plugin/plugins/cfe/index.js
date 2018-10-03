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
	
	
	
	getLayouts() {
        var result = {
            name: 'cfe',
            text: 'Core Flight Executive',
            description: 'Core Flight Executive services.',
            nodes: [
                {
                    name: 'es',
                    text: 'Essential Services',
                    description: 'Core essential services.',
                    nodes: [
                        {
                            name: 'main',
                            text: 'Main',
                            filePath: '/es/main_layout.json',
                            urlPath: '/cfe/es/main_layout.json',
                            description: 'Main Essential Services.'
                        }
                    ]
                }
            ]
        };
        
        return result;    
	}
	

    
    getPanels() {
        var result = {
            name: 'cfe',
            text: 'Core Flight Executive',
            description: 'Core Flight Executive services.',
            nodes: [
                {
                    name: 'es',
                    text: 'Essential Services',
                    description: 'Core essential services.',
                    nodes: [
                        {
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
                },{
                    name: 'evs',
                    text: 'Event Services',
                    description: 'Core event services.',
                    nodes: [
                        {
                            name: 'main',
                            text: 'Main',
                            filePath: '/evs/main.pug',
                            urlPath: '/cfe/evs/main.pug',
                            description: ''
                        }
                    ]
                },{
                    name: 'sb',
                    text: 'Software Bus',
                    description: 'Core software bus services.',
                    nodes: [
                        {
                            name: 'main',
                            text: 'Main',
                            filePath: '/sb/main.pug',
                            urlPath: '/cfe/sb/main.pug',
                            description: ''
                        }
                    ]
                },{
                    name: 'tbl',
                    text: 'Table Services',
                    description: 'Core table services.',
                    nodes: [
                        {
                            name: 'main',
                            text: 'Main',
                            filePath: '/tbl/main.pug',
                            urlPath: '/cfe/tbl/main.pug',
                            description: ''
                        }
                    ]
                },{
                    name: 'time',
                    text: 'Time Services',
                    description: 'Core time services.',
                    nodes: [
                        {
                            name: 'main',
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
