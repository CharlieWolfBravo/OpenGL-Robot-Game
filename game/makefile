INCLUDE = -I/usr/include/
LIBDIR = -L/usr/lib/

COMPILERFLAGS = -Wall
CC = gcc
CFLAGS = $(COMPILERFLAGS) $(INCLUDE) $(INC)
LIBRARIES = -lX11 -lXi -lXmu -lglut -lGL -lGLU -lm

all: robot

# robot: main.cpp bmpread.c
# 	$(CC) $(CFLAGS) -o $@ $(LIBDIR) $< $(LIBRARIES)

robot: main.o Building.o Robot.o
	gcc -c Building.cc
	gcc -c Robot.cc
	gcc -c main.cpp
	$(CC) $(CFLAGS) main.o Building.o -o robot $(LIBDIR) $(LIBRARIES)

clean:
	rm -f *.o *~ robot