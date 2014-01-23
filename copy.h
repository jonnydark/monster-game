#ifndef COPY_H

#define COPY_H

class Print 
{
  public:
    static void AsciiArtTitle() {
      std::cout << "\n\n\n";
      std::cout << "\t###    #    #   ##   ###  ####      ##       ###   ##   #    # ####\n"
                << "\t #     ##  ##  #  #  #  # #==      #  #     #     #  #  ##  ## #==\n"
                << "\t #     # ## # ###### #  # #       ######    # *# ###### # ## # #\n"
                << "\t###    #    # #    # ###  ####    #    #     ### #    # #    # ####\n"
                << "\t===================================================================\n"
                << "\t                      WITH  A MONSTER IN IT!!\n"
                << "\t===================================================================\n\n\n\t";
    }

    static void OpeningMessage() {
      std::cout << "\n\n   You find yourself in the dark dungeon. It's impossible to see more than\n"
        << "a few metres in here! Luckily you brought with you an iPhone which has \n"
        << "an app for just such an occasion. You have a look at the map.\"O\" marks\n"
        << "your current location. You can bring this up at any time by typing \"map\"\n"
        << "Apparently, there is a monster in this dungeon and it's up to you to go kill it.\n"
        << "Why, you ask? Who knows, the producers spent all the money on your iPhone and\n"
        << "didn't have enough left over for a decent plot, so you'll just have to make do.\n\n"
        << "Type 'help' at any time to bring up the controls\n";
    }

    static void Help() {
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
    }
    
    static void DeathByPitfall() {
      std::cout << "\n\"Caution! Falling down bottomless pits is hazardous to your health and is not\""
           << "\nadvised...is what the sign would have said, had you bothered to read it."
           << "\nInstead you fell head first in to the pit." 
           << "\nNow there's some good news and some bad news:\n"
           << "\tThe good news is, the pit isn't bottomless!\n"
           << "\tThe bad news is, you still died when you hit the bottom\n";
    }

    static void InputError() {
      std::cout << "Excuse me?\n";
    }

    static void StartBattle() {
      std::cout << "\n\nOH MY GIDDY AUNT! IT'S THE MONSTER! It's very scary!\n\n\tPrepare to fight!";
    }
    
    static void MonsterHadouken() {
      std::cout << "\n\n\tThe monster turned side on to you, spread its legs for better stance\n"
              "\tand with its mighty hands concentrated a glowing blue ball of energy.\n"
              "\tThen, in one swift movement...\n\nHADOUKEN!\n\nThe monster did 30 damage."
              "\tThat hurt.\n\n";
    }
  
    static void MonsterMockery() {
      std::cout << "\n\n\tThe monster took a step back, pushed its chest out and shouted at you.\n"
              "\t\"YOU FIGHT LIKE A DAIRY FARMER!\" it said. You don't really know what it\n"
              "\tmeant by this, but far away an aging pirate by the name of Guybrush\n"
              "\tThreepwood shed a tear in mourning of his former glory and continued\n"
              "\t to drown his sorrows in grog.\n\n";
    }

    static void MonsterWhoopAss() {
      std::cout << "\n\n\tThe monster withdrew from his pocket a can not dissimelar to a \n"
              "\t coke can. You can make out the writing on the side to read \"Whoop-Ass(TM)\"\n"
              "\tThe monster opened the can with a satisfying \"tsssk\" sound, and you\n"
              "\tsustained 40 damage; it's super effective!\n\n";
    }

    static void MonsterTackle() {
      std::cout << "\n\n\tThe monster used tackle and did 10 damage\n\n";
    }

};


#endif /* end of include guard: COPY_H */

