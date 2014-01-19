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
