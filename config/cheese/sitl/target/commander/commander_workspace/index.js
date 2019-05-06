var path = require('path');
var fs = require('fs');

var Commander = require(path.join(global.CDR_INSTALL_DIR, 'commander'));
var VariableServer = require(path.join(global.CDR_INSTALL_DIR, 'variable-server'));
var PanelSim = require('./panel_sim');
var PanelDisplay = require('./panel_display');

var commander = new Commander(global.CDR_WORKSPACE, `${global.CDR_WORKSPACE}/etc/commander-config.json`);

global.COMMANDER = commander;

var airliner = commander.addInstance('airliner', function(namespace) {
    var variableServer = new VariableServer({namespace: namespace, name: 'variable-server', workspace: global.CDR_WORKSPACE, configFile: `${global.CDR_WORKSPACE}/etc/variable-server-config.json`});
    var panelSim = new PanelSim({namespace: namespace, name: 'panel-sim', workspace: global.CDR_WORKSPACE, configFile: `${global.CDR_WORKSPACE}/etc/panel-sim-config.json`});
    var panelDisplay = new PanelDisplay({namespace: namespace, name: 'panel-display', workspace: global.CDR_WORKSPACE, configFile: `${global.CDR_WORKSPACE}/etc/panel-display-config.json`});
	
    commander.setDefaultInstance(namespace);
	
    var outFiles = [];
    var fullPath = path.join(global.CDR_WORKSPACE, 'plugins');
});



function parsePluginPath(instance, indexFilePath, basePath) {
    if (fs.existsSync(indexFilePath)) {
        var config = {namespace: instance};
        var NewPluginClass = require(path.dirname(indexFilePath));
        var newPlugin = new NewPluginClass(config);
        
        newPlugin.initialize(config);
    } else {
	parsePluginPath(pluginPath, newBasePath);
    }
}



function findIndex(dir, cb) {
	var results = [];
	fs.readdir(dir, function(err, list) {
		if (err) return cb(err);
		var i = 0;
		(function next() {
			var file = list[i++];
			if (!file) return cb(null, results);
			file = dir + '/' + file;
			fs.stat(file, function(err, stat) {
				if (stat && stat.isDirectory()) {
					findIndex(file, function(err, res) {
						results = results.concat(res);
						next();
					});
				} else {
					if(path.basename(file) === 'index.js') {
						results.push(file);
						return cb(null, results)
					} 
					next();
				}
			});
		})();
	});
};