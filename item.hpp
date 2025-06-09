#ifndef ITEM_HPP
#define ITEM_HPP
#include <string>

// enum class ItemType { STAKE,MIRRORED_BOX,GARLIC,TAROOT_DECK, FLOWER,CHARM, WOLFSBANE,TABLET,VIOLIN,SCROLL_OF_THOTH
// ,TORCH,SHOVEL }; //tاere is 30 of them 

enum class ItemColor { RED, BLUE, YELLOW };

class Item {
public:
    Item(std::string name, ItemColor color, int power , std::string location);
    std::string get_name() const;
    ItemColor get_color() const;
    int get_power() const;

    void place_item(int);  // every monstercard has this 

    void pick_up_item(int);  // for the the invisableman 

private:
    std::string item_name;
    // ItemType type;
     ItemColor Item_color;
    std::string Item_location;
    int Item_power;
    
};


#endif
