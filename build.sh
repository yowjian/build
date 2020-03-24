#!/bin/bash

LLVM_URL="https://github.com/gaps-closure/capo/releases/download/T0.1/LLVM-10.0.0svn-Linux.deb"
EMU_ARM_URL="https://github.com/gaps-closure/emu/releases/download/v1.0/ubuntu-arm64-goldenimage.tgz"

RELEASES=($LLVM_URL $EMU_ARM_URL)
BIN=bin

usage_exit() {
  [[ -n "$1" ]] && echo $1
  echo "Usage: $0 [ -chl ] \\"
  echo "          [ -b BRANCH ]"
  echo "-b LLVM_BRANCH  Build LLVM from the BRANCH branch of the source"
  echo "-c              Clean up"
  echo "-l              Build LLVM from source"
  echo "-h              Help"
  exit 1
}

handle_opts() {
  local OPTIND
  while getopts "b:clh" options; do
    case "${options}" in
      b) LLVM_BRANCH=${OPTARG}  ;;
      c) CLEAN=1                ;;
      l) INCLUDE_LLVM=1         ;;
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

function contains() {
    local n=$#
    local value=${!n}
    for ((i=1;i < $#;i++)) {
        if [ "${!i}" == "${value}" ]; then
            echo "y"
            return 0
        fi
    }
    echo "n"
    return 1
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

if [[ $INCLUDE_LLVM ]]; then
    components=( "llvm" "${components[@]:0}" )
fi

components=($(echo "${components[@]}" | tr ' ' '\n' | sort -u | tr '\n' ' '))

echo Will build/install the following components: ${components[@]}


# first, install llvm, which may not be the first item after sorting
if [ $(contains "${components[@]}" "llvm") == "y" ]; then
    echo "install llvm"
    if [[ ! $LLVM_BRANCH ]]; then
        LLVM_BRANCH="qualatypes"
    fi
    echo "Build llvm $LLVM_BRANCH branch................"
    pushd src/capo
    ./build.sh -b $LLVM_BRANCH
    popd
fi

for c in "${components[@]}"
do
    case $c in
        llvm)
            # built above
            ;;
	    capo)
            echo "Building $c ........................."
            pushd src/capo
            ./build.sh -l
            popd
            ;;       
        cvi | mules | mbig)
            echo "Building $c ........................."
            pushd src/$c
            ./build.sh
            popd
            ;;       
    esac
done

