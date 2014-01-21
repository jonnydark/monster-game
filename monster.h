/*
 * monster.h
 *
 * Monster character inherits from character class
 * as defined in charBase.h
 */

#ifndef MONSTER_H
#define MONSTER_H

#include "charBase.h"

class map;

  class monster : public charBase::character
  {
    private:
    // Not sure of what other private data is needed
    // other than health xPos yPos and alive

    public:

      // Standard constructor - random position along top row
      // Monster health is related to the size of the map
      monster(dungeon_map::map &mp) : charBase::character(mp, 1, 100+2*mp.getSize()) {}

      // Destructor
      ~monster() {}

      // Movement
      // The monster can move in any direction that isn't off the map
      // or on to a pitfall. Direction of movement is random
      void move(const dungeon_map::map &mp);

      // The monster fights. This should never be called
      // outside of a battle.
      void fight(Player &p);
  };


#endif
