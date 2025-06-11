#include "Mayor.hpp"
#include <iostream>
using namespace st ; 

Mayor::Mayor() : Hero("Mayor" , 5 , "Theatre" , "No special action.") {}

void Mayor::DisplayInfo()const {
    cout << GetName() << ":\n" << "location: " << GetCurrentLocation() << "\n" << "Actions: " << 
    GetRemainingActions() << "/" << 5 << "\n" << "special Action: " << GetSpecialActionInfo() << "\n"  ; 
}