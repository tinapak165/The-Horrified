#ifndef LOCATION_HPP
#define LOCATION_HPP
#include <string>
#include <vector>
#include "item.hpp"
#include "monster.hpp"
#include "hero.hpp"
#include "villager.hpp"

class Item;
class Monster;
class Hero;
class villager ;   


class Location {

    private:
        
            std::string name;
            std::vector<Item> items;
            std::vector<Villager*> villagers ; 
            std::vector<Hero*> heroes;
            std::vector<Monster*> monsters;
            std::vector<Location*> neighbors;
            bool hascoffin = false; // فقط واسio دراکولاس
        
    public:
            
            friend std::ostream& operator <<( std::ostream &output ,const Location&);
            friend std::ostream operator <<( std::ostream &output , std::vector<Monster*> &);

            Location(const std::string & name);
            void connect(Location * other);
            
            void add_item(const Item& item);
            void add_villager(Villager*) ;
            void add_monster(Monster* monster);
            void add_hero(Hero* hero);

            void remove_hero(Hero*);
            void remove_monster(Monster* );
            void remove_villager(Villager *);

            bool has_coffin();
            void place_coffin();
            void remove_coffin();
        
            const std::string& get_name() const;
            std::vector<Item>& get_items() ; 
            std::vector<Monster*>& get_monsters();
            std::vector<Hero*>& get_heroes();
            std::vector<Villager *>& get_villagers();
            const std::vector<Location*>& get_neighbors() const;
            
            Location* findNeighbor(const std::string& name) const  ; 
        
    };
    
#endif