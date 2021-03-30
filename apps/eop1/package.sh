#!/bin/bash
rm -f $1.tgz
tar zcf $1.tgz $1/xdcc amqlib build.sh xdcc_ctl.sh $1/deploy/hal*.cfg transcriptview
