#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <unordered_map>
#include <memory>
#include "GameMap.hpp"
#include "perkcards.hpp"
#include "Monstercards.hpp"
#include "TurnManager.hpp"
#include "monster.hpp"
#include "Dracula.hpp"
#include "InvisibleMan.hpp"
#include "Hero.hpp"
#include "Dice.hpp"
#include "Itembag.hpp"
#include "Heroes.hpp"

class Game {
    friend class Monstercard;
    friend std::ostream& operator<<(std::ostream& os, ItemColor color) ;
private:
    bool skipMonsterPhase = false ;
    bool terrorAlreadyIncreased = false;

    GameMap map;
    MonstercardDeck deck;
    TurnManager turnManager;
    PerkDeck PerkDeck ; 

    Hero* mayor = nullptr;
    Hero* archaeologist = nullptr;
    Dracula* dracula = nullptr;
    InvisibleMan* invisibleMan = nullptr;
    Monster* frenziedMonster = nullptr;
    
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
    void initializaDeck() ; 
    void ChoosePerkCardANDplay(Hero*) ;
    void getNewCard(Hero*) ;
    void locationOverview() ;
    void graph_map_text();
    void monster_objectes() const;
    void return_item(const Item& item);

    std::string checkString(std::string) ; 
   
    void monster_phase();
    void monster_dice();
    void send_hero_to_hospital(Hero* );
    bool both_monsters_defeated();
    void increase_terror_level();

    void distribute_initial_items();
    void initializaMDeck();
    void Changing_frenzy_marker();
    void frenzied_strike(Monster* m, MonsterType type, std::vector<DiceFace>& results, bool& terrorAlreadyIncreased) ;
    Monster* get_frenzied_monster();
    
};

#endif