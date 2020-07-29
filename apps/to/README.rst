Telemetry Output
====================================

.. toctree:: 
   :caption: Table of Contents
   :name: TO

Overview
========

The :term:`TO` Application application subscribes to and transmits Consultative 
Committee for Space Data Systems (:term:`CCSDS`) Space Packet Protocol Telemetry 
packets (:cfe:`ccsds.h`) from the cFE Software Bus, and transmits them via the 
transmission media.  The specifics of the transmission media are handled by the 
platform specific TO "custom" layer, contained within the build configuration, 
but is normally sent via a IP/UDP message.

Messages are prioritized, to help manage traffic throughput.  Transmission rates 
are ultimately driven by the rate that TO is scheduled to execute, the rate that
messages are published to the bus, and how the prioritized messages are 
interleaved at runtime.

TO supports multiple simultaneous output channels.  Configuration is set at build
time, but most configurable parameters can be changed at runtime via CFE table 
and/or command.  

Limitations and Known Issues
============================

- The number of or type of channels can only be set at build time, not run time.



Design
======

.. graphviz::
   :caption: TO Context Diagram
   
   digraph TO_Context_Diagram {
         
      SCH -> TO [label="SEND_HK and\nPROCESS_TELEMETRY\ncmds"];
      CI  -> TO [label="Ground\nCommands"];
      CFG_TBL -> TO [label="MsgIDs and\npriority queue\nassignments"];
      TO -> DS [label="HK\ntelemetry"];
      TO -> HK [label="HK\ntelemetry"];
      CF -> TO [dir="both" label="File\nData"];
      TO -> CF [label="Semaphore"];
      CFE -> TO [label="Messages\nfor\ndownlink"];
      ALL_APPS -> TO [label="Messages\nfor\ndownlink"];
       
      TO  [style=filled, fillcolor="#dee1ff", shape=circle, width=2, label="Telemetry Output"]
      SCH [style=filled, fillcolor="#f5ffc7", URL="../sch/README.html", shape=circle, width=1]
      CI  [style=filled, fillcolor="#f5ffc7", URL="../ci/README.html", shape=circle, width=1]
      CFG_TBL [style=filled, fillcolor="#fbe6ff", shape=folder, width=1, height=1, label="Config Table(s)"]
      DS  [style=filled, fillcolor="#f5ffc7", URL="../ds/README.html", shape=circle, width=1, label="DS"]
      HK  [style=filled, fillcolor="#f5ffc7", URL="../hk/README.html", shape=circle, width=1, label="HK"]
      CF  [style=filled, fillcolor="#f5ffc7", URL="../cf/README.html", shape=circle, width=1]
      CFE  [style=filled, fillcolor="#f5ffc7", shape=circle, width=1, label="CFE"]
      ALL_APPS  [style=filled, fillcolor="#f5ffc7", shape=circle, width=1, label="All Apps"]
      
    }
  

.. graphviz::
   :caption: TO Executive Diagram
   
   digraph TO_Executive_Diagram {
         
      POINT -> START;
      START -> CLASSIFIER;
      CLASSIFIER -> SCHEDULER;
      SCHEDULER -> END
      
      POINT [shape=point];
      START [style=filled, fillcolor="#dee1ff", shape=ellipse, label="Process Telemetry"];
      CLASSIFIER [style=filled, fillcolor="#8fffad", shape=rect, label="Run Classifier"];
      SCHEDULER [style=filled, fillcolor="#8fffad", shape=rect, label="Run Scheduler"];
      END [style=filled, fillcolor="#dee1ff", shape=ellipse, label="End"];
      
    }

Detailed Design
-------------------

Detailed design documentation can be found `here <../../doxy/apps/to/index.html>`_.

.. image:: /docs/_static/doxygen.png
   :target: ../../doxy/apps/sonar/index.html
 

---------

Etiam turpis ante, luctus sed velit tristique, finibus volutpat dui. Nam sagittis vel ante nec malesuada.
Praesent dignissim mi nec ornare elementum. Nunc eu augue vel sem dignissim cursus sed et nulla.
Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas.
Pellentesque dictum dui sem, non placerat tortor rhoncus in. Sed placerat nulla at rhoncus iaculis. 

Document Section
================

Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed condimentum nulla vel neque venenatis,
nec placerat lorem placerat. Cras purus eros, gravida vitae tincidunt id, vehicula nec nulla.
Fusce aliquet auctor cursus. Phasellus ex neque, vestibulum non est vitae, viverra fringilla tortor.
Donec vestibulum convallis justo, a faucibus lorem vulputate vel. Aliquam cursus odio eu felis sodales aliquet.
Aliquam erat volutpat. Maecenas eget dictum mauris. Suspendisse arcu eros, condimentum eget risus sed,
luctus efficitur arcu. Cras ut dictum mi. Nulla congue interdum lorem, semper semper enim commodo nec.

Document Subsection
-------------------


