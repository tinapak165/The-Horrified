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

void Hero::DisplayActions() const{

    cout << "----ACTIONS----\n" ; 
    for(const auto a : ListOfActions)
        cout << a.name << ": " << a.Description << '\n' ; 
    cout << "---------------\n" ; 
}

void Hero::resetMaxActions(){
    (this)->SetRemainingActions((this)->getMaxActions()) ; 
}

void Hero::AddAvailablePerk(Perkcards card){
    availableCards.push_back(card) ;   
}

void Hero::displayavailblecards() const{
    cout << "available perk cards: " ; 
    for(size_t i = 0 ; i < availableCards.size() ; i++)
        cout << availableCards[i].get_Event() << ", " ;
    cout << endl ; 
}

void Hero::displayPlayedCards() const{
    cout << "played perk cards: " ; 
    if(playedCards.empty()){
        cout << "-\n" ;
    }else{
        for(size_t i = 0 ; i < playedCards.size() ; i++)
            cout << playedCards[i].get_Event() << ", " ;
        cout << endl ;        
    }
}

vector<Perkcards>& Hero::GetAvailablePerkCards(){
    return availableCards;
}

void Hero::addPlayedCards(Perkcards p){
    playedCards.push_back(p) ;
    for(size_t i = 0 ; i < this->GetAvailablePerkCards().size() ; i++){
        if(p.get_Event() == availableCards[i].get_Event()){
            this->GetAvailablePerkCards().erase(this->GetAvailablePerkCards().begin() + i);
            break;
        }
    }
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
int Hero::AdvanceActionForDracula(){
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
        
        cout << "please select any item by number(0 is for quiting): " ;
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
            cout << "total strength has reached to " << totalStrength << '\n';
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
    return totalStrength ; 
}

void Hero::AdvanceActionForInvisibleMan(InvisibleMan* monster){
    vector<Item> items = this->GetItems() ; 
    vector<Item> evidenceItems ; 
    for(const Item& item : items){
        std::string loc = item.getLocationName() ; 
        if (loc == "Inn" || loc == "Barn" || loc == "Institute" || loc == "Laboratory" || loc == "Mansion") {
            evidenceItems.push_back(item);  
        }  
    }
    if(evidenceItems.empty()){
        std::cout << "You have no valid items for evidence.\n";
        return;        
    }
    std::cout << "Choose one item to place as evidence against Invisible Man:\n";

    for (size_t i = 0; i < evidenceItems.size(); ++i) {
        std::cout << i + 1 << ". " << evidenceItems[i].getName()
                  << " (from " << evidenceItems[i].getLocationName() << ")\n";
    }
    int choice;
    std::cout << "Enter number (or 0 to cancel): ";
    std::cin >> choice;

    if (choice <= 0 || choice > static_cast<int>(evidenceItems.size())) {
        std::cout << "Cancelled.\n";
        return;
    }
    Item selected = evidenceItems[choice - 1];  

    if(monster->add_evidence(selected.getLocationName())) {
        removeItems(selected);
        std::cout << "Evidence placed successfully.\n";
    }else{
        std::cout << "Evidence from that location already exists. Choose another.\n";
    } 

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
                //throw runtime_error("This hero does not have special action") ;
                cerr << "This hero does not have special action\n" ;
                return false ;  
            }

            if((*this).GetRemainingActions() > 0){
                cout << "[playing " << act << "]\n" ;
                (*this).SetRemainingActions((*this).GetRemainingActions()-1) ; 
                return true; 
            }else{
               // throw runtime_error("not enough action remaining!") ; 
                cerr << "not enough action remaining!(Quit to end the phase)\n" ;
                return false ; 
            }
        }
    }
    //throw runtime_error("action not available!") ;
    cerr << "action not available!\n" ;
    return false ;  

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
void Hero::MoveTo(Location* new_location , vector<Villager*> vill){ // move with villagers
    if (!new_location) return;
    
    if(new_location == (*this).GetCurrentLocation()){
       // throw runtime_error("already in the location!") ; 
        cerr << "already in the location!\n" ; 
    }
    (*this).GetCurrentLocation()->remove_hero(this) ; 
    (*this).SetCurrentLocation(new_location) ;
    new_location->add_hero(this) ;  

    cout << (*this).GetName() << " moved to " << *(*this).GetCurrentLocation() << '\n' ; 

    if (currentLocation)
        currentLocation->remove_hero(this);
    
    new_location->add_hero(this);

    for(auto *v : vill){
        v->get_currentLocation()->remove_villager(v) ; 
        v->set_currentLocation(new_location) ;
        new_location->add_villager(v) ; 
        cout << v->get_name() << " moved with hero to " << *(v->get_currentLocation()) << '\n';
    }  
}

