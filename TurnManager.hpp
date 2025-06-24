#include <memory>
#include <vector>
#include "Hero.hpp"

class TurnManager {
    private:
        Hero* mayor ; 
        Hero* archaeologist ; 
        size_t current = 0 ;
        bool archTurn ; 
    
    public:
        
        TurnManager(Hero* , Hero*);
        TurnManager() ; 
        //TurnManager(const std::vector<Hero*>& heroes);
        Hero* get_active_hero() const;
        void next_turn();
        //void add_hero(Hero* hero);
    };
    