Configuration
=============

Mission Specific
^^^^^^^^^^^^^^^^

+-------------------------+--------------------------------+
| File                    | Parameter                      |
+=========================+================================+
| :pe:`pe_mission_cfg.h`  | :pe:`PE_SB_TIMEOUT`            |
|                         +--------------------------------+
|                         | :pe:`PE_ONE_G`                 |
+-------------------------+--------------------------------+
| :pe:`pe_perfids.h`      | :pe:`PE_MAIN_TASK_PERF_ID`     |
+                         +--------------------------------+
|                         | :pe:`PE_UPDATE_TASK_PERF_ID`   |
+                         +--------------------------------+
|                         | :pe:`PE_SENSOR_GPS_PERF_ID`    |
+                         +--------------------------------+
|                         | :pe:`PE_SENSOR_BARO_PERF_ID `  |
+                         +--------------------------------+
|                         | :pe:`PE_SENSOR_LAND_PERF_ID`   |
+                         +--------------------------------+
|                         | :pe:`PE_SENSOR_MAT_PERF_ID `   |
+                         +--------------------------------+
|                         | :pe:`PE_SENSOR_FLOW_PERF_ID`   |
+                         +--------------------------------+
|                         | :pe:`PE_SENSOR_DIST_PERF_ID `  |
+-------------------------+--------------------------------+

.. note::
   The performance IDs defined in the :pe:`pe_perfids.h` file must have values
   that are unique system wide.  Most applications also have performance IDs.
   No two performance IDs may have the same value.
   

Platform Specific
^^^^^^^^^^^^^^^^^

+-------------------------+-------------------------------------+
| File                    | Parameter                           |
+=========================+=====================================+
| :pe:`pe_msgids.h`       | :pe:`PE_HK_TLM_MID`                 |
|                         +-------------------------------------+
|                         | :pe:`PE_SEND_HK_MID`                |
+                         +-------------------------------------+
|                         | :pe:`PE_WAKEUP_MID`                 |
+                         +-------------------------------------+
|                         | :pe:`PE_CMD_MID`                    |
+-------------------------+-------------------------------------+
| :pe:`pe_platform_cfg.h` | :pe:`PE_MISSION_REV`                |
+                         +-------------------------------------+
|                         | :pe:`PE_SCH_PIPE_DEPTH`             |
+                         +-------------------------------------+
|                         | :pe:`PE_SCH_PIPE_NAME`              |
+                         +-------------------------------------+
|                         | :pe:`PE_SCH_PIPE_PEND_TIME`         |
+                         +-------------------------------------+
|                         | :pe:`PE_WAKEUP_MID_MAX_MSG_COUNT`   |
+                         +-------------------------------------+
|                         | :pe:`PE_SEND_HK_MID_MAX_MSG_COUNT`  |
+                         +-------------------------------------+
|                         | :pe:`PE_CMD_PIPE_DEPTH`             |
+                         +-------------------------------------+
|                         | :pe:`PE_CMD_PIPE_NAME`              |
+                         +-------------------------------------+
|                         | :pe:`PE_CONFIG_TABLE_FILENAME`      |
+                         +-------------------------------------+
|                         | :pe:`PE_STARTUP_TIMEOUT_MSEC`       |
+                         +-------------------------------------+
|                         | :pe:`PE_MAX_EVENT_FILTERS`          |
+                         +-------------------------------------+
|                         | :pe:`REQ_BARO_INIT_COUNT`           |
+                         +-------------------------------------+
|                         | :pe:`BARO_TIMEOUT`                  |
+                         +-------------------------------------+
|                         | :pe:`REQ_GPS_INIT_COUNT`            |
+                         +-------------------------------------+
|                         | :pe:`GPS_TIMEOUT`                   |
+                         +-------------------------------------+
|                         | :pe:`REQ_LAND_INIT_COUNT`           |
+                         +-------------------------------------+
|                         | :pe:`LAND_TIMEOUT`                  |
+                         +-------------------------------------+
|                         | :pe:`REQ_DIST_INIT_COUNT`           |
+                         +-------------------------------------+
|                         | :pe:`DIST_TIMEOUT`                  |
+                         +-------------------------------------+
|                         | :pe:`DIST_BETA_MAX`                 |
+                         +-------------------------------------+
|                         | :pe:`DIST_SENSOR_TYPE`              |
+                         +-------------------------------------+
|                         | :pe:`REQ_FLOW_INIT_COUNT`           |
+                         +-------------------------------------+
|                         | :pe:`FLOW_TIMEOUT`                  |
+                         +-------------------------------------+
|                         | :pe:`FLOW_GYRO_HP_CUTOFF`           |
+-------------------------+-------------------------------------+

