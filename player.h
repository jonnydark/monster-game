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
#include "item.h"

#include <vector>

class Monster;

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
    void UseOnMonster(const unsigned int itemIndex, Monster& monster);

    // Prints all the currently in the player's inventory with numbers associated to them
    void printInventory();

    // Returns the size of the inventory
    int invSize() const { return inventory.size(); }
    void AddItemToInventory(const items::ItemID newItem);

    dungeon_map::Coords NorthCoords() const;
    dungeon_map::Coords SouthCoords() const;
    dungeon_map::Coords WestCoords() const;
    dungeon_map::Coords EastCoords() const;
};

#endif
