#ifndef LOCATION_HPP
#define LOCATION_HPP
#include <string>
#include <vector>
#include "item.hpp"
#include "monster.hpp"
#include "hero.hpp"
class Monster;
class Hero ; 
class Location {
    friend std::ostream& operator<< (std::ostream & os , const Location & loc) ; //برای نمایش اسم لوکیشن
    private:
        std::string name;
        std::vector<Item> items;
        std::vector<Hero*> heroes;
        std::vector<Monster*> monsters;
        std::vector<Location*> neighbors;
        bool hascoffin = false; // فقط واسio دراکولاس
        
        public:
        friend std::ostream operator <<( std::ostream &output , std::vector<Monster*> &);
        Location(const std::string & name);
    
        void add_item(const Item& item);
        void add_hero(Hero* hero);
        void remove_hero(Hero* hero) ; 
        void remove_monster(Monster* monster) ; 

        void add_monster(Monster* monster);
        bool has_coffin();
        void place_coffin();
        void remove_coffin();
    
        const std::string& get_name() const;
         std::vector<Item>& get_items() ; 
        
        std::vector<Monster*>& get_monsters();
        

         std::vector<Hero*>& get_heroes();
       
        const std::vector<Location*>& get_neighbors() const;
        Location* findNeighbor(const std::string& name) const  ;  
        void connect(Location * other);
        
        
        void remove_item_by_index(int index); // برای PickUp
    
    };
    
#endif