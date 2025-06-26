#ifndef DRACULA_HPP
#define DRACULA_HPP

#include "monster.hpp"
#include "Hero.hpp"

class location;

class Dracula : public Monster {
    private:
        int remaining_coffins = 4;
    
    public:


        Dracula(Location* start_location);

        
        
       
        bool can_be_defeated() const;
        void destroy_coffin(Location* loc, std::vector<Item>& used_items);
        
        void defeat(Hero* hero, std::vector<Item>& yellow_items);
        
        void special_power(Hero*) override ; 
        void attack() override ;
        bool is_defeated() override;
    
    };
    


#endif