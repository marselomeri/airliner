#!/bin/bash

sudo service redis-server restart
tput setaf 2; echo "Redis server restarted."


sudo pkill -9 python
tput setaf 3; echo "[!Warning] All python processess are killed."

sudo pkill -9 daphne
tput setaf 2; echo "Daphne server killed."

tput setaf 7;



