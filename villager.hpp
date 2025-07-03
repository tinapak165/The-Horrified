#ifndef VILLAGER_HPP
#define VILLAGER_HPP
#include <iostream>
#include "location.hpp"
#include "GameMap.hpp"
#include <vector>

class Location ; 
class GameMap ; 
class villager{

    private:
        const std::string name ; 
        Location* safePlace ;
        Location* currentLocation ; 
        static std::vector<villager*> vil ; 
    public:
        static std::vector<villager*>& all() ; 
        villager( GameMap& map , const std::string& , Location* , Location*) ; 
        bool in_the_safePlace() const ; 
        void set_currentLocation(Location*) ; 
        Location* get_currentLocation() ; 
        std::string get_name() ; 
        Location* get_safeplace() ; 
        void set_safeplace(Location*) ; 
        void MoveTo(Location*, std::string) ; 
        bool static AnyVillagerInSafePlace() ;
        void static removeVillager();
        void removevillager(villager*) ; 
};

#endif