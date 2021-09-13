FROM closure
RUN sudo apt update 
RUN sudo apt install -y cmake git 

RUN cd /opt/ \
    && sudo mkdir minizinc \
    && sudo wget https://github.com/MiniZinc/MiniZincIDE/releases/download/2.5.5/MiniZincIDE-2.5.5-bundle-linux-x86_64.tgz \
    && sudo tar -xvzf MiniZinc* -C minizinc --strip-components=1

ENV PATH=$PATH:/opt/minizinc/bin:$PATH