Lorem ipsum dolor sit amet, consectetur adipiscing elit. Etiam efficitur in eros et blandit. Nunc maximus,
nisl at auctor vestibulum, justo ex sollicitudin ligula, id faucibus urna orci tristique nisl.
Duis auctor rutrum orci, in ornare lacus condimentum quis. Quisque arcu velit, facilisis quis interdum ac,
hendrerit auctor mauris. Curabitur urna nibh, porttitor at ante sit amet, vestibulum interdum dolor.
Duis dictum elit orci, tincidunt imperdiet sem pellentesque et. In vehicula pellentesque varius.
Phasellus a turpis sollicitudin, bibendum massa et, imperdiet neque. Integer quis sapien in magna rutrum bibendum.
Integer cursus ex sed magna vehicula finibus. Proin tempus orci quis dolor tempus, nec condimentum odio vestibulum.
Etiam efficitur sollicitudin libero, tincidunt volutpat ligula interdum sed.

Document Subsubsection
^^^^^^^^^^^^^^^^^^^^^^

Donec non rutrum lorem. Aenean sagittis metus at pharetra fringilla. Nunc sapien dolor, cursus sed nisi at,
pretium tristique lectus. Sed pellentesque leo lectus, et convallis ipsum euismod a.
Integer at leo vitae felis pretium aliquam fringilla quis odio. Sed pharetra enim accumsan feugiat pretium.
Maecenas at pharetra tortor. Morbi semper eget mi vel finibus. Cras rutrum nulla eros, id feugiat arcu pellentesque ut.
Sed finibus tortor ac nisi ultrices viverra. Duis feugiat malesuada sapien, at commodo ante porttitor ac.
Curabitur posuere mauris mi, vel ornare orci scelerisque sit amet. Suspendisse nec fringilla dui. 

Document Paragraph
""""""""""""""""""

Pellentesque nec est in odio ultrices elementum. Vestibulum et hendrerit sapien, quis vulputate turpis.
Suspendisse potenti. Curabitur tristique sit amet lectus non viverra. Phasellus rutrum dapibus turpis sed imperdiet.
Mauris maximus viverra ante. Donec eu egestas mauris. Morbi vulputate tincidunt euismod. Integer vel porttitor neque.
Donec at lacus suscipit, lacinia lectus vel, sagittis lectus.

*********************
Structural Elements 2
*********************

Etiam turpis ante, luctus sed velit tristique, finibus volutpat dui. Nam sagittis vel ante nec malesuada.
Praesent dignissim mi nec ornare elementum. Nunc eu augue vel sem dignissim cursus sed et nulla.
Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas.
Pellentesque dictum dui sem, non placerat tortor rhoncus in. Sed placerat nulla at rhoncus iaculis. 

Document Section
================

Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed condimentum nulla vel neque venenatis,
nec placerat lorem placerat. Cras purus eros, gravida vitae tincidunt id, vehicula nec nulla.
Fusce aliquet auctor cursus. Phasellus ex neque, vestibulum non est vitae, viverra fringilla tortor.
Donec vestibulum convallis justo, a faucibus lorem vulputate vel. Aliquam cursus odio eu felis sodales aliquet.
Aliquam erat volutpat. Maecenas eget dictum mauris. Suspendisse arcu eros, condimentum eget risus sed,
luctus efficitur arcu. Cras ut dictum mi. Nulla congue interdum lorem, semper semper enim commodo nec.

Document Subsection
-------------------

.. figure:: static/yi_jing_01_chien.jpg
    :align: right
    :figwidth: 200px

    This is a caption for a figure. Text should wrap around the caption.

Lorem ipsum dolor sit amet, consectetur adipiscing elit. Etiam efficitur in eros et blandit. Nunc maximus,
nisl at auctor vestibulum, justo ex sollicitudin ligula, id faucibus urna orci tristique nisl.
Duis auctor rutrum orci, in ornare lacus condimentum quis. Quisque arcu velit, facilisis quis interdum ac,
hendrerit auctor mauris. Curabitur urna nibh, porttitor at ante sit amet, vestibulum interdum dolor.
Duis dictum elit orci, tincidunt imperdiet sem pellentesque et. In vehicula pellentesque varius.
Phasellus a turpis sollicitudin, bibendum massa et, imperdiet neque. Integer quis sapien in magna rutrum bibendum.
Integer cursus ex sed magna vehicula finibus. Proin tempus orci quis dolor tempus, nec condimentum odio vestibulum.
Etiam efficitur sollicitudin libero, tincidunt volutpat ligula interdum sed. Praesent congue sagittis nisl et suscipit.
Vivamus sagittis risus et egestas commodo.Cras venenatis arcu in pharetra interdum.
Donec quis metus porttitor tellus cursus lobortis. Quisque et orci magna. Fusce rhoncus mi mi,
at vehicula massa rhoncus quis. Mauris augue leo, pretium eget molestie vitae, efficitur nec nulla.
In hac habitasse platea dictumst. Sed sit amet imperdiet purus. 