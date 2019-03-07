#######################################################################################
#
# File:  ReadMe.txt
# Desc:  Description of the VC cFS application
#
#######################################################################################

A CFS application runs as a child thread in non-realtime OS, like Linux, and as a task
in realtime OS, like VxWorks.

Once invoked (automatically done by the CFE services), the application first initializes
its data, including creations and registrations of message pipes and tables, subscriptions
to other applications' output data, etc.  It waits for the cFE startup sync.  Once
that is received it enters a main loop, awaiting for messages to respond to.
(From hereon, this will be referring to as listening mode.)

App Behavior:
=============
When in listening mode, there are 2 specific messages the application should respond to:

1) VC_WAKEUP_MID

   This message is normally sent by the CFS message scheduler.  Only upon receiving
   this message would the application start doing work.  When woken up, the application
   will process and respond to all incoming commands before going back to the
   listening mode.

2) VC_SEND_HK_MID

   This message is normally sent by the CFS message scheduler.  Upon receiving this
   message, the application sends out its latest housekepping data (VC_HK_TLM_MID)
   to be downlinked to the ground.  Then it goes back to the listening mode.

   The application's housekeeping data is published only upon receiving an
   VC_SEND_HK_MID message.  It should contain ONLY essential data that the ground
   system needs in order to run the mission effectively.

Commands:
=========

In addition to the WAKEUP and SEND_HK commands, this app has a NOOP command and
a RESET command, a Start Streaming command, and a Stop Streaming command.

The NOOP command increments the command counter in the housekeeping data.
The RESET command resets the command and command error counters in the
housekeeping data. The Start Streaming command starts streaming video to
the ground system specified by the command address and port number and
the stop streaming command stops streaming to the ground system.

cFE Softare Bus Pipes:
======================
This application has two cFE Software Bus pipes for receiving messages.  They
are kept separate because this app's design prioritizes responsiveness to
the VC_WAKEUP_MID and VC_SEND_HK_MID commands over other
messages.

The "scheduling" pipe subscribes to the above wakeup and send housekeeping
commands.

The "command" pipe subscribes to other app command messages.
