#!/bin/sh
echo -e "212 LOAD\nH@ 256 /MOD 2 PC! 2 PC!\n$(cat -)\nH@ 256 /MOD 2 PC! 2 PC! " | ./stage
