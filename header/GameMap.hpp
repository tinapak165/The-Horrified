#ifndef GAMEMAP_HPP
#define GAMEMAP_HPP
#include "Location.hpp"
#include "Villager.hpp"
#include <vector>
#include <memory>
#include <raylib.h>
#include <unordered_map>
#include <queue>


class Villager;

class GameMap {
    private:
        std::vector<std::unique_ptr<Location>> locations;
        Texture2D mapTexture = {0};
    public:
        float scale;
        float drawX, drawY;
        Rectangle get_drawn_rect() const ;
        
        void build_map(); 
        void add_location(const std::string& name, Rectangle area, const std::string& iconPath) ;
        Location* get_location_by_name(const std::string& name);
        Villager* find_villager_by_name(const std::string& name);
        const std::vector<std::unique_ptr<Location>>& get_locations() const; 
        void draw_map();
        const Texture2D& get_mapTexture() const ; 
        Location* check_click(Vector2 mousePos); 
        Location* find_next_step(Location* start, Location* goal);
        ~GameMap() ; 
};

#endif