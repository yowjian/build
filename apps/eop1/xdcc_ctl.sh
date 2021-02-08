#!/bin/bash

COLOR="NONE"
CASE="NONE"
ACTION="restart"

usage_exit() {
    [[ -n "$1" ]] && echo $1
    echo "Usage: $0 [ -h ]"
    echo "          [ -c COLOR] [ -d CASE ] [-r start/stop/restart ]"
    echo "-h        Help"
    echo "-c        orange or greeen"
    echo "-d        directory to run, caseX"
    echo "-r        start, stop, or restart XDCCs and activemq subscriber"
    exit 1
}

handle_opts() {
    local OPTIND
    while getopts "c:d:r:h" options; do
	case "${options}" in
	    c) COLOR=${OPTARG}  ;;
	    d) CASE=${OPTARG}    ;;
	    r) ACTION=${OPTARG} ;;
	    h) usage_exit       ;;
	    :) usage_exit       "Error: -${OPTARG} requires an argument." ;;
	    *) usage_exit       ;;
	esac
    done
    shift "$((OPTIND-1))"

    case $ACTION in
	stop) 
	    stop 
	    exit 1
	    ;;
    esac

    case $COLOR in
	orange)  ;;
	green)   ;;
	*)        usage_exit "Unsupported enclave color $COLOR" ;;
    esac
    if [[ $CASE == "NONE" ]]; then
	usage_exit "-d not specified"
    fi
    if [[ ! -e $CASE ]]; then
	usage_exit "Directory does not exist: $CASE"
    exit 1
    fi
    case $ACTION in
	start) start ;;
	restart) restart ;;
	*) usage_exit "invalid action $ACTION" ;;
    esac
}

start() {
    if [[ "x"$PINSTALL == "x" ]]; then
	echo "PINSTALL not set."
	exit 1
    fi
    if [[ "x"`pgrep egress_xdcc` != "x" ]] || [[ "x"`pgrep ingress_xdcc` != "x" ]]; then
	echo "XDCC appears to be running"
	exit 1
    fi
    PWD=`pwd`
    export LD_LIBRARY_PATH=/opt/closure/lib:${PINSTALL}/lib:${PWD}/amqlib:${PWD}/${CASE}/xdcc/xdcc_echo:${PINSTALL}/../gaps.ma.dependencies/deps/opencv/ffmpeg/install/lib/
    echo $LD_LIBRARY_PATH
    rm -f /tmp/*xdcc*.out
    rm -f /tmp/*.${COLOR}
    pushd ${PINSTALL}/../gaps.ma.dependencies/deps/activemq/activemq/bin
    ./activemq consumer --messageCount 1000000 --destination topic://* &> /tmp/transcript.${COLOR} &
    popd
    pushd ${CASE}/xdcc/egress_xdcc/partitioned/multithreaded/${COLOR}
    ./egress_xdcc &> /tmp/egress_xdcc.out &
    popd
    pushd ${CASE}/xdcc/ingress_xdcc/partitioned/multithreaded/${COLOR}
    ./ingress_xdcc &> /tmp/ingress_xdcc.out &
    popd
}

stop() {
    pkill -f "egress_xdcc"
    pkill -f "ingress_xdcc"
    pkill -f "activemq.jar consumer"
}

restart() {
    stop
    start
}
handle_opts "$@"
