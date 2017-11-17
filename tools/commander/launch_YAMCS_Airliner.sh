#!/bin/bash



cd /opt/yamcs/
screen -S YAMCS -d -m
screen -S YAMCS -X exec bin/yamcs-server.sh
#LAUNCHING YAMCS
echo Launched YAMCS



cd /home/vagrant/git/airliner/build/softsim/default/target/exe/
screen -S AIRLINER -d -m
screen -S AIRLINER -X exec ./core-bin
#LAUNCHING AIRLINER
echo Launched AIRLINER




