

var binaryEncoder = new BinaryEncoder(CMDR_WORKSPACE, `${CMDR_WORKSPACE}/etc/binary-encoder-config.json`);
var binaryDecoder = new BinaryDecoder(CMDR_WORKSPACE, `${CMDR_WORKSPACE}/etc/binary-decoder-config.json`);
var variableServer = new VariableServer(`${CMDR_WORKSPACE}/etc/variable-server-config.json`);
var fswConnector = new UdpStdProvider(`${CMDR_WORKSPACE}/etc/udpstdprovider-config.json`);
var pylinerConnector = new UdpStdProvider(`${CMDR_WORKSPACE}/etc/pyliner-connector-config.json`);
var clientConnector = new ClientConnector(CMDR_WORKSPACE, `${CMDR_WORKSPACE}/etc/client-connector-config.json`, global.NODE_APP);
var protobufEncoder = new ProtobufEncoder(CMDR_WORKSPACE, `${CMDR_WORKSPACE}/etc/protobuf-encoder-config.json`);
var protobufDecoder = new ProtobufDecoder(CMDR_WORKSPACE, `${CMDR_WORKSPACE}/etc/protobuf-decoder-config.json`);

var airliner = commander.addInstance('airliner', function(instance) {
	instance.addApp('binary-encoder',    binaryEncoder);
	instance.addApp('binary-decoder',    binaryDecoder);
	instance.addApp('fsw-connector',     fswConnector);
	instance.addApp('pyliner-connector', pylinerConnector);
	instance.addApp('variable-server',   variableServer);
	instance.addApp('client-connector',  clientConnector);
	instance.addApp('protobuf-encoder',  protobufEncoder);
	instance.addApp('protobuf-decoder',  protobufDecoder);
});