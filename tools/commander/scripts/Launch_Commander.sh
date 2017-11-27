#!/bin/bash

# trap ctrl+c onto bomb function.
trap bomb SIGINT

# get number of wrokers from json file.
WORKERS=`jq '.number_of_workers' launch_config.json`


# Executes when program is interrupted.
bomb(){
  tput setaf 1;
  cat art/commander_blood
  for each in "${arr[@]}"
  do
    echo "Killing process, ID: [$each]"
    kill -9 "$each"
  done
  sleep 2


  tput setaf 2;
  echo "--------------------------------END--------------------------------"
  tput setaf 7;
  kill 0

}

# set font color, change directory and display welcome screen.
tput setaf 2;
cd ../
echo "--------------------------------BEGIN--------------------------------"
cat art/commander
tput setaf 7;
# WORKERS
for i in `seq 1 $WORKERS`
do
  python manage.py runworker &
  arr+=($!)

done

# DAPHNE
daphne commander.asgi:channel_layer --port 8000 &
arr+=($!)
wait

