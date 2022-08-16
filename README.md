# CLOSURE build

DEPRECATED. Please refer to [CLOSURE C Toolchain Documentation](https://github.com/gaps-closure/gaps-closure.github.io/)

[![build](https://github.com/gaps-closure/build/actions/workflows/main.yml/badge.svg)](https://github.com/gaps-closure/build/actions/workflows/main.yml)
[![docker](https://github.com/gaps-closure/build/actions/workflows/docker-image.yml/badge.svg)](https://github.com/gaps-closure/build/actions/workflows/docker-image.yml)

This repository hosts references to all CLOSURE components and the scripts to build CLOSURE or individual components from source. The `master` branch contains the most recent public release software while `develop` contains bleeding-edge updates and work-in-progress features for use by beta testers and early adopters.

This repository is maintained by Perspecta Labs.


## Contents
- [Cloning CLOSURE](#cloning-closure)
- [Build all from source](#build-all-from-source)
- [Installation](#installation)

## Cloning CLOSURE
Clone the CLOSURE components as follows, into the 'build' directory (referred to as $BUILD below) in the current directory, including all CLOSURE submodules, excluding LLVM.

```
git clone --recurse-submodules https://github.com/gaps-closure/build.git
```

## Build all from source

All CLOSURE components can be built using the build.sh script:

```
./build.sh
```

Adding `-c` will clean each subdirectory

## Getting started with the `devcontainer`

The quickest and easiest way to get the most up to date 
build of closure is to build the docker image:

```
docker build -f Dockerfile.dev -t gapsclosure/closuredev:latest .
```

or, you can download the cached image from dockerhub

```
docker pull gapsclosure/closuredev:latest
```

Then, you can open the examples under `apps/examples`
using the Remote - Containers extension for vscode.

## Bare Metal Installation

The CLOSURE toolchain can be installed using:

```
./install.sh -o <install_prefix>
```

When installed you can add environment variables into your session or add it to your `.bashrc`:

```
source <install_prefix>/etc/closureenv
```


