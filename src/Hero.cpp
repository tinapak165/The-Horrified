#include "Hero.hpp"
#include <iostream>
#include <stdexcept>
#include <algorithm>

using namespace std ; 

Hero::Hero( std::string name , int MaxActions , Location* StartingLocation , std::string specialAction , std::string t)
: name(name) , RemainingActions(MaxActions) , MaxActions(MaxActions) , currentLocation(StartingLocation) , specialAction(specialAction) , HeroTex_path(t){

    ListOfActions = {
        {ActionType::Move , "move" , "Move to any locations near by."} ,
        {ActionType::Guide , "guide" , "Move villagers to your location or to a neighbor"} , 
        {ActionType::Pickup , "pickup" , "Take any number of item you want from your location."},
        {ActionType::Advance , "advance" , "You can speed up a monster-related mission and complete it."} ,
        {ActionType::Defeat , "defeat" , "Defeat a monster when you are in the same place as monster."} ,
        {ActionType::SpecialAction , "special" , specialAction} , 
    };
}

bool Hero::drawCancelButton(){
    ClickableText Backbutton("Cancel" , {100 , 400} , 20 , RAYWHITE) ;
    Backbutton.Draw() ; 
    if(Backbutton.isClicked()) 
        return true ; 
    return false ;
}

void Hero::DisplayActions() const{
    const float panelX = 100 ; const float panelY = 80 ; 
    const float panelW = 750 ; const float panelH = 300 ; 

    DrawRectangle(panelX , panelY , panelW , panelH , Fade(DARKGRAY , 0.9f)) ;
    DrawRectangleLines(panelX , panelY , panelW , panelH , GRAY) ;
    DrawRectangleLinesEx({panelX, panelY, panelW, panelH}, 3, RAYWHITE);

    float y = panelY + 20 ; 

    DrawText("----ACTIONS----" , panelX+20 , y , 25 , GREEN) ; 
    y+=40 ;
    for (const auto& action : ListOfActions) {
        string line = action.name + ": " + action.Description;
        
        DrawText(line.c_str(), panelX + 20, y, 20, WHITE);
        y += 30;
    }
}


void Hero::DisplayInfo() const {
    float panelX = 210;
    float panelY = 90;
    float panelWidth = 750;
    float panelHeight = 190;

    DrawRectangle(panelX, panelY, panelWidth, panelHeight, Fade(DARKGRAY, 0.1f));
    DrawRectangleLines(panelX, panelY, panelWidth, panelHeight, GRAY);

    float textX = panelX + 20;
    float textY = panelY + 20;

    DrawText(this->GetName().c_str(), textX, textY, 25, YELLOW);
    textY += 40;

    string location = "Location: " + this->GetCurrentLocation()->get_name();
    DrawText(location.c_str(), textX, textY, 20, WHITE);
    textY += 30;

    string actions = "Actions: " + std::to_string(this->GetRemainingActions()) + '/' + std::to_string(this->getMaxActions());
    DrawText(actions.c_str(), textX, textY, 20, WHITE);
    textY += 30;

    string special = "Special: " + this->GetSpecialActionInfo();
    DrawText(special.c_str(), textX, textY, 20, WHITE);
}

void Hero::resetMaxActions(){
    (this)->SetRemainingActions((this)->getMaxActions()) ; 
}

void Hero::AddAvailablePerk(std::unique_ptr<Perkcard> card){
    availableCards.push_back(std::move(card)) ;   
}

void Hero::displayPlayedCards() const{

    const float panelX = 80 ; const float panelY = 80 ; 
    const float panelW = 600 ; const float panelH = 400 ; 
    DrawRectangleRec({panelX , panelY , panelW , panelH} , Fade(DARKGRAY , 0.95f)) ;
    DrawRectangleLinesEx({panelX , panelY , panelW , panelH} , 3 , RAYWHITE) ;

    float y = 100; 

    DrawText("Played Perk cards:" , 115 , 105 , 24 , RAYWHITE) ; 
    y+=40 ;
    if(playedCards.empty())
        DrawText("-", 350 , 105 , 24 , WHITE ) ;
    else{
        for (size_t i = 0 ; i < playedCards.size() ; i++) {
            string line = playedCards[i]->get_name() ;
            
            DrawText(line.c_str(), panelX + 20, y, 20, WHITE);
            y += 30;
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

    float panelX = 100, panelY = 80, panelWidth = 600, panelHeight = 400;
    
    DrawRectangleRec({panelX, panelY, panelWidth, panelHeight}, Fade(DARKGRAY, 0.95f));
    DrawRectangleLinesEx({panelX, panelY, panelWidth, panelHeight}, 3, RAYWHITE);

    DrawText("Items Collected:", 115, 105, 24, RAYWHITE);

    if (this->GetItems().empty()) 
        DrawText("-", 350, 105, 24, RAYWHITE);

    int startY = 150;

    for (const auto& item : GetItems()) {
        std::string itemStr = item.getName() + '('+ item.getLocationName() + ", " + Item::color_to_string(item.getColor()) +
            ", " + std::to_string(item.getStrength()) + ")";
        
        DrawText(itemStr.c_str(), 110, startY, 22, LIGHTGRAY);
        startY += 30;
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
void Hero::StartSpecial(GameMap &){
    message = "This hero does not have any special action!" ;
    shown = false ;  
}

void Hero::UpdateSpecial(bool& done) {
    if (!shown) {
        shown = true;
        messageStartTime = GetTime();
    }
    else if (GetTime() - messageStartTime >= 2.0) 
        done = true;
}

void Hero::DrawSpecial() {
    DrawText(message.c_str(), 100, 140, 22, WHITE);
}

bool Hero::hasvillagerHere() const
{
    for(auto *v : Villager::all() ){ 
        if(v->get_currentLocation() == (*this).GetCurrentLocation())
            return true ; 
    } 
    return false ;
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

Texture2D Hero::getTexture(){ return HeroTex; }

void Hero::loadTexture(){ HeroTex = LoadTexture(HeroTex_path.c_str()); }