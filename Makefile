LIBLDIR = /opt/homebrew/Cellar/sdl2/2.30.7/lib
INCLLDIR = /opt/homebrew/Cellar/sdl2/2.30.7/include

build:
	gcc -lSDL2 -L$(LIBLDIR) -I$(INCLLDIR) -Wall -std=c99 -Wextra -pedantic src/*.c -o renderer
run:
	./renderer

clean:
	rm renderer
