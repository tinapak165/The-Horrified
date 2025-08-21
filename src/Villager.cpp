#include "Villager.hpp"

std::vector<Villager*> Villager:: vil  ;

Villager::Villager(GameMap& map , const std::string& name, Location* safeplace , Location* current , std::string texpath) : name(name), currentLocation(current) , VillagerTex_path(texpath){ 

    vil.push_back(this) ;
    
    if(current)
        current->add_villager(this) ; 
     if(name == "Dr. Cranly"){
        set_safeplace(map.get_location_by_name("Precinct")); 
        VillagerTex_path = "../Assets/Villager/DrCranly.png";
    }
    else if(name == "Dr. Reed"){
        (*this).set_safeplace(map.get_location_by_name("Camp")) ; 
        VillagerTex_path = "../Assets/Villager/DrReed.png";
    }
    else if(name == "Prof. Pearson"){
    (*this).set_safeplace(map.get_location_by_name("Museum")) ; 
    VillagerTex_path = "../Assets/Villager/ProfPearson.png";
    }
    else if(name == "Maleva"){
        (*this).set_safeplace(map.get_location_by_name("Shop")) ; 
        VillagerTex_path = "../Assets/Villager/Maleva.png";
    }
    else if(name == "Fritz"){
        (*this).set_safeplace(map.get_location_by_name("Institute")) ; 
        VillagerTex_path = "../Assets/Villager/Fritz.png";
    }
    else if(name == "Wilbur & Chick"){
        (*this).set_safeplace(map.get_location_by_name("Dungeon")) ; 
        VillagerTex_path = "../Assets/Villager/WilburAndChick.png";
    }
    else if(name == "Maria"){
        (*this).set_safeplace(map.get_location_by_name("Camp")) ; 
        VillagerTex_path = "../Assets/Villager/Maria.png";
    }
    VillagerTex = LoadTexture(VillagerTex_path.c_str());

}

bool Villager::in_the_safePlace() const{

    return currentLocation == safePlace;
}

void Villager::set_currentLocation(Location* newLocation){
    currentLocation = newLocation ; 
}

Location* Villager::get_currentLocation(){
    return currentLocation;
}

std::string Villager::get_name(){ return name; }

Location* Villager::get_safeplace(){ return safePlace; }

void Villager::set_safeplace(Location* newplace){
    safePlace = newplace ; 
}

void Villager::MoveTo(Location* newPlace , std::string charc){ // only villager move
  
    for(auto *v :vil){
        if(v->get_name() == charc){
            if(newPlace == v->get_currentLocation())
                throw std::runtime_error("you are in the current location") ;
            v->get_currentLocation()->remove_villager(v) ; 
            v->set_currentLocation(newPlace) ; 
            newPlace->add_villager(v) ; 
            return ;  
        }
    }
    throw std::invalid_argument("villager not found!") ; 

}
void Villager::removeVillager(){

    for(auto it = vil.begin() ; it != vil.end() ; ){
        if((*it)->in_the_safePlace()){
            if((*it)->get_currentLocation()){
                (*it)->get_currentLocation()->remove_villager(*it) ; 
            }
            delete *it ; 
            it  = vil.erase(it) ;
        }
        else ++it ; 
    }  
}

void Villager::removevillager(Villager * v){ //killed by attack of monster
    vil.erase(remove(vil.begin() , vil.end() , v) , vil.end()) ; 
}


bool Villager::AnyVillagerInSafePlace(){
    for(auto *e : all()){
        if(e->in_the_safePlace()){
            return true ; 
        }
    }
    return false ;
}

std::vector<Villager*> &Villager::all(){ return vil ;}

Texture2D Villager::getTexture(){ return VillagerTex;}

 std::string Villager::getTexturePath(){return  VillagerTex_path;}

Villager* Villager::find_villager_by_name(const std::string name){
    for(auto vi : all()){
        if(vi->get_name() == name)
            return vi; 
    }
    return nullptr ; 
}
void Villager::DisplayInfo() {
    DrawRectangle(600, 50, 350, 900, Fade(DARKGRAY, 0.8f));
    DrawText("Villagers:", 620, 70, 25, WHITE);

    float startY = 150;
    float imageSize = 100.0f; 
    float spacing = imageSize + 40.0f;
    int fontSize = 20;

    for (size_t i = 0; i < vil.size(); ++i) {
        Villager* v = vil[i];
        float y = startY + i * spacing;

        Texture2D tex = v->getTexture();
        Rectangle src = {0, 0, (float)tex.width, (float)tex.height};
        Rectangle dest = {620.0f, y, imageSize, imageSize};
        Vector2 origin = {0, 0};
        DrawTexturePro(tex, src, dest, origin, 0.0f, WHITE);

        float textX = dest.x + imageSize + 10;
        DrawText(v->get_name().c_str(), textX, y + 5, fontSize + 2, YELLOW);

        std::string s = "Safe place: " + v->get_safeplace()->get_name();
        DrawText(s.c_str(), textX, y + 30, fontSize, WHITE);
    }
}

void Villager::loadTexture(){
    VillagerTex = LoadTexture(VillagerTex_path.c_str());
}

Villager::~Villager() {
    UnloadTexture(VillagerTex);
}