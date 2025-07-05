#include "perkcards.hpp"

Perkcards::Perkcards(std::string Event):Event(Event){}

Perkcards::Perkcards(){}

std::string Perkcards::get_Event() const{
    return Event ; 
}  
