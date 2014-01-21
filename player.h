/*
 * Player. h 
 *
 * Class to describe the Player character. Class inherits from character class from 
 * charBase.h
 * Inherited values:
 *   int health, xPos, yPos - all self explanatory
 *   bool alive - true if alive, false if dead
 */


#ifndef PLAYER_H
#define PLAYER_H

#include "charBase.h"
#include "items/item.h"

#include <vector>

class Player : public charBase::character
{
  private:
    // The inventory is a vector of base class pointers
    std::vector<items::item*> inventory;                  

  public:
    Player(dungeon_map::map &mp);

    // Destructor - will need to delete the vector of items
    ~Player();

    void MoveNorth();
    void MoveSouth();
    void MoveEast();
    void MoveWest();
    void Wait();

    // Accessor for the inventory 
    items::item * select(const unsigned int itemIndex) const;

    void UseItem(const unsigned int itemIndex);

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
    void AddItemToInventory(const items::ItemID newItem);

    dungeon_map::Coords NorthCoords() const;
    dungeon_map::Coords SouthCoords() const;
    dungeon_map::Coords WestCoords() const;
    dungeon_map::Coords EastCoords() const;
};

#endif
