/*
 * player. h 
 *
 * Class to describe the player character. Class inherits from character class from 
 * charBase.h
 * Inherited values:
 *   int health, xPos, yPos - all self explanatory
 *   bool alive - true if alive, false if dead
 *
 * x() and y() are location accessors
 * hp() is the health acessor
 * kill() sets alive to false
 * dead() returns the opposite of alive (is the character dead?)
 */


#ifndef PLAYER_H
#define PLAYER_H

#include "charBase.h"
#include "items/item.h"
#include "items/0fists.h"

#include <vector>

class player : public charBase::character
{
  private:
    // The inventory is a vector of base class pointers
    std::vector<items::item*> inventory;                  

  public:
    // Constructor inherits from character base.
    // Takes two integers to define place. 
    // Health is set to 100 - might make this variable
    // Constructor also prints a delightful welcome message
    player(dungeon_map::map &mp) : character(mp, mp.getSide(), 100) { 
      std::cout << "\n\n   You find yourself in the dark dungeon. It's impossible to see more than\n"
                << "a few metres in here! Luckily you brought with you an iPhone which has \n"
                << "an app for just such an occasion. You have a look at the map.\"O\" marks\n"
                << "your current location. You can bring this up at any time by typing \"map\"\n"
                << "Apparently, there is a monster in this dungeon and it's up to you to go kill it.\n"
                << "Why, you ask? Who knows, the producers spent all the money on your iPhone and\n"
                << "didn't have enough left over for a decent plot, so you'll just have to make do.\n\n"
                << "Type 'help' at any time to bring up the controls\n";

      // Put the default fists item in there
      inventory.push_back(new items::fists);
    }
   
    // Destructor - will need to delete the vector of items
    ~player();

    // Movement commands - these change the values of xPos and yPos
    // These take the character n, w, s, e for north west south east respectively
    // It relies on values for 'side' and 'size' of the map which are accessible globally
    // Comical error messages are printed if the player tries to move off map
    // Defaults to waiting
    void move(char d, dungeon_map::map &m);

   // Accessor for the inventory 
    items::item * select(unsigned int i) const;
    
   // Prints all the currently in the player's inventory with numbers associated to them
   void printInventory();

   // Returns the size of the inventory
   int invSize() const { return inventory.size(); }

   // This function adds an item to the player's inventory. It is called when the player
   // stands on an item space. All items have an ID associated with them. The ID provided
   // as an argument determines what item gets added
   // 1 - vorpalSword
   // 2 - rareCandy
   // 3 - chekhovsGun 
   // 4 - ruler
   // 5 - shoryuken
   // 6 - iiDrive
   // 7 - timeBomb
   void getItem(unsigned int itemID);
};

#endif
