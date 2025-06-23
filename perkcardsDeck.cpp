#include "perkcardsDeck.hpp"
#include <vector>
#include <ctime>
#include <stdexcept>
#include <iostream>
using namespace std ;

PerkDeck::PerkDeck(){
    cards.push_back(Perkcards("Visit from the Detective.")) ;
    cards.push_back(Perkcards("Visit from the Detective.")) ;
    cards.push_back(Perkcards("Visit from the Detective.")) ;

    cards.push_back(Perkcards("Break of Dawn.")) ;
    cards.push_back(Perkcards("Break of Dawn.")) ;
    cards.push_back(Perkcards("Break of Dawn.")) ;

    cards.push_back(Perkcards("Overstock.")) ;
    cards.push_back(Perkcards("Overstock.")) ;
    cards.push_back(Perkcards("Overstock.")) ;
    cards.push_back(Perkcards("Overstock.")) ;


    cards.push_back(Perkcards("Late into the Night.")) ;
    cards.push_back(Perkcards("Late into the Night.")) ;
    cards.push_back(Perkcards("Late into the Night.")) ;
    cards.push_back(Perkcards("Late into the Night.")) ;

    cards.push_back(Perkcards("Repel.")) ;
    cards.push_back(Perkcards("Repel.")) ;
    cards.push_back(Perkcards("Repel.")) ;
    cards.push_back(Perkcards("Repel.")) ;

    cards.push_back(Perkcards("Hurry.")) ;
    cards.push_back(Perkcards("Hurry.")) ;
    cards.push_back(Perkcards("Hurry.")) ;
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

void PerkDeck::display_the_card(const Perkcards& card){
    string event = card.get_Event() ; 

    if(event == "Hurry.")
        cout << "[Playing Hurry - perk card] - > Move each hero by two spaces.\n" ;
        
    else if(event == "Repel.")
        cout << "[Playing Repel - perk card] -> Move each monster by two spaces.\n";

    else if(event == "Late into the Night.")
        cout << "[Playing Late into the Night - perk card] - > You can have 2 more actions.\n" ;
    
    else if(event == "Overstock.")
        cout << "[Playing Overstock - perk card] -> Each player should take one item out of the item bag and place it in their location.\n" ;
    
    else if(event == "Break of Dawn.")
        cout << "[Playing Break of Dawn - perk card] -> The next monster phase is skipped. Take 2 items out of the bag and place them in their location.\n";

    else if(event == "Visit from the Detective."){
        cout << "Place the invisible man at a location of the player's choice on the game screen.\n" ; 
        //change invisibleMan location
    }
}

