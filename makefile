BUILD_ROOT = .
SRC = $(BUILD_ROOT)/src
EXEC = test

ARCH="`uname -m`"
CC = gcc
CXX = g++
CFLAGS += -I$(BUILD_ROOT)/include -I.
CPPFLAGS += -I$(BUILD_ROOT)/include -I.
LDFLAGS += -L$(BUILD_ROOT)/lib

ifeq ($(ARCH), armv7l)
	LDFLAGS += -llibgtest_armv7
endif

FILES += $(foreach d, $(SRC), $(wildcard $(d)/*.cpp))
FILES += $(foreach d, $(SRC), $(wildcard $(d)/*.c))
OBJS += $(patsubst %.cpp, %.o, $(FILES))
OBJS += $(patsubst %.c, %.o, $(FILES))


.PHONY: all

all: build

build: $(EXEC)

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $(LDFLAGS) $<

%.o: %.cpp
	$(CXX) -c $(CPPFLAGS) -o $@ $(LDFLAGS) $<

$(EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

clean:
	rm -rf $(EXEC) $(OBJS)