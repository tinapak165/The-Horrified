#include "Hero.hpp"
#include <iostream>
#include <stdexcept>

using namespace std ; 

Hero::Hero( std::string name , int MaxActions , std::string StartingLocation , std::string specialAction)
: name(name) , MaxActions(MaxActions) , currentLocation(StartingLocation) , specialAction(specialAction){}

Hero::Hero(){}

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
void Hero::SetMaxActions(int newMax){
    MaxActions = newMax ; 
}
void Hero::SetCurrentLocation(std::string location){
    currentLocation = location ;
}
void Hero::MoveTo(std::string Newlocation){
    currentLocation = Newlocation ; 
    cout << GetName() << " moved to " << GetCurrentLocation() << endl ;
}
std::ostream& operator << (std::ostream &out , const Hero &hero){
    out << "Hero Name: " << hero.GetName() << endl  ; 
    out << "location: " << hero.GetCurrentLocation() << endl  ; 
    out << "actions: " << hero.GetSpecialActionInfo() << endl  ;  
    return out ; 
}