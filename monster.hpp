#ifndef MONSTER_HPP
#define MONSTER_HPP

#include <string>
#include "Location.hpp"

class Location; // forward declaration
class Hero ; //added
class Monster {
private:
    std::string name;
    Location* current_location;
    //friend std::ostream operator<<(std::ostream &output, Monster);    commented here to not get errors
public:
    Monster(const std::string& name, Location* start_location);

    const std::string& get_name() const;
    Location* get_location() const ;

    Location* find_nearest_target(Location* start);
    Location* find_next_step(Location* target);
    // برای ایونت ها
    void Monster_move_event(Location* new_location); 
    // برای حرکت از روی استرایک
    void move_towards(int steps);

    virtual void attack() = 0;
    virtual void special_power(Hero*) =0 ;
    virtual bool is_defeated()=0;

};
 #endif
