# Compiler
CC := g++

# Flags
CFLAGS := `sdl2-config --libs` -lSDL2_image -lm

# Source file
SRCS := main.cpp

# Exec name
EXEC := snake


all: main.o renderer.o game.o texturemanager.o object.o sprite.o
	$(CC) $(CFLAGS) -o $(EXEC) renderer.o main.o game.o texturemanager.o object.o sprite.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

game.o: game.cpp
	$(CC) $(CFLAGS) -c game.cpp

renderer.o: renderer.cpp
	$(CC) $(CFLAGS) -c renderer.cpp

texturemanager.o: texturemanager.cpp
	$(CC) $(CFLAGS) -c texturemanager.cpp

sprite.o: sprite.cpp
	$(CC) $(CFLAGS) -c sprite.cpp

object.o: object.cpp
	$(CC) $(CFLAGS) -c object.cpp
