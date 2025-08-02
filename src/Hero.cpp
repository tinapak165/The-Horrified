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

    const float panelX = 600 ; const float panelY = 50 ; 
    const float panelW = 400 ; const float panelH = 400 ; 
    const int lineHeight = 30 ; 
    DrawRectangle(panelX , panelY , panelW , panelH , Fade(DARKGRAY , 0.9f)) ;
    DrawRectangleLines(panelX , panelY , panelW , panelH , GRAY) ;

    float y = panelY + 20 ; 

    DrawText("----available Perk cards----" , panelX+20 , y , 25 , YELLOW) ; 
    y+=40 ;
    if(availableCards.empty())
        DrawText("-", panelX + 20 , y , 20 , WHITE ) ;
    else{
        for (size_t i = 0 ; i < availableCards.size() ; i++) {
            string line = availableCards[i]->get_name() ;
            
            DrawText(line.c_str(), panelX + 20, y, 20, WHITE);
            y += lineHeight;
        }        
    }

}

void Hero::displayPlayedCards() const{

    const float panelX = 600 ; const float panelY = 50 ; 
    const float panelW = 400 ; const float panelH = 400 ; 
    const int lineHeight = 30 ; 
    DrawRectangle(panelX , panelY , panelW , panelH , Fade(DARKGRAY , 0.9f)) ;
    DrawRectangleLines(panelX , panelY , panelW , panelH , GRAY) ;

    float y = panelY + 20 ; 

    DrawText("----Played Perk cards----" , panelX+20 , y , 25 , YELLOW) ; 
    y+=40 ;
    if(playedCards.empty())
        DrawText("-", panelX + 20 , y , 20 , WHITE ) ;
    else{
        for (size_t i = 0 ; i < playedCards.size() ; i++) {
            string line = playedCards[i]->get_name() ;
            
            DrawText(line.c_str(), panelX + 20, y, 20, WHITE);
            y += lineHeight;
        }        
    }

}

vector<unique_ptr<Perkcard>>& Hero::GetAvailablePerkCards(){ return availableCards; }

vector<unique_ptr<Perkcard>> &Hero::GetPlayedPerkCards(){ return playedCards ; }

void Hero::addPlayedCards(std::unique_ptr<Perkcard> p){
    playedCards.push_back(std::move(p)) ;
}

vector<Item>& Hero::GetItems(){ return ListOfitems ; }

void Hero::addItems(Item item)
{
    GetItems().push_back(item) ; 

}

void Hero::removeItems(const Item & i){
    for(size_t j = 0 ; j < (*this).GetItems().size() ; j++){
        if(ListOfitems[j].getName() == i.getName()){
            cout << "removing item " << i.getName() << " from " << (*this).GetName() << " list\n" ;
            ListOfitems.erase(ListOfitems.begin() + j) ;
        }
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
    if(currentLocation)
        currentLocation->remove_hero(this) ;
    currentLocation = location ; 
    if(location)
        location->add_hero(this , this->getTexture());
}

void Hero::MoveTo(Location *new_location, vector<Villager *> vill){ // move with villagers
    if (!new_location) return;

    (*this).SetCurrentLocation(new_location) ;

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
    
    (*this).SetCurrentLocation(new_location) ;

    cout << (*this).GetName() << " moved to " << *(*this).GetCurrentLocation() << '\n' ; 
}
void Hero::StartSpecial(GameMap &){}

void Hero::UpdateSpecial(bool& done) {}

void Hero::DrawSpecial() {}

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

bool Hero::isDead(){ return this->GetCurrentLocation() == nullptr; }

Texture2D Hero::getTexture(){ return HeroTex; }

void Hero::loadTexture(){ HeroTex = LoadTexture(HeroTex_path.c_str()); }