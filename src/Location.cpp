#include "location.hpp"
#include <iostream>
#include <algorithm>

Location::Location(const std::string& name ) : name(name){}

void Location::add_item(const Item& item) {
    items.push_back(item);
}

void Location::add_villager(Villager* villager){
    villagers.push_back(villager) ;
}

void Location::add_hero(Hero* hero){
    heroes.push_back(hero);
}

void Location::add_monster(Monster* monster) {
    monsters.push_back(monster);
}
void Location::remove_hero(Hero* hero) {
    heroes.erase(std::remove(heroes.begin(), heroes.end(), hero), heroes.end());
}
void Location::remove_monster(Monster* monster) {
    monsters.erase(std::remove(monsters.begin(), monsters.end(), monster), monsters.end());
}

void Location::remove_villager(Villager * villager){
    villagers.erase(std::remove(villagers.begin() , villagers.end() , villager) , villagers.end()) ;
}

const std::string& Location::get_name() const { return name; }

std::vector<Item>& Location::get_items() {
    return items;
}
   
void Location::connect(Location * other){
    neighbors.push_back(other);
    other->neighbors.push_back(this);      
}

std::vector<Monster*>& Location::get_monsters(){
    return monsters;
}
   
    
std::vector<Hero*>& Location::get_heroes() {
    return heroes;
}

std::vector<Villager *> &Location::get_villagers(){
    return villagers ;
}

const std::vector<Location*>& Location::get_neighbors() const {
    return neighbors;
}
Location* Location::findNeighbor(const std::string& name) const{
    for(auto *n : get_neighbors()){
        if(n->get_name() == name)
            return n ; 
    }
    return nullptr ; 
}

bool Location::has_coffin(){   
    return hascoffin;
}
void Location::place_coffin(){ 
     hascoffin = true;
}
void Location::remove_coffin(){
    hascoffin = false;
}

std::ostream operator <<( std::ostream &op , std::vector<Monster*> & monsters){
    op<<monsters;
}

std::ostream& operator<< (std::ostream & os , const Location & loc) {
    os<< loc.get_name() ;
    return os ;  
}
