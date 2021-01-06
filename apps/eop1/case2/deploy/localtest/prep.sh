#!/bin/bash
FL="rk"

echo "Preparing HAL configurations ..."
cp ../../xdcc/egress_xdcc/partitioned/multithreaded/xdconf.ini ./egress_xdconf.ini
cp ../../xdcc/ingress_xdcc/partitioned/multithreaded/xdconf.ini ./ingress_xdconf.ini
python3 /opt/closure/scripts/merge_xdconf_ini.py -f "./egress_xdconf.ini ./ingress_xdconf.ini"
python3 /opt/closure/scripts/hal_autoconfig.py -o . -x ./xdconf.ini -d ./devices_jaga_bw.json -p localtest_hal

echo "Preparing HAL configurations ..."
ip link set dev ${FL}org down > /dev/null 2>&1 
ip link set dev ${FL}grn down > /dev/null 2>&1
ip link delete  ${FL}org      > /dev/null 2>&1
ip link delete  ${FL}grn      > /dev/null 2>&1

ip tuntap add mode tap ${FL}org
ip tuntap add mode tap ${FL}grn

ip link set dev ${FL}org up
ip link set dev ${FL}grn up

ip addr add 10.111.0.2/24 dev ${FL}org
ip addr add 10.111.0.1/24 dev ${FL}grn

echo "You can run HAL now"
echo "/opt/closure/bin/hal -f <cfg>"
