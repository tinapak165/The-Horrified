#include "TurnManager.hpp"

TurnManager::TurnManager(){}
TurnManager::TurnManager(const std::vector<Hero*>& heroes) : heroes(heroes), current_index(0) {}
    
Hero* TurnManager::get_active_hero() {
    return heroes[current_index];
}

void TurnManager:: next_turn() {
    current_index = (current_index + 1) % heroes.size();

}


void TurnManager::add_hero(Hero* hero) {
    current_index = 0;
    heroes.push_back(hero);
}


std::vector<Hero*> TurnManager::get_heroes(){
    return heroes;
}