#ifndef COPY_H

#define COPY_H

class Print 
{
  public:

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

  

};


#endif /* end of include guard: COPY_H */

