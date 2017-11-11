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

function sleep(ms) {return new Promise(resolve => setTimeout(resolve, ms));}

async function delay(socket,msg,te) {
  await sleep(te);
  socket.send(msg);

}

function log(logtype, message, specials){
    if(logtype == 'ERROR'){
        console.log(logtype+' - '+message+' - '+'['+specials+']' );
    }
    else if (logtype == 'INFO'){
        console.log(logtype+' - '+message+' - '+'['+specials+']' );
    }
    else if (logtype == 'DEBUG'){
        console.log(logtype+' - '+message+' - '+'['+specials+']' );
    }
    else{
        console.log(message+' - '+'['+specials+']' );
    }


}


function makeIterator(array) {
    var nextIndex = 0;

    return {
       next: function() {
           return nextIndex < (array.length) ?
               {value: array[nextIndex++], done: false} :
               {done: true};
       },
       prev: function() {
           return nextIndex > 0 ?
               {value: array[--nextIndex], done: false} :
               {done: true};
       },
       id: function(){
        return nextIndex;
       },
       done: function(){
            if(nextIndex>=0 && nextIndex<array.length){return false;}
            else{return true;}
       },
       set: function(i){
        nextIndex = i;
       }
    };
}

function getSockets(obj){
    var ws_hold =[];
    Object.keys(obj).forEach(function(key,index) {
    if(obj[key] instanceof WebSocket){
            ws_hold.push(obj[key]);

        }

    });

    return ws_hold;



}

//---------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------

var Instance = function(){
    this.ws_scheme = window.location.protocol == "https:" ? "wss" : "ws";
    this.websocket1 = new WebSocket(this.ws_scheme+'://' + window.location.host + '/inst/');
    this.websocket2 = new WebSocket(this.ws_scheme+'://' + window.location.host + '/defaultInst/');

}

Instance.prototype = {

    /*getInstanceList*/
    getInstanceList: function (message, cb){
        var socket = this.websocket1
        socket.onopen = function (){
            socket.send(message);
        }
        socket.onclose = function (){
            socket.close();
        }
        socket.onerror = function (){

        }
        socket.onmessage = function (event){
            cb(event);
            //socket.close();
        }
        if (socket.readyState == WebSocket.OPEN) {
          socket.onopen();
        };
    },

    /*transmitCurrentInstance*/
    transmitCurrentInstance: function(message){
        var socket = this.websocket2


        socket.onopen = function (){

        socket.send(message);

        }
        socket.onclose = function (){
        socket.close();
        }
        socket.onerror = function (){
        log('ERR','setDefaultInstance','')
        }
        socket.onmessage = function (event){
        //log('INFO','SENT',event);
        //socket.close();

        }
        if (socket.readyState == WebSocket.OPEN) {

        socket.onopen();
        };

    },



}
//---------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------

var Directory = function(){
    this.ws_scheme = window.location.protocol == "https:" ? "wss" : "ws";
    this.websocket = new WebSocket(this.ws_scheme+'://' + window.location.host + '/dir/');
}

Directory.prototype = {

    getDirectoryListing: function(message,cb){
        var socket = this.websocket
        socket.onopen = function (){

            socket.send(message);
        }
        socket.onclose = function (){

            socket.close();
        }
        socket.onerror = function (){

            log('ERR','getInstanceList','')
        }
        socket.onmessage = function (event){

            //log('INFO','got resp',event);
            //console.log(event);
            cb(event);
            //socket.close();
        }
        if (socket.readyState == WebSocket.OPEN) {

          socket.onopen();
        };
    },

}

//---------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------
var Telemetry =function(){
    this.ws_scheme = window.location.protocol == "https:" ? "wss" : "ws";
    this.subsc = new WebSocket(this.ws_scheme+'://' + window.location.host + '/tlm_s/');
    this.unsubsc = new WebSocket(this.ws_scheme+'://' + window.location.host + '/tlm_u/');
    this.subscribers = {}


}

Telemetry.prototype = {

    subscribeTelemetry: function(message,cb){
        var socket = this.subsc;
        socket.onopen = function (){

            socket.send(message);
            //log('INFO','SENDING TELEM REQ', message)
        };
        socket.onclose = function (){

            socket.close();
        };
        socket.onerror = function (){

            //log('ERR','getInstanceList','')
        };
        socket.onmessage = function (event){

            //log('INFO','got resp',event);
            cb(event);
            //socket.close();
        };
        if (socket.readyState == WebSocket.OPEN) {

          socket.onopen();
        };

    },

    unSubscribeTelemetry: function(message,cb){
        var socket = this.unsubsc;
        socket.onopen = function (){

            socket.send(message);
        }
        socket.onclose = function (){

            socket.close();
        }
        socket.onerror = function (){

            log('ERR','getInstanceList','')
        }
        socket.onmessage = function (event){

            //log('INFO','got resp',event);
            cb(event);
            //socket.close();
        }
        if (socket.readyState == WebSocket.OPEN) {

          socket.onopen();
        };

    },


    unSubscribeAll: function(){
        var socket = this.unsubsc;
        socket.onopen = function (){

            socket.send('US_ALL');
        }
        socket.onclose = function (){

            socket.close();
        }
        socket.onerror = function (){

            //log('ERR','getInstanceList','')
        }

        if (socket.readyState == WebSocket.OPEN) {

          socket.onopen();
        };

    },

}

