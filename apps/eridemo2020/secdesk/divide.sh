#!/bin/bash

DIVIDER=/home/tezrol/work/capo/divider/program_divider.py

#likely this is more than we need

SYSINCLUDES=-I/usr/lib/gcc/x86_64-linux-gnu/9/../../../../include/c++/9,
SYSINCLUDES+=-I/usr/lib/gcc/x86_64-linux-gnu/9/../../../../include/x86_64-linux-gnu/c++/9,
SYSINCLUDES+=-I/usr/lib/gcc/x86_64-linux-gnu/9/../../../../include/c++/9/backward,
SYSINCLUDES+=-I/usr/local/include,
SYSINCLUDES+=-I/usr/local/lib/clang/10.0.1/include,
SYSINCLUDES+=-I/usr/include
          

python3 $DIVIDER -f ./topology_mod3.json -c ",-v,-x,c,$SYSINCLUDES,-I./refactored/facilio/include,-DINC_FACE_RECOGNITION"




