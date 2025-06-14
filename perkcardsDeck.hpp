#ifndef PERKCARDS_HPP
#define PERKCARDS_HPP
#include "perkcards.hpp"
#include <vector>
class PerkDeck{
    private:
        std::vector<Perkcards> cards; 
    public:
        PerkDeck() ; 
        Perkcards get_random_card(); 
        void do_the_card(const Perkcards&) ; 

};


#endif