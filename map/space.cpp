/*
 * space.cpp
 *
 * Here are the function definitions as prototyped in space.h
 */

#include <iostream>
#include <sstream>

#include "space.h"

namespace dungeon_map
{


  // Function to set a marker
  void space::mark() {
    marked = true;
    set('!');
  }

  //Function to remove a marker
  void space::unmark() {
    marked = false;
    set(' ');
  }

   // function to set the type of space
  void space::setType(unsigned int newType) {
    if(newType < 2) {
      type = newType;
    } else {
      std::cerr << "Can only use space::setType() to set to 0 or 1. Use space::setItemID to set to 2\n";
      // ^ This is for debugging, it should never occur in the game
    }
  }

   
  // Overloaded space insertion operator for spaces
  std::ostream & operator<<(std::ostream &oss, const space &sp) {
    oss << sp.out;
    return oss;
  }



}
