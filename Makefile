CC = g++
CDFLAGS = -Wall -g
SRC = maze.cpp visual.cpp
OBJ = $(SRC:%.cpp=%.o)
EXE = maze.exe

all: compile
	@echo Done!

compile:
	@echo Compiling...
	@$(CC) $(CDFLAGS) -o $(EXE) $(SRC) -lncurses

clean:
	@echo Cleaning up...
	@rm -f *.o
	@rm -f *.core
	@rm -f *.out
	@rm -f $(EXE)
