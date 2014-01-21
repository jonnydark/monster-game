/*
 * Shoryuken is a special attack that you can only use twice
 */

#ifndef SHORYUKEN_H
#define SHORYUKEN_H

namespace items
{

  class shoryuken : public item
  {
    public:
      // Constructor
      shoryuken() {
        name = "Shoryuken";
        info = "        Shoryuken\n"
               "    =================\n"
               "       Literally meaning \"Rising Dragon Fist\", the Shoryuken is a powerful\n"
               "    unarmed combat technique. The move consists of a jumping uppercut in which\n"
               "    the user spins and rockets upwards with some horizontal movement as well,\n"
               "    knocking the opponent to the ground with much damage. You found the\n"
               "    instruction manual for how to do the move in the dungeon, however it's a an\n"
               "    exhausting technique to perform. You'll probably only be able to perform it\n"
               "    twice before getting tired.\n\n"
               "    \tDamage: 40 \tUses: 2\n\n"
               "----------------------------------------------------------------------------------\n\n";
        uses = 2;
      }


      // Destructor
      ~shoryuken() {}

      void use(Player &p, monster &m) {
        std::cout << "\n\tYou clenched your fist and crouched. Then, in one swift movement, you\n"
                  << "\tdelivered a swift rising, flaming uppercut to the monster's jaw.\n\n"
                  << "\t\tSHORYUUKEN!!\n\n";
        m.hitOrHeal(-40);
        uses--;
        std::cout << "\t(" << uses << " use left)\n";
      }

      void useMap(Player &p) {
        std::cout << "\n\tYou performed an excellent shoryuken. You feel a warm sense of\n"
                  << "\tsatisfaction from doing it well. However, you stop to wonder why you\n"
                  << "\tjust did that. The monster is nowhere to be seen...\n\n";
        uses--;
      }

  };

}
#endif
