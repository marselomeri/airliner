Configuration
=============

TODO

Mission Specific
^^^^^^^^^^^^^^^^

TODO: Add Doxygen documentation for flow_mission_cfg.h

+----------------------------+-------------------------------------+
| File                       | Parameter                           |
+============================+=====================================+
| :flow:`flow_mission_cfg.h` | :flow:`FLOW_SB_TIMEOUT`             |
+----------------------------+-------------------------------------+
| :flow:`flow_perfids.h`     | :flow:`FLOW_MAIN_TASK_PERF_ID`      |
+                            +-------------------------------------+
|                            | :flow:`FLOW_COMPUTE_PERF_ID`        |
+----------------------------+-------------------------------------+

.. note::
   The performance IDs defined in the :flow:`flow_perfids.h` file must have values
   that are unique system wide.  Most applications also have performance IDs.
   No two performance IDs may have the same value.
   

Platform Specific
^^^^^^^^^^^^^^^^^

+-----------------------------+---------------------------------------------+
| File                        | Parameter                                   |
+=============================+=============================================+
| :flow:`flow_msgids.h`       | :flow:`FLOW_HK_TLM_MID`                     |
+                             +---------------------------------------------+
|                             | :flow:`FLOW_SEND_HK_MID`                    |
+                             +---------------------------------------------+
|                             | :flow:`FLOW_WAKEUP_MID`                     |
+                             +---------------------------------------------+
|                             | :flow:`FLOW_CMD_MID`                        |
+                             +---------------------------------------------+
|                             | :flow:`FLOW_FRAME_MID`                      |
+                             +---------------------------------------------+
|                             | :flow:`FLOW_DIAG_TLM_MID`                   |
+-----------------------------+---------------------------------------------+
| :flow:`flow_platform_cfg.h` | :flow:`FLOW_MISSION_REV`                    |
+                             +---------------------------------------------+
|                             | :flow:`FLOW_SCH_PIPE_DEPTH`                 |
+                             +---------------------------------------------+
|                             | :flow:`FLOW_SCH_PIPE_NAME`                  |
+                             +---------------------------------------------+
|                             | :flow:`FLOW_SCH_PIPE_PEND_TIME`             |
+                             +---------------------------------------------+
|                             | :flow:`FLOW_WAKEUP_MID_MAX_MSG_COUNT`       |
+                             +---------------------------------------------+
|                             | :flow:`FLOW_SEND_HK_MID_MAX_MSG_COUNT`      |
+                             +---------------------------------------------+
|                             | :flow:`FLOW_CMD_PIPE_DEPTH`                 |
+                             +---------------------------------------------+
|                             | :flow:`FLOW_CMD_PIPE_NAME`                  |
+                             +---------------------------------------------+
|                             | :flow:`FLOW_DATA_PIPE_DEPTH`                |
+                             +---------------------------------------------+
|                             | :flow:`FLOW_DATA_PIPE_NAME`                 |
+                             +---------------------------------------------+
|                             | :flow:`FLOW_CONFIG_TABLE_FILENAME`          |
+                             +---------------------------------------------+
|                             | :flow:`FLOW_STARTUP_TIMEOUT_MSEC`           |
+                             +---------------------------------------------+
|                             | :flow:`FLOW_GYRO_PIPE_DEPTH`                |
+                             +---------------------------------------------+
|                             | :flow:`FLOW_GYRO_PIPE_NAME`                 |
+                             +---------------------------------------------+
|                             | :flow:`FLOW_SENSOR_GYRO_MAX_MSG_COUNT`      |
+-----------------------------+---------------------------------------------+

.. note::
   The message IDs defined in the :flow:`flow_msgids.h` file must have values
   that are unique system wide.  Most applications also have message IDs.
   No two message IDs may have the same value.

Table(s)
^^^^^^^^^^^^^^^^

TODO REVIEW TABLE

+-------------------------------+------------------------------------+---------------------------------------------------------+
| Table Name                    | Default file name                  | Parameter                                               |
+===============================+====================================+=========================================================+
| :flow:`FLOW_CONFIG_TABLENAME` | :flow:`FLOW_CONFIG_TABLE_FILENAME` | :flow:`FLOW_ConfigTbl_t::HFOV`                          |
+                               |                                    +---------------------------------------------------------+
|                               |                                    | :flow:`FLOW_ConfigTbl_t::FLOW_TILE_SIZE`                |
+                               |                                    +---------------------------------------------------------+
|                               |                                    | :flow:`FLOW_ConfigTbl_t::FLOW_NUM_BLOCKS`               |
+                               |                                    +---------------------------------------------------------+
|                               |                                    | :flow:`FLOW_ConfigTbl_t::FLOW_DEFAULT_OUTPUT_RATE`      |
+                               |                                    +---------------------------------------------------------+
|                               |                                    | :flow:`FLOW_ConfigTbl_t::FLOW_DEFAULT_IMAGE_WIDTH`      |
+                               |                                    +---------------------------------------------------------+
|                               |                                    | :flow:`FLOW_ConfigTbl_t::FLOW_DEFAULT_IMAGE_HEIGHT`     |
+                               |                                    +---------------------------------------------------------+
|                               |                                    | :flow:`FLOW_ConfigTbl_t::FLOW_DEFAULT_SEARCH_SIZE`      |
+                               |                                    +---------------------------------------------------------+
|                               |                                    | :flow:`FLOW_ConfigTbl_t::FLOW_DEFAULT_FEATURE_THRESHOLD`|
+                               |                                    +---------------------------------------------------------+
|                               |                                    | :flow:`FLOW_ConfigTbl_t::FLOW_DEFAULT_VALUE_THRESHOLD`  |
+                               |                                    +---------------------------------------------------------+
|                               |                                    | :flow:`FLOW_ConfigTbl_t::FLOW_MEAN_COUNT_THRESHOLD`     |
+-------------------------------+------------------------------------+---------------------------------------------------------+

Below is an example table.

.. literalinclude:: ../fsw/tables/flow_config.c
  :language: C
  :caption: Nominal Configuration Table


System Integration
^^^^^^^^^^^^^^^^^^

TODO: Describe System Integration instructions specific to FLOW.


Run Time Configuration
^^^^^^^^^^^^^^^^^^^^^^

TODO: Describe Run Time Configuration for FLOW.






















