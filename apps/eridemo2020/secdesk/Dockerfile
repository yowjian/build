FROM gapsclosure/closuredev:master

RUN sudo apt update -y \
&&  sudo apt install -y cmake software-properties-common
RUN sudo add-apt-repository ppa:deadsnakes/ppa
RUN sudo apt install -y python3.7 python3.7-dev libpython3.7 libsqlite3-dev python3.7-distutils
RUN sudo -H python3.7 -m pip install numpy face_recognition opencv-python scikit-learn imutils 
