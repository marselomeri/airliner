'use strict';

var path = require( 'path' );

const CdrFlightPlugin = require(path.join(global.CDR_INSTALL_DIR, '/commander/classes/CdrFlightPlugin')).CdrFlightPlugin;

module.exports = class CfeCdrPlugin extends CdrFlightPlugin {
    constructor(config) {
        config.name = 'core';
        config.webRoot = path.join( __dirname, 'web');  
        super(config);

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
                            perf: {
                                type: CdrFlightPlugin.ContentType.PANEL,
                                shortDescription: 'Performance',
                                longDescription: 'Performance monitoring.',
                                filePath: 'es/perf.pug'
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
    }
};
