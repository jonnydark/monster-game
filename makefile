# This is the makefile for the game #

#this will expand
OBJS = main.o input.o game.o charBase.o player.o monster.o space.o map.o 6iiDrive.o
CC = g++
DEBUG = -g -pedantic-errors 
CFLAGS = -std=c++0x -Wall -c $(DEBUG)
LFLAGS = -std=c++0x -Wall $(DEBUG)

game.exe : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o game.exe
	@echo "Cleaning Up"
	\rm *.o 
	@echo "\
		Game now compiled as game.exe\
		"

space.o : map/space.h map/space.cpp
	$(CC) $(CFLAGS) $(DEBUG) map/space.cpp 

map.o : map/map.cpp map/map.h player.h 
	$(CC) $(CFLAGS) $(DEBUG) map/map.cpp

game.o : game.cpp game.h player.h monster.h
	$(CC) $(CFLAGS) $(DEBUG) game.cpp

charBase.o : charBase.cpp charBase.h
	$(CC) $(CFLAGS) $(DEBUG) charBase.cpp

6iiDrive.o : items/6iiDrive.h items/6iiDrive.cpp
	$(CC) $(CFLAGS) $(DEBUG) items/6iiDrive.cpp

player.o : player.cpp charBase.h player.h items/item.h items/0fists.h items/1vorpalSword.h items/2rareCandy.h items/3chekhovsGun.h items/4ruler.h items/5shoryuken.h items/6iiDrive.h items/7timeBomb.h
	$(CC) $(CFLAGS) $(DEBUG) player.cpp

monster.o : monster.cpp charBase.h map/map.h monster.h
	$(CC) $(CFLAGS) $(DEBUG) monster.cpp

input.o : input.h input.cpp
	$(CC) $(CFLAGS) $(DEBUG) input.cpp

main.o : main.cpp player.h map/map.h input.h monster.h game.h
	$(CC) main.cpp $(CFLAGS) 



# Here for rebuilds
clean:
	\rm *.o *~ game.exe
