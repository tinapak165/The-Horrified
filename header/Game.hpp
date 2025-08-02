#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <unordered_map>
#include <memory>
#include <raylib.h>
#include <string>
#include <map>
#include <iomanip>
#include <set>
#include <limits>
#include <utility>
#include "GameMap.hpp"
#include "Perkcards.hpp"
#include "Monstercards.hpp"
#include "TurnManager.hpp"
#include "Monster.hpp"
#include "Dracula.hpp"
#include "InvisibleMan.hpp"
#include "Hero.hpp"
#include "Dice.hpp"
#include "Itembag.hpp"
#include "Heroes.hpp"
#include "State.hpp"
#include "GameRender.hpp"
#include "Villager.hpp"
#include "Menu.hpp"
#include <fstream>
class Menu;
class State ;
class GameRender ;

struct PlayerInfo{
    std::string name ; 
    Hero* hero ; 
};

enum class Phase{
    HeroPhase ,
    MonsterPhase ,

};

// for log
#define GAME_LOG(game, msg) \
    do { \
        std::cout << msg << std::endl; \
        game.log(msg); \
    } while(0)
/// 

class Game {
    friend class Monstercard;
private:
    Phase currentPhase = Phase::HeroPhase ;

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
   
    
    static int terror_Level;
    bool game_over = false;
    bool heroTurnInProgress = false ;
    Hero* activeHero ; 
    std::vector<std::string> logs;
    
public:
    Game();
    ~Game();
    void start() ;
    void initialize(const PlayerSelection&, const PlayerSelection&) ; 
    PlayerInfo getPlayer1() const ;
    PlayerInfo getPlayer2() const ;
    void setPlayer1(const std::string& , Hero*) ; 
    void setPlayer2(const std::string& , Hero*) ; 

    GameMap& get_map();
    std::unordered_map<MonsterType, Monster*>& get_monsters() ;
    Monstercard* get_current_card() const ;
    TurnManager& get_turnManager();
    Dracula* get_dracula() ; 
    InvisibleMan* get_invisibleMan() ; 
    ItemPool& get_pool() ;

    void set_skipMonsterPhase(bool) ;
    bool ShouldSkipMonsterPhase() const ;
    void set_currentPhase(Phase) ; 
    void set_HeroTurnInProgress(bool) ;  

    bool hero_phase(Hero* , GameRender*)  ;
    void initializaDeck() ; 
    void getNewCard(Hero*) ;
    void monster_objectes() const;
    void return_item(const Item& item);

    std::string checkString(std::string) ; 
    std::unique_ptr<Monstercard> current_card = nullptr;


    void monster_phase();
    void monster_dice();
    bool both_monsters_defeated();
    static void increase_terror_level();

    void distribute_initial_items();
    void initializaMDeck();
   
    void Changing_frenzy_marker();
    Monster* get_frenzied_monster();
    
    std::vector<std::string> get_last_events(int count) ;

    void SaveGame();
    void LoadGame() ; 
    Villager* create_villager(const std::string& , Location*) ;
    Hero* create_hero_by_name(const std::string& ) ;
    Menu* get_menu() ;
    ItemColor string_to_color(const std::string&);
    std::unique_ptr<Perkcard> create_perk_by_name(const std::string&) ;


    void log(const std::string& message);
    const std::vector<std::string>& get_logs() const;
    void clear_logs();
};

#endif