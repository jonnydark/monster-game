/*
 * input.cpp
 *
 * And here are the definitions as laid out in input.h
 */

#include "player.h"
#include "monster.h"
#include "input.h"

#include <cstdlib>
#include <sstream>


/*
 * Get map size
 */
unsigned int getMapSize() {
  cout << "To start a new game - please enter a size of a map (4-10): ";

  while(true) {
    unsigned int mapSize;
    std::cin >> mapSize;
    if(!std::cin.fail() && mapSize > 3 && mapSize <= 10) {
      std::cin.ignore();
      return mapSize; 
      break;
    }
    std::cin.clear();
    std::cin.ignore();
    std::cerr << "I don't know how to make a map that size...try again?: ";
  }
}


