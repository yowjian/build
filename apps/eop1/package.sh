#!/bin/bash
rm -f $1.tgz
tar zcf $1.tgz $1/xdcc amqlib /opt/closure/lib /opt/closure/include
