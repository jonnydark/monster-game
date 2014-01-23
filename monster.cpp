/*
 * monster.cpp
 *
 * Monster definitions 
 */


#include "monster.h"
#include "player.h"
#include "map.h"

#include <cstdlib>

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
      Print::MonsterHadouken();
      p.hitOrHeal(-30);
      break;
    case 1:
      // Mockery
      Print::MonsterMockery();
      break;
    case 2:
      // A can of whoop-ass
      Print::MonsterWhoopAss();
      p.hitOrHeal(-40);
      break;
    default:
      // Tackle
      Print::MonsterTackle();
      p.hitOrHeal(-10);
      break;
  }

}
