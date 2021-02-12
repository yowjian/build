#!/bin/sh
rm -f MA_1.0.tgz
tar zcf MA_1.0.tgz include scripts ImageDetector ImageReceiver CMakeLists.txt --dereference #gaps.ma.dependencies 
