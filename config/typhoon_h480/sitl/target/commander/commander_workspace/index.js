var path = require('path');
var fs = require('fs');

var Commander = require(path.join(global.CDR_INSTALL_DIR, 'commander'));
var BinaryEncoder = require(path.join(global.CDR_INSTALL_DIR, 'binary-encoder'));
var BinaryDecoder = require(path.join(global.CDR_INSTALL_DIR, 'binary-decoder'));
var UdpStdProvider = require(path.join(global.CDR_INSTALL_DIR, 'udp-std-provider'));
var VariableServer = require(path.join(global.CDR_INSTALL_DIR, 'variable-server'));
var ProtobufEncoder = require(path.join(global.CDR_INSTALL_DIR, 'protobuf-encoder'));
var ProtobufDecoder = require(path.join(global.CDR_INSTALL_DIR, 'protobuf-decoder'));
var ConfigDatabase = require(path.join(global.CDR_INSTALL_DIR, 'config-database'));

var commander = new Commander(global.CDR_WORKSPACE, `${global.CDR_WORKSPACE}/etc/commander-config.json`);
var binaryEncoder = new BinaryEncoder(global.CDR_WORKSPACE, `${global.CDR_WORKSPACE}/etc/binary-encoder-config.json`);
var binaryDecoder = new BinaryDecoder(global.CDR_WORKSPACE, `${global.CDR_WORKSPACE}/etc/binary-decoder-config.json`);
var variableServer = new VariableServer(`${global.CDR_WORKSPACE}/etc/variable-server-config.json`);
var fswConnector = new UdpStdProvider(`${global.CDR_WORKSPACE}/etc/udpstdprovider-config.json`);
var pylinerConnector = new UdpStdProvider(`${global.CDR_WORKSPACE}/etc/pyliner-connector-config.json`);
var protobufEncoder = new ProtobufEncoder(global.CDR_WORKSPACE, `${global.CDR_WORKSPACE}/etc/protobuf-encoder-config.json`);
var protobufDecoder = new ProtobufDecoder(global.CDR_WORKSPACE, `${global.CDR_WORKSPACE}/etc/protobuf-decoder-config.json`);
var configDB = new ConfigDatabase(global.CDR_WORKSPACE, `${global.CDR_WORKSPACE}/etc/config-database-config.json`);

global.COMMANDER = commander;

var airliner = commander.addInstance('airliner', function(instance) {
	instance.addApp('binary-encoder',    binaryEncoder);
	instance.addApp('binary-decoder',    binaryDecoder);
	instance.addApp('fsw-connector',     fswConnector);
	instance.addApp('pyliner-connector', pylinerConnector);
	instance.addApp('variable-server',   variableServer);
	instance.addApp('protobuf-encoder',  protobufEncoder);
	instance.addApp('protobuf-decoder',  protobufDecoder);
	instance.addApp('config-database',   configDB);
	
	commander.setDefaultInstance(instance);
	
    var outFiles = [];
    var fullPath = path.join(global.CDR_WORKSPACE, 'plugins');
    
    parsePluginPath(instance, path.join(fullPath, 'cfe/index.js'), '/');
    findIndex(path.join(fullPath, 'apps'), function(err, results) {
    	if(err) throw err;
    	for(var i = 0; i < results.length; ++i) {
    		parsePluginPath(instance, results[i], '/');
    	}
    });
});



function parsePluginPath(instance, indexFilePath, basePath) {
    if (fs.existsSync(indexFilePath)) {
        var NewPluginClass = require(path.dirname(indexFilePath));
        var newPlugin = new NewPluginClass(basePath);
        
        newPlugin.initialize(commander, instance);
	} else {
		//parsePluginPath(pluginPath, newBasePath);
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