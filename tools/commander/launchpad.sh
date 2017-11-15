#!/bin/bash

CH_WORKERS=15

screen -dmS REDIS 
screen -S REDIS -X stuff "redis-server \n"

for i in `seq 1 $CH_WORKERS`
do  
	NAME="WORKER"$i
	echo $NAME
	screen -dmS $NAME 
	screen -S $NAME -X stuff "python manage.py runworker \n"
done

screen -dmS DAPHNE 
screen -S DAPHNE -X stuff "daphne commander.asgi:channel_layer --port 8000 \n\n\n"


