#include "location.hpp"
#include <iostream>

Location::Location(const std::string& name ) : name(name){}

void Location::add_item(const Item& item) {
    items.push_back(item);
}

void Location::add_hero(Hero* hero){
    heroes.push_back(hero);
}

void Location::add_monster(Monster* monster) {
    monsters.push_back(monster);
}

void Location::set_coffin(bool present) {
    has_coffin = present;
}

bool Location::coffin_present() const {
    return has_coffin;
}

const std::string& Location::get_name() const { return name;
}

const std::vector<Item>& Location::get_items() const {
    return items;
}

void Location::remove_item_by_index(int index) {
    if (index >= 0 && index < items.size()) {
        items.erase(items.begin() + index); }
}

void Location::connect(Location * other){
    neighbors.push_back(other);
    other->neighbors.push_back(this);

}




const std::vector<Location*>& Location::get_neighbors() const {
    return neighbors;
}