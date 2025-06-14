#include "perkcards.hpp"
#include "perkcardsDeck.hpp"

int main(){
    PerkDeck p ; 
    Perkcards p2 ; 
    p2 = p.get_random_card() ;
    std::cout << p2 << std::endl;
    p.do_the_card(p2)   ;
}