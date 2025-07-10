#include "item.hpp"
#include <iostream>
#include "monstercards.hpp"
#include "Dice.hpp"
#include <ctime>

    

Monstercard::Monstercard(std::string card_name, int itemCount, std::string event,
    std::vector<Strike> s, GameMap& map)
: card_name(card_name), type(CardType::MonsterAffecting), item_count(itemCount),
event_text(event), strikes(s), map(map) {}


Monstercard::Monstercard(std::string card_name, int itemCount, std::string event, std::vector<Strike> s,
    std::string character, std::string location, GameMap& map)
: card_name(card_name),
type(CardType::MonsterAffecting),
item_count(itemCount),
event_text(event),
strikes(std::move(s)),
character_name(std::move(character)),
destination_location(std::move(location)),
map(map)
{}



FormTheBat::FormTheBat(ItemPool& p, GameMap& g, TurnManager& t,
    std::unordered_map<MonsterType, Monster*>& m)
    : Monstercard("form the bat", 2, "Dracula moves where your hero is.",
        { {{MonsterType::Dracula}, 1, 2} }, g),
        pool(p), map(g), turnManager(t), monstersMap(m) {}
        
Sunrise::Sunrise(ItemPool& p, GameMap& g, TurnManager& t,
            std::unordered_map<MonsterType, Monster*>& m)
        : Monstercard("sunrise",0, "Place Dracula at Crypt.", { {{MonsterType::InvisibleMan}, 1, 2} },g),
        pool(p), map(g), turnManager(t), monstersMap(m) {}
        

TheInnocent::TheInnocent(ItemPool& p,
    GameMap& g ,
    TurnManager& t,
    std::unordered_map<MonsterType, Monster*>& m) : Monstercard("the innocent", 3, "Place Maria at the Barn.",
        { {{MonsterType::Dracula, MonsterType::InvisibleMan}, 1, 3} }, "Maria", "Barn", g),
        map(g), turnManager(t), monstersMap(m) ,pool(p) {}
        
        
        TheDelivary::TheDelivary(ItemPool& p,
    GameMap& g ,
    TurnManager& t,
    std::unordered_map<MonsterType, Monster*>& m) : Monstercard("The delivary", 3, "Place Wilbur & Chick at Docks.",
        { {{MonsterType::Frenzied}, 1, 3} }, "Wilbur & Chick", "Docks", g),
    map(g), turnManager(t), monstersMap(m) ,pool(p) {}
    
    
    
    FormerEmoloyer::FormerEmoloyer(ItemPool& p,
        GameMap& g ,
        TurnManager& t,
        std::unordered_map<MonsterType, Monster*>& m) : Monstercard ("Former employer", 3, "Place Dr. Cranly at Laboratory.",
            { {{MonsterType::InvisibleMan}, 1, 2} }, "Dr. Cranly", "Laboratory", g),
            map(g), turnManager(t), monstersMap(m) ,pool(p) {} 
            
            
            
            Thief::Thief(ItemPool& p,
        GameMap& g ,
        TurnManager& t,
        std::unordered_map<MonsterType, Monster*>& m) : Monstercard ("Thief", 2, "The Invisible Man moves where items are the most.",
            { { {MonsterType::InvisibleMan}, 1 , 3 } }, g),
        map(g), turnManager(t), monstersMap(m) ,pool(p) {}
        
        
        
        
        FortuneTeller::FortuneTeller(ItemPool& p,
        GameMap& g ,
        TurnManager& t,
        std::unordered_map<MonsterType, Monster*>& m) : Monstercard ("Fortune teller", 3, "Place Maleva at Camp.",
            { {{MonsterType::Frenzied}, 1, 2} }, "Maleva", "Camp", g),
        map(g), turnManager(t), monstersMap(m) ,pool(p) {}


        
