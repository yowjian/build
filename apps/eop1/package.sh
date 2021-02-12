#!/bin/bash
rm -f $1.tgz
tar zcf $1.tgz $1/xdcc amqlib /opt/closure/lib /opt/closure/include build.sh xdcc_ctl.sh $1/deploy/hal*.cfg
