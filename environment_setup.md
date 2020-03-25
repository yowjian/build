# CLOSURE Development Server HW/SW Configuration
CLOSURE utilizes a number of open-source libraries, tools, and sources to support the various sub-modules. We do not have strict version dependencies (other than LLVM as described below). Standard install processes are employed (apt install, pip3 install, etc.). Main, Restricted, Universe, and Multiverse Ubuntu repositories are required.

## Hardware
  * <b>Processors:</b> Dell R630 2x Intel Xeon E5-2667 v3 3.2Ghz 8 Core 20MB Cache 
  * <b>Memory:</b> 384GB DDR4 ECC

## Operating System & Kernel
  * <b>OS:</b> Ubuntu 19.10 x86_64
  * <b>Kernel:</b> 5.3.0-29-generic
  
## IDE
  * Visual Studio Code (VSCode) v1.42.1
  
## Utilities & Tools
### LLVM & Clang
CLOSURE will keep current with the latest LLVM and Clang releases, periodically merging updates from the official repository. As we will be introducing additional LLVM or Clang features (e.g. type annotation support in Clang), it is recommended that CLOSURE users download LLVM and Clang from the [CLOSURE LLVM fork](https://github.com/gaps-closure/llvm-project) or use our [prepackaged binaries](https://github.com/gaps-closure/capo/releases).
| Package       | Version | 
|:--------------|:--------|
| LLVM/Clang    | 10.0    |

### Debian Packages (apt install)
(Note that the [EMU install procedure](https://github.com/gaps-closure/emu#installing-external-dependencies) automatically retrieves the majority of these packages)

| Package       | Version | 
|:--------------|:---------------|
| bash          | 5.0-4ubuntu1 |
| bridge-utils  | 1.6-2ubuntu1 |
| build-essential |12.8ubuntu1 |
| cmake | 3.13.4-1build1 |
|[CORE](https://github.com/coreemu/core/releases/tag/release-5.5.2)| 5.5.2 | 
| ebtables | 2.0.10.4+snapshot20181205-1ubuntu1|
| ethtool |1:4.19-1 |
| iproute2 |5.2.0-1ubuntu2|
| libconfig-dev | 1.5-0.4   |
| libffi-dev |3.2.1-9 |
| libssl-dev | 1.1.1c-1ubuntu4 |
| libtk-img | 1:1.4.9+dfsg-1|
| libzmq3-dev   | 4.3.2-1   |
| mgen |5.02.b+dfsg1-2.2build1 |
| net-tools |1.60+git20180626.aebd88e-1ubuntu1 |
| Python3       | 3.7.5-1     |
| python3-dev |3.7.5-1 |
| python3-pip |18.1-5 |
| python3-venv | 3.7.5-1|
| qemu |1:4.0+dfsg-0ubuntu9.4 |
| qemu-efi |0~20190606.20d2e5a1-2ubuntu1|
| qemu-system-arm | 1:4.0+dfsg-0ubuntu9.4|
| qemu-system-x86 | 1:4.0+dfsg-0ubuntu9.4|
| qemu-user | 1:4.0+dfsg-0ubuntu9.4|
| qemu-user-static |1:4.0+dfsg-0ubuntu9.4 |
| quagga |1.2.4-4build1 |
| tcl | 8.6.9+1|
| tcl8.6 | 8.6.9+dfsg-2 |
| traceroute |1:2.1.0-2|
| tshark        | 3.0.5-1   |
| ubuntu-dev-tools |0.173ubuntu1 |
| uml-utilities |20070815.2-1build1 |
| xdot          | 1.1-1     |
| xterm | 348-2ubuntu1|

### Python3 packages (pip3 install)
| Package       | Version | 
|:--------------|:--------------|
| decorator   | 4.4.1 |
| lark-parser | 0.7.8 |
| networkx    | 2.4   |
| pexpect     | 4.7.0 |
| pydot       | 1.4.1 |
