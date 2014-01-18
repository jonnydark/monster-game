# This is the makefile for the game #

#this will expand
OBJS = main.o input.o charBase.o player.o monster.o space.o map.o 6iiDrive.o
CC = g++
DEBUG = -g -ansi -pedantic-errors
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

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

main.o : main.cpp player.h map/map.h input.h monster.h
	$(CC) $(CFLAGS) $(DEBUG) main.cpp



# Here for rebuilds
clean:
	\rm *.o *~ game.exe
