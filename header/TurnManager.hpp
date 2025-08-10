#ifndef TURNMANAGER_H
#define TURNMANAGER_H
#include <vector>
#include "Hero.hpp"

class TurnManager {
    private:
        std::vector<Hero*> heroes;
        int current_index;
    
    public:
        TurnManager();
        TurnManager(const std::vector<Hero*>& heroes);
    
        Hero* get_active_hero();
        void set_active_hero(const std::string&) ; 
        Hero* find_hero_by_name(const std::string&) ;
    
        void next_turn();

        
    void add_hero(Hero* hero);
    std::vector<Hero*> get_heroes();
    };
    
#endif