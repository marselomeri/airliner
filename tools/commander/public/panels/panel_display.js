"use strict";



class PushButton
{
    constructor(draw, state, x, y, cb) {
        var self = this;
        
        this.x = x;
        this.y = y;
        
        this.width = 75;
        
        this.buttonGroup = draw.group();
        
        this.button = this.buttonGroup.rect(this.width , this.width ).fill('#ffffff').stroke({ width: 1 }).move(x, y);

        this.setState(state);
        
        this.buttonGroup.click(function() {
            if(self.state == 'IN') {
                self.setState('OUT');
            } else {
                self.setState('IN');
            }

            if(typeof cb === 'function') {
                cb(self);
            };
        })
    }
      
    getState() {
        return this.state;
    }
      
    setState(state) {          
        switch(state) {
           case 'IN':
               this.in();
               break;
               
           default:
               this.out();
               break;
        }
    }
      
    in() {
        if(this.state != 'IN') {
            this.state = 'IN';
            this.button.fill('#00ff00');
        }
    }
      
    out() {
        if(this.state != 'OUT') {
            this.state = 'OUT';
            this.button.fill('#ffffff');
        }
    }
}

class Switch
{
    constructor(draw, state, x, y, cb) {
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
            this.upSwitchGroup.show();
            this.middleSwitchGroup.hide();
            this.downSwitchGroup.hide();
    	}
    }
      
    middle() {
    	if(this.state != 'MIDDLE') {
            this.state = 'MIDDLE';
            this.upSwitchGroup.hide();
            this.middleSwitchGroup.show();
            this.downSwitchGroup.hide();
    	}
    }
      
    down() {
    	if(this.state != 'DOWN') {
            this.state = 'DOWN';
            this.upSwitchGroup.hide();
            this.middleSwitchGroup.hide();
            this.downSwitchGroup.show();
        }
    }
}


class SwitchHorizontal extends Switch {
    constructor(draw, state, x, y, cb) {
        super(draw, state, x, y, cb);
        
        this.switchGroup.rotate(90);
    }
      
    setState(state) {          
        switch(state) {
           case 'UP':
           case 'RIGHT':
               this.right();
               break;
                 
           case 'MIDDLE':
               this.middle();
               break;

           case 'DOWN':
           case 'LEFT':
               this.left();
               break;
              
           default:
               this.middle();
               break;
        }
    }
      
    right() {
        if(this.state != 'RIGHT') {
            this.state = 'RIGHT';
            this.upSwitchGroup.show();
            this.middleSwitchGroup.hide();
            this.downSwitchGroup.hide();
        }
    }
      
    middle() {
        if(this.state != 'MIDDLE') {
            this.state = 'MIDDLE';
            console.log(this.state);
            this.upSwitchGroup.hide();
            this.middleSwitchGroup.show();
            this.downSwitchGroup.hide();
        }
    }
      
    left() {
        if(this.state != 'LEFT') {
            this.state = 'LEFT';
            this.upSwitchGroup.hide();
            this.middleSwitchGroup.hide();
            this.downSwitchGroup.show();
        }
    }
}


class LED
{
    constructor(draw, state, color, x, y, board, lamp) {
        var self = this;
        
        this.color = color;
        this.radius = 40;
          
        this.ledGroup = draw.group();
      
        /* Draw the LED. */
        this.led = this.ledGroup.circle('' + (this.radius / 2)).fill(this.color).move((this.radius / 4),0);
        this.led.move(0,0);
        
        /* Draw the click region. */
        this.clickRegion = this.ledGroup.circle('' + (this.radius / 2)).fill('#00ff0000').stroke({ width: 0}).move((this.radius / 4),0);
        this.clickRegion.show();
        this.clickRegion.move(0,0);
        
        this.ledGroup.move(x,y);
        
        this.board = board;
        this.lamp = lamp;
        
        this.setState(state);
        
        this.clickRegion.click(function() {
            var command;
            var intensity = 0;
            
            if(self.state == 'ON') {
                self.setState('OFF');
            } else {
                self.setState('ON')
            }
            
            if(self.state == 'ON') {
                intensity = 4095;
            } else {
                intensity = 0;
            }
           
            if((typeof self.board === 'number') || (typeof self.lamp === 'number')) {
                session.sendCommand({ops_path: '/panel-display/SetLED', args:{'Board': self.board, 'Lamp': self.lamp, 'Intensity': intensity}});
            } else {
                for(var i in self.board) {
                    session.sendCommand({ops_path: '/panel-display/SetLED', args:{'Board': self.board[i], 'Lamp': self.lamp[i], 'Intensity': intensity}});
                }
            }
        })
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
        this.state = 'ON';
        this.led.fill(this.color);
    }
    
