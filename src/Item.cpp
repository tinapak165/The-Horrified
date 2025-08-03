#include "Item.hpp"

Item::Item(std::string name,ItemColor c, int strength , std::string locationName , std::string texturepath)
    : name(name),color(c),strength(strength) ,locationName(locationName), texturepath(texturepath) {}
Item::Item(){}

void Item::loadTexture() {
        texture = LoadTexture(this->get_TexturePath().c_str());
    }

void Item::unloadTexture(){
    UnloadTexture(this->getTexture()) ;
}  
Texture2D Item::getTexture() const {
    return texture;
}

 const std::string& Item::getName() const{ return name;}
 ItemColor Item::getColor() const{ return color;}
 int Item::getStrength() const{ return strength;}

void Item::setStrength(int new_Strength){ strength = new_Strength ; }
 std::string Item::getLocationName() const {
    return locationName;  
}

std::string Item::color_to_string(ItemColor color) {
    switch (color) {
        case ItemColor::Red:    return "Red";
        case ItemColor::Blue:   return "Blue";
        case ItemColor::Yellow: return "Yellow";
        default:                return "Unknown";
    }
}
std::string Item::get_TexturePath() const { return texturepath; }