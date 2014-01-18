/*
 * player.cpp
 *
 * This file contains all the definitions for the player as laid out in the protyped
 * and described in char.h
 */

#include "player.h"

// Items
#include "items/1vorpalSword.h"
#include "items/2rareCandy.h"
#include "items/3chekhovsGun.h"
#include "items/4ruler.h"
#include "items/5shoryuken.h"
#include "items/6iiDrive.h"
#include "items/7timeBomb.h"

using namespace std;
using namespace items;

// Destructor
player::~player() {
  vector<items::item*>::iterator it;
  for(it=inventory.begin(); it!=inventory.end(); ++it) {
    delete *it;
  }
}

// Directional commands
void player::move(char d, dungeon_map::map &mp) {
  switch(d) {
    case 'n':
      if(yPos > 1) {
        yPos -= 1;
        cout << "moved north";
      } else {
        cout << "\nA wise old wizard once said \"YOU SHALL NOT PASS!\" I think that advice applies here,\n there is a wall in front of you\n";
      }
      break;
    case 's':
      if(yPos < mp.getSide()) {
        yPos += 1;
        cout << "moved south";
      } else {
        cout << "\nYou just walked straight into a wall. Make an appointment at your nearest opticians,\n you may be suffering from near-sightedness\n";
      }
      break;
    case 'w':
      if(xPos > 1) {
        xPos -= 1;
        cout << "moved west";
      } else {
        cout << "\nEffects of going west can involve things appearing more delicious than they actually are,\n and disorientation. You just walked in to a wall, simmer down son.\n";
      }
      break;
    case 'e':
      if(xPos < mp.getSide()) {
        xPos += 1;
        cout << "moved east";
      } else {
        cout << "\nYeah! Fight the man! Don't let him tell you where you can and can't go! You make your own rules!\n Hit the wall harder!\n";
      }
      break;
    default:
      cout << "\nYou stood still and admired your surroundings. I wonder what the rent is on a place like this?\n";
  }
}


// Inventory Accessor
item * player::select(unsigned int i) const {
  if(i-1 <= inventory.size()) {
    return inventory[i-1];
  }
  cerr << "No such item, returning item 1\n"; // This is more for catching errors
  return inventory[0];
}


// Function to print the entire inventory
void player::printInventory() {
  int i(1);
  vector<item*>::iterator sel; // Declare an iterator sel
  for(sel = inventory.begin(); sel != inventory.end(); ++sel) {
    // if the iten has been used up, then delete it
    if((*sel)->getUses() == 0) {
     delete *sel;
      sel = inventory.erase(sel);
      --sel;
      continue;
    }
    if(i%2 == 0) {
      cout << "\t\t";
    }
    cout << "\t" <<  i << ". " << (*sel)->getName();
    if(i%2 == 0) {
      cout << endl;
    }
    i++;
  }
}


// Function to add an item to your inventory
void player::getItem(unsigned int itemID) {
  switch(itemID) {
    case 1:
      inventory.push_back(new items::vorpalSword);
      break;
    case 2:
      inventory.push_back(new items::rareCandy);
      break;
    case 3:
      inventory.push_back(new items::chekhovsGun);
      break;
    case 4:
      inventory.push_back(new items::ruler);
      break;
    case 5:
      inventory.push_back(new items::shoryuken);
      break;
    case 6:
      inventory.push_back(new items::iiDrive);
      break;
    case 7:
      inventory.push_back(new items::timeBomb);
      break;
    case 8:
      inventory.push_back(new items::iiDrive);
      break;
    default:
      cout << "\n\nThe item dissappeared in your hand...HOW MYSTERIOUS...\n"; // error msg
      break;
  }
}


