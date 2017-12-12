'use strict';
var babel_polyfill = require('babel-polyfill')
const cl = require('../templates/client');
const  Server = require('mock-socket').Server;
const sqlite3 = require('sqlite3').verbose();
const db = new sqlite3.Database('../test_database');
var chai = require('chai')

var assert = chai.assert;
var expect = chai.expect;
chai.should();

describe('Replace function',()=>{
    it('Replace all given x\'s in a string with all given y\'s',()=>{
    assert.equal(cl.replaceAll('aaabbbcccaaa','a','f'),'fffbbbcccfff');
    assert.equal(cl.replaceAll('0nc740923n74[9223r  ','r','000'),'0nc740923n74[9223000  ');
    assert.equal(cl.replaceAll('a','a','f'),'f');
    assert.equal(cl.replaceAll('4s4s','4','i'),'isis');
    expect(()=>cl.replaceAll(1,1,1)).to.throw(TypeError);
    });
});

describe('Print date',()=>{
    it('Should print correct datetime',()=>{
    assert.equal(cl.getDate('d'), new Date());
    assert.equal(cl.getDate(12), new Date());
    var t1 = new Date().getTime();
    var t2 = Number(cl.getDate('s'));
    //console.log('asdasd',t1,t2)
    assert.equal(t2-t1<10,true);
    });
});

describe('Introspect specific objects - specially tlm & cmd',()=>{
    it('Should error out on malicious inputs.',()=>{
        let select = "SELECT INPUT,OUTPUT FROM TESTCASES WHERE MAPPING = \'PREPROCTLM\' "
        db.all(select,[],(err,rows)=>{
            if (err){
                throw err;
            }
            rows.forEach((row) => {
                expect(()=>cl.introspectTlm('sd')).to.not.throw(TypeError);
                //expect(()=>cl.introspectTlm(row)).to.not.throw();
            });
        });
    });
});

describe('Array iterator',()=>{
    var ar = cl.makeIterator([1,2,3,4,5,6,7]);
    it('should increment index pointer',()=>{
        assert.equal(ar.next().value,1);
        assert.equal(ar.next().value,2);
        assert.equal(ar.next().value,3);
        assert.equal(ar.next().value,4);
        assert.equal(ar.next().value,5);
        assert.equal(ar.next().value,6);
        assert.equal(ar.next().value,7);
    });
    it('should hit end of array',()=>{
        assert.equal(ar.next().done,true);
    });
    it('set pointer to a particular index',()=>{
        ar.set(1)
        assert.equal(ar.next().value,2);
        ar.set(2)
        assert.equal(ar.next().value,3);
        ar.set(3)
        assert.equal(ar.next().value,4);
        ar.set(4)
        assert.equal(ar.next().value,5);
        ar.set(5)
        assert.equal(ar.next().value,6);
    });
    it('should throw a error',()=>{
        expect(()=>ar.set(-1)).to.throw();
        expect(()=>ar.set('sd')).to.throw();
    });


});

describe('Instance-client',()=>{

    it('should connect with this mock server for INSTANCE specific data',(done)=>{
        var u = 'ws://localhost:8000/inst/'
        var u1 = 'ws://localhost:8000/defaultInst/'
        const mockServer = new Server(u);
        const mockServer2 = new Server(u1);
        var i = new  cl.Instance();
        //console.log(mockServer)
        mockServer.on('connection', msg => {
            //console.log(msg);
            assert.equal(typeof msg, 'object');
            assert.equal(msg.url,u);
        });
        mockServer2.on('connection', msg => {
            //console.log(msg);
            assert.equal(typeof msg, 'object');
            assert.equal(msg.url,u1);
        });
        setTimeout(()=>{i.transmitCurrentInstance('INST_NAME');}, 10);

        mockServer.on('message', msg => {
             //console.log(msg);
             assert.equal(msg,'INVOKE')
             mockServer.send('RESPONSE');
        });
        mockServer2.on('message', msg => {
             //console.log(msg);
             assert.equal(msg,'INST_NAME')
             //mockServer.send('RESPONSE');
        });

        i.getInstanceList((d)=>{
            //console.log(d.data);
            assert.equal(d.data,'RESPONSE');

        });
        setTimeout(()=>{
        mockServer.stop();
        mockServer2.stop();
        done();
        }, 200);
    });

});

describe('Directory-client',()=>{

    it('should request data based on getdirectiorylisting function call',(done)=>{
    var u = 'ws://localhost:8000/dir/'
    const mockServer = new Server(u);
    var d = new cl.Directory();
    mockServer.on('connection',msg =>{
        assert.equal(typeof msg, 'object');
        assert.equal(msg.url,u);
    });
    mockServer.on('message',msg =>{
        if (msg!=''){
            assert.equal(msg,'XYZ');
            mockServer.send('ABC');

        }
    });
    setTimeout(()=>{d.getDirectoryListing('XYZ',function(e){
    //console.log(e);
    assert.equal(e.data,'ABC');
    });
    },10);

    setTimeout(()=>{
        mockServer.stop();
        done();
        }, 200);

    });

});

