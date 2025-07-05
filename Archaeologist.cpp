#include "Archaeologist.hpp"
#include <iostream>
using namespace std; 

Archaeologist:: Archaeologist(GameMap& Map): Hero("Archaeologist" , 4 , Map.get_location_by_name("Docks") , "Can take any number of items from adjacent locations.") {
    Map.get_location_by_name("Docks")->add_hero(this) ; 
}

void Archaeologist:: DisplayInfo() const{
    cout << GetName() << ":\n" << "location: " << *GetCurrentLocation() << "\n" << "Actions: " << 
    GetRemainingActions() << "/" << 4 << '\n' << "special action: " << GetSpecialActionInfo() << '\n'  ; 
} 


