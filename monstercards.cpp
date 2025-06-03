#include "item.hpp"

#include "monstercards.hpp"

    
// Monstercard form_the_bat( 2,std::string ("Dacula moved where your hero was"), { { { MonsterType::Dracula, MonsterType::InvisibleMan }, 1, 3 }}  );
    
Monstercard ::Monstercard (int itemCount, std::string event, std::vector<Strike> s) : Item_count(std::move(itemCount)), Event((event)),striks((s)) {}

int Monstercard::get_item_count(){return Item_count; }
std::string Monstercard::get_Event(){return Event;}



