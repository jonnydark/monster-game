#include "battle.h"
#include "game.h"

void BattleGround::Start(Game& currentGame) {
  // Opening message
  std::cout << "\n\nOH MY GIDDY AUNT! IT'S THE MONSTER! It's very scary!\n\n\tPrepare to fight!";

    // Time to battle
  // Loop while the monster and the player aren't dead and
  // nobody has escaped
  bool escape(false);
  while(!currentGame._player.dead() && !currentGame._monster.dead() && !escape) { 
   
    // Get the char input and start the player's turn
    while(true) {
      std::cout << "\n\tYou :    " << currentGame._player.healthBar() << "\n"; 
      std::cout << "\tMonster: " << currentGame._monster.healthBar() << "\n";
      std::cout << "\n\nWhat do you do?\n\t(f)ight     Check your (b)ackpack     (r)un\n>> ";
      std::string in;
      getline(std::cin,in);

      // If the first letter is f, show the item list and ask for a number
      // Use the item associated with that number
      if(in[0] == 'f') {
          currentGame._player.printInventory();
          std::cout << "\n\nFight with what?: ";
          
          int i;
          std::cin >> i;
          if(!std::cin.fail() && i <= currentGame._player.invSize() && i > 0) {
            currentGame._player.select(i)->use(currentGame._player,currentGame._monster);
            std::cin.ignore();
            break;
          } else {
            // failstate
            std::cout << "That item doesn't exist...\n\n";
            std::cin.clear();
            std::cin.ignore();
            continue;
          }
        break; // End the player's turn
      }


      // If the first letter is b, show the item list and ask for a number
      // Print the info for the item associated with that number
      if(in[0] == 'b') {
        currentGame._player.printInventory();
        std::cout << "\n\nSelect the item you want to look at: ";

        int i;
        std::cin >> i;
        // if fails, it wasn't a number or it was too big - cancel the info request 
        if(!std::cin.fail() && i <= currentGame._player.invSize() && i > 0) {
          std::cout << "\n" << currentGame._player.select(i)->getInfo();
          std::cin.ignore();
        } else {
          // clear the failstate
          std::cin.clear();
          std::cin.ignore();
        }
        continue;
      }


      // Run away
      if(in[0] == 'r') {
       // 80% chance of escape 
        if(rand() % 5 != 0) { 
         // Escape, random direction
          while(!escape) {
            int direction = rand() % 4;
            switch(direction) {
              case 0:
                if(currentGame._map.HasSafeSpaceAt(currentGame._player.NorthCoords())) {
                  currentGame._player.MoveNorth();
                  escape = true;
                  break;
                }
              case 1:
                if(currentGame._map.HasSafeSpaceAt(currentGame._player.SouthCoords())) {
                  currentGame._player.MoveSouth();
                  escape = true;
                  break;
                }
              case 2:
                if(currentGame._map.HasSafeSpaceAt(currentGame._player.EastCoords())) {
                  currentGame._player.MoveEast();
                  escape = true;
                  break;
                }
              case 3:
                if(currentGame._map.HasSafeSpaceAt(currentGame._player.WestCoords())) {
                  currentGame._player.MoveWest();
                  escape = true;
                  break;
                }
              default:
                // Ask for another random number
                break;
            }
          } // End random direction escape loop
          std::cout << "\n\tGot away safely...\n";
        } else { // If they don't get a favourable random number
          std::cout << "\n\tCouldn't escape!\n";
        }
        break; // Break out of user input loop
      } 
      // Error message
      std::cout << "\n\tWhat?! This is no time for such gibberish!\n";   
    } // End of user input loop
 
    //If the player didn't escape and the monster isn't dead...
    if(!escape && !currentGame._monster.dead()) {
      //If the timeBomb hasn't been activated

      if(currentGame._timeBombTime == 0) {    

      // Now it's the monster's time to shine. 10% chance of running away
        std::cout << "\nThe monster's turn:";
        if(rand() % 10 != 0) {
          //The monster fights
          currentGame._monster.fight(currentGame._player);
          } else {
          //Make the monster move until the player and the monster aren't
          //on the same square
          while(currentGame._player.x() == currentGame._monster.x() && currentGame._player.y() == currentGame._monster.y()) {
            currentGame._monster.move(currentGame._map);
          }
          std::cout << "The monster ran!\n";
          escape = true;
        }

      } else { 
        // if the timeBomb has been activated
        std::cout << "\n\tThe monster is frozen in time!\n";
        currentGame._timeBombTime--;

        // Tell the player if the monster is now unfrozen
        if(currentGame._timeBombTime == 0) {
          std::cout << "\n\tThe monster was released from the time-lock!\n";
        }
      }
    }
  } // End of battle loop
}
