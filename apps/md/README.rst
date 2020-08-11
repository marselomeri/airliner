Memory Dwell
====================================

The :term:`MD` Aapplication enables an operator to create and control telemetry streams. These dwell telemetry streams can be defined either by table loads or by jam commands. If the operating system supports symbolic addressing, Memory Dwell supports specifying memory addresses using a symbolic name. Memory addresses to be sampled are specified in terms of a numerical "offset" address, and a symbolic address. See Symbolic Address Arguments in the Memory Manager Users Guide for more details about symbolic addressing. Dwell stream definitions and state information (i.e. enable vs. disable) for each dwell that are provided via table load are saved across processor resets. An optional ability to insert string signatures into dwell packets is provided.
Design Overview

MD is a command driven, single threaded application. It will pend indefinitely on the software bus message queue until messages arrive and then processes them sequentially. Memory Dwell utilizes OSAL routines to:

    Read memory
    Translate symbolic addresses to their numerical equivalents
    Determine if a memory address is in a valid range

The fastest rate at which memory values are collected by the Memory Dwell application is determined by the rate at which the Scheduler issues wakeup messages. Collection rates are specified in terms of multiples of wakeup calls. Memory Dwell specifications that are initiated via Table Loads are saved to the Critical Data Store (CDS). Memory Dwell specifications that are initiated via Jam Commands are not saved to the CDS. Similarly, enabled/disabled state information for each Memory Dwell included in Table Loads is saved to the CDS. Enabled/disabled state information set by commands is not saved to the CDS.

.. toctree::
   :caption: Contents
   :name: md_contents
   
   Issues and Limitations <docs/limitations>
   Design <docs/design>
   Activities <docs/activities>
   Configuration <docs/configuration>
   Concept of Operations <docs/conops>
   FAQ <docs/faq>
Detailed design documentation is available `here <../../doxy/apps/md/index.html>`_.

.. image:: /docs/_static/doxygen.png
   :target: ../../doxy/apps/md/index.html
