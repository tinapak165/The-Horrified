#ifndef ITEM_HPP
#define ITEM_HPP
#include <string>
#include "raylib.h"

enum class ItemColor {
    Red,
    Yellow,
    Blue,
    Reset
};


class Item {
private:
    std::string name;
    ItemColor color;
    int strength;
    std::string locationName; 
    std::string texturepath;
    Texture2D texture;
public:
    Item(std::string name,ItemColor color, int strength, std::string locationName, std::string texturepath);

    const std::string& getName() const;
    ItemColor getColor() const;
    int getStrength() const;
    Texture2D getTexture() const;
    void loadTexture() ;
    void unloadTexture(); 
   
    std::string getLocationName() const;
    static std::string color_to_string(ItemColor color);    

};



#endif