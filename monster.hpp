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
    Monster(const std::string& name, Location* start_location);

    const std::string& get_name() const;
    Location* get_location() const ;

    Location* find_nearest_target(Location* start);
    Location* find_next_step(Location* target);
    void Monster_move(Location* new_location);
    void move_towards(int steps);

    void attack();

};
 #endif
