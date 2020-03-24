# CLOSURE build
This repository hosts references to all CLOSURE components and the scripts to build CLOSURE or individual components from source. The `master` branch contains the most recent public release software while `develop` contains bleeding-edge updates and work-in-progress features for use by beta testers and early adopters.

This repository is maintained by Perspecta Labs.

A prerequisite of building CLOSURE from its components is git slave. Download and install [git slave](http://gitslave.sourceforge.net/) as follows, if it is not already installed on your system.
```
set -ex
wget https://sourceforge.net/projects/gitslave/files/gitslave-2.0.2.tar.gz
tar -xzvf gitslave-2.0.2.tar.gz
cd gitslave-2.0.2
sed 's/pod2man/pod2man --name gits/' -i Makefile
sed 's/pod2man/pod2man --name gits-checkup/' -i contrib/Makefile
make
sudo make install
```

## Contents
- [Cloning CLOSURE](#cloning-closure)
- [Build All from source excluding LLVM](#build-all-from-source-excluding-llvm)
- [Build All from source including LLVM](#build-all-from-source-including-llvm)
- [LLVM Only](#build-llvm-only)
- [Build A Subset of Components](#build-a-subset-of-components)

## Cloning CLOSURE
Clone the CLOSURE components as follows, into the 'build' directory (referred to as $BUILD below) in the current directory, including all CLOSURE submodules, excluding LLVM.

```
gits clone https://github.com/gaps-closure/build
```
In the following, $BUILD refers to 


## Build All from source excluding LLVM
To build the entire CLOSURE, except LLVM, from source, do the following

```
$BUILD/build.sh
```

Note that this will install LLVM from a pre-built binaries.

## Build All from source including LLVM
To build the entire CLOSURE including LLVM from source, do the following

```
$BUILD/build.sh -l [-b <llvm-branch>]
```
Note that the default LLVM branch is 'qualatypes'. If you need to build it from other branches, specified the branch name.

## LLVM Only
```
$BUILD/build.sh [-b <llvm-branch>] llvm
```
Note that if the -b <llvm-branch> option is specified, then the 'qualatypes' branch will be checked out, regardless of whether the LLVM source is present in the capo directory.
If the -b <llvm-branch> option is not specified, then the 'qualatypes' branch will be checked out, if the LLVM source is not already present. Otherwise, the current LLVM branch is used in the build.

## Build A Subset of Components
To build a subset of components, specify them in the command line argument to the build script. (emu and hal are in progress)

```
$BUILD/build.sh {capo cvi mules mbig emu hal llvm}
```

