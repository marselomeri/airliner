'use strict';



//Tools
var DEBUG = false;
var ERROR = false;
var INFO = true;

function replaceAll(str, find, replace) {
            var st = str.toString();
            return st.replace(new RegExp(find, 'g'), replace);
        }

function introspectTlm(string_data){
    //console.log(string_data);
    var clean_data1 = replaceAll(string_data.data,"\'", "\"")
    var clean_data2 = replaceAll(clean_data1,'True','true');
    //console.log(clean_data2);
    var j = JSON.parse(clean_data2);
    var items = j['parameter']
    //console.log(j);
    for(var i in items){
        //console.log(i)
        console.log(items[i]['id']['name'])
    }

}

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

function log(logtype, message, specials){
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
/* INSTANCE:
   A web socket function to establish instance specific communication between server and client.
   Initializes two websockets:
    1. receives instance list.
    2. Informs server about the instance selected. */
//---------------------------------------------------------------------------------------------------------------

var Instance = function(){
    this.ws_scheme = window.location.protocol == "https:" ? "wss" : "ws";
    this.websocket1 = new WebSocket(this.ws_scheme+'://' + window.location.host + '/inst/');
    this.websocket2 = new WebSocket(this.ws_scheme+'://' + window.location.host + '/defaultInst/');
    var self = this;


    /*getInstanceList*/
    this.websocket1.onopen = function(){
        log('DEBUG','Connection open.','getInstanceList');
        self.websocket1.send('INVOKE');
        log('INFO','Message Sent.','getInstanceList');
    };
    this.websocket1.onclose = function(){
        log('DEBUG','Connection closed.','getInstanceList');
    };
    this.websocket1.onerror = function(){
        log('ERR','Connection closed.','getInstanceList');
    };


    /*transmitCurrentInstance*/
    this.websocket2.onopen = function(){
        log('DEBUG','Connection open.','transmitCurrentInstance');
    };
    this.websocket2.onclose = function(){
        log('DEBUG','Connection closed.','transmitCurrentInstance');
    };
    this.websocket2.onerror = function(){
        log('ERR','Connection closed.','transmitCurrentInstance');
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
        if (tlm_o.subsc.readyState == WebSocket.OPEN) {
            if(tlm_o.queuedSubscribers.length > 0)
            {
                log('INFO','Flushing queued subscribers.','transmitCurrentInstance');
                tlm_o.queuedSubscribers.forEach(function(subscriber){
                    tlm_o.subscribeTelemetry(subscriber.message, subscriber.callback);
                });
            }
        }
        
        socket.onmessage = function (event){
            log('INFO','Message received.','transmitCurrentInstance');
        }
        
        if (socket.readyState == WebSocket.OPEN) {
            log('INFO','Message sent.','transmitCurrentInstance');
            socket.send(message);
        };
    },
}
//---------------------------------------------------------------------------------------------------------------
/* DIRECTORY:
   A web socket function to establish directory specific communication between server and client.
   Initializes a websocket to retrive directory listing*/
//---------------------------------------------------------------------------------------------------------------

var Directory = function(){
    this.ws_scheme = window.location.protocol == "https:" ? "wss" : "ws";
    this.websocket = new WebSocket(this.ws_scheme+'://' + window.location.host + '/dir/');
    var self = this;

    this.websocket.onopen = function(){
        log('DEBUG','Connection open.','getDirectoryList');
        self.websocket.send('');
        log('INFO','Message Sent.','getDirectoryList');
    }
    this.websocket.onclose = function(){
        log('DEBUG','Connection closed.','getDirectoryList');
    };
    this.websocket.onerror = function(){
        log('ERR','Connection closed.','getDirectoryList');
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

    this.ws_scheme = window.location.protocol == "https:" ? "wss" : "ws";
    this.subsc = new WebSocket(this.ws_scheme+'://' + window.location.host + '/tlm_s/');
    //this.subsc = new WebSocket(this.ws_scheme+'://127.0.0.1:8090/softsim/_websocket');
    //this.unsubsc = new WebSocket(this.ws_scheme+'://' + window.location.host + '/tlm_u/');
    //this.unsubsc = new WebSocket(this.ws_scheme+'://' + window.location.host + '/tlm_u/');

    this.subscribers = [];
    this.queuedSubscribers = [];
    this.allSubscibers = [];
    
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

    /*unSubscribeTelemetry && unSubscribeAll*/
    /*this.unsubsc.onopen = function (){
        log('DEBUG','Connection open.','unSubscribeTelemetry');
    }
   
    this.unsubsc.onclose = function (){
        log('DEBUG','Connection closed.','unSubscribeTelemetry');
    }
    
    this.unsubsc.onerror = function (){
        log('ERR','Connection closed.','unSubscribeTelemetry');

    }*/


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
            //console.log(message);
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
        socket.send(msg);



    },

    unSubscribeAll: function(){
        var self = this;
        for(var i=0;i<20;i++){
        console.log('usall');
        self.subsc.send('USALL');
        }

        for(var i =0; i<self.allSubscibers.length;i++){
            var rem = self.allSubscibers.pop();
            self.unSubscribeTelemetry(rem);
            //console.log('removed',rem)
        }
    },

    unSubscribeAll2: function(){
        var self = this;
        for(var i =0; i<self.allSubscibers.length;i++){
            var rem = self.allSubscibers.pop();
            self.unSubscribeTelemetry(rem);
            console.log('removed',rem)
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
    this.ws_scheme = window.location.protocol == "https:" ? "wss" : "ws";
    this.info = new WebSocket(this.ws_scheme+'://' + window.location.host + '/cmd_i/');
    this.cmd = new WebSocket(this.ws_scheme+'://' + window.location.host + '/cmd_s/');
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
            log('INFO','Button feedback.','sendCommand');
        }

        if (socket.readyState == WebSocket.OPEN) {
          socket.send(message);
        };

    },

    sendCommand2: function(name,args){
    var obj = {"name":name,"args":args}
    var message = JSON.stringify(name)
    var socket = this.cmd;

    socket.onmessage = function (event){
        log('INFO','Button feedback.','sendCommand');
    }

    if (socket.readyState == WebSocket.OPEN) {
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
    this.ws_scheme = window.location.protocol == "https:" ? "wss" : "ws";
    this.event = new WebSocket(this.ws_scheme+'://' + window.location.host + '/event/');
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

}

//---------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------




//---------------------------------------------------------------------------------------------------------------
/* VIDEO:
   A web socket function to establish video specific communication between server and client.
   Initializes web socket to receive video frames.*/
//---------------------------------------------------------------------------------------------------------------
var Video = function() {
        this.ws_scheme = window.location.protocol == "https:" ? "wss" : "ws";
        this.vid_subc = new WebSocket(this.ws_scheme+'://' + window.location.host + '/video/');
        this.video_subscribers = {};
        var self = this;

        this.vid_subc.onopen = function (){
            log('DEBUG','Connection open.','getVideoStream');
            //self.vid_subc.send('INVOKE');
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
