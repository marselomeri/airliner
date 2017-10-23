#!/bin/bash
# Launch arte with inspection of log files in real time with tail
python3 arte.py test_config.json &
gnome-terminal -x tail -f test_script1.txt &
gnome-terminal -x tail -f test_script2.txt &
