#!/bin/sh
# Setup a work space called `flight_test` with two windows
# first window has 2 panes.

session="flight_test"

# set up tmux
tmux start-server

# create a new tmux session
tmux new-session -d -s $session 

# Select pane 1, set dir, get root
tmux selectp -t 1 
tmux send-keys "cd pe_app_test/posix" C-m
tmux send-keys "sudo su" C-m

# Split pane 1 horizontal by 50%
tmux splitw -v -p 50
tmux send-keys "cd pe_app_test/exe" C-m
tmux send-keys "sudo su" C-m

# create a new window called scratch
tmux new-window -t $session:1 -n scratch
tmux send-keys "sudo su" C-m

# return to main vim window
tmux select-window -t $session:0

# Finished setup, attach to the tmux session!
tmux attach-session -t $session



