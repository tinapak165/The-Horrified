#ifndef MONSTERCARDS_HPP
#define MONSTERCARDS_HPP

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <iostream>
#include "monster.hpp"
#include "Dracula.hpp"
#include "InvisibleMan.hpp"
#include "GameMap.hpp"
#include "TurnManager.hpp"
#include "Itembag.hpp"
#include "item.hpp"

enum class CardType { VillagersAffecting, MonsterAffecting };
enum class MonsterType { InvisibleMan, Dracula, Frenzied };

// Strike برای اجرای حرکت و تاس هیولا
struct Strike {
private:
    std::vector<MonsterType> monsters;
    int move_count;
    int dice_count;

public:
    Strike(std::vector<MonsterType> m, int move, int dice)
        : monsters(std::move(m)), move_count(move), dice_count(dice) {}

    int get_move_count() const { return move_count; }
    int get_dice_count() const { return dice_count; }
    const std::vector<MonsterType>& get_monsters() const { return monsters; }
};

// کلاس پایه کارت هیولا
class Monstercard {
friend std::ostream& operator<<(std::ostream& os, const Strike& strike); 
friend std::ostream& operator<<(std::ostream& os, const Monstercard& card);
friend std::ostream& operator<<(std::ostream& os, const std::unique_ptr<Monstercard>& cardPtr);

    private:
    
            std::string card_name;
            CardType type;
            int item_count;
            std::string event_text;
            std::vector<Strike> strikes;
            std::string character_name;
            std::string destination_location;
            GameMap& map ;

        public:
            Monstercard() = default;
            Monstercard(std::string card_name, int itemCount, std::string event, std::vector<Strike> s, GameMap& map);

            Monstercard(std::string card_name, int itemCount, std::string event, std::vector<Strike> s,
                std::string character, std::string location, GameMap& map);
    

                virtual ~Monstercard() = default;

                std::string get_card_name() const;
                int get_item_count() const;
                std::string get_Event() const ;
                const std::vector<Strike>& get_strikes() const;
                std::string get_character_name() const ;
                std::string get_destination_location() const ;
                CardType get_type() const ;

                void send_hero_to_hospital(Hero* h,GameMap& map);
                void remove_villager(Villager* v);
                Villager* create_villager(const std::string& ,const std::string&);
                void place_or_move_villager();
                
                
                void place_items(ItemPool& pool) const;
        
                virtual void play_monster_card() = 0;
                void play_strike(GameMap& map,
                    TurnManager& turnManager,
                    ItemPool& pool,
                    std::unordered_map<MonsterType, Monster*>& monstersMap);
                    
                

};

// کارت 1: Form the Bat (Dracula moves to hero)
class FormTheBat : public Monstercard {
    private:
        ItemPool& pool;
        GameMap& map ;
        TurnManager& turnManager;
        std::unordered_map<MonsterType, Monster*>& monstersMap;

    public:
         FormTheBat(ItemPool& pool, GameMap& map, TurnManager& turnManager,
            std::unordered_map<MonsterType, Monster*>& monstersMap);



        void play_monster_card()override;
                        
};
class Sunrise : public Monstercard {
    private:
        ItemPool& pool;
        GameMap& map ;
        TurnManager& turnManager;
        std::unordered_map<MonsterType, Monster*>& monstersMap;

    public:
         Sunrise(ItemPool& pool, GameMap& map, TurnManager& turnManager,
            std::unordered_map<MonsterType, Monster*>& monstersMap);



        void play_monster_card() override;
                        
};

class TheInnocent : public Monstercard {
    private:
        ItemPool& pool;
        GameMap& map ;
        TurnManager& turnManager;
        std::unordered_map<MonsterType, Monster*>& monstersMap;
    public:
        TheInnocent( ItemPool& pool,
            GameMap& map ,
            TurnManager& turnManager,
            std::unordered_map<MonsterType, Monster*>& monstersMap);
             
    
        void play_monster_card() override;
    };
    



    
    
    
    
    
    
    class TheDelivary : public Monstercard {
    private:
    ItemPool& pool;
        GameMap& map ;
        TurnManager& turnManager;
        std::unordered_map<MonsterType, Monster*>& monstersMap;
        public:
        TheDelivary(ItemPool& pool,
            GameMap& map ,
            TurnManager& turnManager,
            std::unordered_map<MonsterType, Monster*>& monstersMap);
             
    
        void play_monster_card() override;
};

//   Former Employer (Dr. Cranly at Lab + Invisible Man)
class FormerEmoloyer : public Monstercard {
    private:
    ItemPool& pool;
    GameMap& map ;
    TurnManager& turnManager;
    std::unordered_map<MonsterType, Monster*>& monstersMap;
    public:
    FormerEmoloyer( ItemPool& pool,
        GameMap& map ,
        TurnManager& turnManager,
        std::unordered_map<MonsterType, Monster*>& monstersMap);
        
        
        void play_monster_card() override;
    };
    
    //  Thief (InvisibleMan moves to most items)
    class Thief : public Monstercard {
        private:
        ItemPool& pool;
        GameMap& map ;
        TurnManager& turnManager;
        std::unordered_map<MonsterType, Monster*>& monstersMap;
        public:
        Thief( ItemPool& pool,
            GameMap& map ,
            TurnManager& turnManager,
            std::unordered_map<MonsterType, Monster*>& monstersMap);
            
            
            void play_monster_card() override;
};

class HurriedAssistant : public Monstercard {
    private:
    ItemPool& pool;
    GameMap& map ;
    TurnManager& turnManager;
    std::unordered_map<MonsterType, Monster*>& monstersMap;
    public:
    HurriedAssistant( ItemPool& pool,
        GameMap& map ,
        TurnManager& turnManager,
        std::unordered_map<MonsterType, Monster*>& monstersMap);
        
        
        void play_monster_card() override;
    };
    
class EgyptianExpert : public Monstercard {
        private:
        ItemPool& pool;
        GameMap& map ;
        TurnManager& turnManager;
        std::unordered_map<MonsterType, Monster*>& monstersMap;
        public:
        EgyptianExpert( ItemPool& pool,
            GameMap& map ,
            TurnManager& turnManager,
            std::unordered_map<MonsterType, Monster*>& monstersMap);
            
            
            void play_monster_card() override;
            
            
        };
        
        
class FortuneTeller : public Monstercard {
            private:
            ItemPool& pool;
            GameMap& map ;
            TurnManager& turnManager;
            std::unordered_map<MonsterType, Monster*>& monstersMap;
            public:
        FortuneTeller( ItemPool& pool,
            GameMap& map ,
            TurnManager& turnManager,
            std::unordered_map<MonsterType, Monster*>& monstersMap);
            

            void play_monster_card() override;
            
 };
 
 class MonstercardDeck{
     private:
         std::vector<std::unique_ptr<Monstercard>> cards;
     public:
         MonstercardDeck() ; 
         void addCard(std::unique_ptr<Monstercard> card) ; 
         std::unique_ptr<Monstercard> drawcard();
 };
    
 
 #endif 
 
