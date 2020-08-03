Glossary
====================================

.. glossary::
  
  TO
    The Telemetry Output (TO) flight software application sends telemetry from the remote vehicle to the ground.
    
  PE
    The Position Estimator (PE) flight software application sends position data from the remote vehicle to the ground.
    
  PRMLIB
    TODO: Add definition of the Parameter Library (PRMLIB)
    
  CCSDS
    Consultative Committee for Space Data Systems (CCSDS) develops and documents communications and data systems standards for spaceflight. `https://public.ccsds.org`_ 
  Ashai KASEI (AK8963)
   The Ashai KASEI (AK8963) flight software application uses a 3-axis electronic compass to navigate. The app utilizes GPS to determine where the drone is at.
    
  dump table
    CFE Dump Tables are created at run time, not build time.  They do not contain configuration.  They 
    cannot be loaded or reloaded.  All values contained within a CFE dump table are cleared at load time.  
    Dump tables are updated by flight software at run time, but may be written to the file system by 
    ground command for transfer down to the ground.  Typically, dump tables contain run time metrics that 
    are too big to transmit to the ground in real time, or they contain diagnostic data that is not usually
    interesting enough to warrant consumption of the downlink telemetry bandwidth. 