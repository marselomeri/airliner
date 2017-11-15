#!/bin/bash

CH_WORKERS=15


sudo pkill -9 redis
screen -S REDIS -X quit

sudo pkill -9 python

for i in `seq 1 $CH_WORKERS`
do  
	NAME="WORKER"$i
	echo $NAME
	screen -S $NAME -X quit
done

sudo pkill -9 daphne
screen -S DAPHNE -X quit
