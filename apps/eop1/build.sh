#!/bin/bash

CLEAN="no"
BUILD="no"
COLOR="NONE"
DIR="NONE"

usage_exit() {
    [[ -n "$1" ]] && echo $1
    echo "Usage: $0 [ -xbh ]"
    echo "          [ -c COLOR] [ -d DIR ]"
    echo "-h        Help"
    echo "-x        Clean"
    echo "-b        Build"
    exit 1
}

handle_opts() {
    local OPTIND
    while getopts "c:d:xbh" options; do
	case "${options}" in
	    c) COLOR=${OPTARG}  ;;
	    d) DIR=${OPTARG}   ;;
	    x) CLEAN="yes"      ;;
	    b) BUILD="yes"      ;;
	    h) usage_exit       ;;
	    :) usage_exit       "Error: -${OPTARG} requires an argument." ;;
	    *) usage_exit       ;;
	esac
    done
    shift "$((OPTIND-1))"

    if [[ $CLEAN == "no" ]] && [[ $BUILD == "no" ]]; then
	usage_exit
    fi
    case $COLOR in
	orange)  ;;
	green)   ;;
	*)        usage_exit "Unsupported enclave color $COLOR" ;;
    esac
    if [[ $DIR == "NONE" ]]; then
	usage_exit "-d not specified"
    fi
    if [[ ! -e $DIR ]]; then
	usage_exit "Directory does not exist: $DIR"
    exit 1
    fi
}
	

clean () {
    echo "*** Begin Clean ($COLOR) ***"
    pushd amqlib
    make clean; make libclean
    popd
    pushd ${DIR}/xdcc/xdcc_echo
    make clean
    popd
    pushd ${DIR}/xdcc/egress_xdcc/partitioned/multithreaded/${COLOR}
    source ../../../.vscode/closure_env.sh && make -f ../../../.vscode/Makefile.xdcc clean
    popd
    pushd ${DIR}/xdcc/ingress_xdcc/partitioned/multithreaded/${COLOR}
    source ../../../.vscode/closure_env.sh && make -f ../../../.vscode/Makefile.xdcc clean
    popd
    echo "*** Done Clean ($COLOR) ***"
}

build () {
    if [[ x${PINSTALL} == x ]]; then
	echo "Error: PINSTALL environment variable not set"
	exit
    fi
    echo "*** Begin Build ($COLOR) ***"
    echo "Using PINSTALL=${PINSTALL}"
    pushd amqlib
    make
    popd
    pushd ${DIR}/xdcc/egress_xdcc
    source .vscode/closure_env.sh; cd ../xdcc_echo && cp ../egress_xdcc/.vscode/Makefile.xdcc_echo ./Makefile && make && cd ../egress_xdcc; make -C partitioned/multithreaded/${COLOR} -f ../../../.vscode/Makefile.xdcc
    popd
    pushd ${DIR}/xdcc/ingress_xdcc
    source .vscode/closure_env.sh; cd ../xdcc_echo && cp ../ingress_xdcc/.vscode/Makefile.xdcc_echo ./Makefile && make && cd ../ingress_xdcc; make -C partitioned/multithreaded/${COLOR} -f ../../../.vscode/Makefile.xdcc
    popd
    echo "*** Done Build ($COLOR) ***"
}


handle_opts "$@"

if [[ "$CLEAN" == "yes" ]]; then
    clean
fi
if [[ "$BUILD" == "yes" ]]; then
    build
fi

