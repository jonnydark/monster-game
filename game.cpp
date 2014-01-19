#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <sstream>

#include "game.h"

Game::Game(unsigned int mapSize): 
  _mapSize(mapSize),
  _timeBombTime(0),
  _isPlaying(true),
  _map(mapSize),
  _player(_map),
  _monster(_map)
{
   srand((unsigned)time(NULL));
}

void Game::start() {
  _map.update(_player);
  std::cout << "\n\n" << _map;
  mainLoop();
}

void Game::mainLoop() {
    while(!_player.dead() && !_monster.dead()) {
     
      // Check the player's status
      if(status()) {
        // Gameover if the player died from pitfall
        continue; // (Let the while loop evaluate)
      } 
      // The player's turn
      action();
      // Are the player and the monster on the same space?
      if(_player.x() == _monster.x() && _player.y() == _monster.y()) {
        battle();
        continue;
      }
      // The monster's turn
      _monster.move(_map);
      // Are the player and the monster on the same space?
      if(_player.x() == _monster.x() && _player.y() == _monster.y()) {
        battle();
      }

    }
}


/*
 * Function for controls when the player is on the map
 */
void Game::action() {
  // a marker for checking input was valid
  // This ensures that the player doesn't waste
  // turns by mistyping
  bool valid(false); 

  //start a loop
  while(!valid) {
    //get an input
    std::string in;
    // Print a symbol to associate with asking for input
    std::cout << std::endl << ">>  ";
    getline(std::cin, in);


    // Help function
    if(in.compare("help") == 0) {
      // print the help
      std::cout << "\n\n    Help\n"
           << "============\n"
           << "You have found yourself in a square dungeon full of sqaure rooms. There is\n"
           << "also a monster in the dungeon - kill the monster and you win. If you die,\n"
           << "you lose. Simples. You move around like so:\n\n"
           << "Controls:\n\n"
           << "'north' or 'n'  - move north\n"
           << "'south' or 's'  - move south\n"
           << "'west'  or 'w'  - move west\n"
           << "'east'  or 'e'  - move east\n"
           << "'wait'          - stand still for a bit\n\n"
           << "You can bring the map up at any time by typing 'map'\n\n"
           << "There are pitfalls, in this dungeon by the way. If you fall down those, you\n"
           << "die. However your jedi training has given you an ability to know when they\n"
           << "are near. If you suspect a space of being a pitfall you can set a marker to\n"
           << "remind you by typing 'mark' followed by the coordinates. e.g. 'mark a4'\n\n"
           << "You can remove the markers again by typing 'unmark' followed by the coordinates\n\n"
           << "When you confront the monster you'll enter battle, upon which you'll take it in\n"
           << "turns to fight eachother. In battle, your health is displayed every turn, but \n"
           << "you can find out what it is outside of battle any time by typing 'health'\n\n"
           << "There are also items scattered around the dungeon to help you. Type 'i' to find\n"
           << "out what they do and 'u' to use them when out of battle.\n"
           << "To quit the game type 'q'"
           << "\nThe rest you'll have to work out for yourself\n\n\n";
      continue;
    }

    
    // Map related functions
    if(in.compare("map") == 0) {
      _map.update(_player);
      std::cout << _map;
      // Don't want the monster to move if they're just checking the map
      continue;
    }
   

    // Setting and unsetting markers
    // This first if statement will be true for both mark and unmark commands
    if(in.find("mark")!=std::string::npos) {
      // Find the first whitespace char
      unsigned int ws(in.find(' ' , 1));
      if(ws == std::string::npos) {
        std::cout << "No, you're doing it wrong - you're meant to say something like \"mark A4\"\n";
        continue;
        }
      
      // Extract coordinates after first whitespace char and get the letter and number
      char let;
      int num;
      std::stringstream coords(std::stringstream::in|std::stringstream::out);
      coords << in.substr(ws,4); 
      coords >> let;
      coords >> num;
      coords.str("");

      // Check if the input was unmark or mark
      if(in.find("unmark")!=std::string::npos){
        std::cout << "Removing the marker at " << let << num << "\n";
        _map(let,num)->unmark();
      } else {
        std::cout << "Setting marker at " << let << num << "\n";
        _map(let,num)->mark(); 
      }
      _map.update(_player);
      std::cout << _map;
      continue;
    }
   


    // let the player be able to find out their health
    if(in.compare("health") == 0) {
      std::cout << "Health : " << _player.hp() << "/100" << "\n";
      continue;
    }


    // Movement
    switch(in[0]){
      case 'n':
        _player.move('n', _map);
        valid = true;
        break;
      case 's':
        _player.move('s', _map);
        valid = true;
        break;
      case 'e':
        _player.move('e', _map);
        valid = true;
        break;
      case 'w':
        if(in.compare("wait") !=0 ) {
          _player.move('w', _map);
	  valid = true;
          break;
        }
    }
    
    //wait 
    if(in.compare("wait")  == 0) {
      _player.move('x', _map);
      valid = true;
    }

    
    // Inventory
    if(in[0] == 'i') {
      std::cout << "\n\nInventory:\n\n";
      _player.printInventory();
      std::cout << "\n\nWhich item do you want to know about? (Select a number, anything else cancels) ";
      int i;
      std::cin >> i;
      // if fails, it wasn't a number or it was too big - cancel the info request 
      if(!std::cin.fail() && i <= _player.invSize() && i > 0) {
        // Print info
        std::cout << "\n\n" << _player.select(i)->getInfo();
      } else {
        // clear the failstate
        std::cin.clear();
      }
      std::cin.ignore(20, '\n');
      
      continue;
    }

    // Use an item out of battle
    if(in[0] == 'u') {
      std::cout << "\n\nInventory:\n\n";
      _player.printInventory();
      std::cout << "\n\nWhich item do you want to use? (Select a number, anything else cancels) ";
      int i;
      std::cin >> i;
      // Works as above
      if(!std::cin.fail() && i <= _player.invSize() && i > 0) {
        // Call the use function for use on the map
        _player.select(i)->useMap(_player);
        valid = true;
      } else {
        std::cin.clear();
      }
      std::cin.ignore(20, '\n');
      break;
    }


    // Quit
    if(in[0] == 'q') {
      std::cout << "\nAre you sure you want to quit? (y/n): ";
      std::string ans;
      while(true) {
        std::cin >> ans;
        if(ans[0] == 'y') {
          std::cout << "\nSee ya later!\n\n";
          exit(0); // Possibly replace this with a gameOver function
        } else if(ans[0] == 'n') {
          std::cout << "\nYeah! Game On!\n";
          break;
        }
        std::cout << "\n...Pardon? Do you want to quit? (y/n): ";
      }
      continue;
    }

    
    if(valid) {
      break;
    }
    std::cout << "Excuse me?\n";
  }
}


