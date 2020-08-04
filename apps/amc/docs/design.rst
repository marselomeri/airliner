Design
================

/*.. graphviz::
   :caption: AMC Executive Diagram
   
   digraph AMC_Executive_Diagram {
         
      On_Board_file_system -> cFE_TBL_Memory_filter_Tbl;
      cFE_TBL_Memory_filter_Tbl -> cFE_TBL;
      cFE_TBL -> cFE_TBL_Memory_filter_Tbl [label="Manage tables"];
      CFS_DS -> cFE_TBL;
      cFE_TBL -> CFS_DS [label="Manage tables"];
      cFE_TIME -> CFS_DS [label="Manage tables"];
      CFS_DS -> cFE_SB;
      System_Apps -> CFS_DS [label="Data Storage Packets"];
      CI -> CFS_DS;
      SCH -> CFS;
      CFS_DS -> KHTO;
      CFS_DS -> OSAL [label="Data Storage Packets"];
    
      On_Board_file_system [style=filled, fillcolor="#dee1ff", shape=rect, label="On-Board file system"]
      cFE_TBL_Memory_filter_Tbl [style=filled, fillcolor="#dee1ff", shape=rect, label="cFE TBL Memory filter"]
      cFE_TBL [style=filled, fillcolor="#dee1ff", shape=rect, label="cFE TBL"]
      cFE_TIME [style=filled, fillcolor="#dee1ff", shape=round, label="cFE TIME"]
      cFE_SB [style=filled, fillcolor="#dee1ff", shape=round, label="cFE SB"]
      System_Apps [style=filled, fillcolor="#dee1ff", shape=round, label="System Apps"]
      CI [style=filled, fillcolor="#dee1ff", shape=round, label="CI"]
      SCH [style=filled, fillcolor="#dee1ff", shape=round, label="SCH"]
      KHTO [style=filled, fillcolor="#dee1ff", shape=round, label="HK/TO"]
      cFS_DS [style=filled, fillcolor="#dee1ff", shape=round, label="CFS DS"]
      OSAL [style=filled, fillcolor="#dee1ff", shape=rect, label="OSAL"]
      
    }
*/


.. figure:: dox_src/users_guide/CFS_AMC_Context.jpg
   :width: 494px
   :height: 336px

TODO
   
