#!/bin/bash

LLVM_URL="https://github.com/gaps-closure/capo/releases/download/T0.1/LLVM-10.0.0svn-Linux.deb"
EMU_ARM_URL="https://github.com/gaps-closure/emu/releases/download/v1.0/ubuntu-arm64-goldenimage.tgz"

RELEASES=($LLVM_URL $EMU_ARM_URL)
BIN=bin

usage_exit() {
  [[ -n "$1" ]] && echo $1
  echo "Usage: $0 [ -bcdhs ] "
  echo "-h        Help"
  echo "-c        Clean up"
  echo "-d        Dry run"
  echo "-b        Pull releases from all components"
  echo "-s        Populate component source and build"
  exit 1
}

handle_opts() {
  local OPTIND
  while getopts "bcdhs" options; do
    case "${options}" in
      c) CLEAN=1                ;;
      d) DRY_RUN="--dry-run"    ;;
      b) BINARY=1               ;;
      s) SOURCE=1               ;;
      h) usage_exit             ;;
      :) usage_exit "Error: -${OPTARG} requires an argument." ;;
      *) usage_exit             ;;
    esac
  done
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

if [[ $BINARY ]]; then
    down_releases
fi
