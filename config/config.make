# Toolchain.
#
CC       := gcc
CFLAGS   := -W -Wall -O3
CPPFLAGS :=

CXX      := g++
CXXFLAGS := -W -Wall -O3

LD       := $(CXX)
LDFLAGS  := $(CXXFLAGS)
LIBS     :=

# Optional post-link command. The first argument to this command is
# the executable name and the rest of the arguments are the object
# files and libraries that were used to link this executable.
#
POSTLD   :=

# Set RANLIB to empty if your system does not need ranlib.
#
AR       := ar
ARFLAGS  := rc
RANLIB   := ranlib

