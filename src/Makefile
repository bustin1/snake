SHELL=/bin/sh

CC=g++
#sdl2-config is a tool/program to determine the compiler and linker flags	
#--libs: necessary linker flags to link with SDL2
#--cflags necessary compilier flags to compile a cpp program
LDFLAGS=`sdl2-config --libs --cflags` -lSDL2_ttf -lSDL2_image -lm
SRC=*.cpp
EXEC=main

all: $(EXEC)
  
$(EXEC): $(SRC)
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	rm -v $(EXEC)

#the next 2 lines is called a rule
#target: dependency
#	recipe

#.phony: don't make all or clean a target
.PHONY: all clean
