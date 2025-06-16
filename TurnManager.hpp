
#include <vector>
#include "Hero.hpp"

class TurnManager {
    private:
        std::vector<Hero*> heroes;
        int current_index;
    
    public:
        TurnManager(const std::vector<Hero*>& heroes);
    
        Hero* get_active_hero();
    
        void next_turn();

        
    void add_hero(Hero* hero);
    };
    