describe('Telemetry-client',()=>{
    it('should request data from this mockserver upon function call',(done)=>{
        var u = 'ws://localhost:8000/tlm_s/'
        const mockServer = new Server(u);
        var t = new cl.Telemetry();
        var usall_count = 0
        mockServer.on('connection',msg=>{
            assert.equal(typeof msg, 'object');
            assert.equal(msg.url,u);

        });
        mockServer.on('message',msg =>{

        //console.log('dasdasd',msg,msg.startsWith('kill_tlm'));
        //console.log('dasdasd',msg,msg.startsWith('kill_tlm'));
        if (msg.startsWith('{"tlm')){
            //console.log(msg);
            assert.equal(msg,'{"tlm":[{"name":"ABC"}]}');
            mockServer.send('{"parameter":[{"id":{"name":"ABC"}}]}')
        }
        else if(msg.startsWith('kill_tlm')){
            assert.equal(msg,'kill_tlm{"tlm":[{"name":"ABC"}]}');
            mockServer.send('{"parameter":[{"id":{"name":"ABC"}}]}')

        }
        else if(msg.startsWith('USALL')){
            usall_count = usall_count +1
            assert.equal(msg,'USALL');

        }
        });
        setTimeout(()=>{t.subscribeTelemetry('{"tlm":[{"name":"ABC"}]}',function(e){
            assert.equal(e.id.name,"ABC");
        });
        },10);
        setTimeout(()=>{t.unSubscribeTelemetry('{"tlm":[{"name":"ABC"}]}');
        },10);
        setTimeout(()=>{t.killAll();
        },10);
        setTimeout(()=>{t.unSubscribeAll();
        },10);

        setTimeout(()=>{
        mockServer.stop();
        done();
        }, 300);

    });
});

describe('Command-client',()=>{
    it('should request data from this mockserver upon function call',(done)=>{
        var u = 'ws://localhost:8000/cmd_i/'
        var u1 = 'ws://localhost:8000/cmd_s/'
        const mockServer = new Server(u);
        const mockServer2 = new Server(u1);
        var c = new  cl.Command();
        var msg_count = 0

        mockServer.on('connection',msg =>{
        assert.equal(typeof msg, 'object');
        assert.equal(msg.url,u);
        });
        mockServer2.on('connection',msg =>{
        assert.equal(typeof msg, 'object');
        assert.equal(msg.url,u1);
        });


        mockServer.on('message',msg=>{
        //if(msg_count===0){
            //console.log('msg0',msg);
            mockServer.send('aashirvaad');
            //assert.equal(msg,'INVOKE');
        //}

        });

        setTimeout(()=>{
        c.prepareCmds('Hello',1,2);
        },100);

        setTimeout(()=>{
        //console.log(c.CommandQueue[0]['Hello']);
        //console.log(typeof c.CommandQueue[0]['Hello']);
        assert.equal(c.CommandQueue[0]['Hello'][0],2);
        assert.equal(c.CommandQueue[0]['Hello'][1],1);
        assert.equal(c.SendingQueue[0],"Hello");
        //console.log('cq2',c.CommandQueue);
        //console.log('sq2',c.SendingQueue);
        },100);


        setTimeout(()=>{
        c.ProcessCmds(function(cmdInfoStr,jsonObj,btnObj){
        assert.equal(cmdInfoStr.data,'aashirvaad');
        assert.equal(jsonObj,1);
        assert.equal(btnObj,2);
        /*console.log('cb1',cmdInfoStr);
        console.log('cb2',jsonObj);
        console.log('cb3',btnObj);*/
        });
        },100);

        //c.prepareCmds('Hello',1,2);

        setTimeout(()=>{
        mockServer.stop();
        mockServer2.stop();
        done();
        }, 200);

    });

});

describe('Event-client',()=>{
    it('should request data based on getEventListing function call',(done)=>{
        var u = 'ws://localhost:8000/event/'
        const mockServer = new Server(u);
        var e = new  cl.Event();
        var msg_count = 1;
        mockServer.on('connection', msg => {
            //console.log(msg);
            assert.equal(typeof msg, 'object');
            assert.equal(msg.url,u);
        });
        mockServer.on('message', msg => {
             console.log(msg);
             if(msg==='KILLSWITCH'){

             assert.equal(msg,'KILLSWITCH')

             }
             else{

             assert.equal(msg,'INVOKE')
             setTimeout(()=>{
                 mockServer.send('1')
                 mockServer.send('2')
                 mockServer.send('3')
                 mockServer.send('4')
                 mockServer.send('5')
                 mockServer.send('6')

                }, 10);


             }

        });

        setTimeout(()=>{

        e.eventSubscription(function(d){
        assert.equal(d.data,String(msg_count))
        console.log(d.data);
        msg_count = msg_count +1;
        });

        }, 10);


        setTimeout(()=>{
        mockServer.stop();
        done();
        }, 200);
    });


});