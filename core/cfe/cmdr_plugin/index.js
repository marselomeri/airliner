'use strict';

var path = require( 'path' );
const Parser = require(path.join(global.CDR_INSTALL_DIR, 'node_modules', 'binary-parser')).Parser;
var fs = require('fs');
var express = require(path.join(global.CDR_INSTALL_DIR, 'node_modules', 'express'));

const CdrFlightPlugin = require(path.join(global.CDR_INSTALL_DIR, '/commander/classes/CdrFlightPlugin')).CdrFlightPlugin;

module.exports = class CfeCdrPlugin extends CdrFlightPlugin {
    constructor(config) {
        config.name = 'core';
        config.webRoot = path.join( __dirname, 'web');  
        super(config);
        
        console.log(config);

        this.config = config;
        var self = this;
        
        this.logFiles = {perf: []};

        var content = {
            pilot: {
                shortDescription: 'Pilot',
                longDescription: 'Pilot Displays.',
                nodes: {
                    main: {
                        type: CdrFlightPlugin.ContentType.LAYOUT,
                        shortDescription: 'PFD',
                        longDescription: 'Primary Flight Dispaly',
                        filePath: 'pilot/main_layout.lyt'
                    },
                    vm: {
                        type: CdrFlightPlugin.ContentType.PANEL,
                        shortDescription: 'Vehicle Manager',
                        filePath: 'pilot/vm.pug'
                    },
                    telem: {
                        type: CdrFlightPlugin.ContentType.PANEL,
                        shortDescription: 'Telemetry',
                        filePath: 'pilot/telem.pug'
                    },
                    indicator: {
                        type: CdrFlightPlugin.ContentType.PANEL,
                        shortDescription: 'Indicators',
                        filePath: 'pilot/indicator.pug'
                    },
                    events: {
                        type: CdrFlightPlugin.ContentType.PANEL,
                        shortDescription: 'Events',
                        filePath: 'pilot/events.pug'
                    },
                    position: {
                        type: CdrFlightPlugin.ContentType.PANEL,
                        shortDescription: 'Vehicle Position',
                        filePath: 'pilot/position.pug'
                    },
                    misc: {
                        type: CdrFlightPlugin.ContentType.PANEL,
                        shortDescription: 'Miscellaneous',
                        filePath: 'pilot/misc.pug'
                    },
                    vitals: {
                        type: CdrFlightPlugin.ContentType.PANEL,
                        shortDescription: 'Vitals',
                        filePath: 'pilot/vitals.pug'
                    },
                    hud: {
                        type: CdrFlightPlugin.ContentType.PANEL,
                        shortDescription: 'Heads Up Display',
                        filePath: 'pilot/hud.pug'
                    },
                    map: {
                        type: CdrFlightPlugin.ContentType.PANEL,
                        shortDescription: 'Ground Track',
                        filePath: 'pilot/ground_track.pug'
                    },
                    air_traffic: {
                        type: CdrFlightPlugin.ContentType.PANEL,
                        shortDescription: 'Air Traffic',
                        filePath: 'pilot/air_traffic.pug'
                    },
                    mission_manager: {
                        type: CdrFlightPlugin.ContentType.PANEL,
                        shortDescription: 'Mission Manager',
                        filePath: 'pilot/mission_manager.pug'
                    }
                }
            },
            core: {
                shortDescription: 'Core',
                longDescription: 'Core Services.',
                nodes: {
                    es: {
                        shortDescription: 'Essential Services',
                        longDescription: 'Core essential services.',
                        nodes: {
                            main: {
                                type: CdrFlightPlugin.ContentType.LAYOUT,
                                shortDescription: 'Main',
                                longDescription: 'Main Essential Services.',
                                filePath: 'es/main_layout.lyt'
                            },
                            perf: {
                                type: CdrFlightPlugin.ContentType.LAYOUT,
                                shortDescription: 'Performance',
                                longDescription: 'Performance Monitoring.',
                                filePath: 'es/perf_layout.lyt'
                            },
                            appctrl: {
                                type: CdrFlightPlugin.ContentType.PANEL,
                                shortDescription: 'App Ctrl',
                                longDescription: 'Application start, stop, restart, and reload.',
                                filePath: 'es/appctrl.pug'
                            },
                            cdh: {
                                type: CdrFlightPlugin.ContentType.PANEL,
                                shortDescription: 'CFE ES HK',
                                longDescription: 'CFE Essential Services Housekeeping.',
                                filePath: 'es/cdh.pug'
                            },
                            console: {
                                type: CdrFlightPlugin.ContentType.PANEL,
                                shortDescription: 'Console',
                                longDescription: 'System console.',
                                filePath: 'es/console.pug'
                            },
                            logging: {
                                type: CdrFlightPlugin.ContentType.PANEL,
                                shortDescription: 'Logging',
                                longDescription: 'Essential Services logging status and control.',
                                filePath: 'es/logging.pug'
                            },
                            logging_syslogbytesused_dp: {
                                type: CdrFlightPlugin.ContentType.PANEL,
                                shortDescription: 'SysLog Bytes Used',
                                longDescription: 'System Log Bytes Used..',
                                filePath: 'es/logging_syslogbytesused_dp.pug'
                            },
                            logging_syslogentries_dp: {
                                type: CdrFlightPlugin.ContentType.PANEL,
                                shortDescription: 'SysLog Entries',
                                longDescription: 'System Log Entries',
                                filePath: 'es/logging_syslogentries_dp.pug'
                            },
                            memory: {
                                type: CdrFlightPlugin.ContentType.PANEL,
                                shortDescription: 'Memory',
                                longDescription: 'Memory and memory pool status and monitoring.',
                                filePath: 'es/memory.pug'
                            },
                            perf_ctrl: {
                                type: CdrFlightPlugin.ContentType.PANEL,
                                shortDescription: 'Perf Ctrl',
                                longDescription: 'Performance Monitor Control.',
                                filePath: 'es/perf_ctrl.pug'
                            },
                            perf_log_picker: {
                                type: CdrFlightPlugin.ContentType.PANEL,
                                shortDescription: 'Perf Log Picker',
                                longDescription: 'Performance Log File Picker.',
                                filePath: 'es/perf_log_picker.pug'
                            },
                            perf_log_viewer: {
                                type: CdrFlightPlugin.ContentType.PANEL,
                                shortDescription: 'Perf Log Viewer',
                                longDescription: 'Performance Log Viewer.',
                                filePath: 'es/perf_log_viewer.pug'
                            },
                            perf_log_filter: {
                                type: CdrFlightPlugin.ContentType.PANEL,
                                shortDescription: 'Perf Log Filter',
                                longDescription: 'Performance Log Filter.',
                                filePath: 'es/perf_log_filter.pug'
                            },
                            perf_log_trigger: {
                                type: CdrFlightPlugin.ContentType.PANEL,
                                shortDescription: 'Perf Log Trigger',
                                longDescription: 'Performance Log Trigger.',
                                filePath: 'es/perf_log_trigger.pug'
                            },
                            reset: {
                                type: CdrFlightPlugin.ContentType.PANEL,
                                shortDescription: 'Reset',
                                longDescription: 'Core reset and restart.',
                                filePath: 'es/reset.pug'
                            },
                            version: {
                                type: CdrFlightPlugin.ContentType.PANEL,
                                shortDescription: 'Version',
                                longDescription: 'Core versions.',
                                filePath: 'es/version.pug'
                            }
                        }
                    },
                    evs: {
                        shortDescription: 'Event Services',
                        longDescription: 'Core event services.',
                        nodes: {
                            main: {
                                type: CdrFlightPlugin.ContentType.LAYOUT,
                                shortDescription: 'Main',
                                longDescription: 'Main Event Services.',
                                filePath: 'evs/main_layout.lyt'
                            },
                            hk: {
                                type: CdrFlightPlugin.ContentType.PANEL,
                                shortDescription: 'Housekeeping',
                                filePath: 'evs/hk.pug'
                            },
                            efltr: {
                                type: CdrFlightPlugin.ContentType.PANEL,
                                shortDescription: 'Event Filter',
                                filePath: 'evs/efltr.pug'
                            },
                            stats: {
                                type: CdrFlightPlugin.ContentType.PANEL,
                                shortDescription: 'Stats',
                                filePath: 'evs/stats.pug'
                            }
                        }
                    },
                    sb: {
                        shortDescription: 'Software Bus',
                        longDescription: 'Core software bus services.',
                        nodes: {
                            main: {
                                type: CdrFlightPlugin.ContentType.LAYOUT,
                                shortDescription: 'Main',
                                longDescription: 'Main Software Bus Services.',
                                filePath: 'sb/main_layout.lyt'
                            },
                            hk: {
                                type: CdrFlightPlugin.ContentType.PANEL,
                                shortDescription: 'Housekeeping',
                                filePath: 'sb/hk.pug'
                            },
                            stats: {
                                type: CdrFlightPlugin.ContentType.PANEL,
                                shortDescription: 'Statistics Summary',
                                filePath: 'sb/stats.pug'
                            },
                            pipestats: {
                                type: CdrFlightPlugin.ContentType.PANEL,
                                shortDescription: 'Pipe Statistics',
                                filePath: 'sb/pipestats.pug'
                            }
                        }
                    },
                    tbl: {
                        shortDescription: 'Table Services',
                        longDescription: 'Core table services.',
                        nodes: {
                            main: {
                                type: CdrFlightPlugin.ContentType.LAYOUT,
                                shortDescription: 'Main',
                                longDescription: 'Main Table Services.',
                                filePath: 'tbl/main_layout.lyt'
                            },
                            general: {
                                type: CdrFlightPlugin.ContentType.PANEL,
                                shortDescription: 'General',
                                filePath: 'tbl/general.pug'
                            },
                            registry: {
                                type: CdrFlightPlugin.ContentType.PANEL,
                                shortDescription: 'Registry',
                                filePath: 'tbl/registry.pug'
                            },
                            tc: {
                                type: CdrFlightPlugin.ContentType.PANEL,
                                shortDescription: 'Tbl Ctrl',
                                filePath: '/tbl/tc.pug'
                            }
                        }
                    },
                    time: {
                        shortDescription: 'Time Services',
                        longDescription: 'Core time services.',
                        nodes: {
                            main: {
                                type: CdrFlightPlugin.ContentType.LAYOUT,
                                shortDescription: 'Main',
                                longDescription: 'Main time services.',
                                filePath: 'time/main_layout.lyt'
                            },
                            hk: {
                                type: CdrFlightPlugin.ContentType.PANEL,
                                shortDescription: 'Housekeeping',
                                filePath: 'time/hk.pug'
                            },
                            diag_full: {
                                type: CdrFlightPlugin.ContentType.PANEL,
                                shortDescription: 'Diagnostic (Full Message)',
                                filePath: 'time/diag_full.pug'
                            },
                            diag_1: {
                                type: CdrFlightPlugin.ContentType.PANEL,
                                shortDescription: 'Diagnostic (Partial - 1)',
                                filePath: 'time/diag_1.pug'
                            },
                            diag_2: {
                                type: CdrFlightPlugin.ContentType.PANEL,
                                shortDescription: 'Diagnostic (Partial - 2)',
                                filePath: 'time/diag_2.pug'
                            },
                            diag_3: {
                                type: CdrFlightPlugin.ContentType.PANEL,
                                shortDescription: 'Diagnostic (Partial - 3)',
                                filePath: 'time/diag_3.pug'
                            }
                        }
                    },
                    widgets: {
                        shortDescription: 'Widgets',
                        longDescription: 'Widgets',
                        nodes: {
                            clock: {
                                type: CdrFlightPlugin.ContentType.WIDGET,
                                shortDescription: 'Clock',
                                filePath: 'widgets/clock.pug'
                            },
                            timer: {
                                type: CdrFlightPlugin.ContentType.WIDGET,
                                shortDescription: 'Timer',
                                filePath: 'widgets/timer.pug'
                            },
                            network_latency: {
                                type: CdrFlightPlugin.ContentType.WIDGET,
                                shortDescription: 'Network Latency',
                                filePath: 'widgets/network_latency.pug'
                            },
                            network_throughput: {
                                type: CdrFlightPlugin.ContentType.WIDGET,
                                shortDescription: 'Network Throughput',
                                filePath: 'widgets/network_throughput.pug'
                            },
                            socket_latency: {
                                type: CdrFlightPlugin.ContentType.WIDGET,
                                shortDescription: 'Socket Latency',
                                filePath: 'widgets/socket_latency.pug'
                            },
                            connection: {
                                type: CdrFlightPlugin.ContentType.WIDGET,
                                shortDescription: 'Connection',
                                filePath: 'widgets/connection.pug'
                            }
                        }
                    }
                }
	    }
        }
        
	this.addContent(content);
        
        this.initPerfLogServer();
        


        this.cfeFsHeader = new Parser()
            .endianess( 'big' )
            .uint32( 'ContentType' )
            .uint32( 'SubType' )
            .uint32( 'Length' )
            .uint32( 'VehicleID' )
            .uint32( 'ProcessorID' )
            .uint32( 'ApplicationID' )
            .uint32( 'TimeSeconds' )
            .uint32( 'TimeSubSeconds' )
            .string( 'Description', {length: 32} );
        
        this.perfLogHdrBig = new Parser()
            .endianess( 'big' )
            .uint32( 'TimerTicksPerSecond' )
            .uint32( 'TimerLow32Rollover' )
            .uint32( 'State' )
            .uint32( 'Mode' )
            .uint32( 'TriggerCount' )
            .uint32( 'DataStart' )
            .uint32( 'DataEnd' )
            .uint32( 'DataCount' )
            .uint32( 'InvalidMarkerReported' )
            .uint32( 'FilterTriggerMaskSize' )
            .array('FilterMask', {
                type: 'uint32be',
                length: 'FilterTriggerMaskSize'
            })
            .array('TriggerMask', {
                type: 'uint32be',
                length: 'FilterTriggerMaskSize'
            });
        
        this.perfLogHdrLittle = new Parser()
            .endianess( 'Little' )
            .uint32( 'TimerTicksPerSecond' )
            .uint32( 'TimerLow32Rollover' )
            .uint32( 'State' )
            .uint32( 'Mode' )
            .uint32( 'TriggerCount' )
            .uint32( 'DataStart' )
            .uint32( 'DataEnd' )
            .uint32( 'DataCount' )
            .uint32( 'InvalidMarkerReported' )
            .uint32( 'FilterTriggerMaskSize' )
            .array('FilterMask', {
                type: 'uint32le',
                length: 'FilterTriggerMaskSize'
            })
            .array('TriggerMask', {
                type: 'uint32le',
                length: 'FilterTriggerMaskSize'
            });

        /* Initialize server side commands. */
        this.initCommands();            

        this.perfLogMetadata = new Parser()
            .endianess( 'big' )
            .uint8( 'version' )
            .uint8( 'endian' )
            .uint8( 'spare1' )
            .uint8( 'spare2' )
            .choice( 'SecHdr', {
                tag: 'endian',
                choices: {
                    0: this.perfLogHdrLittle,
                    1: this.perfLogHdrBig
                }
            } )
        
        this.namespace.recv('file-received', function(obj) {   
            console.log('1');
            fs.readFile(obj.physicalPath, function(err, contents) {
                console.log(obj.physicalPath);
                console.log(err);
                console.log(contents);
                console.log(contents.length);
                var fileHeader = self.cfeFsHeader.parse(contents); 
            	console.log('2');
                
                /* Convert CFE time to Javascript time. */
                fileHeader.Time = self.cfeTimeToJsTime( fileHeader.TimeSeconds, fileHeader.TimeSubSeconds );
                
                /* Remove nulls from the end of the description. */
                fileHeader.Description = fileHeader.Description.replace(/\0[\s\S]*$/g,'');
                
                if(fileHeader.ContentType === 0x63464531) { 
                	console.log('3');
                    /* This is probably a CFE Table header. */
                    fileHeader.content = contents.slice(64);

                    self.namespace.send('log-file-received', fileHeader);
                    
                    switch(fileHeader.SubType) {
                        case 4:  
                        	console.log('4');
                    	    /* CFE_FS_ES_PERFDATA_SUBTYPE */
                            var perfLog = {Metadata: {}, DataBuffer: []};
                            var contentOffset = 76;

                            perfLog.Metadata = self.perfLogMetadata.parse(fileHeader.content);
                            
                            for(var i = 0; i < perfLog.Metadata.SecHdr.DataCount; ++i) {
                            	var data;
                            	var timerUpper32;
                            	var timerLower32;
                            	
                                if ( perfLog.Metadata.endian == 0 ) {
                                	data = fileHeader.content.readUInt32LE(contentOffset);
                                	contentOffset = contentOffset + 4;
                                	timerUpper32 = fileHeader.content.readUInt32LE(contentOffset);
                                	contentOffset = contentOffset + 4;
                                	timerLower32 = fileHeader.content.readUInt32LE(contentOffset);
                                	contentOffset = contentOffset + 4;
                                } else {
                                	data = fileHeader.content.readUInt32BE(contentOffset);
                                	contentOffset = contentOffset + 4;
                                	timerUpper32 = fileHeader.content.readUInt32BE(contentOffset);
                                	contentOffset = contentOffset + 4;
                                	timerLower32 = fileHeader.content.readUInt32BE(contentOffset);
                                	contentOffset = contentOffset + 4;
                                }
                                
                            	var entry = {Data: data, TimerUpper32: timerUpper32, TimerLower32: timerLower32};
                            	perfLog.DataBuffer.push(entry);
                            }
                            
                            var data = JSON.stringify(perfLog); 
                            var outFileName = self.getDateString() + '.json';
                            var outFullPath = path.join(__dirname, 'logs', 'perf', outFileName);
                            fs.writeFile(outFullPath, data, function (err) { 
                            	console.log('5');
                                console.log(err);
                                
                                var perfLogEntry = {
                                    binFile: obj.virtualPath,
                                    jsonFile: outFileName,
                                    vehicleID: fileHeader.VehicleID,
                                    vehicleTime: fileHeader.Time,
                                    groundTime: obj.gndTime,
                                }
                                
                                var perfLogNotification = {
                                    opsPath: '/' + self.config.name + '/PerfLogNotify',
                                    content: perfLogEntry
                                };
                                
                                self.logFiles.perf.push(perfLogEntry);
                                    
                                self.sendTelemetry(perfLogNotification);
                            }); 
                    }
                }
            });
        });
    }
    
    
    
    getDateString() {
        const date = new Date();
        const year = date.getFullYear();
        const month = `${date.getMonth() + 1}`;
        const day =`${date.getDate()}`;
        const hour =`${date.getHours()}`;
        const minute =`${date.getMinutes()}`;
        const seconds =`${date.getSeconds()}`;
        return `${year}_${month}_${day}_${hour}_${minute}_${seconds}`
    }
    
    
    
    /**
     * Convert CFE time to javascript time
     * @param  {Number} seconds    CFE seconds
     * @param  {Number} subseconds CFE subseconds
     * @return {Object}            javascript date object
     */
    cfeTimeToJsTime( seconds, subseconds ) {
        var microseconds;

        /* 0xffffdf00 subseconds = 999999 microseconds, so anything greater
         * than that we set to 999999 microseconds, so it doesn't get to
         * a million microseconds */

        if ( subseconds > 0xffffdf00 ) {
            microseconds = 999999;
        } else {
            /*
             **  Convert a 1/2^32 clock tick count to a microseconds count
             **
             **  Conversion factor is  ( ( 2 ** -32 ) / ( 10 ** -6 ) ).
             **
             **  Logic is as follows:
             **    x * ( ( 2 ** -32 ) / ( 10 ** -6 ) )
             **  = x * ( ( 10 ** 6  ) / (  2 ** 32 ) )
             **  = x * ( ( 5 ** 6 ) ( 2 ** 6 ) / ( 2 ** 26 ) ( 2 ** 6) )
             **  = x * ( ( 5 ** 6 ) / ( 2 ** 26 ) )
             **  = x * ( ( 5 ** 3 ) ( 5 ** 3 ) / ( 2 ** 7 ) ( 2 ** 7 ) (2 ** 12) )
             **
             **  C code equivalent:
             **  = ( ( ( ( ( x >> 7) * 125) >> 7) * 125) >> 12 )
             */

            microseconds = ( ( ( ( ( subseconds >> 7 ) * 125 ) >> 7 ) * 125 ) >> 12 );

            /* if the subseconds % 0x4000000 != 0 then we will need to
             * add 1 to the result. the & is a faster way of doing the % */
            if ( ( subseconds & 0x3ffffff ) != 0 ) {
                microseconds++;
            }

            /* In the Micro2SubSecs conversion, we added an extra anomaly
             * to get the subseconds to bump up against the end point,
             * 0xFFFFF000. This must be accounted for here. Since we bumped
             * at the half way mark, we must "unbump" at the same mark
             */
            if ( microseconds > 500000 ) {
                microseconds--;
            }
        } /* end else */

        /* Get a date with the correct year. */
        var jsDateTime = new Date('12/1/1980');

        /* Adjust days. */
        jsDateTime.setDate( jsDateTime.getDate() + ( 1 - 1 ) );

        /* Adjust hours minutes and seconds. */
        jsDateTime.setTime( jsDateTime.getTime() +
            ( 0 * 3600000 ) +
            ( 0 * 60000 ) +
            ( 0 * 1000 ) );

        /* Add the CFE seconds. */
        jsDateTime.setTime( jsDateTime.getTime() + ( seconds * 1000 ) );

        /* Finally, add the CFE microseconds. */
        jsDateTime.setMilliseconds( jsDateTime.getMilliseconds() + ( microseconds / 1000 ) );

        return jsDateTime;
    }
    
    
    
    createSubDirectoriesFull(usrPath) {
        var pathElements = path.parse(usrPath);
        var location = '/';
        pathElements.dir.split(path.sep).forEach (function (item) {
            location = path.join(location, item);
            if (!fs.existsSync(location)) {
                fs.mkdirSync(location);
            }
        });

        if (!fs.existsSync(usrPath)) {
            fs.mkdirSync(usrPath);
        }
    }
    
    
    initPerfLogServer() {
        var self = this;
        
        /* Delete the log directories and recreate them. */
        var logsDir = path.join(__dirname, 'logs');
        var perfLogsDir = path.join(logsDir, 'perf');
        if (!fs.existsSync(logsDir)) {
            self.DeleteFolderRecursive(logsDir);
        }
        self.createSubDirectoriesFull(perfLogsDir);        
        
        global.NODE_APP.use('/plugin/' + self.config.name + '/es/perfLogFile', express.static(perfLogsDir));
        
        global.NODE_APP.get('/plugin/' + self.config.name + '/es/perfLogList', function(req, res) {
            var data = {
                perfLogList: [],
                recordsTotal: self.logFiles.perf.length,
                recordsFiltered: self.logFiles.perf.length
            };
            var start = 0;
            var length = self.logFiles.perf.length;
                
            if(req.hasOwnProperty('query') == true) {
                if(req.query.hasOwnProperty('start')) {
                    start = parseInt(req.query.start);
                    data.draw = parseInt(req.query.draw);
                }
                if(req.query.hasOwnProperty('length')) {
                    length = parseInt(req.query.length);
                                
                    if(length == -1) {
                        length = self.logFiles.perf.length;
                    }
                }
            }

            for(var i = start; i < (start+length); ++i) {
                var perfLogObj = self.logFiles.perf[(self.logFiles.perf.length-1) - i];
                if(typeof perfLogObj !== 'undefined') {
                    data.perfLogList.push(perfLogObj);
                }
            }
                     
            res.status(200);
            res.setHeader('Content-type', 'application/json');
            return res.send(JSON.stringify(data));
        });
    }
    

    
    DeleteFolderRecursive(inPath) {
        var self = this;
        if (fs.existsSync(inPath)) {
            fs.readdirSync(inPath).forEach(function(file, index){
                var curPath = inPath + '/' + file;
                if (fs.lstatSync(curPath).isDirectory()) { // recurse
                        self.DeleteFolderRecursive(curPath);
                } else { // delete file
                    fs.unlinkSync(curPath);
                }
            });
            fs.rmdirSync(inPath);
          }
    };
    
    
    
    initCommands() {
    	/* TODO:  Add commands. */
    }
};
