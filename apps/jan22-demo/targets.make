#Targets
#
# Valid targets:
# native - host CPU (ie same as the machine you are compiling on)
# arm64 - Cross compile to aarch64

ORANGE_TARGET=arm64
PURPLE_TARGET=native


#Below is logic to configure the enviroment based on the above configuration

CC_ORANGE=$(CC)
CC_PURPLE=$(CC)
ORANGE_FLAGS=-L../../src/capo/partitioner/src
PURPLE_FLAGS=-L../../src/capo/partitioner/src
BUILD_AARCH64_LIBS=false

# prepare Orange target
ifeq ($(ORANGE_TARGET),arm64)
CC_ORANGE=aarch64-none-linux-gnu-gcc
BUILD_AARCH64_LIBS=true
ORANGE_FLAGS=$(AARCH64_LDFLAGS) $(AARCH64_CFLAGS) -L../../src/mbig/arm64/capo/partitioner/src/
endif

# prepare Purple target
ifeq ($(PURPLE_TARGET),arm64)
CC_PURPLE=aarch64-none-linux-gnu-gcc
BUILD_AARCH64_LIBS=true
PURPLE_FLAGS=$(AARCH64_LDFLAGS) $(AARCH64_CFLAGS) -L../../src/mbig/arm64/capo/partitioner/src/
endif

ifeq ($(BUILD_AARCH64_LIBS),true)
# test the user has sourced the aarch cross compile enviroment
ifeq ($(shell which aarch64-none-linux-gnu-gcc),)
# the aarch64 (ie arm64) compiler was not found
$(error Unable to find arm64 compiler "aarch64-none-linux-gnu-gcc" please cd into the src/mbig/crosscompile and source "env-aarch64")
endif
endif
