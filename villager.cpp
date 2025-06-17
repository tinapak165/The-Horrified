#include "villager.hpp"
#include <iostream>
#include <vector>
using namespace std ;

vector<villager*> villager:: vil  ;

villager::villager(const string name, Location* place) : name(name), currentLocation(place) //for testing if the Move action works or not (!fix!)
{
    //set the safe place..this is the currentPlace
    vil.push_back(this) ;
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

// void villager::DisplayVillagers(){
//     for(auto &e : vill)
//         cout << e.get_name() << " : " << e.get_safeplace() << endl ; 
// }

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
vector<villager*> &villager::all(){
    return vil ;     
}
