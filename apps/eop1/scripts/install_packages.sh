#!/bin/bash

sudo apt install                                        \
    libapr1    						\
    libapr1-dev						\
    nasm						\
    yasm						\
    cmake						\
    autoconf						\
    automake						\
    libtool						\
    libssl-dev						\
    gcc							\
    make						\
    git							\
    libz3-dev						\
    libzmq3-dev						\
    libconfig-dev					\
    python3-pip						\
    wget						\
    libboost-all-dev 					\
    bc 							\
    openjdk-14-jre-headless

sudo -H pip3 install decorator==4.4.1 jsonschema==3.2.0 lark-parser==0.7.8 libconf==2.0.1 vstask==1.1.5
