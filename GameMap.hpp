
#ifndef GAMEMAP_HPP
#define GAMEMAP_HPP

#include "Location.hpp"
#include <vector>
#include <memory>

class GameMap {
private:
    std::vector<std::unique_ptr<Location>> locations;

public:
    void build_map(); 
    Location* find_location_by_name(const std::string& name);
     const std::vector<std::unique_ptr<Location>>& get_locations() const;  
    
};

#endif
