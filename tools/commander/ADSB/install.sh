#!/usr/bin/env bash

# Install dependencies for running the ADS-B receiver in Commander

# 1. driver
sudo apt-get install -y rtl-sdr librtlsdr-dev

# 2 .decoder
mkdir dump1090_MalcomRobb
cd dump1090_MalcomRobb
git clone https://github.com/MalcolmRobb/dump1090.git
cd dump1090
make

