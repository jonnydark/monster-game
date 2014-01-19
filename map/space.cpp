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
  void space::setType(SpaceType newType) {
      type = newType;
  }

   
  // Overloaded space insertion operator for spaces
  std::ostream & operator<<(std::ostream &oss, const space &sp) {
    oss << sp.out;
    return oss;
  }



}
