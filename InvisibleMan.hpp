#ifndef INVISIBLEMAN_HPP
#define INVISIBLEMAN_HPP

#include "monster.hpp"

#include <unordered_set>
#include <string>
#include <utility>
#include <algorithm>
#include "item.hpp"

class Hero;
class Location;

class Villager;



class InvisibleMan : public Monster {
 
    private:

    std::unordered_set<std::string> evidence_locations;
    std::unordered_set<std::string> required_locations;


    public:

        InvisibleMan(Location* start);

        void special_power(Hero*) override ; 
        std::pair<Hero*, Villager*> attack() override ;

        bool is_defeated()const override ;
        bool can_be_defeated()override;

        
        bool try_place_evidence(Item ); 
        int get_evidence_count() const;
        bool add_evidence(const std::string& location);



};

#endif