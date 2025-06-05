#include "item.hpp"


Item::Item(std::string name, ItemColor color, int power , std::string location) :
 item_name (name), Item_color(color), Item_power(power), Item_location(location) {}


 std::string Item::get_name() const{ return item_name;}
 ItemColor Item::get_color() const{ return Item_color;}
 int Item::get_power() const{ return Item_power;}



 void Item::place_item(int){ 

// add a class function that does this action in the location vector 

 }

 void Item::pick_up_item(int){

 }