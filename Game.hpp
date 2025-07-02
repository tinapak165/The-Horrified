#include <iostream>
#include <unordered_map>
#include "GameMap.hpp"
#include "MonsterCardDeck.hpp"
#include "TurnManager.hpp"
#include "monster.hpp"
#include "Dracula.hpp"
#include "InvisibleMan.hpp"
#include "Hero.hpp"
#include "Dice.hpp"
#include "Itembag.hpp"

class Game {
private:
    GameMap map;
    MonsterCardDeck deck;
    TurnManager turnManager;
    PerkDeck p ; 
    Perkcards p2 ;

    Hero* mayor = nullptr;
    Hero* archaeologist = nullptr;
    Dracula* dracula = nullptr;
    InvisibleMan* invisibleMan = nullptr;
    
    ItemPool pool;
    std::unordered_map<MonsterType, Monster*> monstersMap;
    int terror_Level = 0;
    bool game_over = false;
    
public:
    Game();
    ~Game();
    void test();
    void start() ;
    void choose_character();
    void hero_phase(Hero* hero);
    void play_hero_Action(Hero*);
    void playPerkCard(Hero* , std::string);
    void ChoosePerkCard(Hero*) ;
    void getNewCard(Hero*) ;
    void locationOverview() ;
    void graph_map();

    void monster_phase();
    void send_hero_to_hospital(Hero* );
    void remove_villager(villager* );
    villager* create_villager(const std::string& name, const std::string& locName);

    bool both_monsters_defeated();
    void increase_terror_level();

    void distribute_initial_items();
    const std::string reset_color = "\033[0m";
};