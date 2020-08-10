Configuration
=============

Mission Specific
^^^^^^^^^^^^^^^^
TODO: The following do not exist in doxy.

+-------------------------+--------------------------------+
| File                    | Parameter                      |
+=========================+================================+
| :md:`md_perfids.h`      | :md:`MD_APPMAIN_PERF_ID`       |
+-------------------------+--------------------------------+


.. note::
   The performance IDs defined in the :md:`md_perfids.h` file must have values
   that are unique system wide.  Most applications also have performance IDs.
   No two performance IDs may have the same value.
   

Platform Specific
^^^^^^^^^^^^^^^^^

+---------------------------+-------------------------------------+
| File                      | Parameter                           |
+===========================+=====================================+
| :md:`md_msgids.h`         | :md:`MD_CMD_MID`                    |
|                           +-------------------------------------+
|                           | :md:`MD_SEND_HK_MID`                |
+                           +-------------------------------------+
|                           | :md:`MD_DWELL_PKT_MID_BASE`         |
+                           +-------------------------------------+
|                           | :md:`MD_WAKEUP_MID`                 |
+                           +-------------------------------------+
|                           | :md:`MD_HK_TLM_MID`                 |
+---------------------------+-------------------------------------+
| :md:`md_platform_cfg.h`   | :md:`MD_PIPE_NAME`                  |
+                           +-------------------------------------+
|                           | :md:`MD_PIPE_DEPTH`                 |
+                           +-------------------------------------+
|                           | :md:`MD_TBL_FILENAME_FORMAT`        |
+                           +-------------------------------------+
|                           | :md:`MD_NUM_DWELL_TABLES`           |
+                           +-------------------------------------+
|                           | :md:`MD_DWELL_TABLE_SIZE`           |
+                           +-------------------------------------+
|                           | :md:`MD_ENFORCE_DWORD_ALIGN`        |
+                           +-------------------------------------+
|                           | :md:`MD_SIGNATURE_OPTION`           |
+                           +-------------------------------------+
|                           | :md:`MD_SIGNATURE_FIELD_LENGTH`     |
+                           +-------------------------------------+
|                           | :md:`MD_MISSION_REV`                |
+---------------------------+-------------------------------------+

.. note::
   The message IDs defined in the :md:`md_msgids.h` file must have values
   that are unique system wide.  Most applications also have message IDs.
   No two message IDs may have the same value.
   
TODO: Describe the "custom" layer code.


Table(s)
^^^^^^^^
TODO: Tailor this section to be more MD specific. Needs Doxyfication.


Tables are created at build time, though they can be changed at run time. Each 
output channel can, and usually does, have its own unique configuration table.
TO actually has 3 tables per channel.  The first two tables define the same 
configurable parameters, but one of these is the backup table that is compiled
directly into the application binary and only loaded if the nominal table fails
to load from the file system.  Both the nominal and the backup tables have the 
same structure.  

TODO: Complicated table structure



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

.. literalinclude:: ../fsw/tables/md_dw01.c
  :language: C
  :caption: MD default config table

.. literalinclude:: ../fsw/tables/md_dw02.c
  :language: C
  :caption: MD default config table

.. literalinclude:: ../fsw/tables/md_dw02.c
  :language: C
  :caption: MD default config table

.. literalinclude:: ../fsw/tables/md_dw02.c
  :language: C
  :caption: MD default config table




System Integration
^^^^^^^^^^^^^^^^^^




Run Time Configuration
^^^^^^^^^^^^^^^^^^^^^^


TODO: Add references.
