/*
 * charBase.h
 *
 * Base Class for both player and the monster as there is significant similarity.
 * This class never gets instantiated - it just contains common functions between
 * the player and the monster. It made more sense to do it this way than have the
 * monster inherit useless functions from the player and vice versa
 *
 * 
 */


#ifndef CHARBASE_H
#define CHARBASE_H

#include "map/map.h"

#include <string>

namespace charBase {

  class character
  {
    protected:
      int health, xPos, yPos, max; 
      bool alive; // True if alive, false if dead

    public:
      
      // map constructor - used to place a character at a random x for a given y
      character(dungeon_map::map &mp, int y, int h);

      // destructor
      virtual ~character() {}

      // Location accessors
      int x() const {
        return xPos;
      }

      int y() const {
        return yPos;
      }

      dungeon_map::Coords getCoords() const {
        return { xPos, yPos };
      }

      // Health accessor
      int hp() const {
        return health;
      }

      // Function to return a healthbar
      // Written like this so I can change the
      // max health of the monster later
      std::string healthBar();
             

      // Function called when a character is hit
      // or healed. Takes an integer as an argument.
      // That value is added to the current health.
      void hitOrHeal(int h) {
        health += h;
      }

      // Kill the character
      void kill() {
        alive = false;
      }

      // Is the player dead?
      bool dead() {
        // check if the health hasn't gone to zero
        if(health <= 0) {
          alive = false;
        }
        return !alive;
      }

  };

}

#endif
