Design
================

.. graphviz::
   :caption: CF Context Diagram
   
   digraph CF_Context_Diagram {
         
      CF -> Config;
      Config -> CF;
      SCH -> CF [lable="Wake up Msg"];
      CF -> HK [label="Housekeeping"];
      CI -> CF [label="Gnd, Cmds, Uplink PDUs"];
      CF -> OSAL;
      OSAL -> CF;
      OSAL -> FS;
      FS -> OSAL;
      CF -> TO [label="Downlink PDUs Housekeeping DIAG Packets"];
      TO -> CF [label="throttling smaphore"];
      CF -> TO [label="throttling smaphore"];
      
      Config [style=filled, fillcolor="#fbe6ff", shape=rect, width=2, label="Configuration Table"] 
      CF  [style=filled, fillcolor="#dee1ff", shape=circle, width=2, label="CF"]
      SCH [style=filled, fillcolor="#f5ffc7", shape=circle, width=2, label="SCH"]
      HK [style=filled, fillcolor="#f5ffc7", shape=circle, width=2, label="HK,DS"]
      CI [style=filled, fillcolor="#f5ffc7", shape=circle, width=2, label="CI"]
      TO [style=filled, fillcolor="#fbe6ff", shape=circle, width=2, label="TO"]
      OSAL [style=filled, fillcolor="dee1ff", shape=rect, width=2, label="OSAL"]
      FS [style=filled, fillcolor="#dee1f", shape=folder, width=2, label="File system"]
      
    }

TODO Add relevent CF Diagrams.
   
