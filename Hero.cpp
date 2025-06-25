#include "Hero.hpp"
#include <iostream>
#include <stdexcept>
#include <algorithm>

using namespace std ; 

Hero::Hero( std::string name , int MaxActions , Location* StartingLocation , std::string specialAction)
: name(name) , RemainingActions(MaxActions) , MaxActions(MaxActions) , currentLocation(StartingLocation) , specialAction(specialAction){

    ListOfActions = {
        {ActionType::Move , "Move" , "You can move to any places near by. you can also move the villagers with you."} ,
        {ActionType::Guide , "Guide" , "You can move the villagers (that are in your place) to the closest place or move the villagers(that are in your neigbor place) to your place."} , 
        {ActionType::Pickup , "Pickup" , "You can take any number of item you want from the place you are."},
        {ActionType::Advance , "Advance" , "You can speed up a monster-related mission and complete it to get closer to defeating that monster."} ,
        {ActionType::Defeat , "Defeat" , "Once you have completed all the missions related to catching a monster, you can defeat it, but keep in mind that you must be present in the area where the monster is located."} ,
        {ActionType::SpecialAction , "Special" , specialAction} , 
    };
}

void Hero::DisplayActions(){

    cout << "----ACTIONS----\n" ; 
    for(const auto a : ListOfActions)
        cout << a.name << ": " << a.Description << '\n' ; 
    cout << "---------------\n" ; 
}

void Hero::resetMaxActions(){
    (this)->SetRemainingActions((this)->getMaxActions()) ; 
}

void Hero::playedPerk(Perkcards card){
    playedCards.push_back(card) ;   
}

void Hero::displaycards(){
    cout << "perk cards: " ; 
    for(size_t i = 0 ; i < playedCards.size() ; i++)
        cout << playedCards[i].get_Event() << ", " ;
    cout << endl ; 
}

vector<Item> Hero::GetItems(){ return ListOfitems ; }

void Hero::removeItems(const Item & i){
    for(size_t j = 0 ; j < (*this).GetItems().size() ; j++){
        if(ListOfitems[j].getName() == i.getName()){
            cout << "removing item " << i.getName() << " from " << (*this).GetName() << " list\n" ;
            ListOfitems.erase(ListOfitems.begin() + j) ;
        }
    }
}

void Hero::AdvanceActionForDracula(){
    int chosenNumber = -1 ; 
    int totalStrength = 0 ;
    vector<Item> selected ;

    while(true){
        vector<Item> items = (*this).GetItems() ;
        if(items.empty()){
            cerr << (*this).GetName() << " has no more items!\n" ; 
            break; 
        }
        cout << "total strength: " << totalStrength << '\n' ; 
        cout << "items to choose:\n" ;
        for(size_t i = 0 ; i < items.size() ; i++)
            cout << (i + 1) << "-" << items[i].getName() << "(color: " << (*this).colorItems(items[i].getColor()) << ", strength: " << items[i].getStrength() << ")\n" ;
        
        cout << "please select any item by number(0 to end): " ;
        cin >> chosenNumber ; 
        if(chosenNumber == 0) break;
        if(chosenNumber < 1 && chosenNumber > static_cast<int>(items.size())){
            cerr << "invalid. please try again!\n" ;
            continue;
        }
        Item chosenItem = items[chosenNumber - 1] ;
        if(chosenItem.getColor() != ItemColor::RED){
            cerr << "what you chosen is not red! try again.\n" ; 
            continue;
        }
        (*this).removeItems(chosenItem) ;
        selected.push_back(chosenItem) ; 
        totalStrength += chosenItem.getStrength() ;

        if(totalStrength >= 6){
            cout << "total strength has reached to " << totalStrength << ". do you want to choose more items?(yes/no) " ;
            string ans ; cin >> ans ; 
            if(ans == "no") break;
        }
        else if(totalStrength < 6 && items.empty()){
            cout << "no more items left and strength did not reach 6\n" ;
        }
    }
    if(!selected.empty()){
        cout << "items chosen for advance action:\n " ;
        for(size_t i = 0 ; i < selected.size() ; i++){
            cout << (i + 1) << "-" << selected[i].getName() << "(color: " << (*this).colorItems(selected[i].getColor()) << ", strength:" << selected[i].getStrength() << ").\n" ;
            (*this).GetCurrentLocation()->add_item(selected[i]) ; 
        }
    }
    else cout << "no item was selected for advance action!\n" ;
}

