# Specify compiler
CC = g++

# Specify linker
LINK = g++

# Build all target
all : compile link run clean

test: compile link run

# SFML_STATIC can also be defined in the main.cpp file
compile:
	$(CC) -c *.cpp -IC:\SFML_MINGW\SFML-2.6.1\include -DSFML_STATIC

link:
	$(LINK) *.o -o main -LC:\SFML_MINGW\SFML-2.6.1\lib -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32

run:
	./main.exe

clean:
# Ensure empty line is printed before clean so output is clear
# since the output is on the terminal, not a file
	@echo off
	@echo. & rem Empty line
	del /Q /S *.o *.exe
	@echo on


