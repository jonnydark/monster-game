/*
 * The ruler is a useless item. It's here for comic effect only.
 * It's here as a reference to the game Earthbound
 */

#ifndef RULER_H
#define RULER_H

namespace items
{

  class ruler : public item
  {
    public:
      // Constructor
      ruler() {
        name = "Ruler";
        info = "        Plastic Ruler\n"
               "    =====================\n"
               "       Rulers have been used for thousands of years to ascertain the length\n"
               "    of various objects. Rulers made of ivory were in use by the Indus Valley\n"
               "    Civilization prior to 1500BC. This one is made of clear shatter-proof\n"
               "    plastic. How lucky you are to have found it in a place like this!\n\n"
               "    \tDamage: ??? \tUses: Inf.\n\n"
               "------------------------------------------------------------------------------\n\n";
        uses = -1;
      }

      // Destructor
      ~ruler() {}

      void useMap(player &p) {
        std::cout << "\n\tYou sized up the situation!!\n\n";
      }

      // Battle usage is identical to out of battle use
      void use(player &p, monster &m) {
        useMap(p);
      }
  };
}
#endif
