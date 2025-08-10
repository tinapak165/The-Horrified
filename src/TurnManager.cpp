#include "TurnManager.hpp"

TurnManager::TurnManager(){}
TurnManager::TurnManager(const std::vector<Hero*>& heroes) : heroes(heroes), current_index(0) {}
    
Hero* TurnManager::get_active_hero() {
    return heroes[current_index]  ; 
}

void TurnManager::set_active_hero(const std::string& name)
{
    for(size_t i = 0 ; i < heroes.size() ; i++){
        if(heroes[i]->GetName() == name){
            current_index = i ; 
            return ; 
        }
    }
    std::cerr << "Hero with name '" << name << "' not found in TurnManager!\n";
}
Hero* TurnManager::find_hero_by_name(const std::string& name) {
    for (auto hero : heroes) {
        if (hero->GetName() == name) 
            return hero;
    }
    return nullptr;
}

void TurnManager:: next_turn() {
    current_index = (current_index + 1) % heroes.size();
}



void TurnManager::add_hero(Hero* hero) {
    heroes.push_back(hero);
    current_index = 0 ; 
}



std::vector<Hero*> TurnManager::get_heroes(){
    return heroes;
}


