# Airliner Setup in Linux
***
## Assumptions for the use of Airliner:
***
* User can navigate Windows Command Prompt
* User is familiar with navigating Linux Shells
* User is comfortable using git and navigating GitHub
* VirtualBox and Vagrant are installed

***
## Required Versions:
***
* VirtualBox 5.1.38
* Vagrant 2.2.9
* Ubuntu 16.04
* Java 11.0.2

***
## VirtualBox setup in Windows:
***

1. Download [VirtualBox 5.1.38](https://www.virtualbox.org/wiki/Download_Old_Builds_5_1 "VirtualBox 5.1.38")
2. Download [Vagrant 2.2.9](https://www.vagrantup.com/downloads "Vagrant 2.2.9") and follow [installation instructions](https://www.vagrantup.com/docs/installation)
2. Within Windows, create a directory for your environment
3. Within that directory perform a `vagrant init`
4. Open the newly generated Vagrantfile in a text editor and uncomment/edit the following: 

```
config.vm.box = "windhoverlabs/workshop"
```

```
config.vm.provider "virtualbox" do |vb|
            # Display the VirtualBox GUI when booting the machine
            vb.gui = true
            # Customize the amount of memory on the VM (half of system memory is recommended):
            vb.memory = 
end
```

When finished the edited Vagrantfile should appear similar to the image below:

![1](resources/vagrantfile_setup.JPG "Edited Vagrantfile")

5. Perform a `vagrant up` at destination of Vagrantfile

	**NOTE:** This command must be run **ANY TIME** that you want to boot up the Virtual Machine

***
## Airliner Initial Install & Setup:
***


1. Ensure the auto update feature is off in Ubuntu as this has been known to cause version conflicts with Airliner

2.
```
$ ssh-keygen
```

3. 
```
$ cd .ssh
```
4. Navigate to the file below, open within a text editor, and copy everything within this file ```$~/.ssh$ vim id_rsa.pub``` 
5. Create a new SSH key on your personal Github and paste the entirety of what was in the previous file
6. Go to Windhover Lab's Airliner repository and get an SSH key
7. Create or navigate to your git directory in your terminal
8. 
```
$~/git$ git clone git@github.com:WindhoverLabs/airliner.git
```
9. 
```
$~/git$ cd airliner/tools/commander/
```
10. 
```
$~/git/airliner/tools/commander$ npm install
```

The following npm warnings are expected:

![2](resources/npm_install.PNG "NPM Warnings")

11. To show all the options of targets available to make, use command `make`

The following options are the targets currently available to make:
```
$~/git/airliner$ make
bebop2/sitl bebop2/default ocpoc/default ocpoc/quadx shared/cvt_perfids.h tutorial/airliner tutorial/cfs typhoon_h480/sitl reference/default
Specify a target to build.  Available targets are:
bebop2/sitl
bebop2/default
ocpoc/default
ocpoc/quadx
shared/cvt_perfids.h
tutorial/airliner
tutorial/cfs
typhoon_h480/sitl
reference/default
``` 

***
## Airliner Target Installation & Simulation for bebop2/sitl
***
1. 
```
$~/git/airliner$ make bebop2/sitl
```
2. 
```
$~/git/airliner$ cd build/bebop2/sitl
```
3. 
```
$~/git/airliner/build/bebop2/sitl$ make ground_tools
```
4. Open three terminals starting at the following location: 
```
$~/git/airliner/build/bebop2/sitl$
``` 

### Terminal 1: Simulation

1. 
```
$~/git/airliner/build/bebop2/sitl$ cd host/
```
2. **Simulate using Gazebo 8**: At the moment this option is too slow to run in a VM, but feel free to try it 
```
$~/git/airliner/build/bebop2/sitl/host$ ./start-gazebo
``` 
3. **Simulate using Jmavsim**: This option should always work 
```
$~/git/airliner/build/bebop2/sitl/host$ ./start-jmavsim
``` 

Your jmavsim simulation should look as follows if working properly:

![4](resources/jmavsim_start.PNG "Jmavsim Successful")


### Terminal 2: Ground System
1. 
```
$~/git/airliner/build/bebop2/sitl$ make start-commander
```
2. Open a web browser within Virtual Box and go to [http://localhost:3000](http://localhost:3000 "localhost:3000") for the commander interface


### Terminal 3: Flight Shell
1. 
```
$~/git/airliner/build/bebop2/sitl$ cd target/exe
```
2. 
```
$~/git/airliner/build/bebop2/sitl/target/exe$ ./airliner
```
