/*
 * map.h 
 *
 * This is the header file for the map. The map is composed of spaces
 * as outlined in space.h
 */

#ifndef MAP_H
#define MAP_H

#include "space.h"
#include "item.h"


//forward declaration
class Player;

namespace dungeon_map
{

  struct Coords {
    int x;
    int y;

    bool operator==(const Coords& rhs) const {
      return (x == rhs.x && y == rhs.y);
    }
  };

  class map 
  {
    private:
      // Data //
      space *spaces; // an array of spaces
      int side, size;
      
      items::ItemID IntToItemId(const unsigned int i);
      
    public:
      // The constructor initializes the global variables side and size
      // It allocates the memory for the spaces and sets all of them to their
      // relevant types. Spaces are accessed via an array.
      map(unsigned int s);
      
      // Destructor frees up the memory
      ~map (){
        delete[] spaces;
      }

      //This acesses the coordinates on the map using numerical cartesian coords
      space* index(const int x, const int y) const;
      space* index(const Coords coords) const;

    
      bool MaybeGetIndex(space &aSpace, const int x, const int y) const;

      // This is a more human readable accessor. Allows to pick coords out like: map('a',1)
      space * operator()(const char x, const int i) const;

      // Updates the map to set the player location
      void update(const Player &p1); 

      bool HasNormalSpaceAt(const Coords coords) const; 
      bool HasPitfallAt(const Coords coords) const; 
      bool HasItemSpaceAt(const Coords coords) const; 
      bool HasSafeSpaceAt(const Coords coords) const;

      int getSize() const { return size; }
      int getSide() const { return side; }

      //Overload the insertion operator to print like a matrix
      friend std::ostream & operator<<(std::ostream &disp, const map &mp);

  };

}

#endif
