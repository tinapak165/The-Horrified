#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <unordered_map>
#include <memory>
#include <raylib.h>
#include "GameMap.hpp"
#include "perkcards.hpp"
#include "monstercards.hpp"
#include "TurnManager.hpp"
#include "monster.hpp"
#include "Dracula.hpp"
#include "InvisibleMan.hpp"
#include "Hero.hpp"
#include "Dice.hpp"
#include "Itembag.hpp"
#include "Heroes.hpp"
#include "State.hpp"
#include "GameRander.hpp"

class Menu;

struct PlayerInfo{
    std::string name ; 
    Hero* hero ; 
};

class Game {
    friend class Monstercard;
private:
    PlayerInfo player1, player2;
    bool skipMonsterPhase = false ;
    bool terrorAlreadyIncreased = false;

    std::unique_ptr<Menu> menu;
    GameMap map;
    MonstercardDeck deck;
    TurnManager turnManager;
    PerkDeck perkDeck ; 

    std::unique_ptr<Mayor> mayor = nullptr ; 
    std::unique_ptr<Archaeologist>archaeologist  = nullptr ; 
    std::unique_ptr<Courier> courier = nullptr ; 
    std::unique_ptr<Scientist>scientist = nullptr ; 

    std::unique_ptr<Dracula> dracula = nullptr ; 
    std::unique_ptr<InvisibleMan> invisibleMan = nullptr ; 
    Monster* frenziedMonster = nullptr; 
 
    ItemPool pool;
    std::unordered_map<MonsterType, Monster*> monstersMap;
    std::vector<Villager*> all_villagers;
    std::vector<Hero*> heroes;
    
    int terror_Level = 0;
    bool game_over = false;
    
public:
    Game();
    ~Game();
    void start() ;
    void initialize(const PlayerSelection&, const PlayerSelection&) ; 
    PlayerInfo getPlayer1() const ;
    PlayerInfo getPlayer2() const ;
    GameMap& get_map();
    std::unordered_map<MonsterType, Monster*>& get_monsters() ;
    Monstercard* get_current_card() const ;
    TurnManager& get_turnManager();
    Dracula* get_dracula() ; 
    InvisibleMan* get_invisibleMan() ; 
    ItemPool& get_pool() ;

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
    std::unique_ptr<Monstercard> current_card = nullptr;


    void monster_phase();
    void monster_dice();
    void send_hero_to_hospital(Hero* );
    bool both_monsters_defeated();
    void increase_terror_level();

    void distribute_initial_items();
    void initializaMDeck();
   
    void Changing_frenzy_marker();
    Monster* get_frenzied_monster();
    

    std::vector<Villager*>& get_all_villagers();

    void add_villager(Villager* v);

   // void cleanup();
};

#endif