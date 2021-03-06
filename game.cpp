#include <iostream>
#include <string>
#include <sstream>

#include "game.h"
#include "player.h"
#include "monster.h"
#include "map.h"
#include "battle.h"
#include "copy.h"
#include "item.h"

Game::Game(unsigned int mapSize): 
  _mapSize(mapSize),
  _isPlaying(true),
  _map(mapSize),
  _player(_map),
  _monster(_map)
{
}

unsigned int Game::_timeBombTime = 0;

void Game::Start() {
  _map.update(_player);
  std::cout << "\n\n" << _map;
  GameLoop();
}

void Game::GameLoop() {
    while(!_player.dead() && !_monster.dead()) {
      CheckCurrentSpace();
      if(_player.dead())
        // Gameover if the player died from pitfall
        break; 

      // The player's turn
      action();
      // Are the player and the monster on the same space?
      if(_player.Coords() == _monster.Coords()) {
        battle();
        continue;
      }
      // The monster's turn
      if(_timeBombTime == 0) {
        _monster.move(_map);
      }
      // Are the player and the monster on the same space?
      if(_player.Coords() == _monster.Coords()) {
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
      Print::Help();
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
      ParseCoordinatesAndMarkMap(in);
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
        _player.MoveNorth();
        valid = true;
        break;
      case 's':
        _player.MoveSouth();
        valid = true;
        break;
      case 'e':
        _player.MoveEast();
        valid = true;
        break;
      case 'w':
        if(in.compare("wait") !=0 ) {
          _player.MoveWest();
          valid = true;
          break;
        }
    }
    
    if(in.compare("wait")  == 0) {
      _player.Wait();
      valid = true;
    }

    // Inventory
    if(in[0] == 'i') {
      StartInventoryMenu();
      continue;
    }

    // Use an item out of battle
    if(in[0] == 'u') {
      UseItemOutOfBattle(valid);
      break;
    }

    // Quit
    if(in[0] == 'q') {
      QuitDialogue();
      continue;
    }

    if(valid) {
      break;
    }
    Print::InputError(); 
  }
}


void Game::CheckCurrentSpace() {
  // Don't want to print messages if the player died in battle already
  if(!_player.dead()) {
    if(_map.HasNormalSpaceAt(_player.Coords())) {
      CheckSurroundingSpaces();
    }
    if(_map.HasPitfallAt(_player.Coords())) {
      KillPlayerByPitfall();
    }
    if(_map.HasItemSpaceAt(_player.Coords())) {
      GivePlayerNewItem();
    }
  }
}

void Game::StartInventoryMenu() {
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
}

void Game::UseItemOutOfBattle(bool &valid) {
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
}

void Game::QuitDialogue() {
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
  std::cin.ignore(20, '\n');
}

/*
 * Battle Function
 */
void Game::battle() {
  _battleGround.Start(*this);
}

void Game::HandleGameOver() {
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
}

void Game::CheckSurroundingSpaces() {
  if(_map.HasPitfallAt(_player.NorthCoords()) 
      || _map.HasPitfallAt(_player.EastCoords())
      || _map.HasPitfallAt(_player.SouthCoords()) 
      || _map.HasPitfallAt(_player.WestCoords())) {
      std::cout << "\n\t~You sense a disturbance in the force...~\n";
  }
  if(_player.WestCoords() == _monster.Coords()) {
    std::cout << "\n\t~You can sense an evil presence to the west~\n";
  }
  if(_player.EastCoords() == _monster.Coords()) {
    std::cout << "\n\t~You can sense an evil presence to the east~\n";
  }
  if(_player.NorthCoords() == _monster.Coords()) {
    std::cout << "\n\t~You can sense an evil presence to the north~\n";
  }
  if(_player.SouthCoords() == _monster.Coords()) {
    std::cout << "\n\t~You can sense an evil presence to the south~\n";
  }
}

void Game::KillPlayerByPitfall() {
  _player.kill();
  Print::DeathByPitfall();
}

void Game::GivePlayerNewItem() {
  items::ItemID newItem = (_map.index(_player.x(), _player.y()))->getItemID();

  // Pass on the item ID to the player class
  _player.AddItemToInventory(newItem); 
  std::cout << "\n\tYou got a " << _player.select(_player.invSize())->getName() << "! Awesome!\n\tCheck it out in your inventory with 'i'\n\n";
  (_map.index(_player.Coords()))->ConvertToNormal();
  // Run CheckCurrentSpace again to check for pitfalls and such
  CheckCurrentSpace();
}


void Game::ParseCoordinatesAndMarkMap(std::string in) {
// Find the first whitespace char
  unsigned int ws(in.find(' ' , 1));
  if(ws == std::string::npos) {
    std::cout << "No, you're doing it wrong - you're meant to say something like \"mark A4\"\n";
    return;
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
}
