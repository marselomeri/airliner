/****************************************************************************
 *
 *   Copyright (c) 2018 Windhover Labs, L.L.C. All rights reserved.
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

var EventEmitter = require( 'events' );


module.exports = class CommanderInstance extends EventEmitter {

    /**
     * Constructor for commander instance
     * @param       {String} name   instance name
     * @param       {Object} server server object
     * @constructor
     */
    constructor(name, server) {
        super();
        
        this.name = name;
        this.server = server;
        this.apps = {};
        this.emitter = new EventEmitter();
        var self = this;
    }

    
    logError(plugin, message, data) {
        this.server.logError(this.name, plugin, message, data);
    }

    
    logWarn(plugin, message, data) {
        this.server.logWarn(this.name, plugin, message, data);
    }

    
    logInfo(plugin, message, data) {
        this.server.logInfo(this.name, plugin, message, data);
    }

    
    logVerbose(plugin, message, data) {
        this.server.logVerbose(this.name, plugin, message, data);
    }

    
    logDebug(plugin, message, data) {
        this.server.logDebug(this.name, plugin, message, data);
    }



    /**
     * Adds an application
     * @param  {String} name      application name
     * @param  {Object} newAppObj application object
     */
    addApp( name, newAppObj ) {
        var self = this;
        this.apps[ name ] = {
                name: name,
                appObj: newAppObj
        };

        newAppObj.setInstanceEmitter( this.emitter );
    }
    
    
    getInstanceEmitter() {
        return this.emitter;
    }
    


    /**
     * Emit data
     * @param  {String}   streamID stream id
     * @param  {String}   msg      emit message
     * @param	 {Function} callback callback
     */
    emit( streamID, obj, callback ) {
        this.emitter.emit( streamID, obj, callback );
    }
}