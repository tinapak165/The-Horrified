#include "Hero.hpp"
#include <iostream>
#include <stdexcept>

using namespace std ; 

Hero::Hero(std::string name , int MaxActions , std::string StartingLocation){
    name = name ; 
    MaxActions = MaxActions ; 
    currentLocation = StartingLocation ; 
}
std::string Hero::GetName()const{
    return name ; 
}
int Hero::GetMaxAction() const{
    return MaxActions ;
}
int Hero::GetRemainingActions()const{
    return RemainingActions ; 
}
std::string Hero::GetSpecialActionInfo() const{
    return specialAction ; 
}
std::string Hero::GetCurrentLocation() const{
    return currentLocation ; 
}
void Hero::SetName(const std::string& newName){
    name = newName ; 
}
void Hero::SetMaxActions(int newMax){
    MaxActions = newMax ; 
}
void Hero::SetRemainingActions(int newRemaining){
    if(newRemaining >= 0 && newRemaining <= MaxActions )
        RemainingActions = newRemaining ; 
    //else 
        //throw invalid_argument(" ") ; 
}
void Hero::SetCurrentLocation(const std::string& location){
    currentLocation = location ;
}
void Hero::MoveTo(std::string Newlocation){
    currentLocation = Newlocation ; 
    cout << GetName() << " moved to " << GetCurrentLocation() << endl ;
}