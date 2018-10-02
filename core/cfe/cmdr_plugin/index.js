var path = require('path');
var fs = require('fs');

var Commander = require(path.join(global.CDR_INSTALL_DIR, 'commander'));
var BinaryEncoder = require(path.join(global.CDR_INSTALL_DIR, 'binary-encoder'));
var BinaryDecoder = require(path.join(global.CDR_INSTALL_DIR, 'binary-decoder'));
var UdpStdProvider = require(path.join(global.CDR_INSTALL_DIR, 'udp-std-provider'));
var VariableServer = require(path.join(global.CDR_INSTALL_DIR, 'variable-server'));
var ProtobufEncoder = require(path.join(global.CDR_INSTALL_DIR, 'protobuf-encoder'));
var ProtobufDecoder = require(path.join(global.CDR_INSTALL_DIR, 'protobuf-decoder'));

var commander = new Commander(global.CDR_WORKSPACE, `${global.CDR_WORKSPACE}/etc/commander-config.json`);
var binaryEncoder = new BinaryEncoder(global.CDR_WORKSPACE, `${global.CDR_WORKSPACE}/etc/binary-encoder-config.json`);
var binaryDecoder = new BinaryDecoder(global.CDR_WORKSPACE, `${global.CDR_WORKSPACE}/etc/binary-decoder-config.json`);
var variableServer = new VariableServer(`${global.CDR_WORKSPACE}/etc/variable-server-config.json`);
var fswConnector = new UdpStdProvider(`${global.CDR_WORKSPACE}/etc/udpstdprovider-config.json`);
var pylinerConnector = new UdpStdProvider(`${global.CDR_WORKSPACE}/etc/pyliner-connector-config.json`);
var protobufEncoder = new ProtobufEncoder(global.CDR_WORKSPACE, `${global.CDR_WORKSPACE}/etc/protobuf-encoder-config.json`);
var protobufDecoder = new ProtobufDecoder(global.CDR_WORKSPACE, `${global.CDR_WORKSPACE}/etc/protobuf-decoder-config.json`);

var airliner = commander.addInstance('airliner', function(instance) {
	instance.addApp('binary-encoder',    binaryEncoder);
	instance.addApp('binary-decoder',    binaryDecoder);
	instance.addApp('fsw-connector',     fswConnector);
	instance.addApp('pyliner-connector', pylinerConnector);
	instance.addApp('variable-server',   variableServer);
	instance.addApp('protobuf-encoder',  protobufEncoder);
	instance.addApp('protobuf-decoder',  protobufDecoder);
	
	commander.setDefaultInstance(instance);
	
    var outFiles = [];
    var fullPath = path.join(global.CDR_WORKSPACE, 'plugins');
    parsePluginPath(fullPath, '/');
});



function parsePluginPath(inPath, basePath) {
    fs.readdir(inPath, function (err, files) {
        if (err == null) {
            for (var i = 0; i < files.length; ++i) {
            	var pluginPath = path.join(inPath, files[i]);
            	var newBasePath = path.join(basePath);
                var stats = fs.statSync(pluginPath);
                if (stats.isDirectory()) {
                	var indexFilePath = path.join(pluginPath, 'index.js');
                	if (fs.existsSync(indexFilePath)) {
                        var NewPluginClass = require(pluginPath);
                        var newPlugin = new NewPluginClass(newBasePath);
                	} else {
                		//parsePluginPath(pluginPath, newBasePath);
                	}
                }
            };
        };
    });
}