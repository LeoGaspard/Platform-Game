CC = g++
EXEC = Platform
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
FLAGS = 

all: main.o
	$(CC) *.o -o $(EXEC) $(LIBS)

main.o: level.o player.o
	$(CC) src/main.cpp -c $(FLAGS)

level.o :
	$(CC) src/level.cpp -c $(FLAGS)

player.o : level.o
	$(CC) src/player.cpp -c $(FLAGS)

clear :
	rm -f *.o

mr_proper :
	rm -f *.o $(EXEC)