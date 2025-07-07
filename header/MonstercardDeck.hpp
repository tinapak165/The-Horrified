// MonsterCardDeck.hpp
#ifndef MONSTERCARDDECK_HPP
#define MONSTERCARDDECK_HPP

#include "monstercards.hpp"
#include <vector>
#include <cstdlib>
#include <ctime>

class MonsterCardDeck {
private:
    std::vector<Monstercard> cards;

public:
    MonsterCardDeck(); // اضافه کردن کارت ها
    
    Monstercard get_random_card(); 
    Monstercard get_card_by_id(int);
    bool is_empty() const;  
    int remaining_cards() const;        
};

#endif