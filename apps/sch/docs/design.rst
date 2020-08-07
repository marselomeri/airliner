Design
================

.. graphviz::
   :caption: SCH Context Diagram
   
   digraph SCH_Context_Diagram {
         
      C -> SCH [label="Ground Cmds"];
      SCH  -> Apps [label="Schedued Messages"];
      SCH -> HK [label="HK Packets"];
      SCH -> TO [label="HK Packets"];
      SCH -> DS [label="HK Packets"];
      SDT -> SCH [label="Schedule\nof Message\nGeneration"];
      MDT -> SCH [label="Message\nContent\nDefinition"];

      
      cFE -> SCH [dir="both" label="Major Frame\nTiming Control\nand Notification"];
      I -> cFE [];
      
      OS -> SCH [dir="both" label="Minor Frame\nTiming Control\nand Notification"];
      OS -> HW [dir="both"];
       
      SCH  [style=filled, fillcolor="#dee1ff", shape=circle, width=2, label="Scheduler"]
      C [style=filled, fillcolor="#f5ffc7", shape=circle, width=1, label="C"]
      Apps  [style=filled, fillcolor="#f5ffc7", shape=circle, width=1, label="Apps"]
      HK [style=filled, fillcolor="#f5ffc7", shape= circle, width=1, label="HK"]
      TO  [style=filled, fillcolor="#f5ffc7", shape=circle, width=1, label="TO"]
      DS  [style=filled, fillcolor="#f5ffc7", shape=circle, width=1, label="DS"]
      SDT  [style=filled, fillcolor="#fbe6ff", shape=folder, width=1, height=1, label="Schedule\nDefinition\nTable"]
      MDT  [style=filled, fillcolor="#fbe6ff", shape=folder, width=1, height=1, label="Message\nDefinition\nTable"]
      cFE  [style="filled,rounded", fillcolor="#8fffad", shape=rect, label="cFE Time"]
      I  [style=filled, fillcolor="#ffffff", shape=rect, label="1 Hz\n Interface"]
      OS  [style="filled,rounded", fillcolor="#8fffad", shape=rect, label="OS API"]
      HW  [style=filled, fillcolor="#ffffff", shape=rect, label="HW Timer"]
      
    }

Detailed design documentation can be found `here <../../../doxy/apps/sch/cfsschovr.html>`_.

.. image:: /docs/_static/doxygen.png
   :target: ../../../doxy/apps/sch/index.html