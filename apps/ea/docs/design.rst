Design
================

TODO Add relevent EA Diagrams.
   
				CFS EA Context

.. graphviz::
   :caption: EA Context Diagram
   
   digraph EA_Context_Diagram {
         
      SCH -> app [label="HK Requests PERFMON WAKEUP"];
      app -> HK [label="HK Packets"];
      ci -> app [label="Ground Command"];
       
     
      SCH [style=filled, fillcolor="#f5ffc7", URL="../sch/README.html", shape=circle, width=1]
      app [style=filled, fillcolor="#f5ffc7", URL="../sch/README.html", shape=circle, width=1]
      HK [style=filled, fillcolor="#f5ffc7", URL="../sch/README.html", shape=circle, width=1]
      ci [style=filled, fillcolor="#f5ffc7", URL="../sch/README.html", shape=circle, width=1]
      
    }
  

.. figure:: dox_src/users_guide/CFS_EA_Context.jpg
   :width: 1570px
   :height: 1214px
