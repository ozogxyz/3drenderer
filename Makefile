UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
	$(error You seem to be running Linux. I have no idea how to deal with that.)
else ifeq ($(UNAME), Darwin)
	LIBLDIR := /opt/homebrew/Cellar/sdl2/2.30.7/lib
	INCLLDIR := /opt/homebrew/Cellar/sdl2/2.30.7/include
	COMPILER := gcc
else ifeq ($(UNAME), OpenBSD)
	LIBLDIR := /usr/local/lib
	INCLLDIR := /usr/local/include
	COMPILER := cc
else
	$(error You seem to be running Windows. I have no idea how to deal with that.)
endif

build:
	$(COMPILER) -lSDL2 -L$(LIBLDIR) -I$(INCLLDIR) -Wall -std=c99 -Wextra -pedantic src/*.c -o renderer
run:
	./renderer

clean:
	rm renderer
