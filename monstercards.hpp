#ifndef MONSTERCARDS_HPP
#define MONSTERCARDS_HPP
#include "item.hpp"
#include <string>
#include <vector>
#include <optional>
#include <unordered_map>

enum class CardType {villagersAffecting,  MonsterAffecting };

enum class MonsterType {InvisibleMan , Dracula , Frenzied};

struct Strike{
    private:
    
        std::vector<MonsterType> monsters;  // لیست هیولاها
        int move_count;
        int dice_count;

     
    public:
        Strike(std::vector<MonsterType> m, int move, int dice)
            : monsters(std::move(m)), move_count(move), dice_count(dice) {}  
            
        int get_move_count() const{  return move_count;}
        int get_dice_count() const {   return dice_count;}
        std::vector<MonsterType> get_monsters_in_strike() const { return monsters ;}

    

    
};

class Monstercard{

    
    private:
    
        std::string card_name;
        CardType type;
        int Item_count;
        std::string Event;
        std::vector<Strike> striks;
    
        std::string character_name;
        std::string destination_location;
    
        friend std::ostream& operator<<(std::ostream& os, const Monstercard& card);
        // باید بصورت دستی همه ی کارت هارو با کانستارکتور توی یک 
    public:
        Monstercard();
        Monstercard (std::string card_name , int itemCount, std::string event, std::vector<Strike> s );
        Monstercard( std:: string card_name ,int itemCount, std::string event, std::vector<Strike> s, std::string character , std::string location);
  
        std::string get_card_name()const;
        int get_item_count() const;
        std::string get_Event() const;

        std::string get_destination_location() const;
        std::vector<Strike> get_strike() ;
        std::string get_character_name()const ;
        CardType get_type() const;
//               :      توابع تا‌ثیر کارت های هیولا
    
        void place_item();
        void Monstermove();
        void play_monster_card(GameMap& map, std::unordered_map<MonsterType, Monster*>& monsters);

};

#endif

