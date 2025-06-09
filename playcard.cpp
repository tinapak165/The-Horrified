#include "MonstercardDeck.hpp"
#include "actions.hpp"
#include "GameMap.hpp"
#include <iostream>
using namespace std;

int main(){
    GameMap map;
    map.build_map();

    MonsterCardDeck deck;
    Monstercard card;
    int ic;
    deck.get_random_card() = card;
    // cout<<card;


    for (const auto& loc : map.get_locations()) {
        cout << "Location: " << loc->get_name() << "\n";
        for (auto adj : loc->get_neighbor()) {
            cout << "  | connected to: " << adj->get_name() << "\n";
        }
    }

    return 0;
    // ic = card.get_item_count();
    // cout<<ic;
    
   
}