/*
 *  This function checks if the player is dead or not and returns true
 *  or false values. If the player isn't already dead when the function
 *  is instantiated, it checks the square it landed on and prints the
 *  relevant messages. It kills the player if they landed on a pitfall.
 *  Returns true if player dead
 *  Returns false if the player is still alive
 */
bool Game::status() {
  // Don't want to print messages if the player died in battle already
  if(!_player.dead()) {
  // What type of space did the player land on?
    switch((_map.index(_player.x(), _player.y()))->getType()) {
      case dungeon_map::NormalSpace:
        //Check surrounding peices
        CheckSurroundingSpaces();
        return false;
        break;
      case dungeon_map::Pitfall:
        _player.kill();
        std::cout << "\n\"Caution! Falling down bottomless pits is hazardous to your health and is not\""
             << "\nadvised...is what the sign would have said, had you bothered to read it."
             << "\nInstead you fell head first in to the pit." 
             << "\nNow there's some good news and some bad news:\n"
             << "\tThe good news is, the pit isn't bottomless!\n"
             << "\tThe bad news is, you still died when you hit the bottom\n";
        return true;
        break;
      case dungeon_map::ItemSpace:
        //Item space
        int newItem = (_map.index(_player.x(), _player.y()))->getItemID();

        // Pass on the item ID to the player class
        _player.getItem(newItem); 
        std::cout << "\n\tYou got a " << _player.select(_player.invSize())->getName() << "! Awesome!\n\tCheck it out in your inventory with 'i'\n\n";
        (_map.index(_player.x(), _player.y()))->setType(dungeon_map::NormalSpace); // change back to normal space
        // Run status again to check for pitfalls
        status();
        return false;
        break;
    }
  }
  // If the player isn't alive, they must be dead
  return true;
}

/*
 * Battle Function
 */
