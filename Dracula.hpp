#include "monster.hpp"
#include "Hero.hpp"


class Dracula : public Monster {
    private:
        int remaining_coffins = 4;
    
    public:


        Dracula(Location* start_location);

        
        
       
        bool can_be_defeated() const;
        void destroy_coffin(Location* loc, std::vector<Item>& used_items);
        
        void defeat(Hero* hero, std::vector<Item>& yellow_items);
        
        void special_power() override ; 
        void attack() override ;
    
    };
    