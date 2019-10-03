Instructions for installing LLVM from sources can be found at:
[https://llvm.org/docs/GettingStarted.html](https://llvm.org/docs/GettingStarted.html)

```
# Install dependencies on Ubuntu Linux system
sudo apt install build-essential
sudo apt install libxml2-dev
sudo apt install libedit-dev
sudo apt install curl
sudo apt install swig
sudo apt install doxygen
sudo apt install gccgo
sudo apt install libz3-dev
sudo apt install ocaml opam libz3-ocaml-dev
sudo apt install python python-dev python-pip

# Create top level directory  
mkdir -p ~/closure
cd closure

# Fetch latest LLVM sources from our fork
# XXX: For older versions see http://releases.llvm.org/
# XXX: For LLVM master use https://github.com/llvm/llvm-project.git
git clone https://github.com/gaps-closure/llvm-project.git

# Build LLVM projects
cd llvm-project
mkdir build
cd build
# For a full build
# XXX: llgo fails to build, building without llgo for now, needs to be added
# XXX: also need to identify other missing libraries and fix:
# XXX:   Z3, Ocaml, sphinx-build, LIBOMPTARGET_DEP_LIBFFI, CUDA, LLVM FileCheck
# XXX: may want to switch to python 3.x
# cmake -G 'Unix Makefiles' -DLLVM_ENABLE_PROJECTS='clang;clang-tools-extra;compiler-rt;debuginfo-tests;libclc;libcxx;libcxxabi;libunwind;lld;lldb;llgo;openmp;parallel-libs;polly;pstl' -DCLANG_PYTHON_BINDINGS_VERSIONS=2.7 -DCMAKE_BUILD_TYPE=Release ../llvm
# For a more minimal and faster build
cmake -G 'Unix Makefiles' -DLLVM_ENABLE_PROJECTS='clang;libclc;libcxx;libcxxabi;lld' -DCLANG_PYTHON_BINDINGS_VERSIONS=2.7 -DCMAKE_BUILD_TYPE=Release ../llvm
make -j24

# Optionally install under default prefix /usr/local
# XXX: you can always go to build/bin and invoke tools from there
# sudo make install

# Create and test sample program
cd ..
cat << EOF > helloworldmars.cpp
#include <iostream>

using namespace std;

#pragma cle def HIGH_1 \
   { \
       "var": "foo", \
       "arr": [{"bar": "a2ltuae"}, {"baz": 42} \
   }

int main()
{
    #pragma cle HIGH_1
    string str = "Hello World, Mars!";
    cout << str << endl;
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
