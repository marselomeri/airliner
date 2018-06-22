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
 
  session.sendCommand('/CFS/PX4/VehicleArm', null);
  setTimeout(function() {
    session.sendCommand('/CFS/PX4/VehicleLaunch', null);
    setTimeout(function() {
      session.sendCommand('/CFS/PX4/ManualControlSetpoint', [
        {name:'X', value:'0'},
        {name:'Y', value:'0'},
        {name:'Z', value:'500'},
        {name:'InputMask', value:'0x7000000'}
      ]);
      setTimeout(function() {
        session.sendCommand('/CFS/PX4/VehicleChangeMode', [
          {name:'SafetyArmed', value:'ENABLE'},
          {name:'ManualInput', value:'ENABLE'},
          {name:'HIL', value:'DISABLE'},
          {name:'Stabilize', value:'ENABLE'},
          {name:'Guided', value:'DISABLE'},
          {name:'Auto', value:'DISABLE'},
          {name:'Test', value:'DISABLE'},
          {name:'Custom', value:'ENABLE'},
          {name:'CustomMainMode', value:'POSCTL'},
          {name:'CustomSubMode', value:'READY'},
          {name:'HIL', value:'DISABLE'},
        ]);
        var num = 0;
        setInterval(function(){
          var theta = 3.141593 * num;
          var step = ((Math.trunc(theta/6.283186) % 2)*-2)+1;
          var x = Math.trunc(step*Math.sin(theta)*1000);
          var y = Math.trunc(-Math.cos(theta)*1000);
          num += .02;
          session.sendCommand('/CFS/PX4/ManualControlSetpoint', [
            {name:'X', value:x.toString()},
            {name:'Y', value:y.toString()},
            {name:'Z', value:'500'},
            {name:'InputMask', value:'0x7000000'}
          ]);
        },100);
      }, 1000);
    }, 5000);
  }, 1000);

});



