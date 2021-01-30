COLOR=$1
CASE=$2

case $COLOR in
    orange)
	    case $CASE in
		case1)
		    COMPONENTS="MPU MPX ISRM RDR"
		    ;;
		case2)
		    COMPONENTS="MPU MPX"
		    ;;
		case3)
		    COMPONENTS="MPU MPX ISRM"
		    ;;
		*)
		    echo "Arg2 must be case1,case2,or case3"
		    exit 1
	    esac
	    ;;
    green)
	    case $CASE in
		case1)
		    COMPONENTS="EOIR External"
		    ;;
		case2)
		    COMPONENTS="ISRM EOIR RDR External"
		    ;;
		case3)
		    COMPONENTS="ISRMshadow EOIR RDR External"
		    ;;
		*)
		    echo "Arg2 must be case1,case2,or case3"
		    exit 1
	    esac
	    ;;
    *)
	    echo "Arg 1 must be green or orange"
	    exit 1
	    ;;
esac

# Prepare for the case
pushd eop1
tar -zxvf $CASE.tgz
tar -zxvf MA_$CASE.tgz
rm -rf lbuild
#scl enable devtoolset-8
cd scripts
bash -f install-ma.sh
cd ..
./build.sh -x -b -c $COLOR -d $CASE
popd

# Stop Everything
bash ./stop_demo.sh

# clean logs
rm -f /tmp/transcript*
rm -f /tmp/*gress*.out
rm -f /tmp/hal*out

# Start Everything
# HAL
./start_hal.sh $COLOR $CASE

# ActiveMQ
pushd eop1/scripts
bash -f activemq start
# XDCC
cd ..
./xdcc_ctl.sh -c $COLOR -d $CASE -r start
# Mission App
cd scripts
read -p "Press [ENTER] to start $COMPONENTS"
bash -f mission-application.closure start $COMPONENTS
popd
