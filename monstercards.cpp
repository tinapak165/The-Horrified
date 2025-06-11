#include "item.hpp"
#include <iostream>
#include "monstercards.hpp"
#include "MonstercardDeck.hpp"
#include "GameMap.hpp"
#include "monster.hpp"
#include <unordered_map>

    
// Monstercard form_the_bat( 2,std::string ("Dacula moved where your hero was"), { { { MonsterType::Dracula, MonsterType::InvisibleMan }, 1, 3 }}  );
Monstercard::Monstercard(){}

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

std::vector<Strike> Monstercard::get_strike()  { 
    return striks;
   }

// تاثیر ایتم ها 

void Monstercard::place_item(){

}
void Monstercard::play_monster_card(GameMap& map, std::unordered_map<MonsterType, Monster*>& monsters) {

    // فرض می‌گیریم این کارت در حال اجراست، پس اطلاعات خودش رو استفاده می‌کنه
    for (const auto& strike : striks) {
        int moves = strike.get_move_count();
        int dice = strike.get_dice_count();
        const auto& monster_list = strike.get_monsters_in_strike();

        for (MonsterType type : monster_list) {
            if (monsters.count(type)) {
                Monster* m = monsters[type];

                for (int i = 0; i < moves; ++i) {
                    Location* target = m->find_nearest_target();  // فرض: تابع نیاز به نقشه داره
                    // if (target)
                    //     m->move_to(target);
                }

                std::cout << m->get_name() << " rolled " << dice << " dice!\n";
                // اگر بخوای attack بزنه اینجا dice رو استفاده کن
                // مثلاً: m->attack(dice);
            }
        }
    }
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

// Monstercard& operator = ()

