'use strict';
//Tools
function getDate(format){
    var tempstore =new Date();
    try{
        if(format=='d'){
        return tempstore;
        }
        else if (format=='s'){
        return tempstore.getTime();
        }
    }
    catch(err){
    console.log('DATE_TIME_ERR: ',err);
    }
}
function sleep(ms) {
  return new Promise(resolve => setTimeout(resolve, ms));
}

async function delay(socket,msg,te) {
  await sleep(te);
  socket.send(msg);

}

//Session
var Session = function(){
    this.activeInstances = [];
    this.subscribers = [];
    this.eventSubscribers = [];
    this.videoSubscribers = [];
    this.alarmSubscribers = [];
    this.deferredSubscribers = [];
    this.defaultInstance = null;
    this.cmdSeqNum = 0;
    this.tlmSeqNum = 0;
    this.cmdInfo = [];

};

Session.prototype = {
    startHPS:function(name,route,message,cb){
        var hps = new PrioritySocket();
        console.log('$$$$$$$$$$$$$$$$$$$$$',message);
        hps.setName(name);
        hps.subscribe(route,message,cb);
        //console.log(hps);
        this.subscribers.push(hps);
    },

    unsubscribe:function(name,route,message,cb){
        var hps_unsubscribe = new PrioritySocket();
        hps_unsubscribe.setName(name)
        hps_unsubscribe.unsubscribe2(route,message,cb);//SEND UNSUBSCRIBE SIGNAL OVER SUBSCRIBE


    },

    stopPS:function(name){
        for( var i=0; i<this.subscribers.length;i++){
            if(this.subscribers[i].getName() == name){
                this.subscribers[i].unsubscribe();
            }
            this.subscribers.splice(i,1);
        }
    },

    startLPS:function(name,route,message,cb,te){
        var lps = new PrioritySocket();
        //console.log(lps);
        lps.setName(name);
        lps.lazySubscribe(route,message,cb,te);
        //console.log(lps);
        this.subscribers.push(lps);
    },

    pull:function(name,route,message,cb){
        var puller = new PrioritySocket();
        puller.setName(name);
        puller.socketPull(route,message,cb);
    },

    push:function(name,route,message){
        var pusher = new PrioritySocket();
        //console.log(pusher);
        pusher.setName(name);
        pusher.socketPush(route,message);
        //console.log(pusher);

    },

    setDefaultInstance:function(instance){
        this.defaultInstance = instance;
        var pusher = new PrioritySocket();
        pusher.socketPush('defaultInst',instance);

    },
    unsubscribeAll:function(){
        //for( var i=0; i<this.subscribers.length;i++){
        //    var name = 'LooseTelemetry';
        //    var msg = this.subscribers[i]['msg'];
        //    this.unsubscribe(name,'tlm_cmd_u',msg,function(d){
        //    console.log('Unssubscribing object ',i);
        //    });
        //    this.subscribers.splice(i,1);
        //}
    },

    sendCommand:function(a,b){
        var obj = {"name":a,"args":b}
        obj = JSON.stringify(obj)
        var pusher = new PrioritySocket();
        pusher.socketPush('cmd_s',obj);
        console.log(a,'======',b);
    },

};


//Prioritization
var PrioritySocket = function(){
    this.name = 'Player_Unknown';//Should be Unique
    this.ws_scheme = window.location.protocol == "https:" ? "wss" : "ws";
    this.isSocketConnected = false;

};

