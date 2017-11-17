#!/bin/bash
sudo pkill -9 yamcs-server.sh
sudo pkill -9 core-bin
screen -S YAMCS -X quit
echo Cleaned YAMCS
screen -S AIRLINER -X quit
echo Cleaned AIRLINER