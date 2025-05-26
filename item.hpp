#ifndef ITEM_HPP
#define ITEM_HPP
#include <string>

enum class ItemType { STAKE,MIRRORED_BOX,GARLIC,TAROOT_DECK, FLOWER,CHARM, WOLFSBANE,TABLET,VIOLIN,SCROLL_OF_THOTH
,TORCH,SHOVEL }; //tاere is 30 of them 

enum class ItemColor { RED, BLUE, YELLOW };

class Item {
public:
    Item(ItemType type, ItemColor color, int power , std::string location);
    ItemType get_type() const;
    ItemColor get_color() const;
    int get_power() const;

private:
    ItemType type;
    ItemColor color;
    std::string location;
    int power;
    
};


#endif
