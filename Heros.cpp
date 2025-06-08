#include "Heros.hpp"

Heros::Heros(){
    heroes.push_back(Hero("Mayor" , 5 , "Theatre" , "nothing")) ; 
    heroes.push_back(Hero("Archaeologist" , 4 , "Docks" , "Pick up Items from an adjacent space.")) ;    
}
std::ostream& operator << (std::ostream &out , const Heros &heros){
    for (const auto& hero : heros.heroes) {
        out << hero << "\n-----------------\n";
    }   
    return out ; 
}