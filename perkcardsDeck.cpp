#include "perkcardsDeck.hpp"
#include <vector>
#include <ctime>
#include <stdexcept>
#include <iostream>
using namespace std ;

PerkDeck::PerkDeck(){
    cards.push_back(Perkcards("Visit from the Detective")) ;
    cards.push_back(Perkcards("Visit from the Detective")) ;
    cards.push_back(Perkcards("Visit from the Detective")) ;

    cards.push_back(Perkcards("Break of Dawn")) ;
    cards.push_back(Perkcards("Break of Dawn")) ;
    cards.push_back(Perkcards("Break of Dawn")) ;

    cards.push_back(Perkcards("Overstock")) ;
    cards.push_back(Perkcards("Overstock")) ;
    cards.push_back(Perkcards("Overstock")) ;
    cards.push_back(Perkcards("Overstock")) ;


    cards.push_back(Perkcards("Late into the Night")) ;
    cards.push_back(Perkcards("Late into the Night")) ;
    cards.push_back(Perkcards("Late into the Night")) ;
    cards.push_back(Perkcards("Late into the Night")) ;

    cards.push_back(Perkcards("Repel")) ;
    cards.push_back(Perkcards("Repel")) ;
    cards.push_back(Perkcards("Repel")) ;

    cards.push_back(Perkcards("Hurry")) ;
    cards.push_back(Perkcards("Hurry")) ;
    cards.push_back(Perkcards("Hurry")) ;
}
Perkcards PerkDeck::get_random_card(){
        if(cards.empty()) 
            throw runtime_error("No cards left in the deck");
        
        srand(time(0)); 

        int index = rand() % cards.size();
        Perkcards chosen_card = cards[index];

        cards.erase(cards.begin() + index);
    
        return chosen_card;
}