EgyptianExpert ::EgyptianExpert (ItemPool& p,
            GameMap& g ,
            TurnManager& t,
            std::unordered_map<MonsterType, Monster*>& m) : Monstercard ("Egyptian Expert", 3, "Place Prof. Pearson at Cave.",
                { {{MonsterType::Dracula, MonsterType::Frenzied}, 2, 2} }, "Prof. Pearson", "Cave", g),
                map(g), turnManager(t), monstersMap(m) ,pool(p) {}
                
 HurriedAssistant::HurriedAssistant (ItemPool& p,
                    GameMap& g ,
                    TurnManager& t,
                    std::unordered_map<MonsterType, Monster*>& m) : Monstercard ("Hurried Assistant", 3, "Place Fritz at Tower.",
                        { {{MonsterType::Dracula}, 2, 3} }, "Fritz", "Tower", g),
                        map(g), turnManager(t), monstersMap(m) ,pool(p) {}
                        
 TheIchthyologist::TheIchthyologist(ItemPool& p,
                            GameMap& g ,
                            TurnManager& t,
                            std::unordered_map<MonsterType, Monster*>& m) : Monstercard ("Former employer", 3, "Place Dr. Cranly at Laboratory.",
                                { {{MonsterType::InvisibleMan}, 1, 2} }, "Dr. Cranly", "Laboratory", g),
                                map(g), turnManager(t), monstersMap(m) ,pool(p) {} 

std::string Monstercard::get_card_name() const{return card_name;}
int Monstercard::get_item_count() const{ return item_count;}
std::string Monstercard::get_Event() const { return event_text;}
const std::vector<Strike>& Monstercard::get_strikes() const{return strikes;}
std::string Monstercard::get_character_name() const {return character_name;}
std::string Monstercard::get_destination_location() const { return destination_location;}
CardType Monstercard::get_type() const { return type;}
                        
                        
void FormTheBat::play_monster_card() {
        std::cout<<this;
                    
        if (!monstersMap.count(MonsterType::Dracula)) {
            std::cout << "Error: Dracula not found in monstersMap!\n";
            return;
        }
        
        Monster* dracula = monstersMap[MonsterType::Dracula];
        if (!dracula) {
            std::cout << "Error: Dracula pointer is null!\n";
            return;
        }
        
        Hero* hero = turnManager.get_active_hero();
        if (!hero) {
            std::cout << "Error: active hero is null!\n";
            return;
        }
        
        if (!dracula->is_alive()) {
            std::cout << "Dracula is dead, skipping move.\n";
            return;
        }
        
        dracula->set_location(hero->GetCurrentLocation());
        std::cout << "Dracula moved to Heros location : "<< turnManager.get_active_hero()->GetCurrentLocation()<<std::endl;
        
        
        play_strike(map, turnManager, pool, monstersMap);
        place_items(pool);              
        
    }
    
    
    void Sunrise::play_monster_card(){
        std::cout<<this;
        Monster* dracula = monstersMap[MonsterType::Dracula];
        if (dracula && dracula->is_alive()) {
            Location* crypt = map.get_location_by_name("Crypt");
            if (crypt) {
                dracula->set_location(crypt);
                std::cout << "Event: Dracula moved to Crypt.\n";
            }
        }  
        play_strike(map, turnManager, pool, monstersMap);
        place_items(pool);
    }
    
    
void Thief::play_monster_card() {
   
}
                    
void TheInnocent::play_monster_card() {
      
        place_or_move_villager();                  
                    
        play_strike(map, turnManager, pool, monstersMap);
        place_items(pool);

            }
 
void HurriedAssistant::play_monster_card() {
    place_or_move_villager();                  
                    
    play_strike(map, turnManager, pool, monstersMap);
    place_items(pool);
}

void EgyptianExpert::play_monster_card() {
    place_or_move_villager();                  
                    
    play_strike(map, turnManager, pool, monstersMap);
    place_items(pool);
}

void FortuneTeller::play_monster_card() {
    place_or_move_villager();                  
                    
    play_strike(map, turnManager, pool, monstersMap);
    place_items(pool);
}


void FormerEmoloyer::play_monster_card() {
    place_or_move_villager();                  
                    
    play_strike(map, turnManager, pool, monstersMap);
    place_items(pool);
}

void TheDelivary::play_monster_card() {
    place_or_move_villager();                  
                    
        play_strike(map, turnManager, pool, monstersMap);
        place_items(pool);
}      

void TheIchthyologist::play_monster_card() {
    place_or_move_villager();                  
                    
        play_strike(map, turnManager, pool, monstersMap);
        place_items(pool);
}  
                    
