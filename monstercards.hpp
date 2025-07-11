#ifndef MONSTERCARDS_HPP
#define MONSTERCARDS_HPP
#include "item.hpp"
#include "GameMap.hpp"
#include <string>
#include <vector>
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
          
        int get_move_count()const{  return move_count;}
        int get_dice_count()const{   return dice_count;}
        const std::vector<MonsterType>& get_monsters() const { return monsters; }
        


    
};

class Monstercard{

    
    private:
    
    std::string card_name;
    CardType type;
    int Item_count;
    std::string Event;
    std::vector<Strike> strikes;
    
    std::string character_name;
    std::string destination_location;
    
    friend std::ostream& operator<<(std::ostream& os, const Monstercard& card);
        // باید بصورت دستی همه ی کارت هارو با کانستارکتور توی یک 
    public:
    friend std::ostream& operator<<(std::ostream& os, const MonsterType& m);
    friend std::ostream& operator<<(std::ostream& os, const Strike& strike) ;

    Monstercard();
    Monstercard (std::string card_name , int itemCount, std::string event, std::vector<Strike> s );
    Monstercard( std:: string card_name ,int itemCount, std::string event, std::vector<Strike> s, std::string character , std::string location);
  
        std::string get_card_name()const;
        int get_item_count() const;
        std::string get_Event() const;
        std::vector<Strike> get_strikes() const;
        std::string get_destination_location() const;

        std::string get_character_name()const ;
        CardType get_type() const;
//               :      توابع تا‌ثیر کارت های هیولا
    
        void place_item(int item);
        void play_monster_card(GameMap& map, std::unordered_map<MonsterType, Monster*>& monsters);


};

#endif