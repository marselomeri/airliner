/* This is a sample script.  It will display the value for /CFS/CFE_ES_CmdCounter at 
   the rate is is updated, and will send the /CFS/CFE_ES_NoOp command every time
   /CFS/CFE_ES_CmdCounter gets updated.  The script will self terminate after 5 
   updates.  Output should look similar to the following:

     /CFS/CFE_ES/CmdCounter = 0
     /CFS/CFE_EVS/CmdCounter = 0
     /CFS/CFE_ES/CmdCounter = 1
     /CFS/CFE_EVS/CmdCounter = 0
     /CFS/CFE_ES/CmdCounter = 2
     /CFS/CFE_EVS/CmdCounter = 0
     /CFS/CFE_ES/CmdCounter = 3
     /CFS/CFE_EVS/CmdCounter = 0
     /CFS/CFE_ES/CmdCounter = 4
     /CFS/CFE_EVS/CmdCounter = 0
*/

var Sage = require('sage');

var session = new Sage();

session.on('connectFailed', function(err) {
  console.log('Failed to start Sage session.  err = ' + err);
});

session.on('connect', function() {
  var count = 0;

  session.subscribe({name: '/CFS/CFE_ES/CmdCounter'}, function(param) {
    console.log(param.id.name + ' = ' + param.engValue.uint32Value);
    session.sendCommand('/CFS/CFE_ES/NoOp', null);
  });

  session.subscribe({name: '/CFS/CFE_EVS/CmdCounter'}, function(param) {
    console.log(param.id.name + ' = ' + param.engValue.uint32Value);
    count++;
    if(count >= 5){
      process.exit();
    }
  });
});

