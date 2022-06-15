#!/bin/bash
export PROG=$(eval basename `pwd`)
export PYTHON="/usr/bin/python3 -u"

CLOSURE_TOOLS=/opt/closure
source /opt/closure/etc/closureenv
export CLOSURE_BINS=${CLOSURE_TOOLS}/bin
export CLOSURE_INCLUDES=${CLOSURE_TOOLS}/include
export CLOSURE_LIBS=${CLOSURE_TOOLS}/lib
export CLOSURE_PYTHON=${CLOSURE_TOOLS}/python
export CLOSURE_SCHEMAS=${CLOSURE_TOOLS}/schemas
export CLOSURE_DEVICES=${CLOSURE_TOOLS}/etc

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

export CLANG=clang
export CLANG_FLAGS="-S -g -emit-llvm"
export LLVMLINK=llvm-link
export LLVMDIS=llvm-dis

export HWMODE=emu
export IPCMODE=multithreaded
export IPCMODEGEN=Multithreaded
#export IPCMODEGEN=Singlethreaded
export ENCLAVES="orange purple"
export EXT=c
export ECT=ect
export LD_LIBRARY_PATH=ect/z3-4.8.8/lib:$LD_LIBRARY_PATH
