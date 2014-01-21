/*
 * player.cpp
 *
 * This file contains all the definitions for the player as laid out in the protyped
 * and described in char.h
 */

#include <vector>

#include "player.h"
#include "copy.h"

// Items
#include "0fists.h"
#include "1vorpalSword.h"
#include "2rareCandy.h"
#include "3chekhovsGun.h"
#include "4ruler.h"
#include "5shoryuken.h"
#include "6iiDrive.h"
#include "7timeBomb.h"

player::player(dungeon_map::map &mp) : character(mp, mp.getSide(), 100) { 
  Print::OpeningMessage();
  inventory.push_back(new items::fists);
}

// Destructor
player::~player() {
  std::vector<items::item*>::iterator it;
  for(it=inventory.begin(); it!=inventory.end(); ++it) {
    delete *it;
  }
}

void player::MoveNorth() {
  if(yPos > 1) {
    yPos -= 1;
    std::cout << "moved north";
  } else {
    std::cout << "\nA wise old wizard once said \"YOU SHALL NOT PASS!\" I think that advice applies here,\n there is a wall in front of you\n";
  }
}

void player::MoveSouth() {
  if(yPos < _boundry) {
    yPos += 1;
    std::cout << "moved south";
  } else {
    std::cout << "\nYou just walked straight into a wall. Make an appointment at your nearest opticians,\n you may be suffering from near-sightedness\n";
  }
}

void player::MoveWest() {
  if(xPos > 1) {
    xPos -= 1;
    std::cout << "moved west";
  } else {
    std::cout << "\nEffects of going west can involve things appearing more delicious than they actually are,\n and disorientation. You just walked in to a wall, simmer down son.\n";
  }
}

void player::MoveEast() {
  if(xPos < _boundry) {
    xPos += 1;
    std::cout << "moved east";
  } else {
    std::cout << "\nYeah! Fight the man! Don't let him tell you where you can and can't go! You make your own rules!\n Hit the wall harder!\n";
  }
}

void player::Wait() {
  std::cout << "\nYou just walked straight into a wall. Make an appointment at your nearest opticians,\n you may be suffering from near-sightedness\n";
}

// Inventory Accessor
items::item * player::select(const unsigned int index) const {
  if(index-1 <= inventory.size()) {
    return inventory[index-1];
  }
  std::cerr << "No such item, returning item 1\n"; // This is more for catching errors
  return inventory[0];
}

void player::UseItem(const unsigned int index) {
  items::item* itemToUse = select(index);
  itemToUse->useMap(*this);
}

// Function to print the entire inventory
void player::printInventory() {
  std::cout << "\n\nInventory:\n\n";
  int i(1);
  std::vector<items::item*>::iterator sel; // Declare an iterator sel
  for(sel = inventory.begin(); sel != inventory.end(); ++sel) {
    // if the iten has been used up, then delete it
    if((*sel)->getUses() == 0) {
     delete *sel;
      sel = inventory.erase(sel);
      --sel;
      continue;
    }
    if(i%2 == 0) {
      std::cout << "\t\t";
    }
    std::cout << "\t" <<  i << ". " << (*sel)->getName();
    if(i%2 == 0) {
      std::cout << std::endl;
    }
    i++;
  }
}


// Function to add an item to your inventory
void player::AddItemToInventory(const items::ItemID newItem) {
  switch(newItem) {
    case items::VorpalSword:
      inventory.push_back(new items::vorpalSword);
      break;
    case items::RareCandy:
      inventory.push_back(new items::rareCandy);
      break;
    case items::CheckovsGun:
      inventory.push_back(new items::chekhovsGun);
      break;
    case items::Ruler:
      inventory.push_back(new items::ruler);
      break;
    case items::Shoryuken:
      inventory.push_back(new items::shoryuken);
      break;
    case items::InfiniteImprobabilityDrive:
      inventory.push_back(new items::iiDrive);
      break;
    case items::TimeBomb:
      inventory.push_back(new items::timeBomb);
      break;
    default:
      std::cout << "\n\nThe item dissappeared in your hand...HOW MYSTERIOUS...\n"; // error msg
      break;
  }
}

dungeon_map::Coords player::NorthCoords() const {
  return { xPos, yPos-1 };
}

dungeon_map::Coords player::SouthCoords() const {
  return { xPos, yPos+1 };
}

dungeon_map::Coords player::WestCoords() const {
  return { xPos-1, yPos };
}

dungeon_map::Coords player::EastCoords() const {
  return { xPos+1, yPos };
}
