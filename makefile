SRC = mul4x4.c 
EXEC = mul4x4

CC = gcc
CFLAGES = -O3

OBJS += $(SRC:%.c=%.o)

.PHONY: all

all: build

build: $(EXEC)

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(CFLAGES)

clean:
	rm -rf $(EXEC) $(OBJS)