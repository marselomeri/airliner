module.exports = function(myConfig, index){
	var express = require('express');
	var app = module.exports = express();
    var config_entry = {}
    
	app.set('views', __dirname);
	app.set('view engine', 'jade');
	
	app.get('/core', function(req, res) {
		res.render('index', {
			config: myConfig,
			active: './core',
			title: 'Core Flight Executive',
			application: 'CFE_ES',
			description: 'Core Flight Executive Essential Services telemetry and commands.'
		});
	});
	
	app.get('/core/events', function(req, res) {
		res.render('events', {
			config: myConfig,
			active: './core',
			title: 'Event Viewer',
			application: 'CFE_EVS',
			description: 'Core Flight Executive Event Services message viewer.'
		});
	});
	
	app.get('/core/cfe_evs', function(req, res) {
		res.render('cfe_evs/index', {
			config: myConfig,
			active: './core',
			title: 'Event Services',
			application: 'CFE_EVS',
			description: 'Core Flight Executive Event Services commands and telemetry.'
		});
	});
	
	app.get('/core/cfe_sb', function(req, res) {
		res.render('cfe_sb/index', {
			config: myConfig,
			active: './core',
			title: 'Software Bus',
			application: 'CFE_SB',
			description: 'Core Flight Executive Software Bus commands and telemetry.'
		});
	});
	
	app.get('/core/cfe_tbl', function(req, res) {
		res.render('cfe_tbl/index', {
			config: myConfig,
			active: './core',
			title: 'Table Services',
			application: 'CFE_TBL',
			description: 'Core Flight Executive Table Services commands and telemetry.'
		});
	});
	
	app.get('/core/cfe_time', function(req, res) {
		res.render('cfe_time/index', {
			config: myConfig,
			active: './core',
			title: 'Time Services',
			application: 'CFE_TIME',
			description: 'Core Flight Executive Time Services commands and telemetry.'
		});
	});
	
	return app;
};


