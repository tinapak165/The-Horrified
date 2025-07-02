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
    friend std::ostream& operator<<(std::ostream & os , ItemColor color);
    Item(const std::string& name, ItemColor color, int strength, const std::string& locationName);

    const std::string& getName() const;
    ItemColor getColor() const;
    int getStrength() const;
     std::string getLocationName() const;
    static std::string color_to_string(ItemColor color);
    std::string get_color_code(ItemColor color);
    

};



#endif
