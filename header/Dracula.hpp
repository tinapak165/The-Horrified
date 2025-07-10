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
        
        void special_power(Hero*) override ; 
        std::pair<Hero*, Villager*> attack() override ;
         
        bool is_defeated()const override ;
        bool can_be_defeated()override;
        void destroy_coffin_at(std::string locationName);
        const std::map<std::string, bool>& get_coffins_map() const;
        
    };
    


#endif