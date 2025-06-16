#include "Hero.hpp"
#include <iostream>
#include <stdexcept>

using namespace std ; 

Hero::Hero( std::string name , int MaxActions , Location* StartingLocation , std::string specialAction)
: name(name) , RemainingActions(MaxActions) , currentLocation(StartingLocation) , specialAction(specialAction){

    ListOfActions = {
        {ActionType::Move , "Move" , "You can move to any places near by. you can also move the villagers with you."} ,
        {ActionType::Guide , "Guide" , "You can move the villagers (that are in your place) to the closest place or move the villagers(that are in your neigbor place) to your place."} , 
        {ActionType::Pickup , "Pickup" , "You can take any number of item you want from the place you are."},
        {ActionType::Advance , "Advance" , "You can speed up a monster-related mission and complete it to get closer to defeating that monster."} ,
        {ActionType::Defeat , "Defeat" , "Once you have completed all the missions related to catching a monster, you can defeat it, but keep in mind that you must be present in the area where the monster is located."} ,
        {ActionType::SpecialAction , "Special" , specialAction} , 
    };
}

void Hero::DisplayActions(){
    cout << "Here is the list of actions you have\n" ; 
    for(const auto a : ListOfActions)
        cout << a.name << ": " << a.Description << '\n' ; 
}

bool Hero::PerformTheAction(string act)  {
    for(const auto& ac : ListOfActions){
        if(ac.name == act){
            if(act == "Special" && !HasSpecialAction()){
                throw runtime_error("This hero does not have special action") ; 
            }
            if(GetRemainingActions() > 0){
                cout << "[playing " << act << "]\n" ;
                SetRemainingActions(GetRemainingActions()-1) ; 
                return true; 
            }else
                throw runtime_error("not enough action remaining!") ; 
        }
    }
    throw runtime_error("action not available!") ; 

}

std::string Hero::GetName()const{
    return name ; 
}
int Hero::GetRemainingActions()const{
    return RemainingActions ; 
}
std::string Hero::GetSpecialActionInfo() const{
    return specialAction ; 
}
Location* Hero::GetCurrentLocation() const{
    return currentLocation ; 
}
void Hero::SetCurrentLocation(Location* location){
    currentLocation = location ;
}
void Hero::MoveTo(Location* new_location , vector<villager*> vill){ // move with villagers
    // if (!new_location || new_location == currentLocation) return;
    // if (currentLocation) {
    //     currentLocation->remove_hero(this);
    // }
    
    // currentLocation = new_location;
    // new_location->add_hero(this);
    
    // cout << name << " moved to " << new_location->get_name() << endl;

    if(new_location == (*this).GetCurrentLocation())
        throw runtime_error("already in the location!") ; 
    
    SetCurrentLocation(new_location) ; 
    cout << (*this).GetName() << " moved to " << *(*this).GetCurrentLocation() << '\n' ; 

        for(auto *v : vill){
            v->set_currentLocation(new_location) ;
            cout << v->get_name() << " moved with hero to " << *(v->get_currentLocation()) << '\n'; 
        }
    

}
void Hero::MoveTo(Location* new_location){ //without villager
    if(new_location == (*this).GetCurrentLocation())
        throw runtime_error("already in the location!") ;
    
    (*this).SetCurrentLocation(new_location) ; 
    cout << (*this).GetName() << " moved to " << *((*this).GetCurrentLocation()) << '\n' ; 

}
bool Hero::hasvillagerHere() const{

    for(auto *v : villager::all() ){ //باید استاتیک باشد تا اینگونه ازش استفاده کنیم
        if(v->get_currentLocation() == (*this).GetCurrentLocation())
            return true ; 
    } 
    return false ;
}

void Hero::showvillagersHere() const{
    vector<villager*> vill ; 
    for(auto *v : villager::all() ){
        if(v->get_currentLocation() == (*this).GetCurrentLocation()){
            vill.push_back(v) ; 
        }
    }
    for(auto *v : vill)
        cout << v->get_name() << " , " ; 
}

vector<villager*> Hero::villagerHere() const
{
    vector<villager*> vill ; 
    for(auto *v : villager::all() ){
        if(v->get_currentLocation() == GetCurrentLocation())
            vill.push_back(v) ; 
    }
    return vill ;
}

void Hero::SetRemainingActions(int newRemaining)
{
    RemainingActions = newRemaining ;
}
