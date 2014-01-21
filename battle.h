#ifndef BATTLE_H

#define BATTLE_H

class Game;
class Player;
class Monster;


class BattleGround {
  public:
    void Start(Game& currentGame);


  private:
    void DisplayHealthBarsAndOptions(Player&, Monster&);
    void PlayerTurn(Game& currentGame);
    void MonsterTurn(Game& currentGame);
    bool Fight(Game& currentGame);
    void CheckBackpack(Game& currentGame);
    void RunAway(Game& currentGame);

    bool _escape;
};



#endif /* end of include guard: BATTLE_H */
