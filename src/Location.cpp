#include "Location.hpp"

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

void Location::add_item(const Item& item) {
    items.push_back(item);
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
        if(n->get_name() == GameMap::checkString(name))
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

    DrawRectangle(600, 50, 350, 900, Fade(DARKGRAY, 0.8f));

    DrawText(name.c_str(), 620, 70, 30, WHITE);

    DrawText("Items:", 620, 120, 25, YELLOW);
    
    float itemStartY = 150;
    float itemSpacing = 180; 

    std::vector<Item> uniqueItems ; 
    std::vector<int> counts ; 
    
    for (const auto& item : items){
        bool found = false ; 
        for(int i = 0 ; i < uniqueItems.size() ; i++){
            if(uniqueItems[i].getName() == item.getName()){
                counts[i]++ ;
                found = true ;
                break ; 
            }
        }
        if(!found){
            uniqueItems.push_back(item) ;
            counts.push_back(1) ;
        }
    }
    for (int i = 0; i < uniqueItems.size(); ++i) {
        float y = itemStartY + i * itemSpacing;

        std::string displayName = uniqueItems[i].getName();
        if (counts[i] > 1)
            displayName += " x" + std::to_string(counts[i]);

        DrawText(displayName.c_str(), 620, y, 20, WHITE);

        float textureScale = 150.0f / uniqueItems[i].getTexture().width;
        DrawTextureEx(uniqueItems[i].getTexture(), {620, y + 30}, 0.0f, textureScale, WHITE);
    }
}
Location::~Location(){
    UnloadTexture(iconTexture);
}
