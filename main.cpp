/*
 * main.cpp
 *
 * This file contains the main loop and the status funcition
 * It also contains the global variable timeBombTime 
 */

#include <ctime>
#include <cstdlib>

#include "input.h"
#include "game.h"
#include "copy.h"


int main()
{
   srand((unsigned)time(NULL));
  // Welcome message!
    Print::AsciiArtTitle();  
    Game currentGame(getMapSize());
    currentGame.Start();
    currentGame.HandleGameOver();
     return 0;
}
