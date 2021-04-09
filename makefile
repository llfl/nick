SRC = main.cpp
EXEC = main
ifeq ($(SRC),)
  $(error No source files specified)
endif

ifeq ($(EXEC),)
  $(error No executable file specified)
endif

BUILD_ROOT = ./

ARCH="`uname -m`"
CC = gcc
CXX = g++
CFLAGES = -O3
CPPFLAGES += -I$(BUILD_ROOT)/include -I.
LDFLAGES += -L$(BUILD_ROOT)/lib

OBJS += $(SRC:%.c=%.o)

ifeq ($(ARCH), armv7l)
	LDFLAGES += -llibgtest_armv7
endif

.PHONY: all

all: build

build: $(EXEC)

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $(LDFLAGS)$<

%.o: %.cpp
	$(CXX) -c $(CPPFLAGS) -o $@ $(LDFLAGS) $<

$(EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

clean:
	rm -rf $(EXEC) $(OBJS)