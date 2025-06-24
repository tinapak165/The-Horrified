#include <iostream>
#include <unordered_map>
#include "GameMap.hpp"
#include "MonsterCardDeck.hpp"
#include "TurnManager.hpp"
#include "Monster.hpp"
#include "Dracula.hpp"
//#include "InvisibleMan.hpp"
#include "Hero.hpp"
#include "Dice.hpp"
#include "Itembag.hpp"
#include "Archaeologist.hpp"
#include "Mayor.hpp"

class Game {
private:
    GameMap map;
    MonsterCardDeck deck;
    TurnManager turnManager;
    ItemPool pool;
    std::unordered_map<MonsterType, Monster*> monstersMap;
    int terrorLevel = 0;
    
public:
    Game();

    void start() ;
    void hero_phase(Hero* hero);
    void monster_phase();

    bool both_monsters_defeated();

    void distribute_initial_items();
};
