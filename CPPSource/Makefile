# Steps: include bin dlls in project directory. Include sfml, and
# link sfml lib, with graphics, system and windows

# Specify compiler
CC = g++

# Specify linker
LINK = g++

# Build all target
all : compile link run clean

test: compile link run

compile:
	$(CC) -c *.cpp -IC:\SFML_MINGW\SFML-2.5.1\include

link:
	$(LINK) *.o -o main -LC:\SFML_MINGW\SFML-2.5.1\lib -lsfml-graphics -lsfml-window -lsfml-system

run:
	./main.exe

clean:
# Ensure empty line is printed before clean so output is clear
# since the output is on the terminal, not a file
	@echo off
	@echo. & rem Empty line
	del /Q /S *.o *.exe
	@echo on


