BUILD_ROOT = .
SRC = $(BUILD_ROOT)/src
EXEC = test

ARCH=$(shell uname -m)
CC = gcc
CXX = g++
CFLAGS += -g -O3
CPPFLAGS += -g -O3 -fPIC
LDFLAGS += -I$(BUILD_ROOT)/include -I.
LDFLAGS += -L$(BUILD_ROOT)/lib

ifeq ($(ARCH), armv7l)
	LDFLAGS += -lgtest_armv7
	CPPFLAGS += -D__armv7__
else ifeq ($(ARCH), aarch64)
	LDFLAGS += -lgtest_aarch64
	CPPFLAGS += -D__aarch64__
else ifeq ($(ARCH), x86_64)
	LDFLAGS += -lgtest_amd64
	CPPFLAGS += -D__x86_64__
endif
LDFLAGS += -lpthread

CPPFILES += $(foreach d, $(SRC), $(wildcard $(d)/*.cpp))
CFILES += $(foreach d, $(SRC), $(wildcard $(d)/*.c))
OBJS += $(patsubst %.cpp, %.o, $(CPPFILES))
OBJS += $(patsubst %.c, %.o, $(CFILES))


.PHONY: all

all: build run

rebuild: clean build run

build: $(EXEC)

%.o: %.c
	$(CXX) -c $(CPPFLAGS) -o $@ $(LDFLAGS) $<

%.o: %.cpp
	$(CXX) -c $(CPPFLAGS) -o $@ $(LDFLAGS) $<

$(EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

run: build
	$(BUILD_ROOT)/$(EXEC)

clean:
	rm -rf $(EXEC) $(OBJS)