#include <string>
#include <map>
#include <iomanip>
#include <set>
#include <limits>
#include <utility>

#include "Game.hpp"
#include "villager.hpp"

using namespace std;

Game::Game() {
    std::cout<<"                                     THE HORRIFIED                                          "<<endl;
    std::cout<<"                                WELCOME TO THE HORROR WORLD                                  "<<endl;
    map.build_map(); 
    graph_map_text(); 
    distribute_initial_items();
    choose_character();

    initializaDeck() ; 
    
    
    dracula = new Dracula(map.get_location_by_name("Cave")); 


    invisibleMan = new InvisibleMan(map.get_location_by_name("Barn"));

    monstersMap[MonsterType::Dracula] = dracula;
    monstersMap[MonsterType::InvisibleMan] = invisibleMan;

    
}
string get_color_code(ItemColor color) {
    switch (color) {
        case ItemColor::RED:    return "\033[31m";
        case ItemColor::BLUE:   return "\033[34m";
        case ItemColor::YELLOW: return "\033[33m";
        case ItemColor::Reset : return "\033[39m"; 
        default:                return "\033[0m";
    }
}

ostream& operator<<(ostream& os, ItemColor color) {
    return os << get_color_code(color) ;
}
Game::~Game() {
    for (Hero* h : turnManager.get_heroes())
    delete h;
}    

 void Game::choose_character() {
    std::cout << "Player 1: What is the last time you eat Garlic? (in hours ago): ";
    int time1;
    std::cin >> time1;

    std::cout << "Player 2: What is the last time you eat Garlic? (in hours ago): ";
    int time2;
    std::cin >> time2;

    std::string firstPlayer, secondPlayer;
    if (time1 < time2) {
        firstPlayer = "Player 1";
        secondPlayer = "Player 2";
    } else {
        firstPlayer = "Player 2";
        secondPlayer = "Player 1";
    }    

    std::cout << firstPlayer << ", you eat garlic more recently!\n";

    mayor = new Mayor(map);
    archaeologist = new Archaeologist(map);

    std::vector<Hero*> heroes;

    while (true) {
        std::cout << "Choose your hero (Mayor or Archaeologist): ";
        std::string choice;
        std::cin >> choice;
    
        if (choice == "Mayor" || choice == "mayor") {
            heroes.push_back(mayor);
            heroes.push_back(archaeologist);
            std::cout << firstPlayer << " is the Mayor.\n";
            std::cout << secondPlayer << " is the Archaeologist.\n";
            break;
        } else if (choice == "Archaeologist" || choice == "archaeologist") {
            heroes.push_back(archaeologist);
            heroes.push_back(mayor);
            std::cout << firstPlayer << " is the Archaeologist.\n";
            std::cout << secondPlayer << " is the Mayor.\n";
            break;
        } else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }
    
    turnManager = TurnManager(heroes);
} 

void Game::play_hero_Action(Hero *h){
    while(true){
        string chosenAction ; 
        cout << "what action do you want to play this turn(Move, Special , Guide , Pickup , Advance ,Defeat , Perk , Help , Quit)? " ;
        cin >> chosenAction ; 
        if(chosenAction == "Help")
            h->DisplayActions() ;
        if(chosenAction == "Quit")
            break ;
        if(chosenAction == "Perk"){
            ChoosePerkCardANDplay(h) ;
            continue;
        }   
        if(h->PerformTheAction(chosenAction)){
            cout << "actions left: " << h->GetRemainingActions() << '/' << h->getMaxActions() << '\n' ;

            if(chosenAction == "Move"){
                h->MoveAction(map , h) ;                     
            }
            else if(chosenAction == "Guide"){
                h->GuideAction(h , map) ; 
            }
            else if(chosenAction == "Pickup"){
                h->PickupItems() ;
                h->DisplayItem() ; 
            } 
            else if(chosenAction == "Special"){
                    h->Special(h , map)  ;
            }
            else if(chosenAction == "Advance"){ 
                h->AdvanceAction(h , dracula , pool , map , invisibleMan) ; 
            }
            else if(chosenAction == "Defeat"){
                h->DefeatAction(h , invisibleMan , dracula) ; 
            }
        } 
    }    
}

