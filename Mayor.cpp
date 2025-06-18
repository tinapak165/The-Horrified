#include "Mayor.hpp"
#include <iostream>
using namespace std ; 

Mayor::Mayor(GameMap& Map) : Hero("Mayor" , 5 , Map.find_location_by_name("Theater") , "No special action.") {}

void Mayor::DisplayInfo()const {
    cout << GetName() << ":\n" << "location: " << *GetCurrentLocation() << "\n" << "Actions: " << 
    GetRemainingActions() << "/" << 5 << "\n" << "special Action: " << GetSpecialActionInfo() << "\n"  ; 
}