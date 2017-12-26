#!/bin/bash

# Launch Modes
# 0 - Collect Test Cases
# 1 - Test and Report
# 2 - Development Code
# 4 - Production Code

#validation--------------------------
re='^[0-2]+$'
r0='^[0]+$'
r1='^[1]+$'

if ! [[ $1 =~ $re ]] ; then
   echo "ERROR: Enter launch mode correctly, (0 - Train, 1 - Test, 2 - Dev)."
   echo "HELP: ./Launch_Commander <MODE>" >&2; exit 1
fi
#--------------------------------------



# trap ctrl+c onto bomb function.
trap bomb SIGINT

# Executes when program is interrupted.
bomb(){
  tput setaf 1;
  cat art/commander_blood
  tput setaf 7;
  for each in "${arr[@]}"
  do
    echo "Killing process, ID: [$each]"
    kill -9 "$each"
  done
  sleep 1
  kill 0
}



# get number of wrokers from json file.
WORKERS=`jq '.number_of_workers' launch_config.json`
PORT=`jq '.daphne_port' launch_config.json`



tput setaf 2;
if [[ $1 =~ $r0 ]] ; then
    WORKERS=1
    echo "MODE : TRAIN"
    jq '.mode = 0'  launch_config.json > tmp.$$.json && mv tmp.$$.json launch_config.json
elif [[ $1 =~ $r1 ]] ; then
    echo "MODE : TEST"
    jq '.mode = 1'  launch_config.json > tmp.$$.json && mv tmp.$$.json launch_config.json
else
    echo "MODE : DEVELOPMENT"
    jq '.mode = 2'  launch_config.json > tmp.$$.json && mv tmp.$$.json launch_config.json
fi




# set font color, change directory and display welcome screen.
cd ../
cat art/commander

# WORKERS
for i in `seq 1 $WORKERS`
do
  python manage.py runworker  &
  arr+=($!)

done

# DAPHNE
daphne commander.asgi:channel_layer --port "$PORT" &
arr+=($!)

wait