void Game::hero_phase(Hero* hero) {

    hero->DisplayInfo() ;
    play_hero_Action(hero) ;

    if(Villager::AnyVillagerInSafePlace()){
        Villager::removeVillager() ;
        getNewCard(hero) ; 
        cout << hero->GetName() << " got one perk card from moving a villager to its safeplace!\n" ; 
    }
    hero->resetMaxActions() ;
}

void  Game::start() { 

    locationOverview() ;
    for(Hero* hero : turnManager.get_heroes()){
        getNewCard(hero) ; 
    }

    while (true) {

        cout << ItemColor::BLUE << "<-----------HERO PHASE----------->\n" << ItemColor::Reset; 
        Hero* activeHero = turnManager.get_active_hero();
        cout << "It's " << activeHero->GetName() << "'s turn!\n";
        hero_phase(activeHero);

        graph_map_text();

        if(!skipMonsterPhase){
        cout << ItemColor::RED  <<  "\n<-----------MONSTER PHASE---------->\n" <<  ItemColor::Reset  ; 
        monster_phase();
        }
        else{
            cout << "\nMonster Phase skipped due to 'Break of Dawn' perk!\n";   
            skipMonsterPhase = false;     
        }

        locationOverview() ;

        if (terror_Level >= 6) {
            std::cout << "Game Over! Terror level reached 6.\n";
            break;
        }    
        if (deck.is_empty() && !both_monsters_defeated()) {
            std::cout << "Game Over! No more Monster Cards.\n";
            break;
        }    
        if (both_monsters_defeated()) {
            std::cout << "You win! Both monsters defeated!\n";
            break;
        }

        turnManager.next_turn();
    }    
}
void Game::initializaDeck(){
    for(int i = 0 ; i < 3 ; i++){
     //   PerkDeck.addCard(std::make_unique<Repelcard>(dracula, invisibleMan, map));
        PerkDeck.addCard(std::make_unique<Hurrycard>(mayor , archaeologist , map)) ;
        PerkDeck.addCard(std::make_unique<LateintotheNightCARD>()) ;
        PerkDeck.addCard(std::make_unique<BreakofDawnCARD>(pool , map)) ;
        PerkDeck.addCard(std::make_unique<OverstockCard>(pool , map)) ;
        PerkDeck.addCard(std::make_unique<LateintotheNightCARD>()) ;
        PerkDeck.addCard(std::make_unique<VisitfromtheDetectiveCARD>(invisibleMan , map)) ;     
    }
    PerkDeck.addCard(std::make_unique<LateintotheNightCARD>()) ;
    PerkDeck.addCard(std::make_unique<OverstockCard>(pool , map)) ;

}
void Game::getNewCard(Hero* hero){
    auto card = PerkDeck.drawcard() ; 
    hero->AddAvailablePerk(std::move(card)) ;
}

void Game::ChoosePerkCardANDplay(Hero * hero){
    auto& availablePerks = hero->GetAvailablePerkCards() ;
    if(availablePerks.empty()){
        cout << "you do not have any perk cards!\n" ;
        return ;  
    }
    while(true){
        int selected = -1 ; 
        hero->displayavailblecards() ; 
        for(size_t i = 0 ; i < availablePerks.size() ; i++)
            cout << i + 1 << "." << availablePerks[i]->get_name() << '\n' ; 
            
        cout << "enter the card number to play(0 to end): ";
        cin >> selected ; 
        if(selected == 0) return ; 
        if(selected < 1 || selected > availablePerks.size()){
            cerr << "invalid selection! try again\n" ; 
            continue;
        }
        int index = selected - 1 ;
        auto chosencard = std::move( availablePerks[index] ) ;


        if(chosencard->get_name() == "Break of Dawn")
            skipMonsterPhase = true ;
        if(chosencard->get_name() == "Late into the Night")
            chosencard->play(hero) ;
        else chosencard->play() ; 

        hero->addPlayedCards(std::move(chosencard)) ;
        availablePerks.erase(availablePerks.begin() + index);
        hero->displayPlayedCards() ; 
    }

}
bool Game::both_monsters_defeated() {
     return monstersMap[MonsterType::Dracula]->is_defeated() &&
            monstersMap[MonsterType::InvisibleMan]->is_defeated();
}

