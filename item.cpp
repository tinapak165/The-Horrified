#include "item.hpp"

Item::Item(const std::string& name, ItemColor color, int strength, const std::string& locationName)
: name(name), color(color), strength(strength), locationName(locationName) {}

 const std::string& Item::getName() const{ return name;}
 ItemColor Item::getColor() const{ return color;}
 int Item::getStrength() const{ return strength;}



