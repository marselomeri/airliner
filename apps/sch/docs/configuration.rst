Configuration
=============

Mission Specific
^^^^^^^^^^^^^^^^

TODO: Add Doxygen documentation for pe_mission_cfg.h

+-------------------------+--------------------------------+
| File                    | Parameter                      |
+=========================+================================+
| :sch:`pe_perfids.h`     | :sch:`SCH_APPMAIN_PERF_ID`     |
+-------------------------+--------------------------------+

.. note::
   The performance IDs defined in the :sch:`sch_perfids.h` file must have values
   that are unique system wide.  Most applications also have performance IDs.
   No two performance IDs may have the same value.
   

Platform Specific
^^^^^^^^^^^^^^^^^

+--------------------------+-------------------------------------+
| File                     | Parameter                           |
+==========================+=====================================+
| :sch:`sch_msgids.h`      | :sch:`SCH_CMD_MID`                  |
|                          +-------------------------------------+
|                          | :sch:`SCH_SEND_HK_MID`              |
+                          +-------------------------------------+
|                          | :sch:`SCH_UNUSED_MID`               |
+                          +-------------------------------------+
|                          | :sch:`SCH_HK_TLM_MID`               |
+                          +-------------------------------------+
|                          | :sch:`SCH_DIAG_TLM_MID`             |
+                          +-------------------------------------+
|                          | :sch:`SCH_ACTIVITY_DONE_MID`        |
+--------------------------+-------------------------------------+
| :sch:`sch_platform_cfg.h`| :sch:`SCH_PIPE_DEPTH`               |
+                          +-------------------------------------+
|                          | :sch:`SCH_TOTAL_SLOTS`              |
+                          +-------------------------------------+
|                          | :sch:`SCH_ENTRIES_PER_SLOT`         |
+                          +-------------------------------------+
|                          | :sch:`SCH_MAX_MESSAGES`             |
+                          +-------------------------------------+
|                          | :sch:`SCH_MDT_MIN_MSG_ID`           |
+                          +-------------------------------------+
|                          | :sch:`SCH_MDT_MAX_MSG_ID`           |
+                          +-------------------------------------+
|                          | :pe:`PE_CMD_PIPE_DEPTH`             |
+                          +-------------------------------------+
|                          | :pe:`PE_CMD_PIPE_NAME`              |
+                          +-------------------------------------+
|                          | :pe:`PE_CONFIG_TABLE_FILENAME`      |
+                          +-------------------------------------+
|                          | :pe:`PE_STARTUP_TIMEOUT_MSEC`       |
+--------------------------+-------------------------------------+

.. note::
   The message IDs defined in the :pe:`pe_msgids.h` file must have values
   that are unique system wide.  Most applications also have message IDs.
   No two message IDs may have the same value.
   
TODO: Describe the "custom" layer code.


Table(s)
^^^^^^^^

TODO: Add Table explanation

TODO: Add Doxygen documentation for pe_config.tbl

