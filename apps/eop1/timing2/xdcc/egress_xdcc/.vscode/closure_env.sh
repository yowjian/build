#!/bin/bash
export PROG=$(eval basename `pwd`)
export PYTHON="/usr/bin/python3 -u"

CLOSURE_TOOLS=/opt/closure
export CLOSURE_BINS=${CLOSURE_TOOLS}/bin
export CLOSURE_INCLUDES=${CLOSURE_TOOLS}/include
export CLOSURE_LIBS=${CLOSURE_TOOLS}/lib
export CLOSURE_SCRIPTS=${CLOSURE_TOOLS}/scripts
export CLOSURE_SCHEMAS=${CLOSURE_TOOLS}/schemas

export OPT_DBG=${CLOSURE_BINS}/opt-debug
export OPT_NODBG=/usr/local/bin/opt
export VERIFIER=${CLOSURE_BINS}/verifier

export LIBPDG=${CLOSURE_LIBS}/libpdg.so
export LIBGEDL=${CLOSURE_LIBS}/libgedl.so

export PREPROCESSOR=${CLOSURE_SCRIPTS}/qd_cle_preprocessor.py
export JOINCLEMAPS=${CLOSURE_SCRIPTS}/join_clemaps.py
export PARTITIONER=${CLOSURE_SCRIPTS}/partitioner.py
export TAGPROC=${CLOSURE_SCRIPTS}/tag_processor.py
export CUTZOOM=${CLOSURE_SCRIPTS}/cutzoom.py
export DIV=${CLOSURE_SCRIPTS}/program_divider.py
export IDLGENERATOR=${CLOSURE_SCRIPTS}/IDLGenerator.py
export RPCGENERATOR=${CLOSURE_SCRIPTS}/RPCGenerator_rk.py
export AUTOGEN=${CLOSURE_SCRIPTS}/autogen.py
export HALGEN=${CLOSURE_SCRIPTS}/hal_autoconfig.py

LLVM_RELEASE=/usr/local
export CLANG=${LLVM_RELEASE}/bin/clang-10
export CLANG_FLAGS="-S -g -emit-llvm"
export LLVMLINK=${LLVM_RELEASE}/bin/llvm-link
export LLVMDIS=${LLVM_RELEASE}/bin/llvm-dis

export LLVM_DIR=${LLVM_RELEASE}

export IPCMODE=multithreaded
export ENCLAVES="orange green"
export EXT=c

if [[ x$CASE == x ]]; then
    export CASE=`cd ../../ && basename \`pwd\``
fi

export MUXBASE=0
if [[ $HWMODE == "ilip" ]] || [[ $HWMODE == "ILIP" ]]; then
    if [[ "$CASE" == "case1" ]]; then
       export MUXBASE=`echo '2^30' | bc`
    elif [[ "$CASE" == "case2" ]]; then
       export MUXBASE=`echo '2^31' | bc`
    elif [[ "$CASE" == "case3" ]]; then
       export MUXBASE=`echo '2^30 + 2^31' | bc`
    elif [[ "$CASE" == "delighter" ]]; then
       export MUXBASE=`echo '2^30 + 2^31' | bc`
    else
        echo "Case: $CASE not supported for ILIP, default to base=0"
        export MUXBASE=0
    fi
fi
echo "HW=$HWMODE BASE=$MUXBASE CASE=$CASE"
