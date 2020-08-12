Configuration
=============

Mission Specific
^^^^^^^^^^^^^^^^

TODO: Add Doxygen documentation for sch_mission_cfg.h

+-------------------------+--------------------------------+
| File                    | Parameter                      |
+=========================+================================+
| :sch:`sch_perfids.h`    | :sch:`SCH_APPMAIN_PERF_ID`     |
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
|                          | :sch:`SCH_MAX_MSG_WORDS`            |
+                          +-------------------------------------+
|                          | :sch:`SCH_MAX_LAG_COUNT`            |
+                          +-------------------------------------+
|                          | :sch:`SCH_MAX_SLOTS_PER_WAKEUP`     |
+                          +-------------------------------------+
|                          | :sch:`SCH_MICROS_PER_MAJOR_FRAME`   |
+                          +-------------------------------------+
|                          | :sch:`SCH_SYNC_SLOT_DRIFT_WINDOW`   |
+                          +-------------------------------------+
|                          | :sch:`SCH_STARTUP_SYNC_TIMEOUT`     |
+                          +-------------------------------------+
|                          | :sch:`SCH_STARTUP_PERIOD`           |
+                          +-------------------------------------+
|                          | :sch:`SCH_MAX_NOISY_MAJORF`         |
+                          +-------------------------------------+
|                          | :sch:`SCH_LIB_PRESENCE`             |
+                          +-------------------------------------+
|                          | :sch:`SCH_LIB_DIS_CTR`              |
+                          +-------------------------------------+
|                          | :sch:`SCH_SCHEDULE_FILENAME`        |
+                          +-------------------------------------+
|                          | :sch:`SCH_MESSAGE_FILENAME`         |
+                          +-------------------------------------+
|                          | :sch:`SCH_MISSION_REV`              |
+                          +-------------------------------------+
|                          | :sch:`SCH_AD_CHILD_TASK_PRIORITY`   |
+                          +-------------------------------------+
|                          | :sch:`SCH_DEADLINES_PER_SLOT`       |
+                          +-------------------------------------+
|                          | :sch:`SCH_AD_CHILD_TASK_FLAGS`      |
+--------------------------+-------------------------------------+

.. note::
   The message IDs defined in the :sch:`sch_msgids.h` file must have values
   that are unique system wide.  Most applications also have message IDs.
   No two message IDs may have the same value.

Table(s)
^^^^^^^^

TODO: Add Table explanation

TODO: Review these SCH tables and add Doxygen doumentation 

+-------------------------------+------------------------------------+-------------------------------------------------------------+
| Table Name                    | Default file name                  | Parameter                                                   |
+===============================+====================================+=============================================================+
| :sch:`SCH_MESSAGE_TABLENAME`  | :sch:`SCH_MESSAGE_FILENAME`        | :sch:`SCH_MessageEntry_t::MessageBuffer`                    |
+-------------------------------+------------------------------------+-------------------------------------------------------------+
| :sch:`SCH_SCHEDULE_TABLENAME` | :sch:`SCH_SCHEDULE_FILENAME`       | :sch:`SCH_ScheduleEntry_t::EnableState`                     |
+                               |                                    +-------------------------------------------------------------+
|                               |                                    | :sch:`SCH_ScheduleEntry_t::Type`                            |
+                               |                                    +-------------------------------------------------------------+
|                               |                                    | :sch:`SCH_ScheduleEntry_t::Frequency`                       |  
+                               |                                    +-------------------------------------------------------------+
|                               |                                    | :sch:`SCH_ScheduleEntry_t::Remainder`                       |
+                               |                                    +-------------------------------------------------------------+
|                               |                                    | :sch:`SCH_ScheduleEntry_t::MessageIndex`                    |
+                               |                                    +-------------------------------------------------------------+
|                               |                                    | :sch:`SCH_ScheduleEntry_t::GroupData`                       |
+                               |                                    +-------------------------------------------------------------+
|                               |                                    | :sch:`SCH_ScheduleEntry_t::Deadline`                        |
+-------------------------------+------------------------------------+-------------------------------------------------------------+

Below is an example table.

.. literalinclude:: ../fsw/tables/sch_def_msgtbl.c
  :language: C
  :caption: Application Message Table

.. literalinclude:: ../fsw/tables/sch_def_schtbl.c
  :language: C
  :caption: Application Schedule Table

System Integration
^^^^^^^^^^^^^^^^^^

TODO: Describe System Integration instructions specific to SCH.


Run Time Configuration
^^^^^^^^^^^^^^^^^^^^^^

TODO: Describe Run Time Configuration for SCH.
