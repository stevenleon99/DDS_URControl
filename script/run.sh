#!/bin/bash

BASE_DIR='../build/bin'
cd $BASE_DIR

#run publisher
./URController_publisher > /dev/null &2>1 &

#run subscriber
./URController_subscriber > /dev/null &2>1 &

#open display window
./displaywindow > /dev/null &2>1 &