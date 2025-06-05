#include "item.hpp"
#include <iostream>
#include "monstercards.hpp"
#include "actions.hpp"

    
// Monstercard form_the_bat( 2,std::string ("Dacula moved where your hero was"), { { { MonsterType::Dracula, MonsterType::InvisibleMan }, 1, 3 }}  );
    
Monstercard ::Monstercard (std::string card_name, int itemCount, std::string event, std::vector<Strike> s) : 
card_name(card_name),type(CardType::MonsterAffecting),Item_count(std::move(itemCount)), Event((event)),striks((s)) {}

Monstercard ::Monstercard (std::string card_name, int itemCount, std::string event, std::vector<Strike> s, std::string character , std::string location) :
card_name(card_name),type(CardType::MonsterAffecting),Item_count(std::move(itemCount)), Event((event)),striks((s)) , character_name(std::move(character)), destination_location(std::move(location)) {}

std::string Monstercard::get_card_name ()const{ return card_name;}
int Monstercard::get_item_count() const {return Item_count; }

std::string Monstercard::get_Event() const {return Event;}

std::string Monstercard::get_destination_location() const{return destination_location;}

std::string Monstercard:: get_character_name()const{return character_name;}

CardType Monstercard::get_type () const { return type; }

// تاثیر ایتم ها 

void Monstercard::place_item(int Item){

    Item = Item_count;
    

}



std::ostream&  operator<<(std::ostream& os, const Monstercard& card) {
    os << "Card name: " << card.card_name << "\n";
    os << "Item count: " << card.Item_count << "\n";
    os << "Event: " << card.Event << "\n";
    if (!card.character_name.empty())
        os << "Character: " << card.character_name << "\n";
    if (!card.destination_location.empty())
        os << "Location: " << card.destination_location << "\n";



    return os;
}


