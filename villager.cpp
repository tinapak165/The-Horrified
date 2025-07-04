#include "villager.hpp"
#include <iostream>
#include <algorithm>
using namespace std ;

vector<villager*> villager:: vil  ;

villager::villager(GameMap& map , const string& name, Location* safeplace , Location* current) : name(name), currentLocation(current){ 

    vil.push_back(this) ;
    
    if(current)
        current->add_villager(this) ; 
    if(name == "Dr. Cranly"){
        (*this).set_safeplace(map.get_location_by_name("Precinct")) ; 
    }
    else if(name == "Dr. Reed"){
        (*this).set_safeplace(map.get_location_by_name("Camp")) ; 
    }
    else if(name == "Prof. Pearson"){
    (*this).set_safeplace(map.get_location_by_name("Museum")) ; 
    }
    else if(name == "Maleva"){
        (*this).set_safeplace(map.get_location_by_name("Shop")) ; 
    }
    else if(name == "Fritz"){
        (*this).set_safeplace(map.get_location_by_name("Institute")) ; 
    }
    else if(name == "Wilbur & Chick"){
        (*this).set_safeplace(map.get_location_by_name("Dungeon")) ; 
    }
    else if(name == "Maria"){
        (*this).set_safeplace(map.get_location_by_name("Camp")) ; 
    }
}

bool villager::in_the_safePlace() const{

    return currentLocation == safePlace;
}

void villager::set_currentLocation(Location* newLocation){
    currentLocation = newLocation ; 
}

Location* villager::get_currentLocation(){
    return currentLocation;
}

string villager::get_name(){ return name; }

Location* villager::get_safeplace(){ return safePlace; }

void villager::set_safeplace(Location* newplace){
    safePlace = newplace ; 
}

void villager::MoveTo(Location* newPlace , string charc){ // only villager move
  
    for(auto *v :vil){
        if(v->get_name() == charc){
            if(newPlace == v->get_currentLocation())
                throw runtime_error("you are in the current location") ;
            v->get_currentLocation()->remove_villager(v) ; 
            v->set_currentLocation(newPlace) ; 
            newPlace->add_villager(v) ; 
            cout << v->get_name() << " " << "moved to " << *(v->get_currentLocation()) << '\n' ;
            return ;  
        }
    }
    throw invalid_argument("villager not found! in move") ; 

}
void villager::removeVillager(){

    for(auto it = vil.begin() ; it != vil.end() ; ){
        if((*it)->in_the_safePlace()){
            if((*it)->get_currentLocation()){
                (*it)->get_currentLocation()->remove_villager(*it) ; 
            }
            delete *it ; 
            it  = vil.erase(it) ;
        }
        else ++it ; 
    }  
}

void villager::removevillager(villager * v){ //killed by attack of monster
    vil.erase(remove(vil.begin() , vil.end() , v) , vil.end()) ; 
    std::cout << "Removed villager: " << (this)->get_name() << "\n";
}

bool villager::AnyVillagerInSafePlace(){
    for(auto *e : all()){
        if(e->in_the_safePlace()){
            return true ; 
        }
    }
    return false ;
}

vector<villager*> &villager::all(){ return vil ;}