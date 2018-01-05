#!/usr/bin/env bash

cd dump1090_MalcomRobb
cd dump1090
echo "JSON served at http://127.0.0.1:8080/dump1090/data.json"
echo "Raw data is served at http://127.0.0.1:30002"
./dump1090 --quiet --no-fix --gain -10 --net --net-ro-size 500 --net-ro-rate 5
