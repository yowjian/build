#!/bin/bash
export PROG=deploy
export PYTHON=/usr/bin/python3

CLOSURE_TOOLS=/opt/closure
source /opt/closure/etc/closureenv
export CLOSURE_BINS=${CLOSURE_TOOLS}/bin
export CLOSURE_INCLUDES=${CLOSURE_TOOLS}/include
export CLOSURE_LIBS=${CLOSURE_TOOLS}/lib
export CLOSURE_PYTHON=${CLOSURE_TOOLS}/python
export CLOSURE_SCHEMAS=${CLOSURE_TOOLS}/schemas
export CLOSURE_DEVICES=${CLOSURE_TOOLS}/etc
export CLOSURE_EMU=${CLOSURE_TOOLS}/emu

export OPT=/usr/local/bin/opt
export VERIFIER=${CLOSURE_BINS}/verifier

export LIBPDG=${CLOSURE_LIBS}/libpdg.so
export LIBGEDL=${CLOSURE_LIBS}/libgedl.so

export PREPROCESSOR=preprocessor
export JOINCLEMAPS=join_clemaps
export PARTITIONER=partitioner
# only used in cutzoom
export DIV=divider
export IDLGENERATOR=idl_generator
export RPCGENERATOR=rpc_generator
export AUTOGEN=hal_autogen
export HALGEN=hal_autoconfig.py
export XDCONFMERGER=merge_xdconf_ini.py
export FLOW_SOLVER=FlowSolver.py
export XDMF_VIEW=xdmfview.py

export CLANG=clang
export CLANG_FLAGS="-S -g -emit-llvm"
export LLVMLINK=llvm-link
export LLVMDIS=llvm-dis

export IPCMODE=multithreaded
export ENCLAVES="orange green"
export EXT=c
export USER=`whoami`
export CASE=$(eval basename `pwd`)
export HWMODE=emu
export PINSTALL=/opt/eop1/pinstall
