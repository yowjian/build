#!/bin/sh

set -e
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
cd ..
mkdir -p $SCRIPT_DIR/../lbuild
cd $SCRIPT_DIR/../lbuild
cmake ..
make -j 8
echo "Installation Complete"