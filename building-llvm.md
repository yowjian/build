Instructions for installing LLVM from sources can be found at:
[https://llvm.org/docs/GettingStarted.html](https://llvm.org/docs/GettingStarted.html)


```
# Install dependencies on Ubuntu Linux system
sudo apt update
# sudo apt upgrade
sudo apt install cmake gcc g++ build-essential checkinstall 
sudo apt install python python-pip python-dev python-pygments python-yaml 
sudo apt install llvm ocaml opam 
opam init
opam config env
opam install ctypes ctypes-foreign 
opam depext conf-llvm.6.0.0
opam depext conf-m4.1
opam depext conf-pkg-config.1.1
sudo apt install libxml2-dev libplist-dev libedit-dev llvm-7-tools
sudo apt install curl swig doxygen gccgo

# Create top level directory  
mkdir -p ~/closure

# the z3 package is outdated, need to build from source
# may not be an issue in Ubuntu 19.10
cd ~/closure
git clone https://github.com/Z3Prover/z3
cd z3
python scripts/mk_make.py
cd build
make -j24
sudo checkinstall 

# Fetch latest LLVM sources from our fork
# XXX: LLVM master & older versions at https://github.com/llvm/llvm-project.git
cd ~/closure
git clone https://github.com/gaps-closure/llvm-project.git

# Build LLVM projects
cd llvm-project
mkdir build
cd build
# For a full build
# cmake -G 'Unix Makefiles' -DLLVM_ENABLE_PROJECTS=all -DCLANG_PYTHON_BINDINGS_VERSIONS=2.7 -DCMAKE_BUILD_TYPE=Release ../llvm
# Or choose a subset
# cmake -G 'Unix Makefiles' -DLLVM_ENABLE_PROJECTS='clang;clang-tools-extra;compiler-rt;debuginfo-tests;libclc;libcxx;libcxxabi;libunwind;lld;lldb;llgo;openmp;parallel-libs;polly;pstl' -DCLANG_PYTHON_BINDINGS_VERSIONS=2.7 -DCMAKE_BUILD_TYPE=Release ../llvm
# For a minimal, faster build
cmake -G 'Unix Makefiles' -DLLVM_ENABLE_PROJECTS='clang;libclc;libcxx;libcxxabi;lld' -DCLANG_PYTHON_BINDINGS_VERSIONS=2.7 -DLLVM_TARGETS_TO_BUILD="X86" -DCMAKE_BUILD_TYPE=Release ../llvm
make -j24

# Optionally install under default prefix /usr/local
# XXX: you can always go to build/bin and invoke tools from there
# sudo make install

# Create and test sample program
cd ..
cat << EOF > helloworldmars.cpp
#include <iostream>

using namespace std;

string prt() 
{
  string __attribute__((annotate("HIGH_1"))) str = "Hello World, Mars!";
  return str;
}

int main()
{
  cout << prt() << endl;
  return 0;
}
EOF

# Compile and run program
clang++ helloworldmars.cpp
./a.out

# Compile and generate LLVM IR
clang -S -emit-llvm helloworldmars.cpp

# Clean up the build 
rm -rf build
```
