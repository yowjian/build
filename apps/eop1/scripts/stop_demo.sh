#!/bin/bash
pushd eop1/scripts
bash -f mission-application.closure stop
pkill -f MPU 
pkill -f MPX
pkill -f ISRM 
pkill -f ISRMshadow 
pkill -f EOIR 
pkill -f RDR 
pkill -f External

cd ..
./xdcc_ctl.sh -r stop
pkill -f egress_xdcc
pkill -f ingress_xdcc

cd scripts
bash -f activemq stop

pkill -f hal
pkill -f zc

rm -f /tmp/sock_*

popd
