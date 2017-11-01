# ARTE Usage

ARTE requires one command line argument for a JSON configuration file.  
An example is included below:  <br>
{  <br>
  &nbsp;&nbsp;"name": "ARTE test config file",  <br>
  &nbsp;&nbsp;"version": 0.1,  <br>
  &nbsp;&nbsp;"date": "2017-09-22T00:00:00.000Z",  <br>
  &nbsp;&nbsp;"timeout": 300,  <br>
  &nbsp;&nbsp;"timeouts": 5,  <br>
  &nbsp;&nbsp;"watchdog": 5,  <br>
  &nbsp;&nbsp;"majorframe": 200,  <br>
  &nbsp;&nbsp;"clients": [  <br>
      &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;{  <br>
      &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"name": "Pyliner",  <br>
      &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"command": "python2 challenge.py",  <br>
      &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"output": "test_script1.txt",  <br>
      &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"cwd": "../../tools/pyliner/"  <br>
    &nbsp;&nbsp;&nbsp;&nbsp;},  <br>
    &nbsp;&nbsp;&nbsp;&nbsp;{  <br>
      &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"name": "Airliner",  <br>
      &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"command": "./core-bin -M TEST",  <br>
      &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"output": "test_script2.txt",  <br>
      &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"cwd": "../../build/softsim/default/target/exe/"  <br>
    &nbsp;&nbsp;&nbsp;&nbsp;}  <br>
  &nbsp;&nbsp;]  <br>
}  <br>

- timeout
    The overall timeout for the test.
- timeouts
    A generic timeout for anything that would otherwise pend forever.
- watchdog
    A watchdog timeout for threads.
- majorframe 
    The number of minor frames in a major frame.
- clients
    The clients that should connect to ARTE server.
    - name      The name of the client.
    - command   The command to execute a client.
    - output    The file to pipe output to.
    - cwd       The directory to execute the command in.