PrioritySocket.prototype = {

    subscribe:function(routing,message,cb){
        this.socket = new WebSocket(this.ws_scheme+'://' + window.location.host + '/'+routing+'/');
        this.msg = message;
        this.cb = cb;
        var name = this.name;
        var socket = this.socket;
        var msg = this.msg;
        var cb = this.cb;
        var counter = 0;

        socket.onopen = function(){
          socket.send('START_COMM_HS');
          //console.log('[',getDate('d'),'] Initiating Handshake [PRIORITY : HIGH]');
          };

        socket.onmessage = function(event){
          if(event.data == 'START_COMM_ACK'){
            //console.log('[',getDate('d'),'] Handshake Complete [PRIORITY : HIGH]');
            //socket.send(msg);
            this.isSocketConnected = true;
          }
          if(this.isSocketConnected ){
            if(counter<1 ){
            socket.send(msg);}
            if(event.data!='START_COMM_ACK'){
            cb(event);}
            counter = counter+1;
            //console.log('[',getDate('d'),'] Packet#',counter,' Received From Socket : ',name,' [PRIORITY : HIGH]');
          }else{
            this.isSocketConnected = false;
            console.log('closeed here')
            socket.close();
          }
        };

        socket.onerror = function(event){
            console.log('[',getDate('d'),']  Closing Socket Because',event.data,'  [ERROR][PRIORITY : HIGH]');
            this.isSocketConnected = false;
            socket.close();
        }

        if (socket.readyState == WebSocket.OPEN) {
          socket.onopen();
        };
    },

    lazySubscribe:function(routing,message,cb,te){
        this.socket = new WebSocket(this.ws_scheme+'://' + window.location.host + '/'+routing+'/');
        this.msg = message;
        this.cb = cb;
        this.te = te;
        var name = this.name;
        var socket = this.socket;
        var msg = this.msg;
        var cb = this.cb;
        var te = this.te
        var counter = 0;

        socket.onopen = function(){
          socket.send('START_COMM_HS');
          //console.log('[',getDate('d'),'] Initiating Handshake [PRIORITY : LOW]');
          };

        socket.onmessage = function(event){
          if(event.data == 'START_COMM_ACK'){
            //console.log('[',getDate('d'),'] Handshake Complete [PRIORITY : LOW]');
            this.isSocketConnected = true;
          }
          if(this.isSocketConnected){
            delay(socket,msg,te);
            //socket.send(msg);
            cb(event);
            counter = counter+1;
            console.log('[',getDate('d'),'] Packet#',counter,' Received From Socket : ',name,' [PRIORITY : LOW]');
          }else{
            this.isSocketConnected = false;
            socket.close();
          }
        };

        socket.onerror = function(event){
            console.log('[',getDate('d'),']  Closing Socket Because',event.data,'  [ERROR][PRIORITY : LOW]');
            this.isSocketConnected = false;
            socket.close();
        }

        if (socket.readyState == WebSocket.OPEN) {
          socket.onopen();
        };
    },

    unsubscribe:function(){
        console.log('[',getDate('d'),'] Unsubscribed From Socket : ',name,' [PRIORITY : NA]');
        var socket=this.socket;
        if (socket.readyState == WebSocket.OPEN) {
            socket.send('CLOSE_COMM_NOFBCK');
            socket.close();
        }
    },



    unsubscribe2:function(routing,message,cb){
        this.socket = new WebSocket(this.ws_scheme+'://' + window.location.host + '/'+routing+'/');
        this.msg = message;
        this.cb = cb;
        var name = this.name;
        var socket = this.socket;
        var msg = this.msg;
        var cb = this.cb;
        var counter = 0;

        socket.onopen = function(){
          socket.send('START_COMM_HS');
          //console.log('[',getDate('d'),'] Initiating Handshake [PRIORITY : HIGH]');
          };

        socket.onmessage = function(event){
          if(event.data == 'START_COMM_ACK'){
            //console.log('[',getDate('d'),'] Handshake Complete [PRIORITY : HIGH]');
            //socket.send(msg);

            this.isSocketConnected = true;
          }
          if(this.isSocketConnected ){
            //console.log('************',msg);
            if(counter<1 ){
            socket.send(msg);
            console.log('99999999999999999   ',msg)

            }
            if(String(event.data).includes('[1,2')){//kk cleand
            socket.send('CLOSE_COMM_NOFBCK');
            console.log('closing message channel')
            this.isSocketConnected = false;
            cb(event);}
            counter = counter+1;
            console.log('[',getDate('d'),'] Packet#',counter,' Received From Socket : ',name,' [PRIORITY : HIGH]');
          }else{
            this.isSocketConnected = false;
            console.log('closeed here')
            socket.close();
          }
        };

    },

    socketPull:function(routing,message,cb){
        this.socket = new WebSocket(this.ws_scheme+'://' + window.location.host + '/'+routing+'/');
        this.msg = message;
        this.cb = cb;
        var name = this.name;
        var socket = this.socket;
        var msg = this.msg;
        var cb = this.cb;
        var counter = 0;

        socket.onopen = function(){
          socket.send('START_COMM_HS');
          //console.log('[',getDate('d'),'] Initiating Handshake [PRIORITY : NA]');
        };

        socket.onmessage = function(event){
          if(event.data == 'START_COMM_ACK'){
            //console.log('[',getDate('d'),'] Handshake Complete [PRIORITY : NA]');
            socket.send(msg);
          }
          else{
            cb(event);
            counter = counter+1;
            console.log('[',getDate('d'),'] Packet#',counter,' Received From Socket : ',name,' [PRIORITY : NA]');
            socket.send('CLOSE_COMM_NOFBCK');
            console.log('[',getDate('d'),'] Closing Socket [PRIORITY : NA]');
            socket.close();
          }
        };

        if (socket.readyState == WebSocket.OPEN) {
          socket.onopen();
        };
    },

    socketPush:function(routing,message){
        this.socket = new WebSocket(this.ws_scheme+'://' + window.location.host + '/'+routing+'/');
        this.msg = message;
        var name = this.name;
        var socket = this.socket;
        var msg = this.msg;
        var counter = 0;

        socket.onopen = function(){
          socket.send('START_COMM_HS');
          //console.log('[',getDate('d'),'] Initiating Handshake [PRIORITY : NA]');
        };

        socket.onmessage = function(event){
          if(event.data == 'START_COMM_ACK'){
            //console.log('[',getDate('d'),'] Handshake Complete [PRIORITY : NA]');
            socket.send(msg);
            console.log('[',getDate('d'),'] Packet#',counter,' Pushing Through Socket : ',name,' [PRIORITY : NA]');
            console.log('[',getDate('d'),'] Closing Socket [PRIORITY : NA]');
            socket.close();
          }
        };

        if (socket.readyState == WebSocket.OPEN) {
          socket.onopen();
        };
    },

    setName:function(name){
        this.name = name;
    },

    getName:function(){
        return this.name;
    },

};
