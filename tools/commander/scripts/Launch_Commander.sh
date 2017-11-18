#!/bin/bash
trap killgroup SIGINT

WORKERS=`jq '.number_of_workers' ../launch_config.json`
killgroup(){
  echo killing...
  kill 0
}
cd ../

for i in `seq 1 $WORKERS`
do
  python manage.py runworker -v 2 &
  arr+=($!)

done
daphne commander.asgi:channel_layer --port 8000 &
arr+=($!)
wait
