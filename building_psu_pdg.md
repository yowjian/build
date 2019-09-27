This file contains instructions for building and running the PSU program dependency generator, which is a key prerequisite for CLOSURE partioning and optimization. Currently this code is based on LLVM-5.0.  We will be porting this code to the latest LLVM code from the gaps-closure fork. The instructions below are for an Ubuntu system which has build-essentials and does not have other versions of LLVM/clang.

```
sudo apt install llvm-5.0
sudo apt install graphviz
sudo apt install clang-5.0
git clone https://bitbucket.org/psu_soslab/pdg-llvm5.0.git
cd pdg-llvm5.0
mkdir build
make
cat << EOF > helloworldmars.cpp
#include <iostream>

using namespace std;

#pragma cle def HIGH_1 \
{\
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

clang++-5.0 -S -emit-llvm helloworldmars.cpp
llvm-as-5.0 helloworldmars.ll 
opt-5.0 -load ./build/libpdg.so -dot-pdg helloworldmars.bc
dotty pdgragh.main.dot
```

