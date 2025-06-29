#ifndef MONSTER_HPP
#define MONSTER_HPP

#include <string>
#include "Location.hpp"
#include "Hero.hpp"

class Hero;
class Location; // forward declaration

class Monster {
private:
    std::string name;
    Location* current_location;
    friend std::ostream operator<<(std::ostream &output, Monster);
public:
    Monster(const std::string& name, Location* start_location);

    const std::string& get_name() const;
    Location* get_location() const ;
    void set_location(Location* );

    Location* find_nearest_target(Location* start);
    Location* find_next_step(Location* target);
    // برای ایونت ها
    void Monster_move_event(Location* new_location); 
    // برای حرکت از روی استرایک
    void move_towards(int steps);

    virtual void attack() = 0;
    virtual void special_power(Hero* h) =0 ;
    virtual bool is_defeated()const =0 ;
    virtual bool can_be_defeated() = 0;
    virtual void destroy_coffin_at(std::string locationName)=0;

};
 #endif
