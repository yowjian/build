#!/bin/sh
set -e
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
FFMPEG_INSTALL=$SCRIPT_DIR/../gaps.ma.dependencies/deps/opencv/ffmpeg/install
OPENCV_VERSION="4.3.0"
cd $SCRIPT_DIR/../gaps.ma.dependencies/deps/opencv

function install_ffmpeg(){
	tar -xvf ffmpeg.tar.bz2
	cd ffmpeg
	./configure --prefix=$FFMPEG_INSTALL --enable-pic --enable-shared
	make -j 8
	make install
}

function install_opencv(){
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$FFMPEG_INSTALL/lib/
	export PKG_CONFIG_PATH=$PKG_CONFIG_PATH:$FFMPEG_INSTALL/lib/pkgconfig
	cd $SCRIPT_DIR/../gaps.ma.dependencies/deps/opencv
	tar -xvf opencv-"$OPENCV_VERSION".tar.gz
	cd opencv
	mkdir -p build
	cd build
	cmake -DCMAKE_BUILD_TYPE=RELEASE -DCMAKE_INSTALL_PREFIX=$SCRIPT_DIR/../install -DWITH_FFMPEG=ON \
	-DWITH_GTK=ON \
	-DCMAKE_SHARED_LINKER_FLAGS=" -Wl,-rpath-link $FFMPEG_INSTALL/lib/ -L$FFMPEG_INSTALL/lib/" \
	-DCMAKE_MODULE_LINKER_FLAGS=" -Wl,-rpath-link  $FFMPEG_INSTALL/lib/ -L$FFMPEG_INSTALL/lib/" \
	-DCMAKE_EXE_LINKER_FLAGS=" -Wl,-rpath-link  $FFMPEG_INSTALL/lib/ -L$FFMPEG_INSTALL/lib/" \
	..
	make -j 8
	make install
	if [ -d $SCRIPT_DIR/../install/lib64 ]; then
		if [ ! -d $SCRIPT_DIR/../install/lib ]; then
			ln -s $SCRIPT_DIR/../install/lib64 $SCRIPT_DIR/../install/lib
		fi
    elif [ -d $SCRIPT_DIR/../install/lib ]; then
        if [ ! -d $SCRIPT_DIR/../install/lib64 ]; then
            ln -s $SCRIPT_DIR/../install/lib $SCRIPT_DIR/../install/lib64
        fi
    fi
}

install_ffmpeg
install_opencv
