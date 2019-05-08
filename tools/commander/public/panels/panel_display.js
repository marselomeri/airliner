"use strict";

class Switch
{
    constructor(state, x, y, cb) {
        var self = this;
        
        this.x = x;
        this.y = y;
        
        this.width = 50;
        this.thickness = 15;
        this.length = 50;
          
        this.switchGroup = draw.group();
        this.upSwitchGroup = this.switchGroup.group();
        this.middleSwitchGroup = this.switchGroup.group();
        this.downSwitchGroup = this.switchGroup.group();
        this.upClickGroup = this.switchGroup.group();
        this.middleClickGroup = this.switchGroup.group();
        this.downClickGroup = this.switchGroup.group();
          
        const downSwitchPoly = '0,0 ' + (-this.width/2) + ',' + this.length + ' ' + (this.width/2) + ',' + (this.length);
      
        /* Draw the 'DOWN' position. */
        this.downSwitchGroup.polyline(downSwitchPoly).fill('#ffffff').stroke({ width: 1 }).move(0,0);
        this.downSwitchGroup.circle('' + (this.width / 2)).fill('#ffffff').move((this.width / 4),0);
        this.downSwitchGroup.hide();
      
        /* Draw the 'UP' position.  The same as 'DOWN', but flipped. */
        this.upSwitchGroup.polyline(downSwitchPoly).fill('#ffffff').stroke({ width: 1 }).move(0,0);
        this.upSwitchGroup.circle('' + (this.width / 2)).fill('#ffffff').move((this.width / 4),0);
        this.upSwitchGroup.flip('y', (this.width / 4));
        this.upSwitchGroup.hide();
      
        /* Draw the 'MIDDLE' position.  */
        this.middleSwitchGroup.rect(this.width, this.thickness).fill('#ffffff').stroke({ width: 1 }).move(0,(this.width / 4)-(this.thickness/2));
        this.middleSwitchGroup.circle('' + (this.width / 2)).fill('#ffffff').move((this.width / 4),0);
        this.middleSwitchGroup.hide();

        /* Draw the up click region. */
        this.upClickGroup.rect(this.width, (this.length-(this.width/2))).fill('#ff000000').stroke({ width: 0}).move(0, -this.width/2);
        this.upClickGroup.show();
        
        /* Draw the middle click region. */
        this.middleClickGroup.rect(this.width, (this.width / 2)).fill('#00ff0000').stroke({ width: 0}).move(0,0);
        this.middleClickGroup.show();

        /* Draw the up click region. */
        this.downClickGroup.rect(this.width, (this.length-(this.width/2))).fill('#0000ff00').stroke({ width: 0}).move(0, this.width/2);
        this.downClickGroup.show();
        
        this.switchGroup.move(x,y);
          
        this.setState(state);
        
        this.upClickGroup.click(function() {
            self.setState('UP');

            if(typeof cb === 'function') {
                cb(self);
            };
        })
            
        this.middleClickGroup.click(function () {
            self.setState('MIDDLE');

            if(typeof cb === 'function') {
                cb(self);
            };
        });
            
        this.downClickGroup.click(function () {
            self.setState('DOWN');

            if(typeof cb === 'function') {
                cb(self);
            };
        });
    }
      
    getState() {
        return this.state;
    }
      
    setState(state) {          
        switch(state) {
           case 'UP':
               this.up();
               break;
                 
           case 'MIDDLE':
               this.middle();
               break;
                 
           case 'DOWN':
               this.down();
               break;
              
           default:
               this.middle();
               break;
        }
    }
      
    up() {
    	if(this.state != 'UP') {
            this.state = 'UP';
    		console.log('' + this.x + ', ' + this.y + '   ' + this.state);
            this.upSwitchGroup.show();
            this.middleSwitchGroup.hide();
            this.downSwitchGroup.hide();
    	}
    }
      
    middle() {
    	if(this.state != 'MIDDLE') {
            this.state = 'MIDDLE';
    		console.log('' + this.x + ', ' + this.y + '   ' + this.state);
            this.upSwitchGroup.hide();
            this.middleSwitchGroup.show();
            this.downSwitchGroup.hide();
    	}
    }
      
    down() {
    	if(this.state != 'DOWN') {
            this.state = 'DOWN';
    		console.log('' + this.x + ', ' + this.y + '   ' + this.state);
            this.upSwitchGroup.hide();
            this.middleSwitchGroup.hide();
            this.downSwitchGroup.show();
        }
    }
}



class LED
{
    constructor(state, color, x, y) {
        var self = this;
        
        this.color = color;
        this.radius = 40;
          
        this.led = draw.group();
      
        /* Draw the LED. */
        this.led = draw.circle('' + (this.radius / 2)).fill(this.color).move((this.radius / 4),0);

        this.led.move(x,y);
        
        this.setState(state);
    }
      
    getState() {
        return this.state;
    }
      
    setState(state) {          
        switch(state) {
           case 'OFF':
               this.off();
               break;
                 
           case 'ON':
               this.on();
               break;
              
           default:
               this.off();
               break;
        }
    }
    
    on() {
        this.led.fill(this.color);
    }
    
    off() {
        this.led.fill('#000000');
    }
}
