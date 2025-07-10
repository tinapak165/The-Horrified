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

void Hero::AddAvailablePerk(std::unique_ptr<Perkcard> card){
    availableCards.push_back(std::move(card)) ;   
}

void Hero::displayavailblecards() const{
    cout << "available perk cards: " ; 
    for(size_t i = 0 ; i < availableCards.size() ; i++)
        cout << availableCards[i]->get_name()<< ", " ;
    cout << endl ; 
}

void Hero::displayPlayedCards() const{
    cout << "played perk cards: " ; 
    if(playedCards.empty()){
        cout << "-\n" ;
    }else{
        for(size_t i = 0 ; i < playedCards.size() ; i++)
            cout << playedCards[i]->get_name() << ", " ;
        cout << endl ;        
    }
}

vector<unique_ptr<Perkcard>>& Hero::GetAvailablePerkCards(){
    return availableCards;
}

void Hero::addPlayedCards(std::unique_ptr<Perkcard> p){
    playedCards.push_back(std::move(p)) ;
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
            cout << (i + 1) << "-" << items[i].getName() << "(color: " << items[i].color_to_string(items[i].getColor())  << ", strength: " << items[i].getStrength() << ")\n" ;
        
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
            cout << (i + 1) << "-" << selected[i].getName() << "(color: " << selected[i].color_to_string(selected[i].getColor()) << ", strength:" << selected[i].getStrength() << ").\n" ;
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
void Hero::DefeatAction(Hero* h , InvisibleMan* invisibleMan , Dracula* dracula){
                   
    Location* heroLoc = h->GetCurrentLocation();       
    if (invisibleMan && invisibleMan->get_location() == heroLoc) {
        if (invisibleMan->can_be_defeated()) {
            cout << "You are ready to defeat the Invisible Man! Use RED items (total strength >= 9).\n";
            int redPower = h->select_items_to_defeat(ItemColor::RED);
        if (redPower >= 6) {
            invisibleMan->set_location(nullptr); 
            cout << "Invisible Man has been defeated!\n";
        } else {
            cout << "Not enough RED item power. Invisible Man survived.\n";
            }
        }
    }
    if (dracula && dracula->get_location() == heroLoc) {
        if (dracula->can_be_defeated()) {
            cout << "You are ready to defeat Dracula! Select yellow items to attack.\n";
            int yellowPower = h->select_items_to_defeat(ItemColor::YELLOW);
                
            if (yellowPower >= 6) {
                cout << "Dracula has been defeated!\n";
                dracula->set_location(nullptr); 
                } else {
                    cout << "Not enough yellow item power. dracula did not die.\n";
                    }
        } else {
            cout << "You must destroy all coffins first to defeat Dracula.\n";
            }
    }else{
        cerr << "you can not use defeat action unless you are in monster place\n" ;
        }
}
void Hero::PickupItems()
{
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
                "( color: " <<  ItemsAtLocation[i].color_to_string(ItemsAtLocation[i].getColor()) << ", " <<
                "strength: " << ItemsAtLocation[i].getStrength() << ")\n";
        }
        cout << "enter the item number to pick up(0 to end): " ; 
        cin >> selectedItems ;
        if(selectedItems == 0) return ;
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

void Hero::DisplayItem(){
    cout << "items collected:\n" ;
    if(GetItems().empty()) cout << "-\n" ;
    for(const auto i : GetItems()){
        cout << i.getName() << '('  ;
        cout << i.color_to_string(i.getColor()) ; 
        cout << ", strength:" << i.getStrength() << ")\n" ; 
    }
    cout << '\n' ; 
}

bool Hero::PerformTheAction(string act)  {

    if(act == "quit" || act == "help" || act == "perk") return true;
    for(const auto& ac : ListOfActions){
        if(ac.name == act){
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
void Hero::MoveAction(GameMap& map, Hero* h){
    string chosenPlace ; 
    cout << "Which neighboring place do you want to move to? " ;
    cin >> chosenPlace ;
    Location* currentLoc = h->GetCurrentLocation() ; 
    Location* chosenLocation = map.get_location_by_name(chosenPlace);

    if(currentLoc->findNeighbor(chosenPlace)){
        if(h->hasvillagerHere()){
            auto here = h->villagerHere() ; 
            string ans ;
            cout << "some villagers are at the same place as you. " ; 
            h->showvillagersHere() ; 
            cout << "\ndo you want to move the villagers with you?(yes = moving all villagers with you/no = moving alone) " ; 
            cin >> ans ; 
            if(ans == "yes")
                h->MoveTo(chosenLocation , here) ; 
            else if(ans == "no")
                h->MoveTo(chosenLocation) ;
            else cerr << "wrong answer\n" ; 
        }
        else { 
            h->MoveTo(chosenLocation); 
        }    
    }
    else{
        cerr << "what you have chosen is not a neighboirng place!\n" ;  
    }

}

void Hero::MoveTo(Location *new_location, vector<Villager *> vill){ // move with villagers
    if (!new_location) return;
    
    if(new_location == (*this).GetCurrentLocation()){
       // throw runtime_error("already in the location!") ; 
        cerr << "already in the location!\n" ; 
    }
    (*this).GetCurrentLocation()->remove_hero(this) ; 
    (*this).SetCurrentLocation(new_location) ;
    new_location->add_hero(this) ;  

    cout << (*this).GetName() << " moved to " << *(*this).GetCurrentLocation() << '\n' ; 
    
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
}
void Hero::GuideAction(Hero * h , GameMap& map){
    string chosenPlace , mode ; 
    Location* currentLoc = h->GetCurrentLocation() ; 
    cout << "Guide:\n" 
         << "current -> move a villager from your location to a neighbor\n"
         << "neighbor -> move a villager from a neighbor to your location\n"
         << "choose: ";
     cin >> mode ; 

    if(mode == "current"){
        if(h->hasvillagerHere()){
            cout << "some villagers are at the same place as you: " ;
            h->showvillagersHere() ;
            cout << "\nwho do you want to move? " ; 
            string chosenvillager ;
            cin.ignore(numeric_limits<streamsize>::max(), '\n') ; 
            getline(cin , chosenvillager) ; 
            bool found = false ; 
            for(auto *v : h->villagerHere()){
                if(chosenvillager == v->get_name()){
                    found = true ; 
                    cout << "Which neighboring place do you want to move them? " ;
                    cin >> chosenPlace ; 
                    if(currentLoc->findNeighbor(chosenPlace)){
                        Location* chosenLocation = map.get_location_by_name(chosenPlace) ;  
                        v->MoveTo(chosenLocation , chosenvillager) ;
                        //cout << chosenvillager << " has been guided to " << chosenPlace << '\n' ;
                        found = true ; 
                        break ;
                        }else{
                            //throw invalid_argument( "what you have chosen is not a neighboring place!\n");   
                            cerr << "what you have chosen is not a neighboring place!\n" ; 
                        }
                }
            } 
            if(!found){
                //  throw invalid_argument("villager not found!") ;
                cerr << "villager not found!\n" ;
            }  

        }else cerr << "no villagers at your location!\n";
    }
    else if(mode == "neighbor"){
        Location* currentLoc = h->GetCurrentLocation() ;
        vector<Villager*> availableVillager ;
        for(auto *neigbor :  currentLoc->get_neighbors()){
            for(auto *v : Villager::all()){
                if(v->get_currentLocation() == neigbor)
                    availableVillager.push_back(v) ;                                        
            }
        }
        if(availableVillager.empty()) cerr << "no villager nearby!\n" ;
        else{
            cout << "some villagers in the neigbors are: " ;
            for(auto v : availableVillager)
                cout << *(v->get_currentLocation()) << " -> " << v->get_name() << '\n';
                string chosenvillager ; 
                cout << "Which villager do you want to move to your location? " ;
                cin.ignore(numeric_limits<streamsize>::max(), '\n') ; 
                getline(cin , chosenvillager) ;  
                bool found = false ; 
                for(auto *v : availableVillager){
                    if(chosenvillager == v->get_name()){
                        v->MoveTo(currentLoc , chosenvillager) ;
                        found = true ;
                        break ;  
                    } 
                }
                if(!found){
                    // throw invalid_argument("villager not found!") ;
                    cerr << "villager not found!\n" ; 
                } 
            }
    }else{
         //throw invalid_argument("wrong answer!\n");   
        cerr << "wrong answer!\n" ;
        }      
}
void Hero::Special(Hero * h , GameMap& map){

    if(h->GetName() == "Mayor"){
        cout << "You dont have special action\n" ;
        return ;
    }
    Location* heroLoc = h->GetCurrentLocation() ; 
    vector<Location*> heroLocNeighbor = heroLoc->get_neighbors() ; 
    cout << "neighboring locations: " ;
    for(size_t i = 0 ; i <heroLocNeighbor.size() ; i++)
        cout << heroLocNeighbor[i]->get_name() << " " ;
    cout << endl ; 
    cout << "Which neighboring place do you want to pick up its items? " ;
    string chosenplace ; 
    cin >> chosenplace ;
    if(heroLoc->findNeighbor(chosenplace)){
        Location* chosenLoc = map.get_location_by_name(chosenplace) ;
        h->SpecialAction(chosenLoc) ;
        h->DisplayItem() ; 
    }else{
        //throw invalid_argument("what you have chosen is not a neighboring place!\n") ; 
        cout << "what you have chosen is not a neighboring place!\n" ; 
    } 

}

void Hero::AdvanceAction(Hero* h , Dracula* dracula , ItemPool pool , GameMap& map , InvisibleMan* invisi ){
    //for dracula
    Location* current = h->GetCurrentLocation();
    string locName = current->get_name();
    if(locName == "Cave" || locName == "Dungeon" || locName == "Crypt" || locName == "Graveyard" ){
        cout << "To destroy Dracula's coffin, use red items with total strength >= 6.\n" ;
        int totalStrength = h->AdvanceActionForDracula() ;
        if (totalStrength >= 6) {
            dracula->destroy_coffin_at(locName); 
            pool.add_items(h->getUsedItemsForDracula()) ; 
        } else {
            std::cout << "Advance action failed Not enough red item strength.\n";
            }
    }
    //for invisible man
    else if(h->GetCurrentLocation() == map.get_location_by_name("Precinct")) { 
         h->AdvanceActionForInvisibleMan(invisi) ;
        pool.add_items(h->getUsedItemsForDracula()) ; 
    }
    else cerr << "you can not do advance action unless you are in coffin places or search locations\n" ; 
         
}

bool Hero::hasvillagerHere() const
{

    for(auto *v : Villager::all() ){ 
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
                      << " (" << items[i].color_to_string(items[i].getColor())
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
            std::cout << "- " << item.getName() << " (" << item.color_to_string(item.getColor()) << ", " << item.getStrength() << ")\n";
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
std::vector<Item> Hero::getUsedItemsForDracula() {
    return usedItemsForDracula;
}

std::vector<Item> Hero::getUsedItemsForInvisibleMan() {
    return usedItemsForInvisibleMan;
}