#include "item.hpp"

Item::Item(const std::string& name, ItemColor color, int strength, const std::string& locationName)
: name(name), color(color), strength(strength), locationName(locationName) {}

 const std::string& Item::getName() const{ return name;}
 ItemColor Item::getColor() const{ return color;}
 int Item::getStrength() const{ return strength;}

void Item::setStrength(int new_Strength){
    strength = new_Strength ; 
 }

 std::string Item::getLocationName() const {
    return locationName;  
}
std::string Item::color_to_string(ItemColor color) {
    switch (color) {
        case ItemColor::red:    return "Red";
        case ItemColor::blue:   return "Blue";
        case ItemColor::yellow: return "Yellow";
        default:                return "Unknown";
    }
}