void Hero::AdvanceActionForInvisibleMan(){
    int chosenNumber = -1 ; 
    vector<Item> selected ;

    while(true){
        vector<Item> items = (*this).GetItems() ;
        vector<Item> ItemsToChoose ; 
        if(items.empty()){
            cerr << (*this).GetName() << " has no more items!\n" ; 
            break; 
        }
        cout << "items to choose:\n" ;
        for(size_t i = 0 ; i < items.size() ; i++){
            if(items[i].getLocationName() == "Inn" || items[i].getLocationName() == "Barn" || items[i].getLocationName() == "Institute" || items[i].getLocationName() == "Laboratory" || items[i].getLocationName() == "Mansion")
                ItemsToChoose.push_back(items[i]) ;
        }
        for(size_t i = 0 ; i < ItemsToChoose.size() ; i++)
                cout << (i + 1) << "-" << ItemsToChoose[i].getName() << "(location: " << ItemsToChoose[i].getLocationName() << ")\n" ;
        
        cout << "please select any item by number(0 to end): " ;
        cin >> chosenNumber ; 
        if(chosenNumber == 0) break;
        if(chosenNumber < 1 && chosenNumber > static_cast<int>(ItemsToChoose.size())){
            cerr << "invalid. please try again!\n" ;
            continue;
        }
        Item chosenItem = items[chosenNumber - 1] ;

        (*this).removeItems(chosenItem) ;
        selected.push_back(chosenItem) ; 

    }
    if(!selected.empty()){
        cout << "items chosen for advance action:\n " ;
        for(size_t i = 0 ; i < selected.size() ; i++){
            cout << (i + 1) << "-" << selected[i].getName() << "(color: " << (*this).colorItems(selected[i].getColor()) << ", strength:" << selected[i].getStrength() << ")\n" ;
            (*this).GetCurrentLocation()->add_item(selected[i]) ; 
        }
    }
    else cout << "no item was selected for advance action!\n" ;
}

void Hero::PickupItems(){ //pick up item from current location
    vector<Item>& ItemsAtLocation = (*this).GetCurrentLocation()->get_items() ;
    if(ItemsAtLocation.empty()){
        cout << (*this).GetName() << " found no items to pick up in the current location(" << (*this).GetCurrentLocation()->get_name() << ")\n" ;
        return ;
    }
    int selectedItems = -1 ; 
    while(!ItemsAtLocation.empty()){
        cout << "items available in " << ((*this).GetCurrentLocation())->get_name() << " :\n" ;
        for(size_t i = 0 ; i < ItemsAtLocation.size() ; i++){
            cout << (i+1) << ". " << ItemsAtLocation[i].getName() << 
                "( color: " <<  colorItems(ItemsAtLocation[i].getColor()) << ", " <<
                "strength: " << ItemsAtLocation[i].getStrength() << ")\n";
        }
        cout << "enter the item number to pick up(0 to end): " ; 
        cin >> selectedItems ;
        if(selectedItems == 0) //هیچی انتخاب نکرد
            return ;
        if(selectedItems < 1 || selectedItems > ItemsAtLocation.size()){
            cerr << "invalid selection.try again\n" ;
            continue;
        }
        int index = selectedItems - 1 ;
        ListOfitems.push_back(ItemsAtLocation[index]) ;
        cout << (*this).GetName() << " picked up " << ItemsAtLocation[index].getName() << ".\n";
        ItemsAtLocation.erase(ItemsAtLocation.begin() + index) ; 
        if(ItemsAtLocation.empty()){
            cout << "no more items available in " << (*this).GetCurrentLocation()->get_name() << ".\n" ;
            break ;
        }
    }
    for(const auto& i : ItemsAtLocation){
        ListOfitems.push_back(i) ;
        cout << (*this).GetName() << " picked up " << i.getName() << " from location " << (*this).GetCurrentLocation()->get_name() << '\n' ;
    }
    ItemsAtLocation.clear() ;
}

