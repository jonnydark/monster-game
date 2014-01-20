#ifndef GAME_H

#define GAME_H


#include "player.h"
#include "monster.h"
#include "map/map.h"

class Game {
  public:
    Game(const unsigned int size);
    ~Game () {}

    void Start();
    void HandleGameOver();

  private:
    void GameLoop();
    void action();
    void CheckCurrentSpace();
    void CheckSurroundingSpaces();
    void KillPlayerByPitfall();
    void GivePlayerNewItem();
    void battle();

    unsigned int     _mapSize;
    unsigned int     _timeBombTime;
    bool             _isPlaying;

    dungeon_map::map _map;
    player           _player;
    monster          _monster;
};


#endif /* end of include guard: GAME_H */
