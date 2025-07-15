#ifndef MONSTER_HPP
#define MONSTER_HPP

#include <string>
#include <iostream>
#include <utility>

class Hero;
class Villager;
class Location;



enum class MonsterType { InvisibleMan, Dracula, Frenzied };
class Monster {
private:

    std::string name;
    Location* current_location;
    MonsterType type;
 

protected:

    bool defeated = false;
 

public:
    Monster(const std::string& name, Location* start_location , MonsterType );

    const std::string& get_name() const;
    Location* get_location() const ;
    void set_location(Location* );
    MonsterType get_type() const;


    Location* find_nearest_target(Location* start);
    Location* find_nearest_hero(Location* start);
    Location* find_nearest_villager(Location* start);

    Location* find_next_step(Location* target);
    // برای ایونت ها
    void Monster_move_event(Location* new_location); 
    // برای حرکت از روی استرایک
    void move_towards(int steps);

    bool is_alive() const; 

    virtual std::pair<Hero*, Villager*> attack() = 0;
    virtual void special_power(Hero* h) =0 ;
    virtual bool is_defeated()const =0 ;
    virtual bool can_be_defeated() = 0;


};
 #endif