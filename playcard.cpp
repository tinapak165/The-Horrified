#include "MonstercardDeck.hpp"
#include <stdexcept>
#include <ctime>
#include "GameMap.hpp"
#include <iostream>
using namespace std;

int main(){
    GameMap map;
    map.build_map();
    unordered_map<MonsterType, Monster*> monstersmap;

    MonsterCardDeck deck;
    Monstercard card = deck.get_random_card();
    cout << card;
    card.play_monster_card(map , monstersmap );
    

   
   
}