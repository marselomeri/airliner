Limitations and Known Issues
============================

Application Termination
^^^^^^^^^^^^^^^^^^^^^^^^^
Potential causes for AK8963 to terminate prematurely are an error return from the software bus in the application main loop or error return from one of the cFE table services functions when AK8963 tries to do table management (check for updates, dump requests etc.) during each housekeeping cycle.

Crital Data Store Operation
^^^^^^^^^^^^^^^^^^^^^^^^^
When using the Critical Data Store (CDS), the results tables and housekeeping data will only be restored if the application was shut down through cFE Executive Services and exited clean. If this is not the case, default values will be used

TODO

