#include <iostream>
#include <unordered_map>
#include <memory>
#include "GameMap.hpp"
#include "MonsterCards.hpp"
#include "TurnManager.hpp"
#include "monster.hpp"
#include "Dracula.hpp"
#include "InvisibleMan.hpp"
#include "Hero.hpp"
#include "Dice.hpp"
#include "Itembag.hpp"
#include <vector>

class Game {
    friend class Monstercard;
    friend std::ostream& operator<<(std::ostream& os, ItemColor color) ;
private:
    bool skipMonsterPhase = false ;
    GameMap map;
    MonstercardDeck deck;
    TurnManager turnManager;
    PerkDeck p ; 
    Perkcards p2 ;

    Hero* mayor = nullptr;
    Hero* archaeologist = nullptr;
    Dracula* dracula = nullptr;
    InvisibleMan* invisibleMan = nullptr;
    Monster* frenziedMonster;

    
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
    void graph_map_text();
    void monster_objectes() const;
    void return_item(const Item& item);

   

    void monster_phase();
    void monster_dice();
    void frenzied_strike(Monster* m, MonsterType type, std::vector<DiceFace>& results, bool& terrorAlreadyIncreased);
    void send_hero_to_hospital(Hero* );
    void remove_villager(Villager* );
    Villager* create_villager(const std::string& name, const std::string& locName);

    bool both_monsters_defeated();
    void increase_terror_level();

    void distribute_initial_items();
    void initializaMDeck();

    void Changing_frenzy_marker();
    
};