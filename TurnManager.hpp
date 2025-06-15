
#include <vector>
#include "Hero.hpp"

class TurnManager {
    private:
        std::vector<Hero*> heroes;
        int current_index;
    
    public:
        TurnManager(const std::vector<Hero*>& heroes) : heroes(heroes), current_index(0) {}
    
        Hero* get_active_hero() {
            return heroes[current_index];
        }
    
        void next_turn() {
            current_index = (current_index + 1) % heroes.size();
        }
    };
    