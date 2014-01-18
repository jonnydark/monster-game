/*
 * The Rare Candy sets health back to to maximum
 */

#ifndef RARECANDY_H
#define RARECANDY_H

namespace items
{

  class rareCandy : public items::item
  {

    public:
      // constructor
      rareCandy() {
        name = "Rare Candy";
        info = "        Kantan Rare Candy\n"
               "    =========================\n"
               "       This confectionary used to be produced in Kanto region primarily\n"
               "    for Pokemon, however the recipe has been lost for generations and these\n"
               "    candies are now very rare. This item can be used to restore your health\n"
               "    back to maximum. It is remarkably delicious. Side effects might involve\n"
               "    hallucination and paranoia\n\n\t\tUses: 1\n\n"
               "-----------------------------------------------------------------------------\n\n";
        uses = 1;
        }
      
      ~rareCandy(){}

      // use does the same thing as useMap
      void use(player &p, monster &m) {
        useMap(p);
      }

      // Heal the player to maximum
      void useMap(player &p) {
        std::cout << "\n\tRecovered " << 100-p.hp() << " health\n"
             << "\tHowever, you can't shake the feeling this isn't what rare\n"
             << "\tcandies are supposed to do. Is the game developer trying to\n"
             << "\tsabotage you?...\n\n";
        p.hitOrHeal((100-p.hp()));
        uses = 0;
      }
  };

}

#endif
             
