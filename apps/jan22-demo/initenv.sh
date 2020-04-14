#!/bin/bash
#helper script to initialize the enviroment for vscode targets
#(source to include env-aarch if required in targets.make)

#get the number of arm64 targets in targets.make
arm_target_cnt=$(grep -e ORANGE_TARGET -e PURPLE_TARGET targets.make | head -n 2 | grep arm64 | wc -l)

if [ "$arm_target_cnt" != "0" ]
then
    echo source arm enviroment
    cdir=`pwd`
    cd ../../src/mbig/crosscompile/

    source env-aarch64
    cd "$cdir"
    pwd
    export INCLUDE_AARCH64=true
fi
