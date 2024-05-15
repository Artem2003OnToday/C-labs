#!/usr/bin/env bash

gcc main.c -o run.out
./run.out --filepath=ac_dc_shoot_to_thrill.mp3 --show

./run.out --filepath=ac_dc_shoot_to_thrill.mp3 --get=TIT2

rm run.out
echo ---------------------------------------------

id3v2 -l ac_dc_shoot_to_thrill.mp3
