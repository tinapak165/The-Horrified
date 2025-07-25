#include "location.hpp"
#include <iostream>

Location::Location(const std::string& name , Rectangle area, Texture2D icon) : name(name) , clickableArea(area), iconTexture(icon){}

void Location::connect(Location * other){
    neighbors.push_back(other);
    other->neighbors.push_back(this);
}

const Rectangle& Location::get_clickable_area() const { return clickableArea; }
const Texture2D& Location::get_icon_texture() const { return iconTexture; }

void Location::set_screenPos(Vector2 pos){
    screenPos = pos ;
}
Vector2 Location::get_screenPos() const{
    return screenPos ;
}

void Location::add_item(const Item& item, Texture2D itemTex) {
    items.push_back(item);
    itemTextures.push_back(itemTex);
}

void Location::add_hero(Hero* hero, Texture2D heroTex) {
    heroes.push_back(hero);
    heroTextures.push_back(heroTex);
}
void Location::add_villager(Villager* villager){
    villagers.push_back(villager) ;
}

void Location::add_monster(Monster* monster , Texture2D monsterTex) {
    monsterTextures.push_back(monsterTex);
    monsters.push_back(monster);
}


const std::string& Location::get_name() const { 
    return name;
}

std::vector<Item>& Location::get_items()  {
    return items;
}

Location* Location::findNeighbor(const std::string& name) const{
    for(auto *n : get_neighbors()){
        if(n->get_name() == name)
            return n ; 
    }
    return nullptr ; 
}

std::vector<Villager *> &Location::get_villagers(){
    return villagers ;
}

std::vector<Monster*>& Location::get_monsters(){
        return monsters;
}
      
std::vector<Hero*>& Location::get_heroes() {
        return heroes;
}
    
const std::vector<Location*>& Location::get_neighbors() const {
    return neighbors;
}

bool Location::has_coffin(){   
    return hascoffin;
}
void Location::place_coffin(){ 
     hascoffin = true;
}
void Location::remove_coffin(){
    hascoffin = false;
}

void Location::remove_hero(Hero* hero) {
    
    for ( auto it = heroes.begin() ; it != heroes.end();){
        if (*it == hero){
            it= heroes.erase(it);
            
        }else{
            ++it;
        }
    }
}
void Location::remove_monster(Monster* monster) {
    for ( auto it = monsters.begin() ; it != monsters.end();){
        if (*it == monster){
            it= monsters.erase(it);

        }else{
            ++it;
        }
    }
}

void Location::remove_villager(Villager * villager){
    for (auto it = villagers.begin(); it != villagers.end(); ) {
        if (*it == villager) {
            it = villagers.erase(it);  
        } else {
            ++it;  
        }
    }   
}

std::ostream& operator<< (std::ostream & os , const Location & loc) {
    os<< loc.get_name() ;
    return os ;  
}

void Location::draw_info_panel() {
    DrawRectangle(600, 50, 350, 900, Fade(DARKGRAY, 0.8f));  // بکگراند پنل

    DrawText(name.c_str(), 620, 70, 30, WHITE);

    DrawText("Items:", 620, 120, 25, YELLOW);
    for (int i = 0; i < items.size(); i++) {
        DrawTexture(itemTextures[i], 620, 160 + i*100, WHITE);
        DrawText(items[i].getName().c_str(), 700, 190 + i*100, 20, WHITE);
    }

    DrawText("Heroes:", 620, 160 + items.size()*100, 25, GREEN);
    for (int i = 0; i < heroes.size(); i++) {
        DrawTexture(heroTextures[i], 620, 200 + items.size() + i, WHITE);
        DrawText(heroes[i]->GetName().c_str(), 700, 230 + items.size()*100 + i*100, 20, WHITE);
    }
}

Location::~Location(){
    UnloadTexture(iconTexture);
}
