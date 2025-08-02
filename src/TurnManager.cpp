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

void TurnManager::next_turn() {
    remove_dead_heroes() ;
    if (heroes.empty()) return;

    size_t original_index = current_index;

    for (size_t i = 0; i < heroes.size(); ++i) {
        current_index = (current_index + 1) % heroes.size();
        if (!heroes[current_index]->isDead()) {
            return; 
        }
    }
    current_index = original_index;
}



void TurnManager::add_hero(Hero* hero) {
    if (!hero || hero->GetCurrentLocation() == nullptr) return;

    for (auto h : heroes) {
        if (h == hero) return;
    }

    heroes.push_back(hero);
    if (heroes.size() == 1)
        current_index = 0;
}


std::vector<Hero*> TurnManager::get_heroes(){
    return heroes;
}

void TurnManager::remove_dead_heroes() {
    for (size_t i = 0; i < heroes.size(); ) {
        if (heroes[i]->GetCurrentLocation() == nullptr) {
            heroes.erase(heroes.begin() + i);
            if (current_index >= i && current_index > 0)
                current_index--;
        }else 
            i++;     
    }
    if (current_index >= heroes.size())
        current_index = 0;
}

bool TurnManager::all_heroes_dead() const {
    for (const auto& hero : heroes) {
        if (hero && !hero->isDead()) {
            return false;
        }
    }
    return true;
}
