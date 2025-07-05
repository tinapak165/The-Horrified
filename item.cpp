#include "item.hpp"

Item::Item(const std::string& name, ItemColor color, int strength, const std::string& locationName)
: name(name), color(color), strength(strength), locationName(locationName) {}

 const std::string& Item::getName() const{ return name;}
 ItemColor Item::getColor() const{ return color;}
 int Item::getStrength() const{ return strength;}

 std::string Item::getLocationName() const {
    return locationName;  
}
std::string Item::color_to_string(ItemColor color) {
    switch (color) {
        case ItemColor::RED:    return "Red";
        case ItemColor::BLUE:   return "Blue";
        case ItemColor::YELLOW: return "Yellow";
        default:                return "Unknown";
    }
}