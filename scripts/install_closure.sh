#!/bin/bash
INSTALLDIR=/opt/closure
GAPSSRC=~/gaps/build/src
OPTDBG=/opt/closure/devel/10.0.1dbg/bin/opt

echo "Installing to $INSTALLDIR"

for d in bin bin/zc include lib schemas scripts etc
do
    sudo mkdir -p $INSTALLDIR/$d
done

# bin
sudo cp $GAPSSRC/capo/compliance/verifier $INSTALLDIR/bin \
&& sudo cp $GAPSSRC/mules/xdcc_gen/xdcc_gen $INSTALLDIR/bin \
&& sudo cp $GAPSSRC/hal/daemon/hal $INSTALLDIR/bin \
&& sudo cp $GAPSSRC/hal/zc/zc $INSTALLDIR/bin/zc \
&& sudo cp $OPTDBG $INSTALLDIR/bin/opt-debug 

#include
sudo cp $GAPSSRC/hal/api/xdcomms.h $INSTALLDIR/include \
&& sudo cp $GAPSSRC/hal/log/log.h $INSTALLDIR/include

#lib
sudo cp $GAPSSRC/capo/pdg/build/libpdg.so $INSTALLDIR/lib \
&& sudo cp $GAPSSRC/capo/gedl/build/libgedl.so $INSTALLDIR/lib \
&& sudo cp $GAPSSRC/hal/api/libxdcomms.so $INSTALLDIR/lib

#schemas
sudo cp $GAPSSRC/mules/cle-spec/schema/cle-schema.json $INSTALLDIR/schemas \
&& sudo cp $GAPSSRC/capo/gedl/schema/gedl-schema.json $INSTALLDIR/schemas

#heuristics
sudo cp -r $GAPSSRC/capo/gedl/heuristics $INSTALLDIR/

#scripts
sudo cp $GAPSSRC/hal/autogen/*.py $INSTALLDIR/scripts \
&& sudo cp $GAPSSRC/hal/confgen/*.py $INSTALLDIR/scripts \
&& sudo cp $GAPSSRC/capo/divider/*.py $INSTALLDIR/scripts \
&& sudo cp $GAPSSRC/capo/gedl/*.py $INSTALLDIR/scripts \
&& sudo cp $GAPSSRC/capo/partitioner/src/*.py $INSTALLDIR/scripts \
&& sudo cp $GAPSSRC/capo/partitioner/src/cutzoom/*.py $INSTALLDIR/scripts \
&& sudo cp $GAPSSRC/mules/cle-preprocessor/src/join_clemaps.py $INSTALLDIR/scripts \
&& sudo cp $GAPSSRC/mules/cle-preprocessor/src/qd_cle_preprocessor.py $INSTALLDIR/scripts \
&& sudo chmod +x $INSTALLDIR/scripts/*

#etc
sudo cp $GAPSSRC/hal/confgen/device_defs/* $INSTALLDIR/etc

