#!/bin/bash


WORKERS=`jq '.number_of_workers' ../launch_config.json`

cd ../

for i in `seq 1 $WORKERS`
do
  python manage.py runworker -v 2 &
  arr+=($!)

done
daphne commander.asgi:channel_layer --port 8000 &
arr+=($!)
