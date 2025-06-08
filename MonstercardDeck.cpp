#include "MonstercardDeck.hpp"
#include <iostream>
#include <string>

using namespace std;

MonsterCardDeck::MonsterCardDeck() {

    cards.push_back(Monstercard("form the bat",2, "Dracula moves where your hero is.", { {{MonsterType::Dracula}, 1, 2} }));
    cards.push_back(Monstercard("form the bat",2, "Dracula moves where your hero is.", { {{MonsterType::Dracula}, 1, 2} }));
    cards.push_back(Monstercard("form the bat",2, "Dracula moves where your hero is.", { {{MonsterType::Dracula}, 1, 2} }));

    cards.push_back(Monstercard("sunrise",0, "Place Dracula at Crypt.", { {{MonsterType::InvisibleMan}, 1, 2} }));
    cards.push_back(Monstercard("sunrise",0, "Place Dracula at Crypt.", { {{MonsterType::InvisibleMan}, 1, 2} }));
    cards.push_back(Monstercard("sunrise",0, "Place Dracula at Crypt.", { {{MonsterType::InvisibleMan}, 1, 2} }));

    cards.push_back(Monstercard("Thief",2, "The invisable man moves where items are the most",{ { {MonsterType ::InvisibleMan}, 1 , 3 }}));
    cards.push_back(Monstercard("Thief",2, "The invisable man moves where items are the most",{ { {MonsterType ::InvisibleMan}, 1 , 3 }}));
    cards.push_back(Monstercard("Thief",2, "The invisable man moves where items are the most",{ { {MonsterType ::InvisibleMan}, 1 , 3 }}));
    cards.push_back(Monstercard("Thief",2, "The invisable man moves where items are the most",{ { {MonsterType ::InvisibleMan}, 1 , 3 }}));
    cards.push_back(Monstercard("Thief",2, "The invisable man moves where items are the most",{ { {MonsterType ::InvisibleMan}, 1 , 3 }}));

    cards.push_back(Monstercard("the innocent",3, "Place Maria at the Barn.", { {{MonsterType::Dracula, MonsterType::InvisibleMan}, 1, 3} }, "Maria", "Barn"));
    cards.push_back(Monstercard("The delivary",3, "Place Wilbur & Chick at Docks.", { {{MonsterType::Frenzied}, 1, 3} }, "Wilbur & Chick", "Docks"));
    cards.push_back(Monstercard("Former employer",3, "Place Dr. Cranly at Laboratory.", { {{MonsterType::InvisibleMan}, 1, 2} }, "Dr. Cranly", "Laboratory"));
    cards.push_back(Monstercard("Hurried Assistant",3, "Place Fritz at Tower.", { {{MonsterType::Dracula}, 2, 3} }, "Fritz", "Tower"));
    cards.push_back(Monstercard("Egyptian Expert",3, "Place Prof. Pearson at Cave.", { {{MonsterType::Dracula, MonsterType::Frenzied}, 2, 2} }, "Prof. Pearson", "Cave"));
    cards.push_back(Monstercard("Fortune teller",3, "Place Maleva at Camp.", { {{MonsterType::Frenzied}, 1, 2} }, "Maleva", "Camp"));

    std::srand(std::time(0)); 
}

Monstercard MonsterCardDeck::get_card_by_id(int id) {
    switch(id) {
        case 1:
        return Monstercard("form the bat",2, "Dracula moves where your hero is.", { {{MonsterType::Dracula}, 1, 2} });
        case 2:
        return Monstercard("the innocent",3, "Place Maria at the Barn.", { {{MonsterType::Dracula, MonsterType::InvisibleMan}, 1, 3} }, "Maria", "Barn");
        case 3:
        return Monstercard("The delivary",3, "Place Wilbur & Chick at Docks.", { {{MonsterType::Frenzied}, 1, 3} }, "Wilbur & Chick", "Docks");
        case 4 :
        return Monstercard("Former employer",3, "Place Dr. Cranly at Laboratory.", { {{MonsterType::InvisibleMan}, 1, 2} }, "Dr. Cranly", "Laboratory");
        case 5 :
        return Monstercard("Thief",2, "The invisable man moves where items are the most",{ { {MonsterType ::InvisibleMan}, 1 , 3 }});
        case 6 :
            return Monstercard("sunrise",0, "Place Dracula at Crypt.", { {{MonsterType::InvisibleMan}, 1, 2} });
        case 7 :
        return Monstercard("Fortune teller",3, "Place Maleva at Camp.", { {{MonsterType::Frenzied}, 1, 2} }, "Maleva", "Camp");
        case 8 :
            return Monstercard("Egyptian Expert",3, "Place Prof. Pearson at Cave.", { {{MonsterType::Dracula, MonsterType::Frenzied}, 2, 2} }, "Prof. Pearson", "Cave");
        case 9 :
            return Monstercard("Hurried Assistant",3, "Place Fritz at Tower.", { {{MonsterType::Dracula}, 2, 3} }, "Fritz", "Tower");
        default:
            throw std::invalid_argument("Invalid card ID");
        }
    }
    
    Monstercard MonsterCardDeck::get_random_card() {
        if(cards.empty()) {
            throw std::runtime_error("No cards left in the deck");
        }
        int index = std::rand() % cards.size();
        // نشون دادن کارت
        Monstercard chosen_card = cards[index];
        // cout<<chosen_card;
       
        cards.erase(cards.begin() + index);
    
        return chosen_card;
    }