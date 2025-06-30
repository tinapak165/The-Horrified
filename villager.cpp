#include "villager.hpp"
#include <iostream>
#include <algorithm>
using namespace std ;

vector<villager*> villager:: vil  ;

villager::villager(const string name, Location* safeplace , Location* current) : name(name), currentLocation(current) , safePlace(safeplace) { 

    vil.push_back(this) ;
    
    if(current)
        current->add_villager(this) ; 
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
            v->set_currentLocation(newPlace) ; 
            cout << v->get_name() << " " << "moved to " << *(v->get_currentLocation()) << '\n' ;
            return ;  
        }
    }
    throw invalid_argument("villager not found!") ; 

}
void villager::removeVillager(){

    for(auto it = vil.begin() ; it != vil.end() ; ){
        if((*it)->in_the_safePlace()){
            delete *it ; 
            //cout << (*it)->get_name() << " is deleted\n"; checking if the villager actually been deleted
            it  = vil.erase(it) ;
        }
        else ++it ; 
    }  
}

void villager::removevillager(villager * v){ //killed by attack of monster
    vil.erase(remove(vil.begin() , vil.end() , v) , vil.end()) ; 
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
