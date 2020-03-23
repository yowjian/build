#!/bin/bash

LLVM_URL="https://github.com/gaps-closure/capo/releases/download/T0.1/LLVM-10.0.0svn-Linux.deb"
EMU_ARM_URL="https://github.com/gaps-closure/emu/releases/download/v1.0/ubuntu-arm64-goldenimage.tgz"

RELEASES=($LLVM_URL $EMU_ARM_URL)
BIN=bin

usage_exit() {
  [[ -n "$1" ]] && echo $1
  echo "Usage: $0 [ -bcdhs ] "
  echo "-b LLVM_BRANCH  llvm branch to be built"
  echo "-c              Clean up"
  echo "-d              Dry run"
  echo "-n              Exclude LLVM in the build"
  echo "-s              Populate component source and build"
  echo "-h              Help"
  exit 1
}

handle_opts() {
  local OPTIND
  while getopts "b:cdhns" options; do
    case "${options}" in
      b) LLVM_BRANCH=${OPTARG}  ;;
      c) CLEAN=1                ;;
      d) DRY_RUN="--dry-run"    ;;
      n) EXCLUDE_LLVM=1         ;;
      s) SOURCE=1               ;;
      h) usage_exit             ;;
      :) usage_exit "Error: -${OPTARG} requires an argument." ;;
    esac
  done
  
  shift $((OPTIND -1))
  components=($@)
}

down_releases () {
    mkdir -p $BIN
    for m in "${RELEASES[@]}"
    do
        wget $m
        #get_latest_release 
        filename="${m##*/}"
        mv $filename $BIN
    done
}

# Usage
# $ get_latest_release <repo> <
# not working yet
get_latest_release() {
    curl -s https://api.github.com/repos/gaps-closure/$1/releases |
        jq -r ".assets[] | select(.name | test(\"$2\")) | .browser_download_url"
}

handle_opts "$@"

#if [[ $BINARY ]]; then
#    down_releases
#fi

if [ "${#components[@]}" -eq 0 ]; then   # build all
    if [ ! -d src ]; then
        echo "directory does not exist: src"
        exit
    fi

    cd src
    for d in */ ; do
        d=${d::-1}
        components+=("$d")
    done
    cd ..
fi

echo ${components[@]}

for c in "${components[@]}"
do
    case $c in
        llvm)
            if [[ $EXCLUDE_LLVM ]]; then
                echo "-n (exclude llvm) and the llvm component should not be both specified."
                exit
            fi
            
            if [[ ! $LLVM_BRANCH ]]; then
                LLVM_BRANCH="qualatypes"
            fi
            echo "Build llvm $LLVM_BRANCH branch................"
            pushd src/capo
            ./build.sh $DRY_RUN -b $LLVM_BRANCH
            popd
            ;;
	capo)
            if [[ ! $EXCLUDE_LLVM ]]; then
		BUILD_LLVM=-l
	    fi

            echo "Building $c ........................."
            pushd src/capo
            ./build.sh $DRY_RUN $BUILD_LLVM
            popd
            ;;       
        cvi | mules | mbig)
            echo "Building $c ........................."
            pushd src/$c
            ./build.sh $DRY_RUN
            popd
            ;;       
    esac
done

