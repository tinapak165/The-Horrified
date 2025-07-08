#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <unordered_map>
#include <memory>
#include "GameMap.hpp"
#include "perkcards.hpp"
#include "MonsterCardDeck.hpp"
#include "TurnManager.hpp"
#include "monster.hpp"
#include "Dracula.hpp"
#include "InvisibleMan.hpp"
#include "Hero.hpp"
#include "Dice.hpp"
#include "Itembag.hpp"

class Game {
    friend std::ostream& operator<<(std::ostream& os, ItemColor color) ;
private:
    bool skipMonsterPhase = false ;
    GameMap map;
    MonsterCardDeck deck;
    TurnManager turnManager;
    PerkDeck PerkDeck ; 

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
    void start() ;
    void choose_character();
    void hero_phase(Hero* hero);
    void play_hero_Action(Hero*);
   // void playPerkCard(Hero* , const std::string);
    void initializaDeck() ; 
    void ChoosePerkCardANDplay(Hero*) ;
    void getNewCard(Hero*) ;
    void locationOverview() ;
    void graph_map_text();
    void monster_objectes() const;
    void return_item(const Item& item);

   

    void monster_phase();
    void send_hero_to_hospital(Hero* );
    void remove_villager(Villager* );
    Villager* create_villager(const std::string& name, const std::string& locName);

    bool both_monsters_defeated();
    void increase_terror_level();

    void distribute_initial_items();
    
};

#endif