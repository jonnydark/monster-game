#ifndef BATTLE_H

#define BATTLE_H

class Player;
class monster;
namespace dungeon_map {
  class map;
}


class BattleGround {
  public:
    BattleGround (const dungeon_map::map& gameMap);
    ~BattleGround () {}

    void Start(Player& player, monster& theMonster);


  private:
    const dungeon_map::map* _dungeonMap;
};



#endif /* end of include guard: BATTLE_H */
