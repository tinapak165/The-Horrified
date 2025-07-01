
#ifndef GAMEMAP_HPP
#define GAMEMAP_HPP

#include "Location.hpp"
#include "villager.hpp"
#include <vector>
#include <memory>

class villager;

class GameMap {
private:
    std::vector<std::unique_ptr<Location>> locations;


public:
    void build_map(); 
     Location* get_location_by_name(const std::string& name);
     villager* find_villager_by_name(const std::string& name);
     const std::vector<std::unique_ptr<Location>>& get_locations() const;  
     void print_map()const;
    
};

#endif
