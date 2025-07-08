#include "Heroes.hpp"
#include <iostream>
#include "Hero.hpp"
using namespace std ; 

Archaeologist:: Archaeologist(GameMap& Map): Hero("Archaeologist" , 4 , Map.get_location_by_name("Docks") , "Can take any number of items from adjacent locations.") {
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

Mayor::Mayor(GameMap& Map) : Hero("Mayor" , 5 , Map.get_location_by_name("Theatre") , "No special action.") {
    Map.get_location_by_name("Theatre")->add_hero(this) ; 
}

void Mayor::DisplayInfo()const {
    cout << GetName() << ":\n" << "location: " << *GetCurrentLocation() << "\n" << "Actions: " << 
    GetRemainingActions() << "/" << 5 << '\n'  ; 
}

void Mayor::SpecialAction(Location*) {
    cout << "this hero does not have any special action\n" ; 
}
