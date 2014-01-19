#ifndef GAME_H

#define GAME_H


#include "player.h"
#include "monster.h"
#include "map/map.h"

class Game {
  public:
    Game(const unsigned int size);
    ~Game () {}

    void start();
    void handleGameOver();

  private:
    void mainLoop();
    void action();
    void CheckSurroundingSpaces();
    void KillPlayerByPitfall();
    void GivePlayerNewItem();
    void status();
    void battle();

    unsigned int     _mapSize;
    unsigned int     _timeBombTime;
    bool             _isPlaying;

    dungeon_map::map _map;
    player           _player;
    monster          _monster;
};


#endif /* end of include guard: GAME_H */
