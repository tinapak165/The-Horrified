#ifndef LOCATION_HPP
#define LOCATION_HPP
#include <string>
#include <vector>
#include "item.hpp"
#include "monster.hpp"

class Location {
    private:
        std::string name;
        std::vector<Item> items;
        // std::vector<Hero*> heroes;
        std::vector<Monster*> monsters;
        bool has_coffin = false; // فقط واس دراکولاس
    
    public:
        Location(std::string name);
    
        void add_item(const Item& item);
        // void add_hero(Hero* hero);
        void add_monster(Monster* monster);
        void set_coffin(bool present);
        bool coffin_present() const;
    
        const std::string& get_name() const;
        const std::vector<Item>& get_items() const;
        void remove_item_by_index(int index); // برای PickUp
    
    
    };
    
#endif