    off() {
        this.state = 'OFF';
        this.led.fill('#000000');
    }
}



class RotaryKnob
{
    constructor(draw, state, detents, x, y, cb) {
        var self = this;
        
        this.color = '#ffffff';
        this.width = 100;
        this.detents = detents;
          
        this.knobGroup = draw.group();
      
        /* Draw the knob. */
        this.knob = this.knobGroup.circle(this.width).fill(this.color);
        this.knob.attr({cx: x, cy: y});
        
        /* Draw the tick. */
        this.knobGroup.line(x, y-15, x, y - (this.width/2)).stroke({ width: 5}).fill('#000000');
        
        this.knobGroup.attr({cx: x, cy: y});
        
        this.setState(state);
        
        this.knob.click(function() {
            var useNext = false;
            var isSet = false;
            for(var stateName in self.detents) {
                if(useNext) {
                    self.setState(stateName);
                    isSet = true;
                    break;
                } 
                    
                if(stateName == self.state) {
                    useNext = true;
                }
            }

            if(isSet == false) {
                var newState = Object.keys(self.detents)[0];
                self.setState(newState);
            }
        })
    }
      
    getState() {
        return this.state;
    }
      
    setState(state) {   
        if(this.detents.hasOwnProperty(state)) {
            this.knobGroup.rotate(this.detents[state]);
            
            this.state = state;
        }
    }
}



class TextIndicator
{
    constructor(draw, text, state, color, x, y, board, lamp) {
        var self = this;
        
        this.color = color;
        
        this.x = x;
        this.y = y;
          
        this.textGroup = draw.group();
      
        /* Draw the text. */
        this.text = this.textGroup.text(text).size(17).fill(color).move(10,10);
        this.textGroup.rect(100,40).fill('#00000000').move(0, 0);
        this.textGroup.move(x, y);
                
        this.setState(state);
        
        this.board = board;
        this.lamp = lamp;

        this.textGroup.click(function () {
            var intensity = 0;
            
            if(self.state == 'ON') {
                self.setState('OFF');
            } else {
                self.setState('ON')
            }
            
            if(self.state == 'ON') {
                intensity = 4095;
            } else {
                intensity = 0;
            }
           
            if((typeof self.board === 'number') || (typeof lamp === 'number')) {
                session.sendCommand({ops_path: '/panel-display/SetLED', args:{'Board': self.board, 'Lamp': self.lamp, 'Intensity': intensity}});
            } else {
                for(var i in self.board) {
                    session.sendCommand({ops_path: '/panel-display/SetLED', args:{'Board': self.board[i], 'Lamp': self.lamp[i], 'Intensity': intensity}});
                }
            }
        });
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
        this.state = 'ON';
        this.text.fill(this.color);
    }
    
    off() {
        this.state = 'OFF';
        this.text.fill('#000000');
    }
}



class SegmentDigit {
    constructor(draw, color, width, height, weight, x, y, cb) {
        var self = this;
        this.color = color;
        
        this.segmentGroup = draw.group();
        
        this.A = this.segmentGroup.polyline('0,0 ' + width + ',0').fill(this.color).stroke({width: weight});
        this.B = this.segmentGroup.polyline('' + width + ',0 ' + width + ',' + (height/2)).fill(this.color).stroke({width: weight});
        this.C = this.segmentGroup.polyline('' + width + ',' + (height/2) + ' ' + width + ',' + height).fill(this.color).stroke({width: weight});
        this.D = this.segmentGroup.polyline('' + width + ',' + height + ' 0,' + height).fill(this.color).stroke({width: weight});
        this.E = this.segmentGroup.polyline('0,' + height + ' 0,' + (height/2)).fill(this.color).stroke({width: weight});
        this.F = this.segmentGroup.polyline('0,' + (height/2) + ' 0,0').fill(this.color).stroke({width: weight});
        this.G = this.segmentGroup.polyline('0,' + (height/2) + ' ' + width + ','+ (height/2)).fill(this.color).stroke({width: weight});
        this.DP = this.segmentGroup.circle(weight*3).fill(this.color).attr({cx: width+7, cy: height+2});
                
        this.segmentGroup.move(x, y);
    }
    
