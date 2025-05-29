#include "Mayor.hpp"
#include <iostream>
using namespace std ; 

Mayor::Mayor() : Hero("Mayor" , 5 , "Theatre") {
    SetSpecialActionInfo("No special action") ; 
}
void Mayor::DisplayInfo()const {
    cout << GetName() << ":\n" << "location: " << GetCurrentLocation() << "\n" << "Actions: " << 
    GetRemainingActions() << "/" << GetMaxAction() << "\n" << "special Action: " << GetSpecialActionInfo() << "\n"  ; 
}