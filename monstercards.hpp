#ifndef MONSTERCARDS_HPP
#define MONSTERCARDS_HPP
#include "item.hpp"
#include <string>
#include <vector>
#include <optional>


enum class MonsterType {InvisibleMan , Dracula , Frenzied};

struct Strike{
    private:
    
        std::vector<MonsterType> monsters;  // لیست هیولاها
        int move_count;
        int dice_count;

     
    public:
        Strike(std::vector<MonsterType> m, int move, int dice)
            : monsters(std::move(m)), move_count(move), dice_count(dice) {}   

    
};

class Monstercard{
    private:

        int Item_count;
        std::string Event;
        std::vector<Strike> striks;

        std::string character_name;
        std::string destination_location;

        // باید بصورت دستی همه ی کارت هارو با کانستارکتور توی یک 
    public:
    Monstercard(int itemCount, std::string event, std::vector<Strike> s): Item_count(std::move(itemCount)), Event((event)),striks((s)) {}
    Monstercard(int itemCount, std::string event, std::vector<Strike> s,std::string name,, std::string character_name , std::string destination_location);
  
    int get_item_count();
    std::string get_Event();
    std::vector get_striks();
    

};

#endif

