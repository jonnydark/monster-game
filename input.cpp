/*
 * input.cpp
 *
 * And here are the definitions as laid out in input.h
 */

#include "player.h"
#include "monster.h"
#include "input.h"

#include <cstdlib>
#include <sstream>


using namespace std;
using namespace dungeon_map;

extern int timeBombTime;

/*
 * Function for controls when the player is on the map
 */
void action(player &p, dungeon_map::map &m) {
  // a marker for checking input was valid
  // This ensures that the player doesn't waste
  // turns by mistyping
  bool valid(false); 

  //start a loop
  while(!valid) {
    //get an input
    string in;
    // Print a symbol to associate with asking for input
    cout << endl << ">>  ";
    getline(cin, in);


    // Help function
    if(in.compare("help") == 0) {
      // print the help
      cout << "\n\n    Help\n"
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
      m.update(p);
      cout << m;
      // Don't want the monster to move if they're just checking the map
      continue;
    }
   

    // Setting and unsetting markers
    // This first if statement will be true for both mark and unmark commands
    if(in.find("mark")!=string::npos) {
      // Find the first whitespace char
      unsigned int ws(in.find(' ' , 1));
      if(ws == string::npos) {
        cerr << "No, you're doing it wrong - you're meant to say something like \"mark A4\"\n";
        continue;
        }
      
      // Extract coordinates after first whitespace char and get the letter and number
      char let;
      int num;
      stringstream coords(stringstream::in|stringstream::out);
      coords << in.substr(ws,4); 
      coords >> let;
      coords >> num;
      coords.str("");

      // Check if the input was unmark or mark
      if(in.find("unmark")!=string::npos){
        cout << "Removing the marker at " << let << num << endl;
        m(let,num)->unmark();
      } else {
        cout << "Setting marker at " << let << num << endl;
        m(let,num)->mark(); 
      }
      m.update(p);
      cout << m;
      continue;
    }
   


    // let the player be able to find out their health
    if(in.compare("health") == 0) {
      cout << "Health : " << p.hp() << "/100" << endl;
      continue;
    }


    // Movement
    switch(in[0]){
      case 'n':
        p.move('n', m);
        valid = true;
        break;
      case 's':
        p.move('s', m);
        valid = true;
        break;
      case 'e':
        p.move('e', m);
        valid = true;
        break;
      case 'w':
        if(in.compare("wait") !=0 ) {
          p.move('w', m);
	  valid = true;
          break;
        }
    }
    
    //wait 
    if(in.compare("wait")  == 0) {
      p.move('x', m);
      valid = true;
    }

    
    // Inventory
    if(in[0] == 'i') {
      cout << "\n\nInventory:\n\n";
      p.printInventory();
      cout << "\n\nWhich item do you want to know about? (Select a number, anything else cancels) ";
      int i;
      cin >> i;
      // if fails, it wasn't a number or it was too big - cancel the info request 
      if(!cin.fail() && i <= p.invSize() && i > 0) {
        // Print info
        cout << "\n\n" << p.select(i)->getInfo();
      } else {
        // clear the failstate
        cin.clear();
      }
      cin.ignore(20, '\n');
      
      continue;
    }

    // Use an item out of battle
    if(in[0] == 'u') {
      cout << "\n\nInventory:\n\n";
      p.printInventory();
      cout << "\n\nWhich item do you want to use? (Select a number, anything else cancels) ";
      int i;
      cin >> i;
      // Works as above
      if(!cin.fail() && i <= p.invSize() && i > 0) {
        // Call the use function for use on the map
        p.select(i)->useMap(p);
        valid = true;
      } else {
        cin.clear();
      }
      cin.ignore(20, '\n');
      break;
    }


    // Quit
    if(in[0] == 'q') {
      cout << "\nAre you sure you want to quit? (y/n): ";
      string ans;
      while(true) {
        cin >> ans;
        if(ans[0] == 'y') {
          cout << "\nSee ya later!\n\n";
          exit(0); // Possibly replace this with a gameOver function
        } else if(ans[0] == 'n') {
          cout << "\nYeah! Game On!\n";
          break;
        }
        cout << "\n...Pardon? Do you want to quit? (y/n): ";
      }
      continue;
    }

    
    if(valid) {
      break;
    }
    cout << "Excuse me?\n";
  }
}



 

/*
 * Battle Function
 */
