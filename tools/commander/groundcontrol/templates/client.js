'use strict';



//Tools
var DEBUG = true;
var ERROR = false;
var INFO = true;

function replaceAll(str, find, replace) {
            if (typeof str !='string'||typeof find !='string'||typeof replace !='string'){
                throw new TypeError('A non string argument is passed')
            }
            var st = str.toString();
            return st.replace(new RegExp(find, 'g'), replace);
        }
/*exempted*/
function introspectTlm(string_data){
    try{
        var clean_data1 = replaceAll(string_data.data,"\'", "\"")
        var clean_data2 = replaceAll(clean_data1,'True','true');
        var j = JSON.parse(clean_data2);
        var items = j['parameter']
        for(var i in items){
            console.log(items[i]['id']['name'])
        }
    }
    catch(e){
        throw new TypeError('Telemetry format mismatch')
    }

}

function getDate(format){
    var tempstore =new Date();

        if(format=='d'){
        return String(tempstore);
        }
        else if (format=='s'){
        return String(tempstore.getTime());
        }
        else{
        return String(tempstore);
        }
}

function log(logtype, message, specials){

    try{
        if(logtype == 'ERR' && ERROR){
            console.log(logtype+' - '+message+' - '+'[',specials,']' );
        }
        else if (logtype == 'INFO' && INFO){
            console.log(logtype+' - '+message+' - '+'[',specials,']' );
        }
        else if (logtype == 'DEBUG' && DEBUG){
            console.log(logtype+' - '+message+' - '+'[',specials,']' );
        }
    }
    catch(e){
        throw new TypeError('A non string argument was passed')
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
       id: function(){
        return nextIndex;
       },
       done: function(){
            if(nextIndex>=0 && nextIndex<array.length){return false;}
            else{return true;}
       },
       set: function(i){

        if(i<0 || i>array.length){
            throw new Error('index out of bound')
        }
        if(typeof i != 'number'){
            throw new Error('A non number argument was passed')
        }
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


function sleep(ms) {
  return new Promise(resolve => setTimeout(resolve, ms));
}



//---------------------------------------------------------------------------------------------------------------
/* INSTANCE:
   A web socket function to establish instance specific communication between server and client.
   Initializes two websockets:
    1. receives instance list.
    2. Informs server about the instance selected. */
//---------------------------------------------------------------------------------------------------------------

var Instance = function(){
    try{
    this.ws_scheme = window.location.protocol == "https:" ? "wss" : "ws";
    }
    catch(e){
    this.ws_scheme="ws"
    }
    try{
    this.websocket1 = new WebSocket(this.ws_scheme+'://' + window.location.host + '/inst');
    this.websocket2 = new WebSocket(this.ws_scheme+'://' + window.location.host + '/tid');
    }
    catch(e){
    this.websocket1 = new WebSocket(this.ws_scheme+'://localhost:8000/inst');
    this.websocket2 = new WebSocket(this.ws_scheme+'://localhost:8000/tid');
    }
    var self = this;



    /*getInstanceList*/
    this.websocket1.onopen = function(){
        log('DEBUG','Connection open.','getInstanceList');
        self.websocket1.send('INVOKE');
        log('INFO','Invoke Sent.','getInstanceList');
    };
    this.websocket1.onclose = function(){
        log('DEBUG','Connection closed.','getInstanceList');
    };
    this.websocket1.onerror = function(evt){
        log('ERR','Connection closed with error - '+String(evt),'getInstanceList');
    };


    /*transmitCurrentInstance*/
    this.websocket2.onopen = function(){
        log('DEBUG','Connection open.','transmitCurrentInstance');
        //console.log('3333333',this.websocket2)
        log('INFO','NON Invoke Sent.','transmitCurrentInstance');
    };
    this.websocket2.onclose = function(){
        log('DEBUG','Connection closed.','transmitCurrentInstance');
    };
    this.websocket2.onerror = function(evt){
        log('ERR','Connection closed with error - '+String(evt),'transmitCurrentInstance');
    };


}

Instance.prototype = {

    /*getInstanceList*/
    getInstanceList: function (cb){
        var socket = this.websocket1;
        socket.onmessage = function (event){
            log('INFO','Message received.','getInstanceList');
            cb(event);
        }
    },

    /*transmitCurrentInstance*/
    transmitCurrentInstance: function(message){
        var socket = this.websocket2;

        /* Flush the queuedSubscribers queue, if there are any. */
        try{
            if (tlm_o.subsc.readyState == WebSocket.OPEN) {
                if(tlm_o.queuedSubscribers.length > 0)
                {
                    log('INFO','Flushing queued subscribers.','transmitCurrentInstance');
                    tlm_o.queuedSubscribers.forEach(function(subscriber){
                        tlm_o.subscribeTelemetry(subscriber.message, subscriber.callback);
                    });
                }
            }
        }
        catch(e){
        //console.log('nothing');
        }


        socket.onmessage = function (event){
            log('INFO','Message received.','transmitCurrentInstance');
        }
        //sleep(2000).then(()=>{
        //console.log(socket.readyState);
        //console.log(this.websocket2.readyState);






        if (socket.readyState == WebSocket.OPEN) {
            //console.log('1112');

            log('INFO','Message sent.','transmitCurrentInstance');
            socket.send(message);
            //console.log(socket);
            //console.log(this.websocket2);
            //console.log(message);
        };//});
    },
}
//---------------------------------------------------------------------------------------------------------------
/* DIRECTORY:
   A web socket function to establish directory specific communication between server and client.
   Initializes a websocket to retrive directory listing*/
//---------------------------------------------------------------------------------------------------------------

var Directory = function(){
    try{
    this.ws_scheme = window.location.protocol == "https:" ? "wss" : "ws";
    this.websocket = new WebSocket(this.ws_scheme+'://' + window.location.host + '/dir');
    }
    catch(e){
    this.websocket = new WebSocket('ws://localhost:8000/dir');
    }
    var self = this;

    this.websocket.onopen = function(){
        log('DEBUG','Connection open.','getDirectoryList');
        self.websocket.send('');
        log('INFO','Message Sent.','getDirectoryList');
    }
    this.websocket.onclose = function(){
        log('DEBUG','Connection closed.','getDirectoryList');
    };
    this.websocket.onerror = function(evt){
        log('ERR','Connection closed with error - '+String(evt),'getInstanceList');
    };

}

Directory.prototype = {

    getDirectoryListing: function(message,cb){
        var socket = this.websocket;
        socket.onmessage = function (event){
            log('INFO','Message received.','getDirectoryList');
            cb(event);
        }
        if (socket.readyState == WebSocket.OPEN) {
            log('INFO','Message sent.','getDirectoryList');
            socket.send(message);
        };

    },

}

//---------------------------------------------------------------------------------------------------------------
/* TELEMETRY:
   A web socket function to establish telemetry specific communication between server and client.
   Initialized web sockets to:
   1. Send, subscribe and continously receive telemetry.
   2. Unsubscribe a specific telemetry.
   3. Unsubscribe all telemetry.*/
//---------------------------------------------------------------------------------------------------------------

var Telemetry =function(){

    try{
    this.ws_scheme = window.location.protocol == "https:" ? "wss" : "ws";
    }
    catch(e){
    this.ws_scheme="ws"
    }
    try{
    this.subsc = new WebSocket(this.ws_scheme+'://' + window.location.host + '/tlm');

    }
    catch(e){
    this.subsc = new WebSocket(this.ws_scheme+'://localhost:8000/tlm');

    }


    this.subscribers = [];
    this.queuedSubscribers = [];
    this.allSubscibers = [];
    this.activeSubscribers = [];
    this.toUnsubscribe= [];

    var self = this;
    /*subscribeTelemetry*/
    this.subsc.onopen = function (){
        log('DEBUG','Connection open.','subscribeTelemetry');
        //self.subsc.send('HS');
    };

    this.subsc.onclose = function (){
        log('DEBUG','Connection closed.','subscribeTelemetry');
    };

    this.subsc.onerror = function (evt){
        log(evt,'','');
        log('ERR','Connection closed.','subscribeTelemetry');
    };


}

Telemetry.prototype = {


    subscribeTelemetry:function(msgObj,cb)
    {

        var socket = this.subsc;
        var message = "";
        var self = this;
        self.allSubscibers.push(msgObj)
        /* If this msgObj is an object, stringify it. */
        if(typeof msgObj === 'object')
        {
            /* This is an object.  Stringify it. */
            message = JSON.stringify(msgObj);
        }
        else
        {
            /* This is not an object.  Its probably already
               stringify, so just use the string as is, but
               set msgObj to the JSON object so we can parse
               it later.
             */
            message = msgObj;
            msgObj = JSON.parse(message);
        }

        if (socket.readyState == WebSocket.OPEN){
            log('INFO','Message sent.','subscribeTelemetry');

            socket.send(message);

            /* Store the subscription away so we can route the updates
             * to the callback later.  We could have received multiple
             * telemetry items, so store each one off individually.
             */
            msgObj.tlm.forEach(function(tlmItem){
                var subscription;

                /* First check to see if we've ever subscribed to this
                 * telemetry item.  This is so we can support sending updates
                 * to multiple subscriber callbacks for the same telemetry
                 * item.
                 */
                if(!(tlmItem.name in self.subscribers)){
                    /* This telemetry item has not been subscribed to.  Create
                     * an empty array with this key.
                     */
                    self.subscribers[tlmItem.name] = [];
                }

                /* Now push the new subscription onto the subscribers array. */
                self.subscribers[tlmItem.name].push({'callback': cb});
            });
        }
        else
        {
            log('INFO','Message queued.','subscribeTelemetry');
            this.queuedSubscribers.push({'message':message, 'callback':cb});
        }

        socket.onmessage = function (message){
            log('INFO','Message received.','subscribeTelemetry');
            var fixedDataString = message.data.replace(/\'/g, '"')
            fixedDataString = fixedDataString.replace(new RegExp('True', 'g'),'true');
            fixedDataString = fixedDataString.replace(new RegExp('False', 'g'),'false');
            var data = JSON.parse(fixedDataString);
            console.log(data);
            data.parameter.forEach(function(param){
                var tlmName = param.id.name;

                if(tlmName in self.subscribers){
                    var subscriptions = self.subscribers[tlmName];
                    subscriptions.forEach(function(subscription){
                        subscription.callback(param);
                    });
                }
            });
            //this.subscribers[event.data.parameter.data.keys(obj).forEach(function(key,index) {
            //console.log(event);
            //cb(event);
        }
    },

    unSubscribeTelemetry: function(msgObj){
        var socket = this.subsc;
        var message = "";
        //console.log('/**********/');
        //console.log(msgObj);
        //console.log('/**********/');
        /* If this msgObj is an object, stringify it. */
        if(typeof msgObj === 'object')
        {
            /* This is an object.  Stringify it. */
            message = JSON.stringify(msgObj);
            //console.log(message);
        }
        else
        {
            /* This is not an object.  Its probably already
               stringify, so just use the string as is.
             */
            message = msgObj;
        }

        var msg = 'kill_tlm'+message

        for(var i=0;i<2;i++){
        socket.send(msg);}



    },



    killAll: function(){
        var self = this;
        for(var i=0;i<20;i++){
        self.subsc.send('USALL');
        }


    },

    unSubscribeAll: function(){
        var self = this;
        for(var i =0; i<self.allSubscibers.length;i++){
            var rem = self.allSubscibers.pop();
            self.unSubscribeTelemetry(rem);
            log('DEBUG','Unsubscribed to telemetry.','count'+String(i));
        }
    },
}

//---------------------------------------------------------------------------------------------------------------
/* COMMAND:
   A web socket function to establish command specific communication between server and client.
   Initialized web sockets to:
   1. Clean command object variables.
   2. Populate command object variables.
   3. Request command information.
   4. Send commands.*/
//---------------------------------------------------------------------------------------------------------------
var Command =function(){
    try{
    this.ws_scheme = window.location.protocol == "https:" ? "wss" : "ws";
    this.info = new WebSocket(this.ws_scheme+'://' + window.location.host + '/cmd1');
    this.cmd = new WebSocket(this.ws_scheme+'://' + window.location.host + '/cmd2');
    }
    catch(e){
    this.info = new WebSocket('ws://localhost:8000/cmd1');
    this.cmd = new WebSocket('ws://localhost:8000/cmd2');
    }
    this.CommandQueue = [];
    this.SendingQueue = [];
    this.superQ = {};
    this.count=0;
    var self = this;

    /*getCommandInfo*/
    this.info.onopen = function (){
        log('DEBUG','Connection open.','getCommandInfo');
    }

    this.info.onclose = function (){
        log('DEBUG','Connection closed.','getCommandInfo');
    }
    this.info.onerror = function (){
        log('ERR','Connection closed.','getCommandInfo');
    }

    /*sendCommand*/
    this.cmd.onopen = function (){
        log('DEBUG','Connection open.','sendCommand');
    }

    this.cmd.onclose = function (){
        log('DEBUG','Connection closed.','sendCommand');
    }
    this.info.onerror = function (){
        log('ERR','Connection closed.','sendCommand');
    }

}

Command.prototype = {

    cleanSlate: function(){
        this.CommandQueue = [];
        this.SendingQueue = [];
        this.count=0;
        log('DEBUG','Clean slate executed.','commandCleanSlate')
    },

    RequestCmdDef: function(cmdObj, cb){
        var socket = this.info;
        var self = this;
        var cmdName = Object.keys(cmdObj)[0];

        if (!Object.keys(self.superQ).includes(cmdName)){

            socket.send(cmdName);
            return false;
        }
        else{
            try{

                var btn = cmdObj[cmdName][0];
                var jsn = cmdObj[cmdName][1];
                cb(self.superQ[cmdName],jsn,btn);
                return true;
            }
            catch(err){
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


        do{
            if(cq.done()){
                log('INFO','Commanding Queue processing complete.!','sendCommand');
                break;
            }

            Que_obj = cq.next().value;
        } while(this.RequestCmdDef(Que_obj, cb) == true);

        socket.onmessage = function (event){
            /* Retrieve the object and call the callback. */
            var cmdName = Object.keys(Que_obj)[0];
            var btn = Que_obj[cmdName][0];
            var jsn = Que_obj[cmdName][1];
            self.superQ[cmdName]= event;

            cb(event,jsn,btn);

            do{
                if(cq.done()){
		            log('INFO','Commanding Queue processing complete.!','sendCommand');
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
        var socket = this.cmd;

        socket.onmessage = function (event){
           //log('DEBUG',event,'')
            log('INFO','Button feedback.',event);
        }

        if (socket.readyState == WebSocket.OPEN) {
//          #/console.log(message);
          socket.send(message);
        };

    },


}
//---------------------------------------------------------------------------------------------------------------
/* EVENT:
   A web socket function to establish event specific communication between server and client.
   Initializes web socket to receive events.*/
//---------------------------------------------------------------------------------------------------------------

var Event = function(){
    try{
    this.ws_scheme = window.location.protocol == "https:" ? "wss" : "ws";
    this.event = new WebSocket(this.ws_scheme+'://' + window.location.host + '/event');
    }
    catch(e){

    this.event=new WebSocket('ws://localhost:8000/event');
    }
    var self = this;

    this.event.onopen = function (){
        log('DEBUG','Connection open.','getEvents');
        self.event.send('INVOKE');
        log('INFO','Message Sent.','getEvents');
    }

    this.event.onclose = function(){
        log('DEBUG','Connection closed.','getEvents');
    }
    this.event.onerror = function(){
        log('ERR','Connection closed.','getEvents');
    }
}

Event.prototype = {

    eventSubscription: function(cb){
        var socket = this.event

        socket.onmessage = function (event){
            log('INFO','Message received.','getEvents');
            cb(event);
        }

    },

    kill:function(){
    var socket = this.event
    for(var i=0;i<20;i++){
        socket.send('KILLSWITCH');
        }
    },



}

//---------------------------------------------------------------------------------------------------------------
/* ADSB:
   A web socket function to establish adsb specific communication between server and client.
   Initializes web socket to receive video frames.*/
//---------------------------------------------------------------------------------------------------------------
var ADSB = function() {
        this.ws_scheme = window.location.protocol == "https:" ? "wss" : "ws";
        this.vid_subc = new WebSocket(this.ws_scheme+'://' + window.location.host + '/adsb');
        this.video_subscribers = {};
        var self = this;

        this.vid_subc.onopen = function (){
            log('DEBUG','Connection open.','getAdsbStream');
            //self.vid_subc.send('INVOKE');//TODO
            //log('INFO','Message Sent.','getAdsbStream');
        }

        this.vid_subc.onclose = function(){
            log('DEBUG','Connection closed.','getAdsbStream');
        }
        this.vid_subc.onerror = function(){
            log('ERR','Connection closed.','getAdsbStream');
        }

}
ADSB.prototype = {

    getAdsbStream(cb){
        var socket = this.vid_subc;

        socket.onmessage = function (event){
            log('INFO','Message received.','getAdsbStream');
            cosole.log(event)
            //cb(event);
        }
        //if (socket.readyState == WebSocket.OPEN) {
        //  socket.send('INVOKE');
        //  log('INFO','Message Sent.','getVideoStream');
        //};


    },

}




//---------------------------------------------------------------------------------------------------------------
/* VIDEO:
   A web socket function to establish video specific communication between server and client.
   Initializes web socket to receive video frames.*/
//---------------------------------------------------------------------------------------------------------------
var Video = function() {
        this.ws_scheme = window.location.protocol == "https:" ? "wss" : "ws";
        this.vid_subc = new WebSocket(this.ws_scheme+'://' + window.location.host + '/video');
        this.video_subscribers = {};
        var self = this;

        this.vid_subc.onopen = function (){
            log('DEBUG','Connection open.','getVideoStream');
            //self.vid_subc.send('INVOKE');//TODO
            log('INFO','Message Sent.','getVideoStream');
        }

        this.vid_subc.onclose = function(){
            log('DEBUG','Connection closed.','getVideoStream');
        }
        this.vid_subc.onerror = function(){
            log('ERR','Connection closed.','getVideoStream');
        }

}
Video.prototype = {

    getVideoStream(cb){
        var socket = this.vid_subc;

        socket.onmessage = function (event){
            log('INFO','Message received.','getVideoStream');
            cb(event);
        }
        //if (socket.readyState == WebSocket.OPEN) {
        //  socket.send('INVOKE');
        //  log('INFO','Message Sent.','getVideoStream');
        //};


    },

}

//---------------------------------------------------------------------------------------------------------------
/* SESSION:
   A data management function to supervise all above communications.
   It is a collection of utilities to perform advanced operations on communication channels and data.*/
//---------------------------------------------------------------------------------------------------------------

var Session = function(){
    this.DefaultInstance = 'softsim';
    this.CurrentInstance = null;
    this.Master = false;
    this.sockets = [];

}
Session.prototype ={
    //TODO

    setCurrentInstance : function(instance){
        this.CurrentInstance = instance;
    },

    getCurrentInstance : function(){
        return this.CurrentInstance;
    },

    saveSockets : function(list){
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




module.exports.getDate = getDate;
module.exports.replaceAll = replaceAll;
module.exports.introspectTlm = introspectTlm;
module.exports.log = log;
module.exports.makeIterator = makeIterator;
module.exports.getSockets = getSockets;
module.exports.Instance = Instance;
module.exports.Directory = Directory;
module.exports.Telemetry = Telemetry;
module.exports.Command = Command;
module.exports.Event = Event;
module.exports.Video = Video;
module.exports.Session = Session;
