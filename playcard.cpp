#include "MonstercardDeck.hpp"
#include <stdexcept>
#include <ctime>
#include "GameMap.hpp"
#include <iostream>
using namespace std;

int main(){
    GameMap map;
    map.build_map();

    MonsterCardDeck deck;
    Monstercard card = deck.get_random_card();
    cout << card;
    

   
   
}