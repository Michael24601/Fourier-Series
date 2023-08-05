# Specify compiler
CC=g++

# Specify linker
LINK=g++


all : compile link run clean

compile:
	$(CC) -c *.cpp

link:
	$(LINK) *.o -o generateFourrier

run:
	./generateFourrier.exe

clean:
	del /Q /S *.o *.exe