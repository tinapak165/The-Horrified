#ifndef LOCATION_HPP
#define LOCATION_HPP
#include <string>
#include <vector>
#include "Item.hpp"
#include "Monster.hpp"
#include "Hero.hpp"
#include "Villager.hpp"
#include <raylib.h>
class Item;
class Monster;
class Hero;
class villager ;   


class Location {

    private:
        Vector2 screenPos ; 
        Rectangle clickableArea;   // منطقه قابل کلیک روی نقشه
        Texture2D iconTexture;     // آیکون تصویری برای این مکان
        std::string name;
        std::vector<Texture2D> itemTextures;
        std::vector<Texture2D> heroTextures;
        std::vector<Texture2D> monsterTextures;
        std::vector<Item> items;
        std::vector<Villager*> villagers ; 
        std::vector<Hero*> heroes;
        std::vector<Monster*> monsters;
        std::vector<Location*> neighbors;
        bool hascoffin = false;
    public:   
        friend std::ostream& operator <<( std::ostream &output ,const Location&);

        Location(const std::string & name, Rectangle area, Texture2D icon);
        void connect(Location * other);
        void draw_info_panel() ;

        void add_item(const Item& item , Texture2D itemTex);
        void add_villager(Villager*) ;
        void add_monster(Monster* monster , Texture2D monstertex);
        void add_hero(Hero* hero, Texture2D heroTex);

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
        const Rectangle& get_clickable_area() const;
        const Texture2D& get_icon_texture() const;
        void set_screenPos(Vector2) ; 
        Vector2 get_screenPos() const ;
        ~Location() ; 
    };
    
#endif