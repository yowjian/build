#!/bin/bash
CASE=

usage_exit() {
  [[ -n "$1" ]] && echo $1
  echo "Usage: $0 [ -h ] [ -d CASE ]"
  echo "-h          Help"
  echo "-d CASE     case1, case2, or case3"
  exit 1
}

handle_opts() {
    local OPTIND
    while getopts "d:h" options; do
	case "${options}" in
	    d) CASE=${OPTARG}      ;;
	    h) usage_exit          ;;
	    :) usage_exit "Error: -${OPTARG} requires argument." ;;
	    *) usage_exit
	esac
    done
    shift "$((OPTIND-1))"
    
    if [[ "x$CASE" == "x" ]]; then
	usage_exit
    fi
    PWD=`pwd`
    PINSTALL="${PWD}/../$CASE/MA_v1.0_src/pinstall"
}
handle_opts "$@"

pushd ../$CASE/MA_v1.0_src/scripts
PINSTALL=$PINSTALL bash -f mission-application.closure stop
pkill -f MPU 
pkill -f MPX
pkill -f ISRM 
pkill -f ISRMshadow 
pkill -f EOIR 
pkill -f RDR 
pkill -f External
pkill -f ImageDetector
pkill -f ImageReceiver
pkill -f "helper.py"
pkill -f "python3 pith.py"
pkill -f tail
popd

pushd ..
./xdcc_ctl.sh -r stop
pkill -f egress_xdcc
pkill -f ingress_xdcc
popd


pushd ../$CASE/MA_v1.0_src/scripts
bash -f activemq stop
popd

pkill -f hal
pkill -f zc

rm -f /tmp/sock_*


