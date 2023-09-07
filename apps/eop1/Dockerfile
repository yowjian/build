FROM gapsclosure/closuredev:develop
MAINTAINER mkaplan@peratonlabs.com
ARG DEBIAN_FRONTEND=noninteractive

RUN sudo apt-get -y update                              \
&&  sudo apt-get -y install				\
    libapr1    						\
    libapr1-dev						\
    nasm						\
    yasm						\
    cmake						\
    autoconf						\
    automake						\
    libtool						\
    libssl-dev						\
    openjdk-16-jre-headless				\
    libavcodec-dev 					\
    libavformat-dev 					\
    libswscale-dev

RUN python3 -m pip install				\
    Flask==2.0.0					\
    Werkzeug==2.0.0
    
RUN mkdir /tmp/gaps && cd /tmp/gaps						     \
&&  git clone https://github.com/gaps-closure/build				     \
&&  cd /tmp/gaps/build/apps/eop1/scripts					     \
&&  bash -f ./build_pinstall.sh							     \
&&  sudo mkdir -p /opt/eop1/EOIR && cd /opt/eop1				     \
&&  sudo cp -r /tmp/gaps/build/apps/eop1/case1/MA_v1.0_src/install . 	 	     \
&&  sudo cp -r /tmp/gaps/build/apps/eop1/case1/MA_v1.0_src/pinstall .		     \
&&  sudo cp -r /tmp/gaps/build/apps/eop1/case1/MA_v1.0_src/gaps.ma.dependencies .    \
&&  sudo cp /tmp/gaps/build/apps/eop1/case1/MA_v1.0_src/EOIR/walking.avi ./EOIR/     \
&&  sudo cp /tmp/gaps/build/apps/eop1/case1/MA_v1.0_src/EOIR/yolov3.weights ./EOIR/  \
&&  cd /opt/eop1/install 						    	     \
&&  sudo rm lib64 								     \
&&  sudo ln -s lib lib64							     \
&&  rm -rf /tmp/gaps/build