//---------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------
var Command =function(){
    this.ws_scheme = window.location.protocol == "https:" ? "wss" : "ws";
    this.info = new WebSocket(this.ws_scheme+'://' + window.location.host + '/cmd_i/');
    this.cmd = new WebSocket(this.ws_scheme+'://' + window.location.host + '/cmd_s/');
    this.CommandQueue = [];
    this.SendingQueue = [];
    this.superQ = {};
    this.count=0;



}

Command.prototype = {

    cleanSlate: function(){
        this.CommandQueue = [];
        this.SendingQueue = [];
        this.count=0;
        log('INFO','CLEAN SLATE',this)
    },

    ProcessCmds: function(cb){

        var socket = this.info;
        var self = this;
        var cq = makeIterator(this.CommandQueue)
        var btn = null;
        var jsn = null;
        var Que_obj = null;
        var message = null;


        //var RQ = this.ReceivingQueue;



        socket.onopen = function (){
            socket.send('HS');

        }
        socket.onclose = function (){
            socket.close();
        }




        socket.onmessage = function (event){


            if(event.data === 'HSOK'){

                if(cq.done()){

                console.log("Completed Processing Commanding Queue!");

                }
                else{

                Que_obj = cq.next().value;
                message = Object.keys(Que_obj)[0];
                btn = Que_obj[message][0];
                jsn = Que_obj[message][1];

                if (!Object.keys(self.superQ).includes(message)){
                        console.log("VIA SOCK     ",message);
                        socket.send(message);

                    }
                else{
                     try{
                     console.log("VIA CACHE**     ",message);
                     cb(self.superQ[message],jsn,btn);}
                     catch(err){
                     //skip
                      console.log("[ERR] SKIP**     ",message);
                      socket.send('HS');
                     }


                     while(true){

                        if(cq.done()){

                        console.log("Completed Processing Commanding Queue!");
                        break;

                        }
                        else{

                        Que_obj = cq.next().value;
                        message = Object.keys(Que_obj)[0];
                        btn = Que_obj[message][0];
                        jsn = Que_obj[message][1];

                        if (!Object.keys(self.superQ).includes(message)){
                                console.log("CHANGING PROTOCOL...     ",message)
                                cq.set(cq.id()-1);
                                socket.send('HS');
                                break;

                        }else{
                            try{
                            console.log("VIA CACHE     ",message);
                            cb(self.superQ[message],jsn,btn);}
                            catch(err){
                            console.log("[ERR] SKIP     ",message);
                            socket.send('HS');
                            break;
                            }
                        }


                        }




                     }


                }


                }

            }
            else{
                console.log("CACHE LOAD COMPLETE     ",message);
                self.superQ[message]= event;
                cb(event,jsn,btn);
            }


        }



        if (socket.readyState == WebSocket.OPEN) {
          socket.onopen();
        };



    },

    prepareCmds: function(message,jobj,btn){
    var lookup_obj = {}
    lookup_obj[message]=[btn,jobj]
    this.CommandQueue.push(lookup_obj);
    if(!this.SendingQueue.includes(message)){
        this.SendingQueue.push(message);
    }
    },

    sendCommand: function(name,args){
        var obj = {"name":name,"args":args}
        var message = JSON.stringify(obj)
        //log('HEEEEEEEEREEEEEEEEEE','',obj);
        var socket = this.cmd;
        socket.onopen = function (){

            socket.send(message);
        }
        socket.onclose = function (){

            socket.close();
        }
        socket.onerror = function (){

            //log('ERR','getInstanceList','')
        }
        socket.onmessage = function (event){

            //log('INFO','got resp',event);
            console.log('do nothing with');
            //cb(event);
            //socket.close();
        }
        if (socket.readyState == WebSocket.OPEN) {

          socket.onopen();
        };

    },

}
//---------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------

var Event = function(){
    this.ws_scheme = window.location.protocol == "https:" ? "wss" : "ws";
    this.event = new WebSocket(this.ws_scheme+'://' + window.location.host + '/event/');

}


Event.prototype = {

    eventSubscription: function(cb){
        var socket = this.event


        socket.onopen = function (){

            socket.send('HS');
        }
        socket.onclose = function (){

            socket.close();
        }
        socket.onerror = function (){

            log('ERR','getInstanceList','')
        }
        socket.onmessage = function (event){

            //log('INFO','got resp',event);
            cb(event);
            //socket.close();
        }
        if (socket.readyState == WebSocket.OPEN) {

          socket.onopen();
        };
    },

}


//---------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------

var Session = function(){
    this.DefaultInstance = 'softsim';
    this.CurrentInstance = null;
    this.sockets = [];

}
Session.prototype ={


    setCurrentInstance : function(instance){
        this.CurrentInstance = instance;
    },

    getCurrentInstance : function(){
        return this.CurrentInstance;
    },

    saveSockets : function(list){
        console.log('here');
        for(var i in list){
            this.sockets = this.sockets.concat(getSockets(list[i]));
        }
    },

    sendMessage : function(message,ws_obj,cb){



        ws_obj.onopen = function (){

            ws_obj.send(message);
        }
        ws_obj.onclose = function (){

            ws_obj.close();
        }
        ws_obj.onerror = function (){


        }
        ws_obj.onmessage = function (event){

            //log('INFO','got resp',event);
            cb(event);
            //socket.close();
        }
        if (ws_obj.readyState == WebSocket.OPEN) {

          ws_obj.onopen();
        };


    }




}