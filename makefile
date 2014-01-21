# This is the makefile for the game #



#this will expand
OBJS = main.o input.o game.o battle.o charBase.o player.o monster.o space.o map.o 6iiDrive.o
CC = g++
DEBUG = -g -pedantic-errors 
CFLAGS = -std=c++0x -Wall -c 
LFLAGS = -std=c++0x -Wall 
INC=-I$(CURDIR)/map -I$(CURDIR)/items -I$(CURDIR)

game.exe : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o game.exe $(INC)
	@echo "Cleaning Up"
	\rm *.o 
	@echo "\
		Game now compiled as game.exe\
		"

space.o : map/space.h map/space.cpp
	$(CC) map/space.cpp $(CFLAGS) $(INC)

map.o : map/map.cpp map/map.h player.h 
	$(CC) map/map.cpp $(CFLAGS) $(INC)

game.o : game.cpp game.h player.h monster.h
	$(CC) game.cpp $(CFLAGS) $(INC)

battle.o : battle.cpp battle.h monster.h map/map.h player.h
	$(CC) battle.cpp $(CFLAGS) $(INC)

charBase.o : charBase.cpp charBase.h
	$(CC) charBase.cpp $(CFLAGS) $(INC)
 
6iiDrive.o : items/6iiDrive.h items/6iiDrive.cpp
	$(CC) items/6iiDrive.cpp $(CFLAGS) $(INC)

player.o : player.cpp charBase.h player.h items/item.h items/0fists.h items/1vorpalSword.h items/2rareCandy.h items/3chekhovsGun.h items/4ruler.h items/5shoryuken.h items/6iiDrive.h items/7timeBomb.h
	$(CC) player.cpp $(CFLAGS) $(INC)

monster.o : monster.cpp charBase.h map/map.h monster.h
	$(CC) monster.cpp $(CFLAGS) $(INC)

input.o : input.h input.cpp
	$(CC) input.cpp $(CFLAGS) $(INC)

main.o : main.cpp player.h map/map.h input.h monster.h game.h
	$(CC) main.cpp $(CFLAGS) $(INC)



# Here for rebuilds
clean:
	\rm *.o *~ game.exe
