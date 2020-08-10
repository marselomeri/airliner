Configuration
=============

Mission Specific
^^^^^^^^^^^^^^^^
TODO: The following do not exist in doxy.

+----------------------------------+---------------------------------------+
| File                             | Parameter                             |
+==================================+=======================================+
| :mavlink:`mavlink_mission_cfg.h` | :mavlink:`MAVLINK_SB_TIMEOUT`         |
+----------------------------------+---------------------------------------+
| :mavlink:`mavlink_perfids.h`     | :mavlink:`MAVLINK_MAIN_TASK_PERF_ID`  |
+----------------------------------+---------------------------------------+


.. note::
   The performance IDs defined in the :mavlink:`mavlink_perfids.h` file must have values
   that are unique system wide.  Most applications also have performance IDs.
   No two performance IDs may have the same value.
   

Platform Specific
^^^^^^^^^^^^^^^^^

+-----------------------------------+--------------------------------------------------+
| File                              | Parameter                                        |
+===================================+==================================================+
| :mavlink:`mavlink_msgids.h`       | :mavlink:`MAVLINK_CMD_MID`                       |
|                                   +--------------------------------------------------+
|                                   | :mavlink:`MAVLINK_SEND_HK_MID`                   |
+                                   +--------------------------------------------------+
|                                   | :mavlink:`MAVLINK_WAKEUP_MID`                    |
+                                   +--------------------------------------------------+
|                                   | :mavlink:`MAVLINK_OUT_DATA_MID`                  |
+                                   +--------------------------------------------------+
|                                   | :mavlink:`MAVLINK_HK_TLM_MID`                    |
+-----------------------------------+--------------------------------------------------+
| :mavlink:`mavlink_platform_cfg.h` | :mavlink:`MAVLINK_MISSION_REV`                   |
+                                   +--------------------------------------------------+
|                                   | :mavlink:`MAVLINK_SCH_PIPE_DEPTH`                |
+                                   +--------------------------------------------------+
|                                   | :mavlink:`MAVLINK_SCH_PIPE_NAME`                 |
+                                   +--------------------------------------------------+
|                                   | :mavlink:`MAVLINK_SCH_PIPE_PEND_TIME`            |
+                                   +--------------------------------------------------+
|                                   | :mavlink:`MAVLINK_SCH_PIPE_WAKEUP_RESERVED`      |
+                                   +--------------------------------------------------+
|                                   | :mavlink:`MAVLINK_SCH_PIPE_SEND_HK_RESERVED`     |
+                                   +--------------------------------------------------+
|                                   | :mavlink:`MAVLINK_SCH_PIPE_PROC_TIMEOUT_RESERVED`|
+                                   +--------------------------------------------------+
|                                   | :mavlink:`MAVLINK_CMD_PIPE_DEPTH`                |
+                                   +--------------------------------------------------+
|                                   | :mavlink:`MAVLINK_CMD_PIPE_NAME`                 |
+                                   +--------------------------------------------------+
|                                   | :mavlink:`MAVLINK_DATA_PIPE_DEPTH`               |
+                                   +--------------------------------------------------+
|                                   | :mavlink:`MAVLINK_DATA_PIPE_NAME`                |
+                                   +--------------------------------------------------+
|                                   | :mavlink:`MAVLINK_ACTION_MAP_TABLE_FILENAME`     |
+                                   +--------------------------------------------------+
|                                   | :mavlink:`MAVLINK_TIMEOUT_TABLE_FILENAME`        |
+                                   +--------------------------------------------------+
|                                   | :mavlink:`MAVLINK_STARTUP_TIMEOUT_MSEC`          |
+                                   +--------------------------------------------------+
|                                   | :mavlink:`MAVLINK_MSG_PARAM_NAME_LEN`            |
+                                   +--------------------------------------------------+
|                                   | :mavlink:`MAVLINK_SYSTEM_ID`                     |
+                                   +--------------------------------------------------+
|                                   | :mavlink:`MAVLINK_COMPONENT_ID`                  |
+                                   +--------------------------------------------------+
|                                   | :mavlink:`MAVLINK_GCS_IP`                        |
+                                   +--------------------------------------------------+
|                                   | :mavlink:`MAVLINK_GCS_PORT`                      |
+                                   +--------------------------------------------------+
|                                   | :mavlink:`MAVLINK_PASSTHRU_IP_SRC`               |
+                                   +--------------------------------------------------+
|                                   | :mavlink:`MAVLINK_PASSTHRU_INGEST_PORT`          |
+                                   +--------------------------------------------------+
|                                   | :mavlink:`MAVLINK_HEARTBEAT_WAIT_CYCLES`         |
+                                   +--------------------------------------------------+
|                                   | :mavlink:`MAVLINK_ACTION_MAP_ENTRIES`            |
+                                   +--------------------------------------------------+
|                                   | :mavlink:`MAVLINK_LISTENER_TASK_FLAGS`           |
+-----------------------------------+--------------------------------------------------+

.. note::
   The message IDs defined in the :mavlink:`mavlink_msgids.h` file must have values
   that are unique system wide.  Most applications also have message IDs.
   No two message IDs may have the same value.
   
TODO: Describe the "custom" layer code.


Table(s)
^^^^^^^^
TODO: Tailor this section to be more MAVLINK specific. Needs Doxyfication.


Tables are created at build time, though they can be changed at run time. Each 
output channel can, and usually does, have its own unique configuration table.
TO actually has 3 tables per channel.  The first two tables define the same 
configurable parameters, but one of these is the backup table that is compiled
directly into the application binary and only loaded if the nominal table fails
to load from the file system.  Both the nominal and the backup tables have the 
same structure.  

TODO: This is a nested table

+---------------------------------------+-----------------------------+-----------------------------------------------------------+
| Table Name                            | Default file name           | Parameter                                                 |
+=======================================+=============================+===========================================================+
| :mavlink:`MAVLINK_CDS_TABLENAME`      | :mavlink:'mavlink_CdsTbl'   | :mavlink:`MAVLINK_CdsTbl_t:iParam:`                       |
+                                       |                             +-----------------------------------------------------------+
|                                       |                             | :mavlink:`MAVLINK_ActionMapTbl_t::MAVLINK_ActionMapData_t`|
+                                       |                             +-----------------------------------------------------------+
|                                       |                             | :mavlink:`MAVLINK_ActionMapData_t::MAVLINK_MsgAction_t`   |
+                                       |                             +-----------------------------------------------------------+
|                                       |                             | :mavlink:`MAVLINK_MsgAction_t::ACTION_HANDLE`             |
+---------------------------------------+-----------------------------+-----------------------------------------------------------+

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

.. literalinclude:: ../fsw/tables/mavlink_config.c
  :language: C
  :caption: MAVLINK default config table




System Integration
^^^^^^^^^^^^^^^^^^




Run Time Configuration
^^^^^^^^^^^^^^^^^^^^^^


TODO: Add references.
