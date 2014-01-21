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

  void space::ConvertToNormal() {
    type = NormalSpace;
  }

  void space::ConvertToPitfall() {
    type = Pitfall;
  }

   
  // Overloaded space insertion operator for spaces
  std::ostream & operator<<(std::ostream &oss, const space &sp) {
    oss << sp.out;
    return oss;
  }



}
