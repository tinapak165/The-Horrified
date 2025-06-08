#include "perkcards.hpp"

Perkcards::Perkcards(std::string Event):Event(Event){}

Perkcards::Perkcards(){}

std::string Perkcards::get_Event() const{
    return Event ; 
}  
std::ostream& operator << (std::ostream &out , const Perkcards &cards){
    out << "card event: " << cards.get_Event() ; 
    return out ; 
}
