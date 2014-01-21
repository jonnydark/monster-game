/*
 * This is the item abtract base class
 * It contains the virtual functions use and useMap
 * some accessors are also included as they will always be the same
 *
 * iostream is included here purely because iostream is needed in
 * all item classes. It seemed pointless including it every time
 */

#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>

// Forward declare player class
class Player;
class Monster;

namespace items {

  enum ItemID {
    Fists,
    VorpalSword,
    RareCandy,
    CheckovsGun,
    Ruler,
    Shoryuken,
    InfiniteImprobabilityDrive,
    TimeBomb
  };


  class item 
  {
    protected:
      // Data //
      /*
       * The string 'name' is the item's name.
       *    Its accessor is getName();
       * The string 'info' contains a description of the item and its function
       *    Its accessor is 'getInfo()';
       * The integer 'uses' is the number of uses left. This number can be set
       * to decrease with the function use(Player &, monster &). If an item's
       * value for uses = 0, it will be deleted from the vector next time
       * Player::printInventory() is called. For infinite use items, the standard
       * value is -1.
       *    Its accessor is getUses();  
       */
     
      std::string name;
      std::string info; 
      int uses;

    public:
      virtual ~item() {}

      // This is the function called when the player
      // uses the item. Items always affect the monster or
      // the player and so they take those as arguments by
      // reference
      virtual void use(Player&, Monster&)=0;


      // This function is called for using the item outside
      // battle. Only works for some items - battle only items
      // print a humourous message about how it did nothing.
      virtual void useMap(Player&)=0;
     

      std::string getName() {
        return name;
      }
      
      std::string getInfo() {
        return info;
      }

      int getUses() {
        return uses;
      }
  };

}

#endif