void Hero::MoveTo(Location* new_location){ //without villager
    if (!new_location) return;
    
    if(new_location == (*this).GetCurrentLocation()){
       // throw runtime_error("already in the location!") ; 
        cerr << "already in the location!\n" ; 
    }
    (*this).GetCurrentLocation()->remove_hero(this) ; 
    (*this).SetCurrentLocation(new_location) ;
    new_location->add_hero(this) ;  

    cout << (*this).GetName() << " moved to " << *(*this).GetCurrentLocation() << '\n' ; 

    if (currentLocation)
        currentLocation->remove_hero(this);
    
    new_location->add_hero(this);

}
bool Hero::hasvillagerHere() const{

    for(auto *v : Villager::all() ){ //باید استاتیک باشد تا اینگونه ازش استفاده کنیم
        if(v->get_currentLocation() == (*this).GetCurrentLocation())
            return true ; 
    } 
    return false ;
}

void Hero::showvillagersHere() const{
    vector<Villager*> vill ; 
    for(auto *v : Villager::all() ){
        if(v->get_currentLocation() == (*this).GetCurrentLocation()){
            vill.push_back(v) ; 
        }
    }
    for(auto *v : vill)
        cout << v->get_name() << " , " ; 
}

vector<Villager*> Hero::villagerHere() const
{
    vector<Villager*> vill ; 
    for(auto *v : Villager::all() ){
        if(v->get_currentLocation() == GetCurrentLocation())
            vill.push_back(v) ; 
    }
    return vill ;
}

void Hero::SetRemainingActions(int newRemaining){
    RemainingActions = newRemaining ;
}

int Hero::select_items_to_defeat(ItemColor requiredColor) {
    int totalStrength = 0;
    vector<Item> selected;
    int choice = -1;

    while (true) {
        auto items = GetItems();
        if (items.empty()) {
            std::cerr << "No items left!\n";
            break;
        }

        std::cout << "Total selected power: " << totalStrength << "\n";
        std::cout << "Available items:\n";
        for (size_t i = 0; i < items.size(); ++i) {
            std::cout << (i + 1) << ") " << items[i].getName()
                      << " (" << colorItems(items[i].getColor())
                      << ", strength " << items[i].getStrength() << ")\n";
        }

        std::cout << "Choose item number to use (0 to stop): ";
        std::cin >> choice;
        if (choice == 0) break;

        if (choice < 1 || choice > static_cast<int>(items.size())) {
            std::cerr << "Invalid selection.\n";
            continue;
        }

        Item chosen = items[choice - 1];
        if (chosen.getColor() != requiredColor) {
            std::cerr << "Item is not of required color.\n";
            continue;
        }

        removeItems(chosen);
        totalStrength += chosen.getStrength();
        selected.push_back(chosen);
    }

    if (!selected.empty()) {
        std::cout << "Used items:\n";
        for (auto& item : selected)
            std::cout << "- " << item.getName() << " (" << colorItems(item.getColor()) << ", " << item.getStrength() << ")\n";
    }

    return totalStrength;
}


bool Hero::has_items() const {
    return !ListOfitems.empty();
}

void Hero::remove_item_by_index(int index) {
    if (index >= 0 && index < static_cast<int>(ListOfitems.size())) {
        ListOfitems.erase(ListOfitems.begin() + index);
    } else {
        std::cerr << "Invalid item index. No item removed.\n";
    }
}