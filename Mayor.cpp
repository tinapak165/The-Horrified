#include "Mayor.hpp"
#include <iostream>
using namespace std ; 


Mayor::Mayor(GameMap& Map)
    : Hero("Mayor", 5, Map.get_location_by_name("Theatre"), "No special action.") 
{
    Location* start = Map.get_location_by_name("Theatre");
    if (!start) {
        std::cerr << " Error: Location 'Theater' not found!\n";
        throw std::runtime_error("Theater location not found in GameMap!");
    }
    start->add_hero(this);
}


void Mayor::DisplayInfo()const {
    cout << GetName() << ":\n" << "location: " << *GetCurrentLocation() << "\n" << "Actions: " << 
    GetRemainingActions() << "/" << 5 << "\n" << "special Action: " << GetSpecialActionInfo() << "\n"  ; 
}