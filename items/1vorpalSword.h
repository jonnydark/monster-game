/*
 * The vorpal sword is a simple attack boost item - 
 * it has no out of battle effects other than an easter
 * egg involving Indiana Jones. It goes snicker snack!
 */

#ifndef VORPAL_H
#define VORPAL_H

namespace items
{

  class vorpalSword : public item
  {
    private:
    // This is for an easter egg. If you use the sword too much, Indiana Jones comes and shoots you
    int used;

    public:
      // Constructor
      vorpalSword() {
        name = "Vorpal Sword";
        info = "        The Legendary Vorpal Sword\n"
               "    ==================================\n"
               "       Rumour has it this sword was used to slay the mighty Jabberwock - a\n"
               "    dangerous monster with jaws that bite and claws that catch. The blade\n"
               "    is also famous for its characteristic 'snicker-snack' which makes it\n"
               "    the perfect weapon for any adventurer who might find himself (or herself)\n"
               "    assaulted by a beast whiffling through the tulgy wood\n\n"
               "    \tDamage: 30 \tUses: Inf.\n\n"
               "------------------------------------------------------------------------------\n\n";
        uses = -1;
        used = 0;
      }
      
      ~vorpalSword() {}

      // This will also do something later
      void use(Player &p, Monster &m) {
        // Print different message if this is the final blow
        if(m.hp() <= 30) {
          std::cout << "\n\n\tOne, two! One, two! and through and through\n"
                    << "\tThe Vorpal blade went snicker-snack!\n"
                    << "\tYou left it dead, and with its head\n"
                    << "\tYou went galumphing back\n\n";
        } else {
          std::cout << "\n\tThe Vorpal blade went snicker-snack!\n";
        }
        m.hitOrHeal(-30);
      }

      void useMap(Player &p) {
        if(used < 3) {
          std::cout << "\n\tYou swung the Vorpal Sword around.\n"
                    << "\tHey, you remember that guy from the first Indiana Jones film with the\n"
                    << "\tsword? The one who was spinning it around? And you remember what\n"
                    << "\thappened to him? Yeah, you probably want to stop doing that...\n\n";
          used++;
        }
        if(used == 3) {
          std::cout << "\n\tYou swung the Vorpal Sword around.\n"
                    << "\tSuddenly, out of nowhere, Indiana Jones appeared and shot you.\n" 
                    << "\tLook at that. You're now dead. Don't say I didn't warn you.\n\n";
          p.kill();
        }
      }

  };

}

#endif
