#!/bin/sh
set -e
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
AMQ_CPP_VERSION="3.9.5"
cd $SCRIPT_DIR/../gaps.ma.dependencies/deps/activemq-cpp
tar -xvf activemq-cpp-library-$AMQ_CPP_VERSION-src.tar.gz
cd activemq-cpp-library-$AMQ_CPP_VERSION
echo "$(pwd)"
./autogen.sh
mkdir -p build
cd build
./../configure --prefix $SCRIPT_DIR/../pinstall
make -j 8
make install
