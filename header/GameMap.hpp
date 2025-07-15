
#ifndef GAMEMAP_HPP
#define GAMEMAP_HPP

#include "Location.hpp"
#include "villager.hpp"
#include <vector>
#include <memory>
#include <unordered_map>
#include <queue>

class Villager;

class GameMap {
private:
    std::vector<std::unique_ptr<Location>> locations;
public:
    void build_map(); 
     Location* get_location_by_name(const std::string& name);
     Villager* find_villager_by_name(const std::string& name);
     const std::vector<std::unique_ptr<Location>>& get_locations() const;  
     Location* find_next_step(Location* start, Location* goal);
    
};

#endif