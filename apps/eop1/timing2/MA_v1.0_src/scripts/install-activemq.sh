#!/bin/sh
set -e
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
ACTIVEMQ_VERSION="5.16.0"

cd $SCRIPT_DIR/../gaps.ma.dependencies/deps/activemq
tar -xvf apache-activemq-$ACTIVEMQ_VERSION-bin.tar.gz
mv apache-activemq-$ACTIVEMQ_VERSION activemq 