void Game::battle() {
  // Opening message
  std::cout << "\n\nOH MY GIDDY AUNT! IT'S THE MONSTER! It's very scary!\n\n\tPrepare to fight!";

    // Time to battle
  // Loop while the monster and the player aren't dead and
  // nobody has escaped
  bool escape(false);
  while(!_player.dead() && !_monster.dead() && !escape) { 
   
    // Get the char input and start the player's turn
    while(true) {
      std::cout << "\n\tYou :    " << _player.healthBar() << "\n"; 
      std::cout << "\tMonster: " << _monster.healthBar() << "\n";
      std::cout << "\n\nWhat do you do?\n\t(f)ight     Check your (b)ackpack     (r)un\n>> ";
      std::string in;
      getline(std::cin,in);

      // If the first letter is f, show the item list and ask for a number
      // Use the item associated with that number
      if(in[0] == 'f') {
          _player.printInventory();
          std::cout << "\n\nFight with what?: ";
          
          int i;
          std::cin >> i;
          if(!std::cin.fail() && i <= _player.invSize() && i > 0) {
            _player.select(i)->use(_player,_monster);
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
        _player.printInventory();
        std::cout << "\n\nSelect the item you want to look at: ";

        int i;
        std::cin >> i;
        // if fails, it wasn't a number or it was too big - cancel the info request 
        if(!std::cin.fail() && i <= _player.invSize() && i > 0) {
          std::cout << "\n" << _player.select(i)->getInfo();
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
            int dir = rand() % 4;
            switch(dir) {
              case 0:
                if(_player.y() > 1 && _map.index(_player.x(), _player.y()-1)->getType() != 1) {
                  _player.move('n', _map);
                  escape = true;
                  break;
                }
              case 1:
                if(_player.y() < _map.getSide() && _map.index(_player.x(), _player.y()+1)->getType() != 1) {
                  _player.move('s', _map);
                  escape = true;
                  break;
                }
              case 2:
                if(_player.x() < _map.getSide() && _map.index(_player.x()+1, _player.y())->getType() != 1) {
                  _player.move('e', _map);
                  escape = true;
                  break;
                }
              case 3:
                if(_player.x() > 1 && _map.index(_player.x()-1, _player.y())->getType() != 1) {
                  _player.move('w', _map);
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
    if(!escape && !_monster.dead()) {
      //If the timeBomb hasn't been activated

      if(_timeBombTime == 0) {    

      // Now it's the monster's time to shine. 10% chance of running away
        std::cout << "\nThe monster's turn:";
        if(rand() % 10 != 0) {
          //The monster fights
          _monster.fight(_player);
          } else {
          //Make the monster move until the player and the monster aren't
          //on the same square
          while(_player.x() == _monster.x() && _player.y() == _monster.y()) {
            _monster.move(_map);
          }
          std::cout << "The monster ran!\n";
          escape = true;
        }

      } else { 
        // if the timeBomb has been activated
        std::cout << "\n\tThe monster is frozen in time!\n";
        _timeBombTime--;

        // Tell the player if the monster is now unfrozen
        if(_timeBombTime == 0) {
          std::cout << "\n\tThe monster was released from the time-lock!\n";
        }
      }
    }
  } // End of battle loop
} 

void Game::handleGameOver() {
    // Did the player die?
    if(_player.dead()) {
      std::cout << "\n\nIt seems you died. Man, that sucks.\nHere's a hint: you can do better\n\n";
    }
    else if(_monster.dead()) {
      std::cout << "\n\nYou defeated the monster! Congratulations!\nYou're the best kind of person :)\n\n";
    }

    std::cout << "\t\t~GAME OVER~\n\n"
         << "\n\nDo you want to play again? (y/n): ";
    std::string ans;
    while(true) {
      getline(std::cin, ans);
      if(ans[0] == 'y') {
       _isPlaying = true;
       break;
      } else if (ans[0] == 'n') {
        _isPlaying = false;
        break;
      } else {
        // Ask again if it fails
        std::cout << "\nPardon?\n\nPlay again? (y/n): ";
      }
    }
    if(_isPlaying) {
      start();
    }
}

void Game::CheckSurroundingSpaces() {
  dungeon_map::Coords westOfPlayer = { _player.x()-1, _player.y() };
  dungeon_map::Coords eastOfPlayer = { _player.x()+1, _player.y() };
  dungeon_map::Coords northOfPlayer = { _player.x(), _player.y()-1 };
  dungeon_map::Coords southOfPlayer = { _player.x(), _player.y()+1 };

  if(_map.HasPitfallAt(westOfPlayer) || _map.HasPitfallAt(eastOfPlayer)
      || _map.HasPitfallAt(northOfPlayer) || _map.HasPitfallAt(southOfPlayer)) {
      std::cout << "\n\t~You sense a disturbance in the force...~\n";
  }
  if(westOfPlayer.x == _monster.x() && westOfPlayer.y == _monster.y()) {
    std::cout << "\n\t~You can sense an evil presence to the west~\n";
  }
  if(eastOfPlayer.x == _monster.x() && eastOfPlayer.y == _monster.y()) {
    std::cout << "\n\t~You can sense an evil presence to the east~\n";
  }
  if(northOfPlayer.x == _monster.x() && northOfPlayer.y == _monster.y()) {
    std::cout << "\n\t~You can sense an evil presence to the north~\n";
  }
  if(southOfPlayer.x == _monster.x() && southOfPlayer.y == _monster.y()) {
    std::cout << "\n\t~You can sense an evil presence to the south~\n";
  }
}
