#include "Hero.hpp"
#include <iostream>
#include <stdexcept>

using namespace std ; 

Hero::Hero( std::string name , int MaxActions , std::string StartingLocation , std::string specialAction)
: name(name) , MaxActions(MaxActions) , currentLocation(StartingLocation) , specialAction(specialAction){

    ListOfActions = {
        {ActionType::Move , "Move" , "You can move to any places near by. you can also move the villagers with you."} ,
        {ActionType::Guide , "Guide" , "You can move the villagers (that are in your place) to the closest place or move the villagers(that are in your neigbor place) to your place."} , 
        {ActionType::Pickup , "Pickup" , "You can take any number of item you want from the place you are."},
        {ActionType::Advance , "Advance" , "You can speed up a monster-related mission and complete it to get closer to defeating that monster."} ,
        {ActionType::Defeat , "Defeat" , "Once you have completed all the missions related to catching a monster, you can defeat it, but keep in mind that you must be present in the area where the monster is located."} ,
        {ActionType::specialAction , "Special action" , GetSpecialActionInfo()} , 
    };
}

void Hero::DisplayActions(){
    cout << "Here is thr list of actions you have\n" ; 
    for(const auto a : ListOfActions)
        cout << a.name << ": " << a.Description <<  '\n' ; 
}

void Hero::PerformTheAction(ActionType action)  {
    for(const auto ac : ListOfActions){
        if(ac.Type == action){
            if(GetRemainingActions() > 0){
                cout << "you can do the " << ac.name << " action." ; 
                SetRemainingActions(1-GetRemainingActions()) ; 
                return ; 
            }else
                throw runtime_error("not enough action remaining!") ; 
        }else
            throw runtime_error("action not available!") ; 

    }
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
void Hero::MoveTo(Location* Newlocation){
    currentLocation = Newlocation ; 
    cout << GetName() << " moved to " << GetCurrentLocation() << endl ;
}
void Hero::SetRemainingActions(int newRemaining){
    RemainingActions = newRemaining ; 
}