    setDP(state) {
        this.setSegment('DP', state);
    }
    
    setValue(value) {
        switch(value) {
            case ' ':
                this.setSegment('A',  'OFF');
                this.setSegment('B',  'OFF');
                this.setSegment('C',  'OFF');
                this.setSegment('D',  'OFF');
                this.setSegment('E',  'OFF');
                this.setSegment('F',  'OFF');
                this.setSegment('G',  'OFF');
                break;
            
            case '0':
                this.setSegment('A',  'ON');
                this.setSegment('B',  'ON');
                this.setSegment('C',  'ON');
                this.setSegment('D',  'ON');
                this.setSegment('E',  'ON');
                this.setSegment('F',  'ON');
                this.setSegment('G',  'OFF');
                break;
                
            case '1':
                this.setSegment('A',  'OFF');
                this.setSegment('B',  'ON');
                this.setSegment('C',  'ON');
                this.setSegment('D',  'OFF');
                this.setSegment('E',  'OFF');
                this.setSegment('F',  'OFF');
                this.setSegment('G',  'OFF');
                break;
                
            case '2':
                this.setSegment('A',  'ON');
                this.setSegment('B',  'ON');
                this.setSegment('C',  'OFF');
                this.setSegment('D',  'ON');
                this.setSegment('E',  'ON');
                this.setSegment('F',  'OFF');
                this.setSegment('G',  'ON');
                break;
                
            case '3':
                this.setSegment('A',  'ON');
                this.setSegment('B',  'ON');
                this.setSegment('C',  'ON');
                this.setSegment('D',  'ON');
                this.setSegment('E',  'OFF');
                this.setSegment('F',  'OFF');
                this.setSegment('G',  'ON');
                break;
                
            case '4':
                this.setSegment('A',  'OFF');
                this.setSegment('B',  'ON');
                this.setSegment('C',  'ON');
                this.setSegment('D',  'OFF');
                this.setSegment('E',  'OFF');
                this.setSegment('F',  'ON');
                this.setSegment('G',  'ON');
                break;
                
            case '5':
                this.setSegment('A',  'ON');
                this.setSegment('B',  'OFF');
                this.setSegment('C',  'ON');
                this.setSegment('D',  'ON');
                this.setSegment('E',  'OFF');
                this.setSegment('F',  'ON');
                this.setSegment('G',  'ON');
                break;
                
            case '6':
                this.setSegment('A',  'ON');
                this.setSegment('B',  'OFF');
                this.setSegment('C',  'ON');
                this.setSegment('D',  'ON');
                this.setSegment('E',  'ON');
                this.setSegment('F',  'ON');
                this.setSegment('G',  'ON');
                break;
                
            case '7':
                this.setSegment('A',  'ON');
                this.setSegment('B',  'ON');
                this.setSegment('C',  'ON');
                this.setSegment('D',  'OFF');
                this.setSegment('E',  'OFF');
                this.setSegment('F',  'OFF');
                this.setSegment('G',  'OFF');
                break;
                
            case '8':
                this.setSegment('A',  'ON');
                this.setSegment('B',  'ON');
                this.setSegment('C',  'ON');
                this.setSegment('D',  'ON');
                this.setSegment('E',  'ON');
                this.setSegment('F',  'ON');
                this.setSegment('G',  'ON');
                break;
                
            case '9':
                this.setSegment('A',  'ON');
                this.setSegment('B',  'ON');
                this.setSegment('C',  'ON');
                this.setSegment('D',  'OFF');
                this.setSegment('E',  'OFF');
                this.setSegment('F',  'ON');
                this.setSegment('G',  'ON');
                break;
                
            case 'A':
                this.setSegment('A',  'ON');
                this.setSegment('B',  'ON');
                this.setSegment('C',  'ON');
                this.setSegment('D',  'OFF');
                this.setSegment('E',  'ON');
                this.setSegment('F',  'ON');
                this.setSegment('G',  'ON');
                break;
                
            case 'B':
                this.setSegment('A',  'OFF');
                this.setSegment('B',  'OFF');
                this.setSegment('C',  'ON');
                this.setSegment('D',  'ON');
                this.setSegment('E',  'ON');
                this.setSegment('F',  'ON');
                this.setSegment('G',  'ON');
                break;
                
            case 'C':
                this.setSegment('A',  'OFF');
                this.setSegment('B',  'OFF');
                this.setSegment('C',  'OFF');
                this.setSegment('D',  'ON');
                this.setSegment('E',  'ON');
                this.setSegment('F',  'OFF');
                this.setSegment('G',  'ON');
                break;
                
            case 'D':
                this.setSegment('A',  'OFF');
                this.setSegment('B',  'ON');
                this.setSegment('C',  'ON');
                this.setSegment('D',  'ON');
                this.setSegment('E',  'ON');
                this.setSegment('F',  'OFF');
                this.setSegment('G',  'ON');
                break;
                
            case 'E':
                this.setSegment('A',  'ON');
                this.setSegment('B',  'OFF');
                this.setSegment('C',  'OFF');
                this.setSegment('D',  'ON');
                this.setSegment('E',  'ON');
                this.setSegment('F',  'ON');
                this.setSegment('G',  'ON');
                break;
                
            case 'F':
                this.setSegment('A',  'ON');
                this.setSegment('B',  'OFF');
                this.setSegment('C',  'OFF');
                this.setSegment('D',  'OFF');
                this.setSegment('E',  'ON');
                this.setSegment('F',  'ON');
                this.setSegment('G',  'ON');
                break;
        }
    }
    
