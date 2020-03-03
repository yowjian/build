# build
Base repo for organizing CLOSURE code

## Development Server Specification & Configuration
CLOSURE utilizes a number of open-source libraries, tools, and sources to support the various sub-modules. We do not have strict version dependencies (other than LLVM as described below). Standard install processes are employed (apt install, pip3 install, etc.). Main, Restricted, Universe, and Multiverse Ubuntu repositories are required.

### Hardware
  * <b>Processors:</b> Dell R630 2x Intel Xeon E5-2667 v3 3.2Ghz 8 Core 20MB Cache 
  * <b>Memory:</b> 384GB DDR4 ECC

### Operating System & Kernel
  * <b>OS:</b> Ubuntu 19.10 x86_64
  * <b>Kernel:</b> 5.3.0-29-generic
  
### IDE
  * Visual Studio Code (VSCode) v1.42.1
  
### Utilities & Tools

| Package       | Version | 
|---------------|:--------------:|
| CORE          | 5.5.2          |
| Python3       | 3.7.5          |
| QEMU Emulator | 4.0.0          |
| GNU bash      | 5.0.3          |
| libzmq3-dev   | 4.3.2-1        |
| libconfig-dev | 1.5-0.4        |
| tshark        | 3.0.5-1        |
| xdot          | 1.1-1          |
| LLVM/Clang | 10.0 (https://github.com/gaps-closure/capo/releases) |
| lark-parser (python) | 0.7.8 |
| pydot (python) | 1.4.1 |
| decorator (python) | 4.4.1 |