void Monstercard::play_strike(GameMap& map,
                               TurnManager& turnManager,
                               ItemPool& pool,
                               std::unordered_map<MonsterType, Monster*>& monstersMap) {
    for (const Strike& strike : strikes) {
        int moves = strike.get_move_count();
        int dice = strike.get_dice_count();
        const auto& monster_list = strike.get_monsters();


        Dice d(3);
        std::vector<DiceFace> results = d.roll(dice);
        
        for (MonsterType type : monster_list) {
            Monster* m = monstersMap[type];
            if (!m || !m->is_alive()) {
                std::cout << "Monster is dead or invalid.\n";
                continue;
            }

            std::cout << "---MONSTER MOVE FROM STRIKE---\n";

            for (int i = 0; i < moves; ++i) {
                Location* target = nullptr;

                if (type == MonsterType::Dracula) {
                    target = m->find_nearest_target(m->get_location());
                } else if (type == MonsterType::InvisibleMan) {
                    target = m->find_nearest_villager(m->get_location());
                    if (target) {
                        Location* nextStep = m->find_next_step(target);
                        if (nextStep) {
                            m->set_location(nextStep);
                            std::cout << m->get_name() << " moved towards villager at " << target->get_name() << "\n";
                        }
                    }
                }

                if (target) {
                    m->move_towards(1);
                } else {
                    std::cout << m->get_name() << " found no target to move toward.\n";
                    break;
                }
            }

            bool terrorAlreadyIncreased = false;
            Location* currentLoc = m->get_location();
            bool invisiblePowerTriggered = false;

            for (DiceFace face : results) {
                std::cout << "Dice result: ";
                switch (face) {
                    case DiceFace::Power:
                        std::cout << "Power\n";
                        if (type == MonsterType::InvisibleMan)
                            invisiblePowerTriggered = true;
                        break;

                    case DiceFace::Attack:
                    std::cout << "Attack\n";

                        if (type == MonsterType::Dracula) {
                            auto target = m->attack(); // (hero, villager)
                            if (target.first && !target.second) {
                                Hero* h = target.first;
                                std::cout << "Dracula attacks " << h->GetName() << "!\n";

                                if (h->has_items()) {
                                    const auto& items = h->GetItems();
                                    for (size_t i = 0; i < items.size(); ++i) {
                                        std::cout << i + 1 << ". " << items[i].getName()
                                        << " (" << items[i].color_to_string(items[i].getColor()) << ")\n";
                                    }

                                    std::string choice;
                                    std::cout << "Do you want to use one item to block the attack? (yes/no): ";
                                    std::cin >> choice;

                                    if (choice == "yes" || choice == "y") {
                                        std::cout << "Select the item number to use: ";
                                        int itemIndex;
                                        std::cin >> itemIndex;

                                        if (itemIndex >= 1 && itemIndex <= (int)items.size()) {
                                            h->remove_item_by_index(itemIndex - 1);
                                            pool.add_item(items[itemIndex]);
                                            std::cout << "Item used to block the attack!\n";
                                        } else {
                                            std::cout << "Invalid selection. Dracula's attack succeeds.\n";
                                            send_hero_to_hospital(h,map);
                                            if (!terrorAlreadyIncreased) {
                                                // increase_terror_level();
                                                terrorAlreadyIncreased = true;
                                            }
                                        }
                                    } else {
                                        std::cout << "No item used. Dracula's attack succeeds.\n";
                                        send_hero_to_hospital(h,map);
                                        if (!terrorAlreadyIncreased) {
                                            // increase_terror_level();
                                            terrorAlreadyIncreased = true;
                                        }
                                    }
                                } else {
                                    std::cout << h->GetName() << " has no items. Dracula's attack succeeds.\n";
                                    send_hero_to_hospital(h,map);
                                    if (!terrorAlreadyIncreased) {
                                        // increase_terror_level();
                                        terrorAlreadyIncreased = true;
                                    }
                                }

                            } else if (target.second) {
                                Villager* v = target.second;
                                std::cout << "Dracula attacks " << v->get_name() << "!\n";
                                remove_villager(v);
                                if (!terrorAlreadyIncreased) {
                                    // increase_terror_level();
                                    terrorAlreadyIncreased = true;
                                }
                            }
                        } else if (type == MonsterType::InvisibleMan) {
                            auto kv = m->attack(); // (nullptr, villager)
                            if (kv.second) {
                                std::cout << "Invisible Man kills " << kv.second->get_name() << "!\n";
                                remove_villager(kv.second);
                                // increase_terror_level();
                            }
                        }

                        break;

                    case DiceFace::empty:
                        std::cout << "Empty\n";
                        break;
                }
            }

            if (type == MonsterType::InvisibleMan && invisiblePowerTriggered) {
                Location* target = m->find_nearest_villager(m->get_location());
                if (target) {
                    Location* nextStep = m->find_next_step(target);
                    if (nextStep) {
                        m->set_location(nextStep);
                        std::cout << m->get_name() << " moved toward villager at " << target->get_name() << "\n";
                    }
                } else {
                    std::cout << "Invisible Man found no villager for dice power.\n";
                }
            }
        }
    }
}


