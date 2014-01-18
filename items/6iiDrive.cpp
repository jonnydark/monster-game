/*
 * Function definitions for the Infinite Improbability Drive
 * Placed in here because functions are too long to be inlined
 */


#include "item.h"
#include "6iiDrive.h"
#include "../player.h"
#include "../monster.h"

#include <cstdlib>


using namespace std;
using namespace items; 

void iiDrive::useMap(player &p) {
  cout << "\n\tYou withdrew The Infinite Improbability Drive from your bag. It started\n"
       << "\tto glow quite ominously. Then, all of a sudden, ";
  int n = rand() % 3;
  switch(n) {
    // Heal
    case 0:
      cout << "the drive vanished and\n"
           << "\tin your mouth appeared the perfect mouthful of tea. Surprising as it was\n"
           << "\tit was just what you needed. You recovered 50 points of health.\n\n";
      if(p.hp() < 50) {
        p.hitOrHeal(50);
      } else {
        p.hitOrHeal(100-p.hp());
      }
      uses--;
      break;
    // Do nothing
    case 1:
      cout << "it stopped glowing.\n"
           << "\tHow...disappointing...\n\n";
      break;
      // Self destruct
    case 2:
      cout << "it turned in to a ball\n"
           << "\tof string and spontaneously combusted. How helpful...\n\n";
      uses--;
      break;
  }
}



// In battle function
void iiDrive::use(player &p, monster &m) {
  cout << "\n\tYou withdrew The Infinite Improbability Drive from your bag. It started\n"
       << "\tto glow quite ominously. Then, all of a sudden, ";
  int n = rand() % 10;
  switch(n) {
    // Heal 33% chance
    case 0:
    case 1:
    case 2:
      cout << "the drive vanished and\n"
           << "\tin your mouth appeared the perfect mouthful of tea. Surprising as it was\n"
           << "\tit was just what you needed. You recovered 50 points of health.\n\n";
      if(p.hp() < 50) {
        p.hitOrHeal(50);
      } else {
        p.hitOrHeal(100-p.hp());
      }
      uses--;
      break;
    // Self destruct 20% chance
    case 3:
    case 4:
      cout << "the drive turned in to\n"
           << "\tthe ghost of Douglas Adams, who then proceeded to scold the game developer\n"
           << "\tfor relying too heavily on references to pop culture and not being original\n"
           << "\tenough in his writing\n...SPOOKY!\n\n";
      uses--;
      break;
    // One-hit K.O 10% chance
    case 5:
      cout << "the drive imploded in to a\n"
           << "miniature black whole that began to engulf the monster. Before the monster\n"
           << "passed the event horizon you were able to hear its final words:\n\n"
           << "\t\t\"BLACK HOLES SUUUUCK!!\"\n\n"
           << "\tA statement which at this very moment is causing physicists around the world\n"
           << "\tto hang their heads in exasperation. However, you care little for these\n"
           << "\ttrivialities. The deed was done and soon the black hole would evaporate via\n"
           << "\tHawking radiation. The monster would trouble you no more.\n\n";
      m.kill();
      uses--;
      break;
     // Do nothing 40% chance
    default:
      cout << "teleported right back in\n"
           << "\tto your bag again. That was odd...\n\n";
      break;
  }
}

