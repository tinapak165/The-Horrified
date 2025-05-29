#include "Archaeologist.hpp"
#include <iostream>
using namespace std; 

Archaeologist:: Archaeologist(): Hero("Archaeologist" , 4 , "Docks"){
    SetSpecialActionInfo("Can take any number of items from adjacent locations") ; 
    
}
void Archaeologist:: DisplayInfo() const{
    cout << GetName() << ":\n" << "location: " << GetCurrentLocation() << "\n" << "Actions: " << 
    GetRemainingActions() << "/" << GetMaxAction() << "\n" << "special Action: " << GetSpecialActionInfo() << "\n"  ; 
} 
void Archaeologist::DoTheSpecialAction(){
    //do the special action
}


