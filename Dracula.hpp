#ifndef DRACULA_HPP
#define DRACULA_HPP

#include <map>
#include "monster.hpp"
#include "Hero.hpp"


class location;

class Dracula : public Monster {
    private:
    std::map<std::string, bool> coffinsDestroyed;
    
    public:


        Dracula(Location* start_location);

        
        
       // چههار تابوت همه شان نابود باشن
        

        void print_remaining_coffins() const;
        
        void defeat(Hero* hero, std::vector<Item>& yellow_items);
        
        void special_power(Hero*) override ; 
        void attack() override ;
        bool is_defeated()const override ;
        bool can_be_defeated()override;
        void destroy_coffin_at(std::string locationName)override;
        
    };
    


#endif