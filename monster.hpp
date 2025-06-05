#ifndef MONSTER_HPP
#define MONSTER_HPP

#include <string>
#include "location.hpp"

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

    void move_to(Location* new_location);
};
 #endif