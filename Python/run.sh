#!/bin/bash

#start as root
if [ "$EUID" -ne 0 ]
  then echo "Please run as root"
  exit
fi

#run test.py
sudo /home/tmc/miniconda3/envs/pico/bin/python test.py