/*
 * charBase.cpp
 *
 * The function definitions for ones that were declared in charBase.h
 * <string> and map.h are included in the header so I don't need to
 * re-include them here
 */


#include "charBase.h"

#include <cstdlib>
#include <sstream>


using namespace std;
using namespace charBase;

// map constructor - used to place a character at a random x for a given y
character::character(dungeon_map::map &mp, int y, int h) {
  alive = true;
  health = h;
  max = h;
  while(true) {
    int x = (rand() % (mp.getSide()) + 1);
    if((mp.index(x,y))->getType() != 1) {
      xPos = x;
      yPos = y;
      break;
    }
  }
}


string character::healthBar() {
  // Define a stringstream to make the health bar
  ostringstream bar;
  // start of the bar
  bar << "[";
  if(health > 0) {
    for(int i=0; i < health; i+=4) {
      bar << "=";
    }
  }
  // if the health is not maximum, fill the rest with spaces
  if(health < max) {
    for(int i=health; i < max; i+=4) {
      bar << " ";
    }
  }
  // end of bar and return the string
  bar << "]";
  return bar.str();
}

