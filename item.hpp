#ifndef ITEM_HPP
#define ITEM_HPP
#include <string>


enum class ItemColor { RED, YELLOW, BLUE };

class Item {
private:
    std::string name;
    ItemColor color;
    int strength;
    std::string locationName; // اسمی از مکان که در آن ظاهر می‌شود

public:
    Item(const std::string& name, ItemColor color, int strength, const std::string& locationName);

    const std::string& getName() const;
    ItemColor getColor() const;
    int getStrength() const;
     std::string getLocationName() const;
};



#endif
