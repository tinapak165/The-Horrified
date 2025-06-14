#ifndef LOCATION_HPP
#define LOCATION_HPP
#include <string>
#include <vector>
#include "item.hpp"
#include "monster.hpp"
#include "hero.hpp"
class Monster;

class Location {
    private:
        std::string name;
        std::vector<Item> items;
        std::vector<Hero*> heroes;
        std::vector<Monster*> monsters;
        std::vector<Location*> neighbors;
        bool hascoffin = false; // فقط واسio دراکولاس
    
    public:
        Location(const std::string & name);
    
        void add_item(const Item& item);
        void add_hero(Hero* hero);
        void add_monster(Monster* monster);
        bool has_coffin();
        void place_coffin();
        void remove_coffin();
        
        void remove_hero(Hero* hero) ; 
        void remove_monster(Monster* monster) ;
    
        const std::string& get_name() const;
        const std::vector<Item>& get_items() const;
        
         std::vector<Monster*>& get_monsters();
        const std::vector<Hero*>& get_heroes()const;
       
        const std::vector<Location*>& get_neighbors() const;
        
        void connect(Location * other);
        
        
        void remove_item_by_index(int index); // برای PickUp
    
    };
    
#endif