    setSegment(segment, state) {
        var color = this.color;
        if(state == 'OFF') {
            color = '#000000';
        }
        
        switch(segment) {
            case 'A': 
                this.A.stroke({color: color});
                break;
                
            case 'B': 
                this.B.stroke({color: color});
                break;
                
            case 'C': 
                this.C.stroke({color: color});
                break;
                
            case 'D': 
                this.D.stroke({color: color});
                break;
                
            case 'E': 
                this.E.stroke({color: color});
                break;
                
            case 'F': 
                this.F.stroke({color: color});
                break;
                
            case 'G': 
                this.G.stroke({color: color});
                break;
                
            case 'DP': 
                this.DP.fill(color);
                break;
        }
    }
}



class SegmentIndicator {
    constructor(draw, digitCount, value, x, y, cb) {
        var self = this;
        
        this.color = '#00ff00';
        this.value = value;
        this.width = 15;
        this.height = this.width * 2;
        this.weight = 2;
        this.spacing = 15;
        this.digitCount = digitCount;
        
        this.x = x;
        this.y = y;
          
        this.digits = [];
        
        for(var i = 0; i < digitCount; ++i) {
            this.digits.push(new SegmentDigit(draw, this.color, this.width, this.height, this.weight, x+(this.spacing + this.width)*i, y, cb));
        }

        this.setValue('    ');

        for(var i = 0; i < this.digitCount; ++i) {
            this.digits[i].setDP('OFF');
        }
    }
      
    getValue() {
        return this.value;
    }
    
    setDP(digit, state) {
        if(digit < this.digitCount) {
            this.digits[digit].setDP(state);
        }
    }
      
    setValue(value) {          
        var strDigits = ('' + value).toUpperCase();
        
        for(var i = 0; i < this.digitCount; ++i) {
            this.digits[i].setValue(' ');
        }
        
        if(strDigits.length <= this.digitCount) {
            for(var i = strDigits.length-1; i >= 0; --i) {
                var newValue = (strDigits)[i];
                this.digits[i].setValue(newValue);
            }
        }
    }
}



function setLED(board, lamp, state) {
    var intensity = 0;
    
    if(state == 'ON') {
        intensity = 4095;
    } else {
        intensity = 0;
    }
   
    if((typeof board === 'number') || (typeof lamp === 'number')) {
        session.sendCommand({ops_path: '/panel-display/SetLED', args:{'Board':board, 'Lamp': lamp, 'Intensity': intensity}});
    } else {
        for(var i in board) {
            session.sendCommand({ops_path: '/panel-display/SetLED', args:{'Board':board[i], 'Lamp': lamp[i], 'Intensity': intensity}});
        }
    }
}