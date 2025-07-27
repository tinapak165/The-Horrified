#include "Hero.hpp"
#include <iostream>
#include <stdexcept>
#include <algorithm>

using namespace std ; 

Hero::Hero( std::string name , int MaxActions , Location* StartingLocation , std::string specialAction , std::string t)
: name(name) , RemainingActions(MaxActions) , MaxActions(MaxActions) , currentLocation(StartingLocation) , specialAction(specialAction) , HeroTex_path(t){

    ListOfActions = {
        {ActionType::Move , "move" , "You can move to any places near by. you can also move the villagers with you."} ,
        {ActionType::Guide , "guide" , "You can move the villagers (that are in your place) to the closest place or move the villagers(that are in your neigbor place) to your place."} , 
        {ActionType::Pickup , "pickup" , "You can take any number of item you want from the place you are."},
        {ActionType::Advance , "advance" , "You can speed up a monster-related mission and complete it to get closer to defeating that monster."} ,
        {ActionType::Defeat , "defeat" , "Once you have completed all the missions related to catching a monster, you can defeat it, but keep in mind that you must be present in the area where the monster is located."} ,
        {ActionType::SpecialAction , "special" , specialAction} , 
    };
}

void Hero::DisplayActions() const{
    const float panelX = 600 ; const float panelY = 50 ; 
    const float panelW = 400 ; const float panelH = 400 ; 
    const int lineHeight = 30 ; 
    DrawRectangle(panelX , panelY , panelW , panelH , Fade(DARKGRAY , 0.9f)) ;
    DrawRectangleLines(panelX , panelY , panelW , panelH , GRAY) ;

    float y = panelY + 20 ; 

    DrawText("----ACTIONS----" , panelX+20 , y , 25 , YELLOW) ; 
    y+=40 ;
    for (const auto& action : ListOfActions) {
        string line = action.name + ": " + action.Description;
        
        DrawText(line.c_str(), panelX + 20, y, 20, WHITE);
        y += lineHeight;
    }
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

vector<Item>& Hero::GetItems(){ return ListOfitems ; }

void Hero::removeItems(const Item & i){
    for(size_t j = 0 ; j < (*this).GetItems().size() ; j++){
        if(ListOfitems[j].getName() == i.getName()){
            cout << "removing item " << i.getName() << " from " << (*this).GetName() << " list\n" ;
            ListOfitems.erase(ListOfitems.begin() + j) ;
        }
    }
}

void Hero::DefeatAction(Hero* h ,InvisibleMan*  invisibleMan ,Dracula* dracula){
                   
    Location* heroLoc = h->GetCurrentLocation();       
    if (invisibleMan && invisibleMan->get_location() == heroLoc) {
        if (invisibleMan->can_be_defeated()) {
            cout << "You are ready to defeat the Invisible Man! Use Red items (total strength >= 9).\n";
            int RedPower = h->select_items_to_defeat(ItemColor::Red);
        if (RedPower >= 6) {
            invisibleMan->set_location(nullptr); 
            cout << "Invisible Man has been defeated!\n";
        } else {
            cout << "Not enough Red item power. Invisible Man survived.\n";
            }
        }
    }
    if (dracula && dracula->get_location() == heroLoc) {
        if (dracula->can_be_defeated()) {
            cout << "You are ready to defeat Dracula! Select Yellow items to attack.\n";
            int YellowPower = h->select_items_to_defeat(ItemColor::Yellow);
                
            if (YellowPower >= 6) {
                cout << "Dracula has been defeated!\n";
                dracula->set_location(nullptr); 
                } else {
                    cout << "Not enough Yellow item power. dracula did not die.\n";
                    }
        } else {
            cout << "You must destroy all coffins first to defeat Dracula.\n";
            }
    }else{
        cerr << "you can not use defeat action unless you are in monster place\n" ;
        }
}


void Hero::DisplayItem(){

    DrawRectangle(50, 50, 700, 500, Fade(DARKGRAY, 0.8f)); 

    DrawText("Items Collected:", 70, 60, 28, YELLOW);

    if (GetItems().empty()) {
        DrawText("-", 80, 100, 24, RAYWHITE);
        return;
    }

    int startY = 100;
    int index = 1;

    for (const auto& item : GetItems()) {
        std::string itemStr = std::to_string(index) + ". " + item.getName() +
            " (Color: " + Item::color_to_string(item.getColor()) +
            ", Strength: " + std::to_string(item.getStrength()) + ")";
        
        DrawText(itemStr.c_str(), 80, startY, 22, LIGHTGRAY);
        startY += 30;
        index++;
    }
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

void Hero::SetCurrentLocation(Location *location)
{
    currentLocation = location ;
}

void Hero::MoveTo(Location *new_location, vector<Villager *> vill){ // move with villagers
    if (!new_location) return;

    (*this).GetCurrentLocation()->remove_hero(this) ; 
    (*this).SetCurrentLocation(new_location) ;
    new_location->add_hero(this , this->getTexture()) ;  

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
    
    (*this).GetCurrentLocation()->remove_hero(this) ; 
    (*this).SetCurrentLocation(new_location) ;
    new_location->add_hero(this , this->getTexture()) ;  

    cout << (*this).GetName() << " moved to " << *(*this).GetCurrentLocation() << '\n' ; 
}
void Hero::StartSpecial(GameMap &){}

void Hero::UpdateSpecial(bool& done) {}

void Hero::DrawSpecial() {}

void Hero::GuideAction(Hero *h, GameMap &map)
{
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
                            cerr << "what you have chosen is not a neighboring place!\n" ; 
                        }
                }
            } 
            if(!found){
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
                    cerr << "villager not found!\n" ; 
                } 
            }
    }else{
        cerr << "wrong answer!\n" ;
        }
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

int Hero::select_items_to_defeat(ItemColor requiRedColor) {
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
        if (chosen.getColor() != requiRedColor) {
            std::cerr << "Item is not of requiRed color.\n";
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
vector<Item> Hero::getUsedItemsForDracula() {
    return usedItemsForDracula;
}

vector<Item> Hero::getUsedItemsForInvisibleMan() {
    return usedItemsForInvisibleMan;
}

Hero::~Hero(){
    UnloadTexture(HeroTex) ;  
    if(StartingLocation) delete StartingLocation  ;
    if(currentLocation) delete currentLocation ;
}

bool Hero::HasAbility(){ return false ; }


Texture2D Hero::getTexture(){ 
    return HeroTex;
}

void Hero::loadTexture(){
    HeroTex = LoadTexture(HeroTex_path.c_str());
}