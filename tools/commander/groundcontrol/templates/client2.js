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

    this.subsc.onopen = function (){
    };

    this.subsc.onclose = function (){
    };

    this.subsc.onerror = function (){
        //log('ERR','getInstanceList','')
    };

    this.unsubsc.onopen = function (){
    }
   
    this.unsubsc.onclose = function (){
    }
    
    this.unsubsc.onerror = function (){
        log('ERR','getInstanceList','')
    }
}

Telemetry.prototype = {
    subscribeTelemetry: function(message,cb){
        if (this.subsc.readyState == WebSocket.OPEN)
        {
            this.subsc.send(message);
            //log('INFO','SENDING TELEM REQ', message)
        }

        this.subsc.onmessage = function (event)
        {
            //log('INFO','got resp',event);
            cb(event);
            //socket.close();
        };
    },

    unSubscribeTelemetry: function(message,cb){
        if (this.unsubsc.readyState == WebSocket.OPEN) {
            this.unsubsc.send(message);
        };

        this.unsubsc.onmessage = function (event)
        {
            //log('INFO','got resp',event);
            cb(event);
            //socket.close();
        }
    },

    unSubscribeAll: function(){
        var socket = this.unsubsc;
        if (this.unsubsc.readyState == WebSocket.OPEN) {
            this.unsubsc.send('US_ALL');
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
    
    var self = this;
    this.info.onopen = function (){
        //self.info.send('HS');
    }
        
    this.info.onclose = function (){
    }

}

Command.prototype = {

    cleanSlate: function(){
        this.CommandQueue = [];
        this.SendingQueue = [];
        this.count=0;
        log('INFO','CLEAN SLATE',this)
    },

    RequestCmdDef: function(cmdObj, cb){
        var socket = this.info;
        var self = this;
        var cmdName = Object.keys(cmdObj)[0];
        
        //console.log("Requesting command definition.");

        if (!Object.keys(self.superQ).includes(cmdName)){
            //console.log("VIA SOCK     ",cmdName);
            socket.send(cmdName);
            return false;
        }
        else{
            try{
                //console.log("VIA CACHE**     ",cmdName);
                var btn = cmdObj[cmdName][0];
                var jsn = cmdObj[cmdName][1];
                cb(self.superQ[cmdName],jsn,btn);
                return true;
            }
            catch(err){
                //skip
                //console.log("[ERR] SKIP**     ",cmdName);
                //socket.send('HS');
                return true;
            }
        }
    },

    ProcessCmds: function(cb){
        var socket = this.info;
        var self = this;
        var cq = makeIterator(this.CommandQueue)
        var btn = null;
        var jsn = null;
        var Que_obj = null;
        var message = null;
        var i = 0;

        //var RQ = this.ReceivingQueue;
        do{
            if(cq.done()){        
                console.log("Completed Processing Commanding Queue!");
                break;
            }

            Que_obj = cq.next().value; 
        } while(this.RequestCmdDef(Que_obj, cb) == true);

        socket.onmessage = function (event){
            //console.log("Command definition received");
            /* Retrieve the object and call the callback. */
            var cmdName = Object.keys(Que_obj)[0];
            var btn = Que_obj[cmdName][0];
            var jsn = Que_obj[cmdName][1];
            self.superQ[cmdName]= event;

            cb(event,jsn,btn);
            
            do{
                if(cq.done()){      
		    console.log("Completed Processing Commanding Queue! ", cq.id());
                    break;
                }
    
                Que_obj = cq.next().value; 
            } while(self.RequestCmdDef(Que_obj, cb) == true);
        }
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




//---------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------
var Video = function() {
        this.ws_scheme = window.location.protocol == "https:" ? "wss" : "ws";
        this.vid_subc = new WebSocket(this.ws_scheme+'://' + window.location.host + '/video/');
        this.video_subscribers = {}

}
Video.prototype = {

    getVideoStream(cb){
        var socket = this.vid_subc;
        socket.onopen = function (){

            socket.send('SEND VIDEO');
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