void Game::distribute_initial_items() {
    std::cout<<"placing 12 initial items \n";
   
    auto items = pool.draw_random_items(12);
    
    for (const auto& item : items) {
        Location* loc = map.get_location_by_name(item.getLocationName());
        if (loc) {
            loc->add_item(item);
            std::cout << "Placed " << get_color_code(item.getColor()) << " " << item.getName() << get_color_code(ItemColor::Reset) << " at " << item.getLocationName() << std::endl;
        }
    }
}
void Game::monster_phase() {
    
    Location* loc = dracula->get_location();
    Location* loc2 = invisibleMan->get_location();
    
    if (loc)
        std::cout << "Dracula's location: " << loc->get_name() << "\n";  // چاپ نام مکان
        else
        std::cout << "Dracula has no location. Probably Dead yay!\n";
    
    if (loc2)
        std::cout << "Invisible Man's location: " << loc2->get_name() << "\n";
        else
        std::cout << "Invisible Man has no location.\n";
        
        
  
        
        Monstercard card = deck.get_random_card();
        std::cout << card;
        if (!card.get_character_name().empty() && !card.get_destination_location().empty()) {
            std::string name = card.get_character_name();
            std::string dest = card.get_destination_location();
            
            Location* targetLoc = map.get_location_by_name(dest);
            if (!targetLoc) {
                std::cout << "Destination location '" << dest << "' not found!\n";
            } else {
                // جستجو در ویلیجرها
                Villager* v = nullptr;
                for (auto* vill : Villager::all()) {
                    if (vill->get_name() == name) {
                        v = vill;
                        break;
                    }
                }
                
                // اگر پیدا شد، منتقلش کن
            if (v) {
                v->set_currentLocation(targetLoc);
                std::cout << "Event: Villager " << name << " was moved to " << dest << ".\n";
            } 
            // اگر نبود، ویلیجر بساز
            else {
                v = create_villager(name, dest);
                if (v) {
                    std::cout << "Event: Villager " << name << " was created and placed at " << dest << ".\n";
                }
            }
        }
    }
    
    // اجرای event کارت‌های خاص
    std::string cardName = card.get_card_name();
    
    if (cardName == "form the bat") {
        Monster* dracula = monstersMap[MonsterType::Dracula];
        Hero* hero = turnManager.get_active_hero();
        if (dracula && dracula->is_alive() && hero) {
            Location* heroLoc = hero->GetCurrentLocation();
            if (heroLoc) {
                dracula->set_location(heroLoc);
                std::cout << "Event: Dracula moved to " << heroLoc->get_name() << " (hero location)\n";
            }
        }
    }else if (cardName == "Thief") {
        Monster* inv = monstersMap[MonsterType::InvisibleMan];
        if (inv && inv->is_alive()) {
            Location* maxLoc = nullptr;
            int maxItems = -1;
            for (const auto& locPtr : map.get_locations()) {
                Location* loc = locPtr.get();
                if ((int)loc->get_items().size() > maxItems) {
                    maxItems = (int)loc->get_items().size();
                    maxLoc = loc;
                }
            }
    
            if (maxLoc) {
                inv->set_location(maxLoc);
                std::cout << "Event: Invisible Man moved to " << maxLoc->get_name() << " (most items)\n";
            }
        }
    }
    
    else if (cardName == "sunrise") {
        Monster* dracula = monstersMap[MonsterType::Dracula];
        if (dracula && dracula->is_alive()) {
            Location* crypt = map.get_location_by_name("Crypt");
            if (crypt) {
                dracula->set_location(crypt);
                std::cout << "Event: Dracula moved to Crypt.\n";
            }
        }
    }
    
    std::cout<<"---PLACING THE ITEMS---"<<endl;
    // قرار دادن آیتم‌ها
    int itemCount = card.get_item_count();
    auto newItems = pool.draw_random_items(itemCount);
    
    for (const auto& item : newItems) {
        Location* loc = map.get_location_by_name(item.getLocationName());
        if (loc) {
            loc->add_item(item);
            std::cout << "Placed " << get_color_code(item.getColor()) << item.getName() <<  get_color_code(ItemColor::Reset)  << " at " << item.getLocationName() << "\n";
        }
    }
    
    
    for (const auto& strike : card.get_strikes()) {
        int moves = strike.get_move_count();
        int dice = strike.get_dice_count();
        const auto& monster_list = strike.get_monsters();

        Dice d(3);
        std::vector<DiceFace> results = d.roll(dice);

        std::cout << "---PLAYING DICE---\n";
        for (int i = 0; i < results.size(); ++i) {
            std::cout << "Dice " << i << " rolled: " << (results[i] == DiceFace::Attack ? "Attack" :
                                                           results[i] == DiceFace::Power ? "Power" :
                                                           "Empty") << "\n";
        }

        for (MonsterType type : monster_list) {
            if (!monstersMap.count(type)) {
                std::cout << "Monster type not found in map, skipping.\n";
                continue;
            }

            Monster* m = monstersMap[type];
            if (!m->is_alive()) {
                std::cout << m->get_name() << " is defeated and will not act.\n";
                continue;
            }

            std::cout << "---MONSTER MOVE FROM STRIKE---" << std::endl;

            for (int i = 0; i < moves; ++i) {
                Location* target = nullptr;
                if (type == MonsterType::Dracula) {
                    target = m->find_nearest_target(m->get_location());
                } else if (type == MonsterType::InvisibleMan) {
                    Location* target = m->find_nearest_villager(m->get_location());
                    if (target) {
                        Location* nextStep = m->find_next_step(target);
                        if (nextStep) {
                            m->set_location(nextStep);  // دقیق به هدف villager می‌ره
                            std::cout << m->get_name() << " moved towards villager at " << target->get_name() << "\n";
                        }
                    }
                    
                } else {
                    std::cout << "Unknown monster type. Skipping movement.\n";
                    break;
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
            bool nearHero = !currentLoc->get_heroes().empty();
            bool nearVillager = !currentLoc->get_villagers().empty();

            // if (type == MonsterType::Dracula && (nearHero || nearVillager)) {
            //     std::cout << "Dracula's presence increased terror level !\n";
            //     increase_terror_level();
            //     terrorAlreadyIncreased = true;
            // }

            // std::cout << " Terror Level Reached : " << terror_Level << std::endl;

            bool invisiblePowerTriggered = false;

            for (DiceFace face : results) {
                std::cout << "Dice result: ";
                switch (face) {
                    case DiceFace::Power:
                        std::cout << "Power\n";
                        if (type == MonsterType::InvisibleMan) {
                            invisiblePowerTriggered = true;
                        }
                        break;
                    case DiceFace::Attack:
                        std::cout << "Attack\n";
                        if (type == MonsterType::Dracula) {
                            auto target = m->attack(); //[heroTarget, villagerTarget]
                            if (target.first && !target.second) {
                                std::cout << "Dracula attacks " << target.first->GetName() << "!\n";
                                if (target.first->has_items()) {
                                    const auto& items = target.first->GetItems();
                                    for (size_t i = 0; i < items.size(); ++i) {
                                        std::cout << i + 1 << ". " << items[i].getName() << " ("
                                                  << items[i].color_to_string(items[i].getColor()) << ")\n";
                                    }
                                    std::cout << "Do you want to use one item to block the attack? (yes/no): ";
                                    std::string choice;
                                    std::cin >> choice;

                                    if (choice == "yes" || choice == "y") {
                                        std::cout << "Select the item number to use: ";
                                        int itemIndex;
                                        std::cin >> itemIndex;

                                        if (itemIndex >= 1 && itemIndex <= (int)items.size()) {
                                            target.first->remove_item_by_index(itemIndex - 1);
                                            pool.add_item(items[itemIndex]);

                                            std::cout << "Item used to block the attack!\n";
                                        } else {
                                            std::cout << "Invalid selection. Dracula's attack succeeds.\n";
                                            send_hero_to_hospital(target.first);
                                            if (!terrorAlreadyIncreased) {
                                                increase_terror_level();
                                                terrorAlreadyIncreased = true;
                                            }
                                            break;
                                        }
                                    } else {
                                        std::cout << "No item used. Dracula's attack succeeds.\n";
                                        send_hero_to_hospital(target.first);
                                        if (!terrorAlreadyIncreased) {
                                            increase_terror_level();
                                            terrorAlreadyIncreased = true;
                                        }
                                        break;
                                    }
                                } else {
                                    std::cout << target.first->GetName() << " has no items. Dracula's attack succeeds.\n";
                                    send_hero_to_hospital(target.first);
                                    if (!terrorAlreadyIncreased) {
                                        increase_terror_level();
                                        terrorAlreadyIncreased = true;
                                    }
                                    break;
                                }
                            } else if (target.second) {
                                std::cout << "Dracula attacks " << target.second->get_name() << "!\n";
                                remove_villager(target.second);
                                if (!terrorAlreadyIncreased) {
                                    increase_terror_level();
                                    terrorAlreadyIncreased = true;
                                }
                                break;
                            }
                        } else if (type == MonsterType::InvisibleMan) {
                            auto kv = m->attack();
                            if (kv.second) {
                                std::cout << "Invisible Man kills " << kv.second->get_name() << "!\n";
                                remove_villager(kv.second);
                                increase_terror_level();
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
                        m->set_location(nextStep);  // دقیق به هدف villager می‌ره
                        std::cout << m->get_name() << " moved towards villager at " << target->get_name() << "\n";
                    }
                 } else {
                    std::cout << "Invisible Man found no villager for doing his Power in dice .\n";
                }
            }
        }
    }
}




void Game::send_hero_to_hospital(Hero* h) {
    Location* hospital = map.get_location_by_name("Hospital");
    h->MoveTo(hospital);
}

void Game::remove_villager(Villager* v) {
    Location* loc = v->get_currentLocation();
    if (loc) {
        auto& villagers = loc->get_villagers();
        villagers.erase(std::remove(villagers.begin(), villagers.end(), v), villagers.end());
    }

    v->removevillager(v);  // حذف از لیست سراسری
    v->set_currentLocation(nullptr);  // مکانش رو خالی کن
    std::cout << "Villager " << v->get_name() << " has been removed from the game.\n";
}
void Game::locationOverview() {
    cout << "-----------------------------Location Overview--------------------------------------\n"; 
    cout << left << setw(13) << "Location" << setw(20) << "Item" << setw(20) << "Monsters" << setw(20) << "Villagers" << setw(20) << "Heroes" << "\n" ;
    cout << right <<"--------------------------------------------------------------------------------------\n"; 

    for (const auto& locPtr : map.get_locations()) {
        Location* loc = locPtr.get();

        // ----- Items -----
        string itemStr;
        const auto items = loc->get_items();
        if (items.empty()) {
            itemStr = "-";
        } else {
            std::map<string, pair<int, ItemColor>> itemcount;
            for (const auto& item : items) {
                auto& entry = itemcount[item.getName()];
                entry.first++;
                entry.second = item.getColor();
            }
            for (const auto& kv : itemcount) {
                const auto& name = kv.first;
                int cnt = kv.second.first;
                ItemColor color = kv.second.second;

                itemStr += get_color_code(color) + name + get_color_code(ItemColor::Reset) + "(" + to_string(cnt) + "),";
            }
            if (!itemStr.empty()) itemStr.pop_back();  // remove last comma
        }

        // ----- Monsters -----
        string monStr;
        const auto monsters = loc->get_monsters();
        if (monsters.empty()) {
            monStr = "-";
        } else {
            for (const auto& m : monsters) {
                if (m) monStr += m->get_name() + ",";
            }
            if (!monStr.empty()) monStr.pop_back();
            else monStr = "-";
        }

        // ----- Villagers -----
        string villagerStr;
        const auto& villagers = loc->get_villagers();
        if (villagers.empty()) {
            villagerStr = "-";
        } else {
            for (const auto& v : villagers) {
                if (v) villagerStr += v->get_name() + ",";
            }
            if (!villagerStr.empty()) villagerStr.pop_back();
            else villagerStr = "-";
        }

        // ----- Heroes -----
        string heroStr;
        const auto& heroes = loc->get_heroes();
        if (heroes.empty()) {
            heroStr = "-";
        } else {
            for (const auto& h : heroes) {
                if (h) heroStr += h->GetName() + ",";
            }
            if (!heroStr.empty()) heroStr.pop_back();
            else heroStr = "-";
        }

        cout << left << setw(13) << loc->get_name()
             << setw(20) << itemStr
             << setw(20) << monStr
             << setw(20) << villagerStr
             << setw(20) << heroStr << "\n";
    }

    cout << "-------------------------------------------------------------------------------------\n";
    cout << "terror level: " << terror_Level << '\n';
    monster_objectes();
    cout<<deck.remaining_cards() << " Monstercard is left ."<<endl;
}
void Game::increase_terror_level() {
    terror_Level++;
    std::cout << "Terror Level increased to " << terror_Level << "!\n";
}

Villager* Game::create_villager(const std::string& name, const std::string& locName) {
    Location* loc = map.get_location_by_name(locName);
    if (!loc) {
        std::cout << "Can't move the villager '" << name << "': location '" << locName << "' not found.\n";
        return nullptr;
    }

    Villager* v = new Villager(map , name, nullptr, loc) ; //safeplace = null 
    std::cout << "Created new villager: " << name << " at " << locName << "\n";
    return v;
}
void Game::graph_map_text() {
    std::cout << R"(


--------------------------------GAME MAP------------------------------------- 
       
                  [Precinct]----[Inn]   [Barn]                                              
                  /         \      \   /                                                
  [Cave]----[Camp]     _______[Theatre]---------[Tower]-----[Dungeon]
                |     /       /                       \
                |    /       /                         \
[Abbey] ----[Mansion]----[Shop]                       [Docks]
    |          /   |           \
    |    [Museum] [Church]    [Laboratory]
 [Crypt]            /    \               \
             [Graveyard][Hospital]        [Institute]
              
          
    )" << '\n';
std::cout<<"--------------------------------------------------------------------------------"<<endl;  
}
void Game::monster_objectes() const {
    if (dracula) {
        int destroyed = 0;
        for (const auto& entry : dracula->get_coffins_map()) {
            if (entry.second) destroyed++;
        }
        std::cout << "Coffins destroyed (Dracula): " << destroyed << "/4\n";
    }

    if (invisibleMan) {
        int collected = invisibleMan->get_evidence_count();
        std::cout << "Evidence collected (Invisible Man): " << collected << "/5\n";
    }
}
void Game::return_item(const Item& item) {
    pool.add_item(item);  // یا هر container که استفاده می‌کنی
}

