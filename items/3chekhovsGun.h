/*
 * Chekhov's Gun is an item that can only be used as a finishing move to kill the monster.
 * Any attempt to use it earlier than this will fail.
 */

#ifndef CHEKHOV_H
#define CHEKHOV_H

namespace items
{

  class chekhovsGun : public items::item
  {
    // No need for additional private data 

    public:
      // Constructor
      chekhovsGun() {
        name = "Chekhov's Gun";
        info = "        Chekhov's Gun\n"
               "    =====================\n"
               "       This is a rather nice antique rifle, though it hasn't been kept in\n"
               "    particularly good nick. It's all rusted and looks like it would probably\n"
               "    jam if you tried to use it. You can make out inscription on the butt of\n"
               "    the gun. \"One must not put a loaded rifle on the stage if no one is\n"
               "    thinking of firing it.\" - Anton Chekhov. There seems to be only one\n"
               "    round loaded in the rifle. Mysterious...\n\n"
               "    \tDamage: 60 \tUses: 1\n\n"
               "------------------------------------------------------------------------------\n\n";
        uses = 1;
      }

      // Destructor
      ~chekhovsGun() {}

      // Battle usage!
      void use(Player &p, monster &m) {
        std::cout << "\n\tYou readied the rifle, took aim and pulled the trigger.\n";
        // If the monster is near death use the item and kill it
        if(m.hp() <= 60) {
          m.kill();
          std::cout << "\tThe rifle fired sending a round flying in to the skull of the\n"
                    << "\tmonster, killing it. The battle was won, and as you looked down\n"
                    << "\ton the motionless body of your slain foe, you breathed a sigh of\n"
                    << "\trelief before leaving the dungeon to greet a brighter tomorrow...\n\n";
          uses--;
        } else {
          std::cout << "\tBut the rifle jammed! In your gut, you knew the time just wasn't\n"
                    << "\tright to fire the rifle\n\n";
        }
      }

      // Map usage
      void useMap(Player &p) {
        std::cout << "\n\tYou readied the rifle and took aim. However, the time just didn't\n"
                  << "\tseem right to pull the trigger. What were you aiming at anyway?\n\n";
      }

  };

}
#endif
