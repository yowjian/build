#!/bin/bash
COLR=
CASE=

usage_exit() {
  [[ -n "$1" ]] && echo $1
  echo "Usage: $0 [ -h ] [ -c COLR] [ -d CASE ]"
  echo "-h          Help"
  echo "-c COLR     Enclave color (e.g, orange, green)"
  echo "-d CASE     case1, case2, or case3"
  exit 1
}

handle_opts() {
    local OPTIND
    while getopts "c:d:h" options; do
	case "${options}" in
	    c) COLR=${OPTARG}      ;;
	    d) CASE=${OPTARG}      ;;
	    h) usage_exit          ;;
	    :) usage_exit "Error: -${OPTARG} requires argument." ;;
	    *) usage_exit
	esac
    done
    shift "$((OPTIND-1))"
    
    if [[ "x$COLR" == "x" ]] || [[ "x$CASE" == "x" ]]; then
	usage_exit
    fi
    
    PWD=`pwd`
    PINSTALL="${PWD}/../$CASE/MA_v1.0_src/pinstall"
}
handle_opts "$@"

case $COLR in
    orange)
	case $CASE in
	    case1)
		COMPONENTS="MPU MPX ISRM RDR"
		;;
	    case2)
		COMPONENTS="MPU MPX"
		;;
	    case3)
		COMPONENTS="MPU MPX ISRM"
		;;
	    *)
		echo "Arg2 must be case1,case2,or case3"
		exit 1
	esac
	;;
    green)
	case $CASE in
	    case1)
		COMPONENTS="EOIR External"
		;;
	    case2)
		COMPONENTS="ISRM EOIR RDR External"
		;;
	    case3)
		COMPONENTS="ISRMshadow EOIR RDR External"
		;;
	    *)
		echo "Arg2 must be case1,case2,or case3"
		exit 1
	esac
	;;
    *)
	echo "Arg 1 must be green or orange"
	exit 1
	;;
esac

stop_demo() {
    bash ./stop_demo.sh -d $CASE
}

clean_logs() {
    rm -f /tmp/transcript*
    rm -f /tmp/*gress*.out
    rm -f /tmp/hal*out
}

start_demo() {
    # HAL
    ./start_hal.sh -c $COLR -d $CASE -e ../$CASE/deploy/hal_${CASE}_${COLR}.cfg

    # ActiveMQ
    pushd ../$CASE/MA_v1.0_src/scripts
    bash -f activemq start
    popd
    
    # XDCC
    pushd ..
    PINSTALL=$PINSTALL ./xdcc_ctl.sh -c $COLR -d $CASE -r start
    popd
    
    # Mission App
    pushd ../$CASE/MA_v1.0_src/scripts
    read -p "Press [ENTER] to start $COMPONENTS"
    PINSTALL=$PINSTALL bash -f mission-application.closure start $COMPONENTS
    popd
}

stop_demo
clean_logs
start_demo
