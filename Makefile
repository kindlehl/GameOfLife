CC=g++
NAME=GameOfLife
CFLAGS=-std=c++14 -g 
SFML = -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system 
ALL= include/grid.h main.cpp source/grid.cpp grid.o
SOURCES=source/grid.cpp main.cpp
OBJECTS=$(SOURCES:.cpp=.o)

ALL: $(NAME)

$(NAME): main.o main.cpp 
	$(CC) $(CFLAGS) -o $(NAME) main.o grid.o $(SFML) 
main.o: grid.o 
	$(CC) $(CFLAGS) -c -o main.o main.cpp $(SFML)
	
grid.o: include/grid.h source/grid.cpp include/creature.h 
	$(CC) $(CFLAGS) -c -o grid.o source/grid.cpp $(SFML)
clean:
	rm -f *.o $(NAME)

