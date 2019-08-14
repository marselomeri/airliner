/****************************************************************************
 *
 *   Copyright (c) 2019 Windhover Labs, L.L.C. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name Windhover Labs nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 *****************************************************************************/

'use strict';


/**
 * Simple object check.
 * @param item
 * @returns {boolean}
 */
function isObject(item) {
  return (item && typeof item === 'object' && !Array.isArray(item));
}


/**
 * Deep merge two objects.
 * @param target
 * @param ...sources
 */
function mergeDeep(target, ...sources) {
    if (!sources.length) return target;
    const source = sources.shift();

    if (isObject(target) && isObject(source)) {
        for (const key in source) {
            if (isObject(source[key])) {
                if (!target[key]) {
                    Object.assign(target, { [key]: {} });
                }
                mergeDeep(target[key], source[key]);
            } else {
                Object.assign(target, { [key]: source[key] });
            }
        }
    }

    return mergeDeep(target, ...sources);
}


class CdrTimeSeriesDataplot {	
    constructor(domObject, objData) {  
        var self = this;
        this.objData = objData;
        this.objMergedData = {};
        
        this.legendFormatter = this.legendFormatter.bind(this);
        this.updatePlot = this.updatePlot.bind(this);
        this.processNewData = this.processNewData.bind(this);
        
        this.dataArray = [];

        this.objMergedData = {
            update_interval: 100,
            homogeneity: {tolerance: 0},
            maxcount: 120,
            ignore_count: 0,
            options : {
                xaxis : {
                    show:  true,
                    mode: 'time',
                    font : {
                        color: "#ffffff"
                    }
                },
                yaxis : {
                    font : {
                        color: "#ffffff"
                    }
                },
                series : {
                    lines : {
                        show : true,
                        lineWidth: 1
                    },
                    points: {
                        show: false
                    },
                    shadowSize: 0   // Drawing is faster without shadows
                },
                legend: {
                    show: true,
                    labelFormatter: this.legendFormatter,
                    labelBoxBorderColor: 'rgba(255, 255, 255, 0.0)',
                    noColumns: 1,
                    position: 'ne',
                    margin: [10,10],
                    backgroundColor: null,
                    backgroundOpacity: 0,
                    container: null,
                    sorted: false
                },
                grid: {
                    show: true,
                    //aboveData: boolean
                    //color: '#ffffff',
                    //backgroundColor: color/gradient or null
                    //margin: number or margin object
                    //labelMargin: number
                    //axisMargin: number
                    //markings: [{ color: "#ffffff" }],
                    //markings: array of markings or (fn: axes -> array of markings)
                    //borderWidth: number or object with "top", "right", "bottom" and "left" properties with different widths
                    //borderColor: color or null or object with "top", "right", "bottom" and "left" properties with different colors
                    //minBorderMargin: number or null
                    //clickable: boolean
                    //hoverable: boolean
                    //autoHighlight: boolean
                    //mouseActiveRadius: number
                }
            }
        };

        mergeDeep(this.objMergedData, objData);
        
        this.msgIDs = {};
        
        for(var i = 0; i < this.objMergedData.data.length; ++i) {
            session.sendCommand({ops_path:'/config-database/getMessageIDFromOpsName', args: [{name:'OpsName', value:this.objMergedData.data[i].tlm.name}]}, function(err, msgID) {
                var keyID = '' + msgID;
                if(self.msgIDs.hasOwnProperty(keyID) == false) {
                    var addAddMessageFlowCmdText = JSON.stringify({ops_path: "/TO/TO_AddMessageFlowCmd_t", args: {MsgID: ""+msgID, MsgLimit: ""+1, PQueueIdx: ""+0, ChannelIdx: ""+0}});
                    var addRemoveMessageFlowCmdText = JSON.stringify({ops_path: "/TO/TO_RemoveMessageFlowCmd_t", args: {MsgID: ""+msgID, MsgLimit: ""+1, ChannelIdx: ""+0}});
                    
                    self.msgIDs[keyID] = msgID;
                    domObject.after('<button class=\'btn cdr-primary\' onclick=\'session.sendCommand(' + addRemoveMessageFlowCmdText + ')\'> Remove </button>');
                    domObject.after('<button class=\'btn cdr-primary\' onclick=\'session.sendCommand(' + addAddMessageFlowCmdText + ')\'> Add </button>');
                } 
            });
        }
        
        this.UtilGraph = $.plot(domObject, [], this.objMergedData.options);
        	  
        var objTlm = [];
        for(var i=0; i < this.objMergedData.data.length; ++i) {
            if(this.objMergedData.data[i].tlm !== undefined) {
                objTlm.push(this.objMergedData.data[i].tlm);
            }
        }
        	  
        this.count = 0;
        	  
        this.values = new Array(this.objMergedData.data.length);
        
        for(var i = 0; i < this.objMergedData.data.length; ++i) {
            this.values[i] = [];
        } 
        
        if(objTlm.length > 0)
        {         	
            this.UtilGraph.draw();
            this.UtilGraph.setupGrid();
    		
            session.subscribe(objTlm, this.processNewData);
            
            if(this.objMergedData.update_interval > 0) {
            	setInterval(this.updatePlot, this.objMergedData.update_interval);
            }
        }
    }    
    

    
    legendFormatter(label, series) {
        return '<div ' +
              'style="color:white;font-size:8pt;text-align:left;padding:4px;padding-left:10px">' +
              label + '</div>';
    };

    

    updatePlot() {             
        this.UtilGraph.setData(this.dataArray);
        this.UtilGraph.setupGrid();
        this.UtilGraph.draw();
    }
    
    
    
    processNewData(data) {
        var dataArray = [];
        
        this.count = this.count + 1;
        if(this.objMergedData.ignore_count > 0){
            this.objMergedData.ignore_count = this.objMergedData.ignore_count - 1;
        } else {
            for(var i = 0; i < data.length; ++i) {
                var timeStamp = new Date(data[i].sample[0].gndTime);
                
                if (this.values[i].length >= this.objMergedData.maxcount) {
                    this.values[i] = this.values[i].slice(1);
                }

                var value = data[i].sample[0].value;
                
                this.values[i].push([new Date(), value]);
                
                var entry = {
                    data: this.values[i],
                    label: this.objMergedData.data[i].label,
                    color: this.objMergedData.data[i].color
                };
                
                dataArray.push(entry);
            }
            
            this.dataArray = dataArray;
                
            if(this.objMergedData.update_interval <= 0) {
                updatePlot();
            };          
        }
    };
}
