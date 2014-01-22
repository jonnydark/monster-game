#ifndef GAME_H

#define GAME_H

#include <string>
#include "player.h"
#include "monster.h"
#include "battle.h"
#include "map.h"


class Game {
  public:
    Game(const unsigned int size);
    ~Game () {}

    void Start();
    void HandleGameOver();
    static unsigned int _timeBombTime;

  private:
    void GameLoop();
    void action();
    void ParseCoordinatesAndMarkMap(std::string input);
    void StartInventoryMenu();
    void UseItemOutOfBattle(bool &valid);
    void QuitDialogue();
    void CheckCurrentSpace();
    void CheckSurroundingSpaces();
    void KillPlayerByPitfall();
    void GivePlayerNewItem();
    void battle();

    unsigned int     _mapSize;
    bool             _isPlaying;

    dungeon_map::map _map;
    Player           _player;
    Monster          _monster;
    BattleGround     _battleGround;

    friend class BattleGround;
};


#endif /* end of include guard: GAME_H */
