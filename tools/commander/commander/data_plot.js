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
        this.objData = objData;
        this.objMergedData = {};
        
        function legendFormatter(label, series) {
            return '<div ' +
        	  'style="color:white;font-size:8pt;text-align:left;padding:4px;padding-left:10px">' +
        	  label + '</div>';
        };

        this.objMergedData = {
            update_interval: 100,
            homogeneity: {tolerance: 0},
            maxcount: 120,
            ignore_count: 0,
            options : {
                xaxis : {
                	show:  true,
                	mode: "time",
                },
                series : {
                	shadowSize: 0	// Drawing is faster without shadows
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
        
        this.UtilGraph = $.plot(domObject, [], this.objMergedData.options);
        	  
        var objTlm = [];
        for(var i=0; i < this.objMergedData.data.length; ++i) {
        	if(this.objMergedData.data[i].tlm !== undefined) {
                objTlm.push(this.objMergedData.data[i].tlm);
        	}
        }
        	  
        var count = 0;
        	  
        this.values = new Array(this.objMergedData.data.length);
        for(var i = 0; i < this.objMergedData.data.length; ++i) {
        	this.values[i] = [];
        } 
        
    	var self = this;
        
        if(objTlm.length > 0)
        {         	
        	self.UtilGraph.draw();
    		self.UtilGraph.setupGrid();
    		
            session.subscribe(objTlm, function(params) {
            	console.log(objTlm.length);
                count = count + 1;
                if(self.objMergedData.ignore_count > 0){
                	self.objMergedData.ignore_count = self.objMergedData.ignore_count - 1;
        	    } else {
        		    for(var i = 0; i < objTlm.length; ++i) {
            	        var timeStamp = new Date(params[i].sample[0].gndTime);
            	        if (self.values[i].length >= self.objMergedData.maxcount) {
            	        	self.values[i] = self.values[i].slice(1);
            	        }

            	        var value = params[i].sample[0].value;
            	    	
            	    	/* compensation for boolean */
            	    	if(value == undefined){
    	        	    	if (params[i].engValue.booleanValue){
    	        	    		value = 1;
    	        	    	}else{
    	        	    		value = 0;
    	        	    	}
            	    	}
            	    	
            	        self.values[i].push([new Date(), value]);
        	        }
        		
        		    if(self.objMergedData.update_interval <= 0) {
        		    	update(self);
        		    };		
        	    }
            });
            
            if(self.objMergedData.update_interval > 0) {
            	setInterval(update, self.objMergedData.update_interval);
            }
        }

        function update() {    		
    		self.UtilGraph.setData(self.values);
        	
    		self.UtilGraph.setupGrid();
        	self.UtilGraph.draw();
        }
    }    
}
