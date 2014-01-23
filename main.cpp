/*
 * main.cpp
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
    bool wantsToPlay = false;
    do {
      Game currentGame(getMapSize());
      currentGame.Start();
      currentGame.HandleGameOver();
      wantsToPlay = currentGame.StillWantsToPlay();
    } while(wantsToPlay);
    return 0;
}
