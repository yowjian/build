#!/bin/bash
COLR=
CASE=
CFG=

usage_exit() {
  [[ -n "$1" ]] && echo $1
  echo "Usage: $0 [ -h ] [ -c COLR] [ -d CASE ] [ -e CFG ]"
  echo "-h          Help"
  echo "-c COLR     Enclave color (e.g, orange, green)"
  echo "-d CASE     case1, case2, or case3"
  echo "-e CFG      HAL config file"
  exit 1
}

handle_opts() {
    local OPTIND
    while getopts "c:d:e:h" options; do
	case "${options}" in
	    c) COLR=${OPTARG}      ;;
	    d) CASE=${OPTARG}      ;;
	    e) CFG=${OPTARG}       ;;
	    h) usage_exit          ;;
	    :) usage_exit "Error: -${OPTARG} requires argument." ;;
	    *) usage_exit
	esac
    done
    shift "$((OPTIND-1))"

    if [[ "x$COLR" == "x" ]] || [[ "x$CASE" == "x" ]] || [[ "x$CFG" == "x" ]]; then
	usage_exit
    fi
}

handle_opts "$@"

PWD=`pwd`
case $CFG in
    /*) ;;
    *)  CFG="$PWD/$CFG"
esac

# only matches MIND configs
IP=`ifconfig eth0 | grep "inet " | awk {'print $2'}`
sed -i 's/addr_in = "192.*/addr_in = "'${IP}'";/' $CFG

pushd /opt/closure/bin
./hal $CFG -l0 &> /tmp/hal_$COLR.out &
popd
