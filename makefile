CC=gcc

CFLAGS=-g -Wall -lm -ldl -fPIC -rdynamic # -O3 -march=native

SRC=./src

BIN=bin

#BIN_INSTALL=/usr/bin/



%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

%.asm: %.c
	$(CC) -S $(CFLAGS) $<



.PHONY: all asm install uninstall clean clean-all

all: $(patsubst %.c,%.o,$(wildcard $(SRC)/*.c))
	$(CC) $(CFLAGS) $^ -o $(BIN)

asm: $(patsubst %.c,%.asm,$(wildcard $(SRC)/*.c))



#install:
#	cp $(BIN) $(BIN_INSTALL)

#uninstall:
#	rm -f $(BIN_INSTALL)/$(BIN)



clean:
	rm -f $(SRC)/*.o

clean-all: clean
	rm -f $(BIN)