void Monstercard::send_hero_to_hospital(Hero* h , GameMap& map) {
    Location* hospital = map.get_location_by_name("Hospital");
    h->MoveTo(hospital);
} 
MonstercardDeck::MonstercardDeck(){}

void MonstercardDeck::addCard(std::unique_ptr<Monstercard> card) {
    cards.push_back(std::move(card));
}

std::unique_ptr<Monstercard> MonstercardDeck::drawcard() {
    if (cards.empty())
        throw std::runtime_error("Monster deck is empty!");

        std::srand(std::time(0));
        int index = std::rand() % cards.size();

    auto chosen_card = std::move(cards[index]);
    cards.erase(cards.begin() + index);
    return chosen_card;
}
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
    os << "MonsterCard name: " << card.get_card_name() << "\n";
    os << "Item count: " << card.get_item_count() << "\n";
    os << "Event: " << card.get_Event() << "\n";
    if (!card.get_character_name().empty())
        os << "Character: " << card.get_character_name() << "\n";
    if (!card.get_destination_location().empty())
        os << "Location: " << card.get_destination_location() << "\n";

    for (const auto& strike : card.get_strikes()) {
        os << strike;
    }

    return os;
}
std::ostream& operator<<(std::ostream& os, const std::unique_ptr<Monstercard>& cardPtr) {
    if (cardPtr) {
        os << *cardPtr;  
    } else {
        os << "Null MonsterCard pointer!";
    }
    return os;
}


Villager* Monstercard::create_villager(const std::string& name, const std::string& locName) {
    Location* loc = map.get_location_by_name(locName);
    if (!loc) {
        std::cout << "Can't move the villager '" << name << "': location '" << locName << "' not found.\n";
        return nullptr;
    }

    Villager* v = new Villager(map , name, nullptr, loc) ; //safeplace = null 
    std::cout << "Created new villager: " << name << " at " << locName << "\n";
    return v;
}
void Monstercard::remove_villager(Villager* v) {
    Location* loc = v->get_currentLocation();
    if (loc) {
        auto& villagers = loc->get_villagers();
        villagers.erase(std::remove(villagers.begin(), villagers.end(), v), villagers.end());
    }

    v->removevillager(v);  // حذف از لیست سراسری
    v->set_currentLocation(nullptr);  // مکانش رو خالی کن
    std::cout << "Villager " << v->get_name() << " has been removed from the game.\n";

}

void Monstercard::place_items(ItemPool& pool) const {
    std::cout << "---PLACING THE ITEMS---" << std::endl;

    int itemCount = get_item_count();
    auto newItems = pool.draw_random_items(itemCount);

    for (const auto& item : newItems) {
        Location* loc = map.get_location_by_name(item.getLocationName());
        if (loc) {
            loc->add_item(item);
            std::cout << "Placed "
                      <<  item.getName()
                      << " at " << item.getLocationName() << "\n";
        } else {
            std::cout << "Location " << item.getLocationName() << " not found! Skipping item.\n";
        }
    }
}

void Monstercard::place_or_move_villager() {
    if (character_name.empty() || destination_location.empty())
        return;

    std::string name = character_name;
    std::string dest = destination_location;

    Location* targetLoc = map.get_location_by_name(dest);
    if (!targetLoc) {
        std::cout << "Destination location '" << dest << "' not found!\n";
        return;
    }

    Villager* v = nullptr;
    for (Villager* vill : Villager::all()) {
        if (vill->get_name() == name) {
            v = vill;
            break;
        }
    }

    if (v) {
        v->set_currentLocation(targetLoc);
        std::cout << "Event: Villager " << name << " was moved to " << dest << ".\n";
    } else {
        v = create_villager(name, dest);
        if (v) {
            std::cout << "Event: Villager " << name << " was created and placed at " << dest << ".\n";
        }
    }
}