#include "item.hpp"
#include <iostream>
#include "monstercards.hpp"
#include "Dice.hpp"

    
// Monstercard form_the_bat( 2,std::string ("Dacula moved where your hero was"), { { { MonsterType::Dracula, MonsterType::InvisibleMan }, 1, 3 }}  );
Monstercard::Monstercard(){}

Monstercard ::Monstercard (std::string card_name, int itemCount, std::string event, std::vector<Strike> s) : 
card_name(card_name),type(CardType::MonsterAffecting),Item_count(std::move(itemCount)), Event((event)),strikes((s)) {}

Monstercard ::Monstercard (std::string card_name, int itemCount, std::string event, std::vector<Strike> s, std::string character , std::string location) :
card_name(card_name),type(CardType::MonsterAffecting),Item_count(std::move(itemCount)), Event((event)),strikes((s)) , character_name(std::move(character)), destination_location(std::move(location)) {}



std::vector<Strike> Monstercard::get_strikes() const { return strikes;}


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

// void Monstercard::play_monster_card(GameMap& map, std::unordered_map<MonsterType, Monster*>& monstersmap) {
  
//     std::cout<< "in Monstercard::play_monster_card ";
    
//     for (const auto& strike : striks) {
//         int moves = strike.get_move_count();
//         int dice = strike.get_dice_count();
//         const auto& monster_list = strike.get_monsters() ;
// // حرکت هیولا سمت قهرمان یا محلی 
//         for (MonsterType type : monster_list) {
//             if (monstersmap.count(type)) {
//                 Monster* m = monstersmap[type];

//                 for (int i = 0; i < moves; ++i) {
//                     Location* target = m->find_nearest_target(m->get_location());                   
//                      if (target)
//                         m->move_towards(strike.get_move_count());
                        
//                 }

//             std::cout << m->get_name() << " rolled " << dice << " dice!\n";
            
//             Dice d(3);  
//             std::vector<DiceFace> results = d.roll(dice);

//             for (DiceFace face : results) {
//                 if (type == MonsterType::Dracula) {
//                     if (face == DiceFace::Power) {
//                         std::cout << "Dracula uses Dark Charm!\n";
//                         m->special_power()
                    
//                     } else if (face == DiceFace::Attack) {
//                         m->attack(); // تابع attack باید داخل Dracula یا Monster تعریف بشه
//                     }
//                 }
//                 else if (type == MonsterType::InvisibleMan) {
//                     if (face == DiceFace::Attack) {
//                         m->attack();
//                     }
                   
//                 }

//                 if (monstersmap.count(MonsterType::InvisibleMan)) {
//                     Monster* invisibleMan = monstersmap[MonsterType::InvisibleMan];
//                     Location* target = invisibleMan->find_nearest_target(invisibleMan->get_location());
//                     if (target) {
//                         invisibleMan->move_towards(2);
//                         std::cout << "Invisible Man sneaks closer to target!\n";
//                     }
//                 }

                
            
//            } 
//         }
//     }
// } 
// }

std::ostream& operator<<(std::ostream& os, const MonsterType& m) {
    switch (m) {
        case MonsterType::InvisibleMan: os << "Invisible Man"; break;
        case MonsterType::Dracula: os << "Dracula"; break;
        case MonsterType::Frenzied: os << "Frenzied"; break;
        default: os << "Unknown Monster"; break;
    }
    return os;
}
std::ostream& operator<<(std::ostream& os, const Strike& strike) {
    os << "Strike: [Monsters: ";
    for (size_t i = 0; i < strike.get_monsters().size(); ++i) {
        os << strike.get_monsters()[i];
        if (i != strike.get_monsters().size() - 1)
            os << ", ";
    }
    os << " | Move: " << strike.get_move_count();
    os << " | Dice: " << strike.get_dice_count() << "]\n";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Monstercard& card) {
    os << "MonsterCard name: " << card.card_name << "\n";
    os << "Item count: " << card.Item_count << "\n";
    os << "Event: " << card.Event << "\n";
    if (!card.character_name.empty())
        os << "Character: " << card.character_name << "\n";
    if (!card.destination_location.empty())
        os << "Location: " << card.destination_location << "\n";

    for (const auto& strike : card.get_strikes()) {
        os << strike;
    }

    return os;
}


//Monstercard::operator = (){}