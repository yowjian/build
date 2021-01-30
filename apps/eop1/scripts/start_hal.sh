case $1 in
    orange)
	;;
    green)
	;;
    *)
	echo "Only orange or green supported"
	exit 1
esac

case $2 in
    case1)
	    ;;
    case2)
	    ;;
    case3) 
	    ;;
    *)
	    echo "Only case1, case2, case3 supported"
	    exit 1
esac

pushd ~/hal
daemon/hal /home/closure/hal_configs/$2/deploy/$2_ilip_$1.cfg -l0 &> /tmp/hal_$1.out &
popd
