#include "Heroes.hpp"
#include <iostream>
#include "Hero.hpp"
using namespace std ; 

Archaeologist:: Archaeologist(GameMap& Map): Hero("archaeologist" , 4 , Map.get_location_by_name("Docks") , "can take any number of items from adjacent locations.") {
    Map.get_location_by_name("Docks")->add_hero(this) ; 
}

void Archaeologist:: DisplayInfo() const{
    cout << GetName() << ":\n" << "location: " << *GetCurrentLocation() << "\n" << "Actions: " << 
    GetRemainingActions() << "/" << 4 << '\n' << "special action: " << GetSpecialActionInfo() << '\n'  ; 
}

void Archaeologist::SpecialAction(Location* chosenplace){

    vector<Item>&  ItemsAtLocation= chosenplace->get_items() ;

    if(ItemsAtLocation.empty()) {
        cerr << "no item available in " << chosenplace->get_name() << "!\n"; 
        return ;  
    }
    else{
        int selectedItems = -1 ; 
        while(!ItemsAtLocation.empty()){
            cout << "items available in " << chosenplace->get_name() << " :\n" ;
            for(size_t i = 0 ; i < ItemsAtLocation.size() ; i++)
                cout << (i+1) << ". " << ItemsAtLocation[i].getName() << 
                    "( color : " <<ItemsAtLocation[i].color_to_string(ItemsAtLocation[i].getColor()) <<
                     " , strength: " << ItemsAtLocation[i].getStrength() << ")\n";
        
            cout << "enter the item number to pick up(0 to end): " ; 
            cin >> selectedItems ;
            if(selectedItems == 0) 
                return ;
            if(selectedItems < 1 || selectedItems > ItemsAtLocation.size()){
                cerr << "invalid selection.try again\n" ;
                continue;
            }
            int index = selectedItems - 1 ;
            GetItems().push_back(ItemsAtLocation[index]) ;
            cout << (*this).GetName() << " picked up " << ItemsAtLocation[index].getName() << ".\n";
            ItemsAtLocation.erase(ItemsAtLocation.begin() + index) ; 
            if(ItemsAtLocation.empty()){
            cout << "no more items available in " << chosenplace->get_name() << ".\n" ;
            break ;
        }
    }
        for(const auto& i : ItemsAtLocation){
            GetItems().push_back(i) ;
            cout << (*this).GetName() << " picked up " << i.getName() << " from location " << chosenplace->get_name() << '\n' ;
        }
        ItemsAtLocation.clear() ;
    }
}

Mayor::Mayor(GameMap& Map) : Hero("mayor" , 5 , Map.get_location_by_name("Theatre") , "No special action.") {
    Map.get_location_by_name("Theatre")->add_hero(this) ; 
}

void Mayor::DisplayInfo()const {
    cout << GetName() << ":\n" << "location: " << *GetCurrentLocation() << "\n" << "Actions: " << 
    GetRemainingActions() << "/" << 5 << '\n'  ; 
}

void Mayor::SpecialAction(Location*) {
    cout << "this hero does not have any special action\n" ; 
}

Courier::Courier(GameMap& Map , TurnManager& m): Hero("courier" , 4 , Map.get_location_by_name("Shop") , "can be moved to a location where one of the other heroes is.") , turn(m) {
    Map.get_location_by_name("Shop")->add_hero(this) ; 
} 

void Courier::DisplayInfo() const {
    cout << GetName() << ":\n" << "location: " << *GetCurrentLocation() << "\n" << "Actions: " << 
    GetRemainingActions() << "/" << 4 << '\n'  ;    
}

void Courier::SpecialAction(Location *){
    auto heroes = turn.get_heroes() ; 
    
    for(size_t i = 0 ; i < heroes.size() ; i++){
        if(heroes[i]->GetName() != "courier") 
            cout << heroes[i]->GetName() << " (current location: " << *(heroes[i]->GetCurrentLocation() )<< ")\n"; 
    }
    cout << "choose a hero: " ; 
    string chosenName ; cin >> chosenName ; 
    for(Hero* h : heroes)
    if(h->GetName() == chosenName && h->GetName() != "courier"){
        MoveTo(h->GetCurrentLocation()) ; 
        return ; 
    }
    cout << "invalid choice\n" ; 
}
Scientist::Scientist(GameMap& Map) : Hero("scientist" , 4 , Map.get_location_by_name("Institute") , "No special action.") {
    Map.get_location_by_name("Institute")->add_hero(this) ; 
}

void Scientist::DisplayInfo() const {
    cout << GetName() << ":\n" << "location: " << *GetCurrentLocation() << "\n" << "Actions: " << 
    GetRemainingActions() << "/" << 4 << '\n'  ;    
}

void Scientist::SpecialAction(Location *){
    cout << "this hero does not have any special action\n" ; 
}
