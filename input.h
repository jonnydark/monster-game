/*
 * input.h 
 * 
 * This file contains the declarations for the two functions that take
 * inputs from cin.
 *
 */

#ifndef INPUT_H
#define INPUT_H

// Forward declarations
class player;
class monster;
namespace dungeon_map {
  class map;
}

/* 
 * This is the interpreter function
 * north or n - move north
 * south or s - move south
 * east  or e - move east
 * west  or w - move west
 * wait - wait
 * map - show the map
 * q - quit
 */
void action(player &p, dungeon_map::map &mp);

/*
 * This is the battle function
 * Everything battlewise goes on in here,
 * including part of the monster's AI 
 *  - does it attack or does it run?
 */
void battle(player &p, monster &m, dungeon_map::map &mp);

/*
 * This is called a the beginning of the game to ask the player
 * what size map they want
 */
unsigned int getMapSize();

#endif
