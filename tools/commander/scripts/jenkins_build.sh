
#!/bin/bash
#export YAMCS_WORKSPACE=~/git/airliner/config/shared/commander_workspace/
#sudo pip install service_identity

#cd /opt/yamcs
#bin/yamcs-server.sh &
#cd ~/git/airliner/build/softsim/default/target/exe/
#./core-bin &
#cd ~/git/airliner



#cd tools/commander/scripts/
./Launch_YAMCS_airliner.sh &
sleep 60
./Launch_Commander.sh 2 &

sleep 5
cd ../
cd groundcontrol/
cd test-reports
touch *.xml
cd ../
#npm install
#./node_modules/.bin/mocha test --reporter mocha-junit-reporter --reporter-options mochaFile=./test-reports/client-results.xml
py.test --junitxml ./test-reports/server-results.xml ./test/unittests.py
#py.test --junitxml ./test-reports/gui-results.xml ./test/uitests.py
echo '###################INTENTIONAL WATING####################'
./killswitch.sh
sleep 20
cd ../
cd scripts/
./kill_YAMCS_airliner.sh


