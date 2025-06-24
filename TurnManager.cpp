#include "TurnManager.hpp"
#include <iostream>
using namespace std ; 

TurnManager::TurnManager(Hero* arch , Hero* may) : archaeologist(arch) , mayor(may), archTurn(true){}

TurnManager::TurnManager(): archaeologist(nullptr) , mayor(nullptr) , archTurn(true){}

Hero* TurnManager::get_active_hero() const {
    return archTurn ? archaeologist : mayor ;
}

void TurnManager::next_turn()
{
    archTurn = !archTurn ;
}