#ifndef MONSTER_HPP
#define MONSTER_HPP

#include <string>
#include "Location.hpp"

class Location; // forward declaration

class Monster {
private:
    std::string name;
    Location* current_location;

public:
    Monster(const std::string& name, Location* start_location)
        : name(name), current_location(start_location) {}

    const std::string& get_name() const { return name; }
    Location* get_location() const { return current_location; }

    virtual Location * find_nearest_target(Location * start);
};
 #endif