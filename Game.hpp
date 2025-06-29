#include <iostream>
#include <unordered_map>
#include "GameMap.hpp"
#include "MonsterCardDeck.hpp"
#include "TurnManager.hpp"
#include "Monster.hpp"
#include "Dracula.hpp"
#include "InvisibleMan.hpp"
#include "Hero.hpp"
#include "monster.hpp"
#include "Dice.hpp"
#include "Itembag.hpp"

class Game {
private:

    GameMap map;
    MonsterCardDeck deck;
    TurnManager turnManager;
    ItemPool pool;

    

    Hero* mayor = nullptr;
    Hero* archaeologist = nullptr;
    Monster* dracula = nullptr;
    Monster* invisibleMan= nullptr;
    
    
    std::unordered_map<MonsterType, Monster*> monstersMap;
   
   
    int terrorLevel = 0;
   
    bool game_over = false;
    
public:
    Game();
    ~Game();
    void test();
    void start() ;

    void choose_character();
    void hero_phase(Hero* hero);
    void play_hero_Action(Hero*);
    void playPerkCard(Hero*);

    void send_hero_to_hospital(Hero* );// for hero attack
    void remove_villager(villager* );
    void monster_phase();
    void locationOverview();

    bool both_monsters_defeated();

    void distribute_initial_items();
};
