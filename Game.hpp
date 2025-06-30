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
    void playPerkCard(Hero* , std::string);
    void ChoosePerkCard(Hero*) ;
    void getNewCard(Hero*) ;
    void locationOverview() ;

    void monster_phase();
    void send_hero_to_hospital(Hero* );
    void remove_villager(villager* );

    bool both_monsters_defeated();

    void distribute_initial_items();
};
