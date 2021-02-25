CC=g++
CFLAGS= $(shell sdl2-config --cflags)
LDFLAGS=  $(shell sdl2-config --libs)
EXEC=tetris

all: $(EXEC)

tetris: tp1.o sprite.o ball.o tetrimino.o window_surface.o surface.o
	$(CC) -o $@ $^ $(LDFLAGS)

tp1.o: tp1.cpp sprite.h ball.h tetrimino.h window_surface.h surface.h
	$(CC) -o $@ -c $< $(CFLAGS)

sprite.o: sprite.cpp sprite.h surface.h
	$(CC) -o $@ -c $< $(CFLAGS)

ball.o: ball.cpp ball.h
	$(CC) -o $@ -c $< $(CFLAGS)

tetrimino.o: tetrimino.cpp tetrimino.h
	$(CC) -o $@ -c $< $(CFLAGS)

window_surface.o: window_surface.cpp window_surface.h tetrimino.h surface.h
	$(CC) -o $@ -c $< $(CFLAGS)

surface.o: surface.cpp surface.h
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o
