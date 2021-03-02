CC=g++
CFLAGS= $(shell sdl2-config --cflags)
LDFLAGS=  $(shell sdl2-config --libs) -lSDL2_ttf -lSDL2_mixer
EXEC=tetris
SRC=src
HEADERS=src

all: $(EXEC)

tetris: game.o board.o tetrimino.o surface.o sprite.o window_surface.o
	$(CC) -o $@ $^ $(LDFLAGS)

game.o: $(SRC)/tp1.cpp 
	$(CC) -o $@ -c $< $(CFLAGS)

board.o: $(SRC)/board.cpp $(HEADERS)/board.h
	$(CC) -o $@ -c $< $(CFLAGS)

tetrimino.o: $(SRC)/tetrimino.cpp $(HEADERS)/tetrimino.h
	$(CC) -o $@ -c $< $(CFLAGS)

surface.o: $(SRC)/surface.cpp $(HEADERS)/surface.h
	$(CC) -o $@ -c $< $(CFLAGS)

sprite.o: $(SRC)/sprite.cpp $(HEADERS)/sprite.h
	$(CC) -o $@ -c $< $(CFLAGS)

window_surface.o: $(SRC)/window_surface.cpp $(HEADERS)/window_surface.h
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm tetris
	rm -rf *.o
