/*
 * main.cpp
 *
 * This file contains the main loop and the status funcition
 * It also contains the global variable timeBombTime 
 */

#include "player.h"
#include "monster.h"
#include "input.h"
#include "game.h"

#include <cstdlib>
#include <string>
#include <ctime>

// This is the timebomb variable. When the
// time bomb is set off - this is set to three.
// monster.cpp and the battle function take care
// of the rest
int timeBombTime = 0;
/*******************/


/*
 *  This function checks if the player is dead or not and returns true
 *  or false values. If the player isn't already dead when the function
 *  is instantiated, it checks the square it landed on and prints the
 *  relevant messages. It kills the player if they landed on a pitfall.
 *  Returns true if player dead
 *  Returns false if the player is still alive
 */
bool status(player &p, monster &m, dungeon_map::map &mp) {
  // Don't want to print messages if the player died in battle already
  if(!p.dead()) {
  // What type of space did the player land on?
    switch((mp.index(p.x(), p.y()))->getType()) {
      // Regular Sapce 
      case 0: 
        //Check surrounding peices
        if(p.x() > 1) {
          // Is there a pitfall nearby?
          if((mp.index(p.x()-1, p.y()))->getType() == 1 ) {
            std::cout << "\n\t~You sense a disturbance in the force...~\n";
          }
          // Is the monster next to you?
          if(p.x()-1 == m.x() && p.y() == m.y()) {
            std::cout << "\n\t~You can sense an evil presence to the west~\n";
          }
        }
        if(p.x() < mp.getSide()) {
          if((mp.index(p.x()+1, p.y()))->getType() == 1) {
           std::cout << "\n\t~You sense a disturbance in the force...~\n";
          }
          if(p.x()+1 == m.x() && p.y() == m.y()) {
            std::cout << "\n\t~You can sense an evil presence to the east~\n";
          }
        }
        if(p.y() > 1) {
          if((mp.index(p.x(), p.y()-1))->getType() == 1 ) {
            std::cout << "\n\t~You sense a disturbance in the force...~\n";
          }
          if(p.x() == m.x() && p.y()-1 == m.y()) {
            std::cout << "\n\t~You can sense an evil presence to the north~\n";
          }
        }
        if(p.y() < mp.getSide()) {
          if((mp.index(p.x(), p.y()+1))->getType() == 1 ) {
            std::cout << "\n\t~You sense a disturbance in the force...~\n";
          }
          if(p.x() == m.x() && p.y()+1 == m.y()) {
            std::cout << "\n\t~You can sense an evil presence to the south~\n";
          }
        }
        return false;
        break;
      case 1:
        //Pitfall, kill the player
        p.kill();
        std::cout << "\n\"Caution! Falling down bottomless pits is hazardous to your health and is not\""
             << "\nadvised...is what the sign would have said, had you bothered to read it."
             << "\nInstead you fell head first in to the pit." 
             << "\nNow there's some good news and some bad news:\n"
             << "\tThe good news is, the pit isn't bottomless!\n"
             << "\tThe bad news is, you still died when you hit the bottom\n";
        return true;
        break;
      case 2:
        //Item space
        int newItem = (mp.index(p.x(), p.y()))->getItemID();

        // Pass on the item ID to the player class
        p.getItem(newItem); 
        std::cout << "\n\tYou got a " << p.select(p.invSize())->getName() << "! Awesome!\n\tCheck it out in your inventory with 'i'\n\n";
        (mp.index(p.x(), p.y()))->setType(0); // change back to normal space
        // Run status again to check for pitfalls
        status(p,m,mp); 
        return false;
        break;
    }
  }
  // If the player isn't alive, they must be dead
  return true;
}






int main()
{
  // Welcome message!
    std::cout << "\n\n\n";
    std::cout << "\t###    #    #   ##   ###  ####      ##       ###   ##   #    # ####\n"
         << "\t #     ##  ##  #  #  #  # #==      #  #     #     #  #  ##  ## #==\n"
         << "\t #     # ## # ###### #  # #       ######    # *# ###### # ## # #\n"
         << "\t###    #    # #    # ###  ####    #    #     ### #    # #    # ####\n"
         << "\t===================================================================\n"
         << "\t                      WITH  A MONSTER IN IT!!\n"
         << "\t===================================================================\n\n\n\t";

    Game currentGame(getMapSize());
    currentGame.start();
    currentGame.handleGameOver();
     return 0;
}
