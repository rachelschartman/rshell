#Bash makefile

#Variables
COMPILE = g++
FLAGS = -g -W -Wall -Werror -ansi -pedantic

all: main.cpp IntVector.o
	$(COMPILE) $(FLAGA) -o a.out main.cpp IntVector.o

IntVector.o: IntVector.cpp IntVector.h 
	$(COMPILE) $(FLAGS) -c IntVector.cpp