void Hero::SpecialPickup(Location* chosenplace){ //pick up item from neighboring place(archaeologist)

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
                    "( color : " << (*this).colorItems(ItemsAtLocation[i].getColor()) <<
                     " , strength: " << ItemsAtLocation[i].getStrength() << ")\n";
        
            cout << "enter the item number to pick up: " ; 
            cin >> selectedItems ;
            if(selectedItems == 0) //هیچی انتخاب نکرد
                return ;
            if(selectedItems < 1 || selectedItems > ItemsAtLocation.size()){
                cerr << "invalid selection.try again\n" ;
                continue;
            }
            int index = selectedItems - 1 ;
            ListOfitems.push_back(ItemsAtLocation[index]) ;
            cout << (*this).GetName() << " picked up " << ItemsAtLocation[index].getName() << ".\n";
            ItemsAtLocation.erase(ItemsAtLocation.begin() + index) ; 
            if(ItemsAtLocation.empty()){
            cout << "no more items available in " << chosenplace->get_name() << ".\n" ;
            break ;
        }
    }
        for(const auto& i : ItemsAtLocation){
            ListOfitems.push_back(i) ;
            cout << (*this).GetName() << " picked up " << i.getName() << " from location " << chosenplace->get_name() << '\n' ;
        }
        ItemsAtLocation.clear() ;
    }
}

void Hero::DisplayItem(){
    cout << "items collected:\n" ;
    if(GetItems().empty()) cout << "-\n" ;
    for(const auto i : GetItems()){
        cout << i.getName() << '('  ;
        cout << colorItems(i.getColor()) ; 
        cout << ", strength:" << i.getStrength() << ")\n" ; 
    }
    cout << '\n' ; 
}

string Hero::colorItems(const ItemColor & color){
    switch (color){
    case ItemColor::BLUE :
        return "Blue" ;
    case ItemColor::RED :
        return "Red" ; 
    case ItemColor::YELLOW :
        return "Yellow" ; 
    default:
        break;
    }
}

bool Hero::PerformTheAction(string act)  {

    if(act == "Quit" || act == "Help" || act == "Perk") return true;

    for(const auto& ac : ListOfActions){
        if(ac.name == act){
            if(act == "Special" && !HasSpecialAction()){
                throw runtime_error("This hero does not have special action") ; 
            }

            if(GetRemainingActions() > 0 && act != "end" && act != "help"){
                cout << "[playing " << act << "]\n" ;
                SetRemainingActions(GetRemainingActions()-1) ; 
                return true; 
            }else
                throw runtime_error("not enough action remaining!") ; 
        }
    }
    throw runtime_error("action not available!") ; 

}

string Hero::GetName()const{
    return name ; 
}
int Hero::getMaxActions() const{
    return MaxActions;
}
int Hero::GetRemainingActions() const{
    return RemainingActions ;
}
string Hero::GetSpecialActionInfo() const{
    return specialAction ; 
}
Location* Hero::GetCurrentLocation() const{
    return currentLocation ; 
}
void Hero::SetCurrentLocation(Location* location){
    currentLocation = location ;
}
void Hero::MoveTo(Location* new_location , vector<villager*> vill){ // move with villagers
    if (!new_location) return;
    
    if(new_location == (*this).GetCurrentLocation())
        throw runtime_error("already in the location!") ; 
    
    SetCurrentLocation(new_location) ; 
    cout << (*this).GetName() << " moved to " << *(*this).GetCurrentLocation() << '\n' ; 

    if (currentLocation)
        currentLocation->remove_hero(this);
    
    new_location->add_hero(this);

    for(auto *v : vill){
        v->set_currentLocation(new_location) ;
        cout << v->get_name() << " moved with hero to " << *(v->get_currentLocation()) << '\n';
    }  
}

void Hero::MoveTo(Location* new_location){ //without villager
    if(new_location == (*this).GetCurrentLocation())
        throw runtime_error("already in the location!") ;
    
    (*this).SetCurrentLocation(new_location) ; 
    cout << (*this).GetName() << " moved to " << *((*this).GetCurrentLocation()) << '\n' ; 

}
bool Hero::hasvillagerHere() const{

    for(auto *v : villager::all() ){ //باید استاتیک باشد تا اینگونه ازش استفاده کنیم
        if(v->get_currentLocation() == (*this).GetCurrentLocation())
            return true ; 
    } 
    return false ;
}

void Hero::showvillagersHere() const{
    vector<villager*> vill ; 
    for(auto *v : villager::all() ){
        if(v->get_currentLocation() == (*this).GetCurrentLocation()){
            vill.push_back(v) ; 
        }
    }
    for(auto *v : vill)
        cout << v->get_name() << " , " ; 
}

vector<villager*> Hero::villagerHere() const
{
    vector<villager*> vill ; 
    for(auto *v : villager::all() ){
        if(v->get_currentLocation() == GetCurrentLocation())
            vill.push_back(v) ; 
    }
    return vill ;
}

void Hero::SetRemainingActions(int newRemaining)
{
    RemainingActions = newRemaining ;
}
