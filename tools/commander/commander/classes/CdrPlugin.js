"use strict";

var path = require('path');
var fs = require('fs');
var express = require('express');
const Emitter = require('events').EventEmitter;
var mergeJSON = require('merge-json');

/* Content Types */
const ContentTypeEnum = Object.freeze({
    'PANEL':  1,
    'LAYOUT': 2,
    'WIDGET': 3
});


/**
 * Commander plugin
 */
class CdrPlugin extends Emitter {
    /**
     * Constructor for commander plugin
     * @param {String} name    directory name
     * @param {String} webRoot directory path
     * @param {String} urlBase base url
     */
    constructor(webRoot) {
	    super();

        this.webRoot = webRoot;
    }
  
  
    addContent(content) {
        if ( typeof content !== 'undefined' ) {
            global.CONTENT_TREE = mergeJSON.merge( global.CONTENT_TREE, content );

            var appViews = global.NODE_APP.get( 'views' );
            appViews.push( this.webRoot );

            this.processContentTree( content, '');
        }
    }


    /**
     * This is called by the underlying framework to initialize the plugin.
     */
    initialize( commander, instance ) {
        var self = this;

        if ( typeof this.getFunctions === 'function' ) {
            var functions = this.getFunctions();
            if(typeof functions !== 'undefined') {
                for(var funcName in functions) {
                    commander.registerFunction(self.name, functions[funcName]);
                }
            }
        }

        if(typeof this.getStreams === 'function') {
            var functions = this.getStreams();
            if(typeof functions !== 'undefined') {
                for(var funcName in functions) {
                    commander.registerStreams(self.name);
                }
            }
        }

        if(typeof this.getServerApp === 'function') {
            var serverApp = this.getServerApp();
  	  
            instance.addApp(serverApp.name, serverApp.obj);
        }
    }


    /**
     * Returns content type
     * @type {Object}
     */
    static get ContentType() {
        return ContentTypeEnum;
    }

    /**
     * Process content tree
     * @param  {Object} content content object
     * @param  {String} inPath  input path
     */
    processContentTree( content, inPath ) {
        var self = this;
        var filePath = content.filePath;
    
        if(typeof filePath !== 'undefined') {
            var fullFilePath = path.join( self.webRoot, filePath );

            if(path.extname(fullFilePath) === '.pug') {
                global.NODE_APP.get( inPath, function( req, res ) {
                    res.render(fullFilePath, {
                        query: req.query
                    });
                });
            } else if(path.extname(fullFilePath) === '.lyt') {
                global.NODE_APP.get(inPath, function(req, res) {
                    self.readJSONFile(fullFilePath, function(err, json) {
                        res.send(json);
                    });
                });
            }

            var staticPath = path.join( self.webRoot );
            global.NODE_APP.use( inPath, express.static( staticPath ) );
        }

        if(typeof content.nodes !== 'undefined') {
            for(var nodeName in content.nodes) {
                self.processContentTree( content.nodes[nodeName], inPath + '/' + nodeName );
            }
        } else {
            for(var argName in content) {
                if(typeof content[argName] === 'object') {
        	        self.processContentTree(content[argName], inPath + '/' + argName);
    	        }
            }
        }
    }


    /**
     * Process panel tree
     * @param  {Object} panels panel object
     */
    processPanelsTree(panels) {
        if(panels.hasOwnProperty('urlPath')) {
            var self = this;
            global.NODE_APP.get(panels.urlPath, function(req, res) {
                res.render(path.join(self.webRoot, panels.filePath));
            });
        }

        if(panels.hasOwnProperty('nodes')) {
            for(var nodeID in panels.nodes) {
                this.processPanelsTree(panels.nodes[nodeID]);
            }
        }
    }


    /**
     * Process layout tree
     * @param  {Object} layouts layout object
     */
    processLayoutsTree(layouts) {
        if(layouts.hasOwnProperty('urlPath')) {
            var self = this;
            global.NODE_APP.get(layouts.urlPath, function(req, res) {
                self.readJSONFile(path.join(self.webRoot, layouts.filePath), function( err, json ) {
                    res.send( json );
                });
            });
        }

        if(layouts.hasOwnProperty('nodes')) {
            for(var nodeID in layouts.nodes) {
                this.processLayoutsTree(layouts.nodes[nodeID]);
            }
        }
    }

    /**
     * Reads a json file and applies a collback on read data.
     * @param  {String}   filename file name
     * @param  {Function} callback callback
     */
    readJSONFile(filename, callback) {
        fs.readFile(filename, function(err, data) {
            if(err) {
                callback(err);
                return;
            }
            
            try {
                callback(null, data);
            } catch (exception) {
                callback(exception);
            }
        });
    }
}



module.exports = {
    CdrPlugin: CdrPlugin,
    ContentTypeEnum: ContentTypeEnum
}