#!/bin/bash
if [ "$#" -ne 2 ]; then
    echo "Usage: build.sh [caseX] [color]"
    exit
fi	
if [[ ! -e $1 ]]; then
    echo "Directory does not exist: $1"
    exit
fi
	
if [[ x${PINSTALL} == x ]]; then
    echo "Error: PINSTALL environment variable not set"
    exit
fi
echo "Using PINSTALL=${PINSTALL}"

COLOR=$2
if [[ $COLOR != "orange" ]] && [[ $COLOR != "green" ]]; then
    echo "Error: Only orange and green expected in this script"
    exit
fi
 
# clean 
pushd $1/xdcc/xdcc_echo
make clean
popd
pushd $1/xdcc/egress_xdcc/partitioned/multithreaded/${COLOR}
source ../../../.vscode/closure_env.sh && make -f ../../../.vscode/Makefile.xdcc clean
popd
pushd $1/xdcc/ingress_xdcc/partitioned/multithreaded/${COLOR}
source ../../../.vscode/closure_env.sh && make -f ../../../.vscode/Makefile.xdcc clean
popd

#build
pushd $1/xdcc/egress_xdcc
source .vscode/closure_env.sh; cd ../xdcc_echo && cp ../egress_xdcc/.vscode/Makefile.xdcc_echo ./Makefile && make && cd ../egress_xdcc; make -C partitioned/multithreaded/orange -f ../../../.vscode/Makefile.xdcc; make -C partitioned/multithreaded/green -f ../../../.vscode/Makefile.xdcc
popd
pushd $1/xdcc/ingress_xdcc
source .vscode/closure_env.sh; cd ../xdcc_echo && cp ../ingress_xdcc/.vscode/Makefile.xdcc_echo ./Makefile && make && cd ../ingress_xdcc; make -C partitioned/multithreaded/orange -f ../../../.vscode/Makefile.xdcc; make -C partitioned/multithreaded/green -f ../../../.vscode/Makefile.xdcc
popd

