#include "location.hpp"
#include <iostream>

Location::Location(const std::string& name ) : name(name){}

void Location::connect(Location * other){
    neighbors.push_back(other);
    other->neighbors.push_back(this);
    
}

    void Location::add_item(const Item& item) {
    items.push_back(item);
}


    void Location::add_hero(Hero* hero){
    heroes.push_back(hero);
}

void Location::add_villager(Villager* villager){
    villagers.push_back(villager) ;
}

    void Location::add_monster(Monster* monster) {
    monsters.push_back(monster);
}



    const std::string& Location::get_name() const { return name;
}


     std::vector<Item>& Location::get_items()  {
    return items;
}

Location* Location::findNeighbor(const std::string& name) const{
    for(auto *n : get_neighbors()){
        if(n->get_name() == name)
            return n ; 
    }
    return nullptr ; 
}

 
std::vector<Villager *> &Location::get_villagers(){
    return villagers ;
}

     std::vector<Monster*>& Location::get_monsters(){
        return monsters;
    }
   
    
     std::vector<Hero*>& Location::get_heroes() {
        return heroes;
    }
    



const std::vector<Location*>& Location::get_neighbors() const {
    return neighbors;
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



void Location::remove_hero(Hero* hero) {
    
    for ( auto it = heroes.begin() ; it != heroes.end();){
        if (*it == hero){
            it= heroes.erase(it);
            
        }else{
            ++it;
        }
    }
}
void Location::remove_monster(Monster* monster) {
    for ( auto it = monsters.begin() ; it != monsters.end();){
        if (*it == monster){
            it= monsters.erase(it);

        }else{
            ++it;
        }
    }
}

void Location::remove_villager(Villager * villager){
    for (auto it = villagers.begin(); it != villagers.end(); ) {
        if (*it == villager) {
            it = villagers.erase(it);  
        } else {
            ++it;  
        }
    }
    
}



std::ostream& operator<< (std::ostream & os , const Location & loc) {
    os<< loc.get_name() ;
    return os ;  
}

int Location::get_x() const { return x; }
int Location::get_y() const { return y; }