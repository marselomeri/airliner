'use strict';
const dgram = require( 'dgram' );

module.exports = class VideoServer {
  constructor() {}

  setInstanceEmitter( newEmitter ) {
    var self = this;
    this.instanceEmitter = newEmitter;

    // video server
    this.socket = dgram.createSocket( 'udp4' );

    this.socket.on( 'error', ( err ) => {
      console.log( `server error:\n${err.stack}` );
      this.socket.close();
    } );

    this.socket.on( 'message', ( frame, info ) => {
      var imageObject = {
        image: true,
        buffer: frame.toString( 'base64' )
      }
      this.instanceEmitter.emit( 'video-stream', imageObject );

      //socket.volatile.emit( 'stream', {
      //  image: true,
      //  buffer: msg.toString( 'base64' )
      //} );
    } );

    this.socket.bind( 3001 );

    global.NODE_APP.videoServer = this.socket;

    this.instanceEmitter.emit( 'advertise-stream', 'video-stream' );

    //this.instanceEmitter.on( config.get( 'binaryInputStreamID' ), function( buffer ) {
    //  self.processBinaryMessage( buffer );
    //} );
  }
}