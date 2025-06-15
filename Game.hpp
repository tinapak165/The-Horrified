#include <iostream>
#include <unordered_map>
#include "GameMap.hpp"
#include "MonsterCardDeck.hpp"
#include "TurnManager.hpp"
#include "Monster.hpp"
#include "Dracula.hpp"
#include "InvisibleMan.hpp"
#include "Hero.hpp"

class Game {
private:
    GameMap map;
    MonsterCardDeck deck;
    TurnManager turnManager;
    std::unordered_map<MonsterType, Monster*> monstersMap;
    int terrorLevel = 0;
    
public:
    Game() {
        // ساخت نقشه ثابت
        map.build_map();

        // اضافه کردن قهرمان‌ها به TurnManager (بهتره از کاربر دریافت کنیم)
        Hero* mayor = new Hero("Mayor", map.find_location("Theater"));
        Hero* archaeologist = new Hero("Archaeologist", map.find_location("Docks"));
        turnManager.add_hero(mayor);
        turnManager.add_hero(archaeologist);

        // اضافه کردن هیولاها
        Dracula* dracula = new Dracula(map.get_location_by_name("Cave")); 
        InvisibleMan* invisibleMan = new InvisibleMan(map.get("Barn"));
        monstersMap[MonsterType::Dracula] = dracula;
        monstersMap[MonsterType::InvisibleMan] = invisibleMan;
    }

    void start() {
        while (true) {
            // ۱. فاز قهرمان
            Hero* activeHero = turnManager.get_active_hero();
            std::cout << "It's " << activeHero->GetName() << "'s turn!\n";
            run_hero_turn(activeHero);

            // ۲. فاز هیولا
            Monstercard card = deck.get_random_card();
            std::cout << card;
            card.play_monster_card(map, monstersMap);

            // ۳. بررسی پایان بازی
            if (terrorLevel >= 6) {
                std::cout << "Game Over! Terror level reached 6.\n";
                break;
            }
            if (deck.is_empty()) {
                std::cout << "Game Over! No more Monster Cards.\n";
                break;
            }
            if (both_monsters_defeated()) {
                std::cout << "You win! Both monsters defeated!\n";
                break;
            }

            // ۴. رفتن به نوبت قهرمان بعدی
            turnManager.next_turn();
        }
    }

    void run_hero_turn(Hero* hero) {
        std::cout << "Choose your action (Move, PickUp, UseItem, ...):\n";
        // فعلاً میذاریم خالی تا بعداً پرش کنیم
    }

    bool both_monsters_defeated() {
        return monstersMap[MonsterType::Dracula]->is_defeated() &&
               monstersMap[MonsterType::InvisibleMan]->is_defeated();
    }



    void monster_phase() {
        Monstercard card = deck.get_random_card();
        std::cout << card;
        

        
    int itemCount = card.get_item_count();
    auto newItems = pool.draw_random_items(itemCount);

    for (const auto& item : newItems) {
        Location* loc = map.get_location_by_name(item.getLocationName());
        if (loc) {
            loc->add_item(item);
            std::cout << "Placed " << item.getName() << " at " << item.getLocationName() << "\n";
        }
        
        // اجرای event (فعلاً می‌زنیم جای خالی چون بعداً می‌سازیمش)
        execute_event(card.get_event());
    
        // اجرای strike
        for (const auto& strike : card.get_strikes()) {
            int moves = strike.get_move_count();
            int dice = strike.get_dice_count();
            const auto& monster_list = strike.get_monsters();
    
            for (MonsterType type : monster_list) {
                if (monstersMap.count(type)) {
                    Monster* m = monstersMap[type];
    
                    // حرکت هیولا
                    for (int i = 0; i < moves; ++i) {
                        Location* target = m->find_nearest_target(m->get_location());
                        if (target)
                            m->move_towards(1); // هر بار یک قدم
                    }
    
                    // تاس انداختن
                    Dice d(3);  
                    std::vector<DiceFace> results = d.roll(dice);
    
                    for (DiceFace face : results) {
                        // دراکولا
                        if (type == MonsterType::Dracula) {
                            if (face == DiceFace::Power) {
                                m->special_power(turnManager.get_active_hero()); 
                            } else if (face == DiceFace::Attack) {
                                m->attack();
                            }
                        }
                        // مرد نامرئی
                        else if (type == MonsterType::InvisibleMan) {
                            if (face == DiceFace::Attack) {
                                m->attack();
                            }
                        }
                    }
                }
            }
        }
    }
    
    void start() {
        while (true) {
            Hero* activeHero = turnManager.get_active_hero();
            std::cout << "It's " << activeHero->GetName() << "'s turn!\n";
            run_hero_turn(activeHero);
    
            monster_phase();
    
            if (terrorLevel >= 6 || deck.is_empty() || both_monsters_defeated()) {
                end_game();
                break;
            }
            turnManager.next_turn();
        }
    }
    

    void distribute_initial_items() {
        ItemPool pool;
        auto items = pool.draw_random_items(12);
    
        for (const auto& item : items) {
            Location* loc = map.get_location_by_name(item.getLocationName());
            if (loc) {
                loc->add_item(item);
                std::cout << "Placed " << item.getName() << " at " << item.getLocationName() << "\n";
            }
        }
    }
    
};
