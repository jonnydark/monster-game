#include "battle.h"
#include "game.h"
#include "copy.h"

void BattleGround::Start(Game& currentGame) {
  // Opening message
  Print::StartBattle();
  
  _escape = false;
  while(!currentGame._player.dead() && !currentGame._monster.dead() && !_escape) { 
    PlayerTurn(currentGame);
 
    //If the player didn't escape and the monster isn't dead...
    if(!_escape && !currentGame._monster.dead()) {
      MonsterTurn(currentGame);
    }
  } // End of battle loop
}

void BattleGround::DisplayHealthBarsAndOptions(Player& player, Monster& monster) {
  std::cout << "\n\tYou :    " << player.healthBar() << "\n"; 
  std::cout << "\tMonster: " << monster.healthBar() << "\n";
  std::cout << "\n\nWhat do you do?\n\t(f)ight     Check your (b)ackpack     (r)un\n>> ";
}

void BattleGround::PlayerTurn(Game& currentGame) {
  while(true) {
    DisplayHealthBarsAndOptions(currentGame._player, currentGame._monster);
    std::string in;
    getline(std::cin,in);

    if(in[0] == 'f') {
      if(Fight(currentGame)) {
        break;
      } else {
        continue;
      }
    }

    if(in[0] == 'b') {
      CheckBackpack(currentGame);
      continue;
    }

    // Run away
    if(in[0] == 'r') {
      RunAway(currentGame);
      break; // Break out of user input loop
    } 
      // Error message
      std::cout << "\n\tWhat?! This is no time for such gibberish!\n";   
  } // End of user input loop
}

bool BattleGround::Fight(Game& currentGame) {
  currentGame._player.printInventory();
  std::cout << "\n\nFight with what?: ";
  
  int i;
  std::cin >> i;
  if(!std::cin.fail() && i <= currentGame._player.invSize() && i > 0) {
    currentGame._player.select(i)->use(currentGame._player,currentGame._monster);
    std::cin.ignore();
    return true;
  } else {
    // failstate
    std::cout << "That item doesn't exist...\n\n";
    std::cin.clear();
    std::cin.ignore();
    return false;
  }
}

void BattleGround::CheckBackpack(Game& currentGame) {
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
}

void BattleGround::RunAway(Game& currentGame) {
// 80% chance of escape 
  if(rand() % 5 != 0) { 
   // Escape, random direction
    while(!_escape) {
      int direction = rand() % 4;
      switch(direction) {
        case 0:
          if(currentGame._map.HasSafeSpaceAt(currentGame._player.NorthCoords())) {
            currentGame._player.MoveNorth();
            _escape = true;
            break;
          }
        case 1:
          if(currentGame._map.HasSafeSpaceAt(currentGame._player.SouthCoords())) {
            currentGame._player.MoveSouth();
            _escape = true;
            break;
          }
        case 2:
          if(currentGame._map.HasSafeSpaceAt(currentGame._player.EastCoords())) {
            currentGame._player.MoveEast();
            _escape = true;
            break;
          }
        case 3:
          if(currentGame._map.HasSafeSpaceAt(currentGame._player.WestCoords())) {
            currentGame._player.MoveWest();
            _escape = true;
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
}

void BattleGround::MonsterTurn(Game& currentGame) {
    if(currentGame._timeBombTime != 0) {    
      HandleTimeBomb(currentGame);
      return;
    }
    // Now it's the monster's time to shine. 10% chance of running away
    std::cout << "\nThe monster's turn:";
    if(rand() % 10 != 0) {
      //The monster fights
      currentGame._monster.fight(currentGame._player);
    } else {
      MonsterRuns(currentGame);
    }
}

void BattleGround::HandleTimeBomb(Game& currentGame) {
  // if the timeBomb has been activated
  std::cout << "\n\tThe monster is frozen in time!\n";
  currentGame._timeBombTime--;

  // Tell the player if the monster is now unfrozen
  if(currentGame._timeBombTime == 0) {
    std::cout << "\n\tThe monster was released from the time-lock!\n";
  }
}

void BattleGround::MonsterRuns(Game& currentGame) {
  //Make the monster move until the player and the monster aren't
  //on the same square
  while(currentGame._player.Coords() == currentGame._monster.Coords()) {
    currentGame._monster.move(currentGame._map);
  }
  std::cout << "The monster ran!\n";
  _escape = true;
}
