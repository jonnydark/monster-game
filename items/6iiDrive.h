/*
 * The Infinite Improbability Drive
 * This is a random chance weapon. It usually does nothing by there is a 10% chance
 * that is will create a black hole and kill the monster and a 10% chance that it'll
 * heal the player by a maximum of 50
 */

#ifndef IIDRIVE_H
#define IIDRIVE_H

namespace items
{

  class iiDrive : public item
  {
    public:
      iiDrive() {
        name = "Inf. Improb. Drive";
        info = "        The Infinite Improbability Drive\n"
               "    ========================================\n"
               "       Originally developed as part of the faster-than-light drive of the\n"
               "    starship \"Heart of Gold\", The Infinite Improbability drive is capable\n"
               "    (as its name suggests) of causing incredibly improbable phenomena to\n"
               "    occur. Use of this item will always yield unexpected results. Use with\n"
               "    caution.\n\n"
               "    \t\tUses: ???\n\n"
               "-------------------------------------------------------------------------------\n\n";
        uses = 1;
      }

      ~iiDrive() {}

      // Only three options
      // Player is healed by 50 points
      // It does nothing
      // It destroys itself
      void useMap(Player &p);

      // Same as on the map, except the self destruct is different
      // and there is also a chance that it kills the monster
      void use(Player &p, Monster &m);

  };

}

#endif
