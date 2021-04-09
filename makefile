BUILD_ROOT = .
SRC = $(BUILD_ROOT)/src
EXEC = test

ARCH="`uname -m`"
CC = gcc
CXX = g++
CFLAGS += -g -O3
CPPFLAGS += -g -O3 -fPIC
LDFLAGS += -I$(BUILD_ROOT)/include -I.
LDFLAGS += -L$(BUILD_ROOT)/lib
LDFLAGS += -lpthread
LDFLAGS += -lgtest_armv7
ifeq ($(ARCH), armv7l)
	@echo 'We get armv7'
	LDFLAGS += -lgtest_armv7
endif

CPPFILES += $(foreach d, $(SRC), $(wildcard $(d)/*.cpp))
CFILES += $(foreach d, $(SRC), $(wildcard $(d)/*.c))
OBJS += $(patsubst %.cpp, %.o, $(CPPFILES))
OBJS += $(patsubst %.c, %.o, $(CFILES))


.PHONY: all

all: build

build: $(EXEC)

%.o: %.c
	$(CXX) -c $(CPPFLAGS) -o $@ $(LDFLAGS) $<

%.o: %.cpp
	$(CXX) -c $(CPPFLAGS) -o $@ $(LDFLAGS) $<

$(EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

clean:
	rm -rf $(EXEC) $(OBJS)