.. note::
   The message IDs defined in the :pe:`pe_msgids.h` file must have values
   that are unique system wide.  Most applications also have message IDs.
   No two message IDs may have the same value.
   
TODO: Describe the "custom" layer code.


Table(s)
^^^^^^^^

Tables are created at build time, though they can be changed at run time. Each 
output channel can, and usually does, have its own unique configuration table.
TO actually has 3 tables per channel.  The first two tables define the same 
configurable parameters, but one of these is the backup table that is compiled
directly into the application binary and only loaded if the nominal table fails
to load from the file system.  Both the nominal and the backup tables have the 
same structure.  Both are instantiations of the :to:`TO_ChannelTbl_t` 
structure.  The third table is a :term:`dump table` that contains performance 
metrics, not configuration.  This table is defined by the 
:to:`TO_ChannelDumpTbl_t` structure.

+-------------------------------+------------------------------------+------------------------------------------+
| Table Name                    | Default file name                  | Parameter                                |
+===============================+====================================+==========================================+
| :to:`TO_UDP_CONFIG_TABLENAME` | :to:`TO_UDP_CONFIG_TABLE_FILENAME` | :to:`TO_ChannelTbl_t::TableID`           |
+                               |                                    +------------------------------------------+
|                               |                                    | :to:`TO_ChannelTbl_t::MessageFlow`       |
+                               |                                    +------------------------------------------+
|                               |                                    | :to:`TO_ChannelTbl_t::PriorityQueue`     |
+-------------------------------+------------------------------------+------------------------------------------+
| :to:`TO_UDP_DUMP_TABLENAME`   | N/A                                | :to:`TO_ChannelDumpTbl_t::TableID`       |
+                               |                                    +------------------------------------------+
|                               |                                    | :to:`TO_ChannelDumpTbl_t::MessageFlow`   |
+                               |                                    +------------------------------------------+
|                               |                                    | :to:`TO_ChannelDumpTbl_t::PriorityQueue` |
+                               |                                    +------------------------------------------+
|                               |                                    | :to:`TO_ChannelDumpTbl_t::OutputQueue`   |
+-------------------------------+------------------------------------+------------------------------------------+

.. note::
   When configuring the backup table, consider the fact that, when this table is in affect, the system
   is already in a failure or partially degraded state.  Both the nominal and backup tables might be 
   identical, but it may be more appropriate for the backup table to have a reduced telemetry 
   definition to reduce the system load.  Be very careful on selecting what telemetry is in the backup 
   table.  Specifically, you may want to ensure that the backup table has enough telemetry defined in 
   the downlink to facilitate troubleshooting and recovering from the failure that caused the
   failover to the backup configuration in the first place.  Lastly, understand that while the nominal
   configuration table can also be changed before or during flight, the backup table cannot be changed
   without recompiling the TO binary.
   
Below are example tables.

.. literalinclude:: ../fsw/tables/pe_config.c
  :language: C
  :caption: Nominal Configuration Table


System Integration
^^^^^^^^^^^^^^^^^^

TODO: Describe the channelization configuration with the CF application.

TODO: Describe adding tables to Checksum Services.

TODO: Describe adding application to Health Services.

TODO: Describe possible integration with Limit Checker.


Run Time Configuration
^^^^^^^^^^^^^^^^^^^^^^

This application supports loading and reloading of table configuration at run time.  Message flows can
be added and removed at run time. 

TODO: Add references.
