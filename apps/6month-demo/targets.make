#Targets
#
# Valid targets:
# native - host CPU (ie same as the machine you are compiling on)
# arm64 - Cross compile to aarch64

ORANGE_TARGET=native
GREEN_TARGET=native


#Below is logic to configure the enviroment based on the above configuration

CC_ORANGE=$(CC)
CC_GREEN=$(CC)
CXX_ORANGE=$(CXX)
CXX_GREEN=$(CXX)
ORANGE_HAL=$(HAL)
GREEN_HAL=$(HAL)
ORANGE_LDFLAGS=$(LDFLAGS)
GREEN_LDFLAGS=$(LDFLAGS)

# prepare Orange target
ifeq ($(ORANGE_TARGET),arm64)
ORANGE_HAL=../../src/mbig/arm64/hal
CC_ORANGE=aarch64-none-linux-gnu-gcc
CXX_ORANGE=aarch64-none-linux-gnu-g++
ORANGE_LDFLAGS=$(AARCH64_LDFLAGS) -L${ORANGE_HAL}/api -L${ORANGE_HAL}/appgen/6month-demo $(HAL_LIBS) -L${ORANGE_HAL}/arm64_prebuild -lzmq -lstdc++ -lc -lpthread -dl -llzma -lsodium -lunwind -ldl
endif

# prepare Green target
ifeq ($(GREEN_TARGET),arm64)
GREEN_HAL=../../src/mbig/arm64/hal
CC_GREEN=aarch64-none-linux-gnu-gcc
CXX_GREEN=aarch64-none-linux-gnu-g++
GREEN_LDFLAGS=$(AARCH64_LDFLAGS) -L${GREEN_HAL}/api -L${GREEN_HAL}/appgen/6month-demo $(HAL_LIBS) -L${GREEN_HAL}/arm64_prebuild -lzmq -lstdc++ -lc -lpthread -dl -llzma -lsodium -lunwind -ldl
endif

#for generic arm64 targets
CXX_ARM64=aarch64-none-linux-gnu-g++
ARM64_CPPFLAGS=$(AARCH64_CFLAGS) $(CPPFLAGS)