+-------------------------------+------------------------------------+------------------------------------------+
| Table Name                    | Default file name                  | Parameter                                |
+===============================+====================================+==========================================+
| :pe:`CONFIG_TBL`              | :pe:`pe_config.tbl`                | :pe:`PE_ConfigTbl_t::VXY_PUB_THRESH`     |
+                               |                                    +------------------------------------------+
|                               |                                    | :pe:`PE_ConfigTbl_t::Z_PUB_THRESH`       |
+                               |                                    +------------------------------------------+
|                               |                                    | :pe:`PE_ConfigTbl_t::ACCEL_XY_STDDEV`    |
+                               |                                    +------------------------------------------+
|                               |                                    | :pe:`PE_ConfigTbl_t::ACCEL_Z_STDDEV`     |
+                               |                                    +------------------------------------------+
|                               |                                    | :pe:`PE_ConfigTbl_t::BARO_FUSE`          |
+                               |                                    +------------------------------------------+
|                               |                                    | :pe:`PE_ConfigTbl_t::BARO_STDDEV`        |
+                               |                                    +------------------------------------------+
|                               |                                    | :pe:`PE_ConfigTbl_t::GPS_FUSE`           |
+                               |                                    +------------------------------------------+
|                               |                                    | :pe:`PE_ConfigTbl_t::GPS_DELAY`          |
+                               |                                    +------------------------------------------+
|                               |                                    | :pe:`PE_ConfigTbl_t::GPS_XY_STDDEV`      |
+                               |                                    +------------------------------------------+
|                               |                                    | :pe:`PE_ConfigTbl_t::GPS_Z_STDDEV`       |
+                               |                                    +------------------------------------------+
|                               |                                    | :pe:`PE_ConfigTbl_t::GPS_VXY_STDDEV`     |
+                               |                                    +------------------------------------------+
|                               |                                    | :pe:`PE_ConfigTbl_t::GPS_VZ_STDDEV`      |
+                               |                                    +------------------------------------------+
|                               |                                    | :pe:`PE_ConfigTbl_t::GPS_EPH_MAX`        |
+                               |                                    +------------------------------------------+
|                               |                                    | :pe:`PE_ConfigTbl_t::GPS_EPV_MAX`        |
+                               |                                    +------------------------------------------+
|                               |                                    | :pe:`PE_ConfigTbl_t::LAND_FUSE`          |
+                               |                                    +------------------------------------------+
|                               |                                    | :pe:`PE_ConfigTbl_t::LAND_Z_STDDEV`      |
+                               |                                    +------------------------------------------+
|                               |                                    | :pe:`PE_ConfigTbl_t::LAND_VXY_STDDEV`    |
+                               |                                    +------------------------------------------+
|                               |                                    | :pe:`PE_ConfigTbl_t::PN_P_NOISE_DENSITY` |
+                               |                                    +------------------------------------------+
|                               |                                    | :pe:`PE_ConfigTbl_t::PN_V_NOISE_DENSITY` |
+                               |                                    +------------------------------------------+
|                               |                                    | :pe:`PE_ConfigTbl_t::PN_B_NOISE_DENSITY` |
+                               |                                    +------------------------------------------+
|                               |                                    | :pe:`PE_ConfigTbl_t::PN_T_NOISE_DENSITY` |
+                               |                                    +------------------------------------------+
|                               |                                    | :pe:`PE_ConfigTbl_t::T_MAX_GRADE`        |
+                               |                                    +------------------------------------------+
|                               |                                    | :pe:`PE_ConfigTbl_t::FAKE_ORIGIN`        |
+                               |                                    +------------------------------------------+
|                               |                                    | :pe:`PE_ConfigTbl_t::INIT_ORIGIN_LAT`    |
+                               |                                    +------------------------------------------+
|                               |                                    | :pe:`PE_ConfigTbl_t::INIT_ORIGIN_LON`    |
+                               |                                    +------------------------------------------+
|                               |                                    | :pe:`PE_ConfigTbl_t::DIST_FUSE`          |
+                               |                                    +------------------------------------------+
|                               |                                    | :pe:`PE_ConfigTbl_t::DIST_STDDEV`        |
+                               |                                    +------------------------------------------+
|                               |                                    | :pe:`PE_ConfigTbl_t::DIST_OFF_Z`         |
+                               |                                    +------------------------------------------+
|                               |                                    | :pe:`PE_ConfigTbl_t::FLOW_FUSE`          |
+                               |                                    +------------------------------------------+
|                               |                                    | :pe:`PE_ConfigTbl_t::FLOW_SCALE`         |
+                               |                                    +------------------------------------------+
|                               |                                    | :pe:`PE_ConfigTbl_t::FLOW_R`             |
+                               |                                    +------------------------------------------+
|                               |                                    | :pe:`PE_ConfigTbl_t::FLOW_RR`            |
+                               |                                    +------------------------------------------+
|                               |                                    | :pe:`PE_ConfigTbl_t::FLOW_QUALITY_MIN`   |
+                               |                                    +------------------------------------------+
|                               |                                    | :pe:`PE_ConfigTbl_t::FLOW_MIN_AGL`       |
+-------------------------------+------------------------------------+------------------------------------------+

TODO: Add Doxygen documentation for pe_config.c

Below is an example table.

.. literalinclude:: ../fsw/tables/pe_config.c
  :language: C
  :caption: Nominal Configuration Table


System Integration
^^^^^^^^^^^^^^^^^^

TODO: Describe System Integration instructions specific to PE.


Run Time Configuration
^^^^^^^^^^^^^^^^^^^^^^

TODO: Describe Run Time Configuration for PE.
