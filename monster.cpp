/*
 * monster.cpp
 *
 * Monster definitions 
 */


#include "monster.h"
#include "player.h"
#include "map/map.h"

#include <cstdlib>

using namespace std;

void Monster::MoveNorth() {
  if(yPos > 1) {
    yPos -= 1;
  }
}

void Monster::MoveSouth() {
  if(yPos < _boundry) {
    yPos += 1;
  }
}

void Monster::MoveWest() {
  if(xPos > 1) {
    xPos -= 1;
  }
}

void Monster::MoveEast() {
  if(xPos < _boundry) {
    xPos += 1;
  }
}


// Function works on a random number generator.
// The numbers are between 0 and 6. 0123 are nsew
// Numbers 456 are just waiting
// This is subject to change
void Monster::move(const dungeon_map::map &mp) {
  int n = rand() % 7;
  //if the time bomb has been used, always wait
  switch(n) {
    case 0:
      if(mp.HasSafeSpaceAt(NorthCoords())) {
        MoveNorth();
        break;
      }
    case 1:
      if(mp.HasSafeSpaceAt(SouthCoords())) {
        MoveSouth();
        break;
      }
    case 2:
      if(mp.HasSafeSpaceAt(EastCoords())) {
        MoveEast();
        break;
      }
    case 3:
      if(mp.HasSafeSpaceAt(WestCoords())) {
        MoveWest();
        break;
      }
    default:
      break;
  }
}

// Fight
void Monster::fight(Player &p) {
  // Similar score, there are four moves the monster can use at random.
  // It is weighted towards the weaker attack, naturally
  int move = rand() % 10;
  switch(move) {
    case 0:
      // Hadouken
      cout << "\n\n\tThe monster turned side on to you, spread its legs for better stance\n"
              "\tand with its mighty hands concentrated a glowing blue ball of energy.\n"
              "\tThen, in one swift movement...\n\nHADOUKEN!\n\nThe monster did 30 damage."
              "\tThat hurt.\n\n";
      p.hitOrHeal(-30);
      break;
    case 1:
      // Mockery
      cout << "\n\n\tThe monster took a step back, pushed its chest out and shouted at you.\n"
              "\t\"YOU FIGHT LIKE A DAIRY FARMER!\" it said. You don't really know what it\n"
              "\tmeant by this, but far away an aging pirate by the name of Guybrush\n"
              "\tThreepwood shed a tear in mourning of his former glory and continued\n"
              "\t to drown his sorrows in grog.\n\n";
      break;
    case 2:
      // A can of whoop-ass
      cout << "\n\n\tThe monster withdrew from his pocket a can not dissimelar to a \n"
              "\t coke can. You can make out the writing on the side to read \"Whoop-Ass(TM)\"\n"
              "\tThe monster opened the can with a satisfying \"tsssk\" sound, and you\n"
              "\tsustained 40 damage; it's super effective!\n\n";
      p.hitOrHeal(-40);
      break;
    default:
      // Tackle
      cout << "\n\n\tThe monster used tackle and did 10 damage\n\n";
      p.hitOrHeal(-10);
      break;
  }

}
