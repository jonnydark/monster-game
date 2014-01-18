/*
 * Your fists are the default item that you get in your inventory
 * They do nothing other than attack in battle
 */


#ifndef FISTS_H
#define FISTS_H

namespace items
{

  class fists : public items::item
  {
    private: 
    //name and info inherited

    public:
      // Constructor - sets the name and info
      fists() { 
        name = "Fists";
        info = "        Your Mighty Fists\n"
               "    =========================\n"
               "       These are your fists, you've had them for as long as you can remember.\n"
               "    You can use them to punch things and such\n\n" 
               "    \tDamage: 10\t Uses: Inf.\n\n"
               "---------------------------------------------------------------------------\n\n";
        uses = -1;
      }

      // Destructor
      ~fists() {}

      // Attack!
      void use(player &p, monster &m) {
        std::cout << "\n\tYou used your mighty fists! HI-YA!\n";
        m.hitOrHeal(-10);
      }

      // Use on the map - i.e do practically nothing
      void useMap(player &p) {
        std::cout << "\n\tYou punched the air with your mighty fists and struck a pose like \n"
                  << "\tyou were Bruce Lee. I'm not going to lie, it looked totally lame. \n"
                  << "\tDon't worry, nobody saw it. Well, nobody except for me. I saw it and\n"
                  << "\tI'm judging you, but nobody else.\n"
                  << "\tJust don't do that again.\n\n";
      }

  };
}

#endif
