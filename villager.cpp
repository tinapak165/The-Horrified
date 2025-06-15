#include "villager.hpp"
#include <iostream>
#include <vector>
using namespace std ;

vector<villager*> villager:: vil  ; 

villager::villager(const string name, string place) : name(name), currentLocation(place) //for testing if the Move action works or not (!fix!)
{
    vil.push_back(this) ;
}


bool villager::in_the_safePlace() const{

    return currentLocation == safePlace;
}

void villager::set_currentLocation(string newLocation){
    currentLocation = newLocation ; 
}

std::string villager::get_currentLocation(){
    return currentLocation;
}

string villager::get_name(){ return name; }

string villager::get_safeplace(){ return safePlace; }

void villager::set_safeplace(string newplace){
    safePlace = newplace ; 
}

// void villager::DisplayVillagers(){
//     for(auto &e : vill)
//         cout << e.get_name() << " : " << e.get_safeplace() << endl ; 
// }
void villager::MoveTo(string newPlace , string charc){
    // for(auto v : vill){
    //     if(v.get_name() == charc){
    //         v.set_safeplace(newPlace) ; 
    //         cout << v.get_name() << " " << "moved to " << v.get_safeplace() ; 
    //         return ; 
    //     }
    // }
    // throw invalid_argument("villager not found!") ; 
    if(newPlace == get_currentLocation())
        throw runtime_error("you are in the current location") ; 
    set_currentLocation(newPlace) ; 
    cout << (*this).get_name() << " " << "moved to " << (*this).get_currentLocation() ; 
}
vector<villager*> &villager::all(){
    return vil ;     
}
