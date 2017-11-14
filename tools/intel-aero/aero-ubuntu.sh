#!/bin/bash

# This script installs the components necessary to build Airliner on the Aero

cd "$(dirname "$0")"
cd ..
WORKSHOP_BASEDIR=$PWD

# Install the prereqs
export DEBIAN_FRONTEND=noninteractive
sudo apt-get -y update
sudo apt-get -y install g++ g++-multilib gcc-multilib git gitk cinnamon libc-bin libc-dev-bin libc6-dev rpm alien doxygen vagrant libc6-dbg libc6-dbg:i386

# Setup locales.  The most current Ubuntu 16.04 version has a bug causing the terminal
# to not open.  These steps will correct it.
sudo dpkg-reconfigure -f noninteractive tzdata
sudo locale-gen "en_US.UTF-8"
sudo dpkg-reconfigure -f noninteractive locales
sudo localectl set-locale LANG="en_US.UTF-8"

# Make the desktop look good - optional
#sudo apt-get install -y xubuntu-desktop
#sudo apt-get purge -y ubuntu-desktop unity-*
#sudo apt-get -y autoremove

# Install additional development tools
sudo apt-get install -y libc6-dbg:i386 valgrind gcovr lcov xsltproc graphviz  

# Install some nice to have stuff
sudo apt-get install -y gedit htop gkrellm 

# Install Airliner build dependencies
sudo apt-get install -y cmake

# Install TFTP server
sudo apt-get install -y xinetd tftpd tftp
sudo cp /vagrant/etc/xinetd.d/tftp /etc/xinetd.d
sudo mkdir /tftpboot
sudo chmod -R 777 /tftpboot
sudo chown -R nobody /tftpboot
sudo service xinetd restart

# Install protobuf compiler
sudo apt-get install -y protobuf-compiler
sudo apt-get install -y python-protobuf

# Install sshpass for jenkins access
sudo apt-get install -y sshpass
