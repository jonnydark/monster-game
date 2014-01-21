/*
 * The time bomb - stops time for the monster temporarily
 * Most of this functionality is taken care of in monster.cpp
 * and by the battle function. All this item does is assign
 * a value to extern int timeBomb
 */

#ifndef TIMEBOMB_H
#define TIMEBOMB_H

extern int timeBombTime;

namespace items
{

  class timeBomb : public items::item
  {
    public:
      // Constructor
      timeBomb() {
        name = "Time Bomb";
        info = "        Time Bomb\n"
               "    =================\n"
               "       As the name suggests, this is a device that stops time for anyone\n"
               "    other than the user for a brief period of time - well, brief for you\n"
               "    at least. It's very expensive, and you only have one, so don't go wasting\n"
               "    it on some childish shenanigans. How does it work you ask? It works pretty\n"
               "    well, thanks.\n\n"
               "    \t\tUses: 1\n\n"
               "------------------------------------------------------------------------------\n\n";
        uses = 1;
      }

      // Destructor
      ~timeBomb() {}

      void useMap(Player &p) {
        std::cout << "\n\tYou activated the time bomb. A shock-wave emanated from the bomb causing all\n"
                  << "\tof time to freeze, except for you. This is pretty wizard...\n\n";
        ::timeBombTime = 3;
        uses=0;
      }

      void use(Player &p, Monster &m) {
        useMap(p);
        uses=0;
      }
  };

}

#endif
