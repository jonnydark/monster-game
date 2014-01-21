/*
 * map.cpp
 *
 * This file contains the class declarations for the map
 * iostream and sstream already included in space
 */

#include <cstdlib>

#include "map.h"
#include "player.h" 


char alphabet[] = "ABCDEFGHIJ";

using namespace std;

namespace dungeon_map
{

  // Map constructor
  map::map(unsigned int s) {
    if(s > 3 && s < 11) {
      //Make the map
      //set the variables at gobal scope
      side = s;
      size = side*side;
      spaces = new space[size];

      //make the pitfalls;
      for(int i=0; i<side-3; i++) {
        // Get the address of a random space, if it isn't already a pitfall, convert it
        space * randomSpace = &spaces[rand() % (size + 1)];
        if(randomSpace->IsNormalSpace()) {
          randomSpace->setType(Pitfall);
          continue;
        }
        --i;
      }

      //make the item spaces
      for(int i=0; i<side-2; i++) {
       // Get the address of a random space, if it isn't already a pitfall or item space convert it 
       space * randomSpace = &spaces[rand() % (size + 1)];
       if(randomSpace->IsNormalSpace()) {
         randomSpace->setItemID(IntToItemId(i)); // i+1 as item 0 is fists and you get that by default
         // randomSpace->mark(); // uncomment only in need of debugging
         continue;
       }
       i--;
      }


    } else {
      cerr << "Error, please select a number between 4 and 10";
    }
  }

  items::ItemID map::IntToItemId(const unsigned int i) {
    items::ItemID array[] = { items::VorpalSword, items::RareCandy, items::CheckovsGun, items::Ruler, 
      items::Shoryuken, items::InfiniteImprobabilityDrive, items::TimeBomb, items::InfiniteImprobabilityDrive };
    return array[i];
  }

  //This acesses the coordinates on the map in a more human readable fashion
  space * map::index(const int x, const int y) const {
    //size will be changed to rows if I choose to make rectangular maps possible
    int loc = (y-1) + (x-1)*side;  
    return &spaces[loc];
  }

  bool map::MaybeGetIndex(space &aSpace, const int x, const int y) const {
    if(x > 0 && y > 0 && x <= side && y<= side) {
      aSpace = *index(x,y); 
      return true;
    }
    return false;
  }



  // This is a more human readable accessor. Allows to pick coords out like: index(a,1)
  space * map::operator()(const char x, const int i) const{
    // convert char to int
    char lowAlphabet[] = "abcdefghij"; // Allow the player to use lowercase
    int j = -1;
    for(int n=0; n<10; n++) {
      if(x == alphabet[n] || x == lowAlphabet[n]) {
        j = n+1;
        break;
      }
    }
    if(j > 0) {
      return index(i,j);
    }
    cerr << "That space doesn't exist! I'm going to assume you meant space A,1\n";
    return &spaces[0];
  }
    


  // Updates the map to set the player location
  void map::update(const player &p1) {
    // Cycles through all the data points 
    // - if the point is marked, then set it as ! if not set it as x
    for(int i=0; i<size; i++) {
      if((&spaces[i])->isMarked()) {
        (&spaces[i])->set('!');
      } else {
        (&spaces[i])->set(' ');
      }
    // Finally, set the position to O
    index(p1.x(), p1.y())->set('O'); 
    }
  }

  bool map::HasNormalSpaceAt(const Coords coords) const {
    space spaceToCheck;
    if(MaybeGetIndex(spaceToCheck, coords.x, coords.y)) {
      return spaceToCheck.IsNormalSpace(); 
    }
    return false;
  }

  bool map::HasPitfallAt(const Coords coords) const {
    space spaceToCheck;
    if(MaybeGetIndex(spaceToCheck, coords.x, coords.y)) {
      return spaceToCheck.IsPitfall();
    }
    return false;
  }

  bool map::HasItemSpaceAt(const Coords coords) const {
    space spaceToCheck;
    if(MaybeGetIndex(spaceToCheck, coords.x, coords.y)) {
      return spaceToCheck.IsItemSpace();
    }
    return false;
  }

  bool map::HasSafeSpaceAt(const Coords coords) const {
    return HasItemSpaceAt(coords) || HasNormalSpaceAt(coords);
  }


  //Insertion operator for map
  //always update the map before drawing it
  ostream & operator<<(ostream &disp, const map &mp) {
    //set the numbers at the top
    disp << "\t\t   ";
    for(int x=1;x<=mp.getSide();x++) {
      disp << " " << x << "  ";
    }
    disp << "\n";
    
    for(int j=1;j<=mp.getSide();j++) { 
      // set the letters at the left side using ::alphabet
      disp << "\t\t" << alphabet[j-1] << "  ";
      for(int i=1;i<=mp.getSide();i++) {
        disp << "[" << *mp.index(i,j) << "] ";
      }
      disp << "\n";
    }
    return disp;
  }

}
