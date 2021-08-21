FROM closure

RUN sudo apt update -y \
&&  sudo apt install -y cmake  software-properties-common
RUN sudo add-apt-repository ppa:deadsnakes/ppa 
RUN sudo apt install -y python3.7 python3.7-dev libpython3.7
RUN sudo -H python3.7 -m pip install numpy face_recognition opencv-python scikit-learn imutils 
#RUN sudo cp -r /usr/local/lib/python3.8/dist-packages/clang /usr/local/lib/python3.7/dist-packages/clang