void battle(player &p, monster &m, dungeon_map::map &mp) {
  
  
  // Opening message
  cout << "\n\nOH MY GIDDY AUNT! IT'S THE MONSTER! It's very scary!\n\n\tPrepare to fight!";

    // Time to battle
  // Loop while the monster and the player aren't dead and
  // nobody has escaped
  bool escape(false);
  while(!p.dead() && !m.dead() && !escape) { 
   
    // Get the char input and start the player's turn
    while(true) {
      cout << "\n\tYou :    " << p.healthBar() << endl; 
      cout << "\tMonster: " << m.healthBar() << endl;
      cout << "\n\nWhat do you do?\n\t(f)ight     Check your (b)ackpack     (r)un\n>> ";
      string in;
      getline(cin,in);

      // If the first letter is f, show the item list and ask for a number
      // Use the item associated with that number
      if(in[0] == 'f') {
          p.printInventory();
          cout << "\n\nFight with what?: ";
          
          int i;
          cin >> i;
          if(!cin.fail() && i <= p.invSize() && i > 0) {
            p.select(i)->use(p,m);
            cin.ignore();
            break;
          } else {
            // failstate
            cout << "That item doesn't exist...\n\n";
            cin.clear();
            cin.ignore();
            continue;
          }
        break; // End the player's turn
      }


      // If the first letter is b, show the item list and ask for a number
      // Print the info for the item associated with that number
      if(in[0] == 'b') {
        p.printInventory();
        cout << "\n\nSelect the item you want to look at: ";

        int i;
        cin >> i;
        // if fails, it wasn't a number or it was too big - cancel the info request 
        if(!cin.fail() && i <= p.invSize() && i > 0) {
            cout << endl << p.select(i)->getInfo();
            cin.ignore();
        } else {
          // clear the failstate
          cin.clear();
          cin.ignore();
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
                if(p.y() > 1 && mp.index(p.x(), p.y()-1)->getType() != 1) {
                  p.move('n', mp);
                  escape = true;
                  break;
                }
              case 1:
                if(p.y() < mp.getSide() && mp.index(p.x(), p.y()+1)->getType() != 1) {
                  p.move('s', mp);
                  escape = true;
                  break;
                }
              case 2:
                if(p.x() < mp.getSide() && mp.index(p.x()+1, p.y())->getType() != 1) {
                  p.move('e', mp);
                  escape = true;
                  break;
                }
              case 3:
                if(p.x() > 1 && mp.index(p.x()-1, p.y())->getType() != 1) {
                  p.move('w', mp);
                  escape = true;
                  break;
                }
              default:
                // Ask for another random number
                break;
            }
          } // End random direction escape loop
        cout << "\n\tGot away safely...\n";
        } else { // If they don't get a favourable random number
        cout << "\n\tCouldn't escape!\n";
        }
        break; // Break out of user input loop
      } 
      // Error message
      cout << "\n\tWhat?! This is no time for such gibberish!\n";   
    } // End of user input loop
 



    //If the player didn't escape and the monster isn't dead...
    if(!escape && !m.dead()) {
      //If the timeBomb hasn't been activated

      if(timeBombTime == 0) {    

      // Now it's the monster's time to shine. 10% chance of running away
       cout << "\nThe monster's turn:";
        if(rand() % 10 != 0) {
          //The monster fights
          m.fight(p);
          } else {
          //Make the monster move until the player and the monster aren't
          //on the same square
          while(p.x() == m.x() && p.y() == m.y()) {
            m.move(mp);
          }
          cout << "The monster ran!\n";
          escape = true;
        }

      } else { 
        // if the timeBomb has been activated
        cout << "\n\tThe monster is frozen in time!\n";
        timeBombTime--;

        // Tell the player if the monster is now unfrozen
        if(timeBombTime == 0) {
          cout << "\n\tThe monster was released from the time-lock!\n";
        }
      }
    }
  } // End of battle loop
} 


/*
 * Get map size
 */
unsigned int getMapSize() {
  cout << "To start a new game - please enter a size of a map (4-10): ";

  while(true) {
    unsigned int mapSize;
    cin >> mapSize;
    if(!cin.fail() && mapSize > 3 && mapSize <= 10) {
      cin.ignore();
      return mapSize; 
      break;
    }
    cin.clear();
    cin.ignore();
    cerr << "I don't know how to make a map that size...try again?: ";
  }
}


