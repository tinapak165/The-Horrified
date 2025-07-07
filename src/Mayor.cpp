#include "Mayor.hpp"
#include <iostream>
using namespace std ; 

Mayor::Mayor(GameMap& Map) : Hero("Mayor" , 5 , Map.get_location_by_name("Theatre") , "No special action.") {
    Map.get_location_by_name("Theatre")->add_hero(this) ; 
}

void Mayor::DisplayInfo()const {
    cout << GetName() << ":\n" << "location: " << *GetCurrentLocation() << "\n" << "Actions: " << 
    GetRemainingActions() << "/" << 5 << '\n'  ; 
}