#!/bin/bash
EMU=
usage_exit() {
    [[ -n "$1" ]] && echo $1
    echo "Usage: $0 [ -e ] [ -p PATH ]"
    echo "-e        if using emulator (make -j2)"
    echo "-p PATH   path to mission app directory"
    exit 1
}

handle_opts() {
  local OPTIND
  while getopts "p:he" options; do
      case "${options}" in
	  e) EMU="YES"         ;;
	  p) MAPATH=${OPTARG}; ;;
	  h) usage_exit        ;;
	  :) usage_exit "Error: -${OPTARG} requires argument." ;;
	  *) usage_exit
      esac
  done
  shift "$((OPTIND-1))"

  if [[ "x$MAPATH" == "x" ]]; then
      usage_exit "Error: Mission App Path must be set, use -p"
      exit 1
  fi
}

handle_opts "$@"

pushd $MAPATH 
tar -zxvf gaps.ma.dependencies.tgz 
cd scripts 
bash -f install-activemq.sh 
bash -f install-activemq-cpp.sh 
if [[ "x$EMU" == "x" ]]; then
    sed -i 's/NUM_JOBS=[1-9]/NUM_JOBS=8/g' install-opencv.sh
else
    sed -i 's/NUM_JOBS=[1-9]/NUM_JOBS=2/g' install-opencv.sh
fi
bash -f install-opencv.sh 
popd
