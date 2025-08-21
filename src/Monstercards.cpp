#include "Monstercards.hpp"
#include "Game.hpp"

Monstercard::Monstercard(std::string card_name, int itemCount, std::string event,
    std::vector<Strike> s, GameMap& map , std::string tp)
: card_name(card_name),
type(CardType::MonsterAffecting),
item_count(itemCount),
event_text(event),
strikes(s),
map(map) , 
texpath(tp) {
     texture = LoadTexture(texpath.c_str());
    if (texture.id == 0) {
        std::cerr << "Failed to load card texture: " << texpath << std::endl;
    }
}

Monstercard::Monstercard(std::string card_name, int itemCount, std::string event, std::vector<Strike> s,
    std::string character, std::string location, GameMap& map , std::string tp)
: card_name(card_name),
type(CardType::MonsterAffecting),
item_count(itemCount),
event_text(event),
strikes(std::move(s)),
character_name(std::move(character)),
destination_location(std::move(location)),
map(map),
texpath(tp)
{  texture = LoadTexture(texpath.c_str());
    if (texture.id == 0) {
        std::cerr << "Failed to load card texture: " << texpath << std::endl;
    }
}


FormTheBat::FormTheBat(ItemPool& p, GameMap& g, TurnManager& t,
    std::unordered_map<MonsterType, Monster*>& m , std::string path)
    : Monstercard("form the bat", 2, "Dracula moves where your hero is.",
        { {{MonsterType::Dracula}, 1, 2} }, g , "../Assets/Monster_Cards/FormOfTheBat.png" ),
        pool(p), map(g), turnManager(t), monstersMap(m) {}
        
Sunrise::Sunrise(ItemPool& p, GameMap& g, TurnManager& t,
            std::unordered_map<MonsterType, Monster*>& m , std::string path)

        : Monstercard("sunrise",0, "Place Dracula at Crypt.", 
            { {{MonsterType::InvisibleMan , MonsterType::Frenzied}, 1, 2} },g , "../Assets/Monster_Cards/Sunrise.png") ,
        pool(p), map(g), turnManager(t), monstersMap(m)  {}
        

TheInnocent::TheInnocent(ItemPool& p,
    GameMap& g ,
    TurnManager& t,
    std::unordered_map<MonsterType, Monster*>& m , std::string path) : Monstercard("the innocent", 3, "Place Maria at the Barn.",
        { {{MonsterType::Dracula, MonsterType::InvisibleMan ,MonsterType::Frenzied }, 1, 3} }, "Maria", "Barn", g , "../Assets/Monster_Cards/TheInnocent.png"),
        map(g), turnManager(t), monstersMap(m) ,pool(p)  {}
        
        
TheDelivary::TheDelivary(ItemPool& p,
    GameMap& g ,
    TurnManager& t,
    std::unordered_map<MonsterType, Monster*>& m , std::string path ) : Monstercard("The delivary", 3, "Place Wilbur & Chick at Docks.",
        { {{MonsterType::Frenzied}, 1, 3} }, "Wilbur & Chick", "Docks", g , "../Assets/Monster_Cards/TheDelivery.png"),
    map(g), turnManager(t), monstersMap(m) ,pool(p) {}
    
    
  
FormerEmoloyer::FormerEmoloyer(ItemPool& p,
        GameMap& g ,
        TurnManager& t,
        std::unordered_map<MonsterType, Monster*>& m , std::string path) : Monstercard ("Former employer", 3, "Place Dr. Cranly at Laboratory.",
            { {{MonsterType::InvisibleMan , MonsterType::Frenzied}, 1, 2} }, "Dr. Cranly", "Laboratory", g , "../Assets/Monster_Cards/FomerEmployer.png"),
            map(g), turnManager(t), monstersMap(m) ,pool(p) {} 
            
            
            
Thief::Thief(ItemPool& p,
        GameMap& g ,
        TurnManager& t,
        std::unordered_map<MonsterType, Monster*>& m , std::string path ) : Monstercard ("Thief", 2, "The Invisible Man moves where items are the most.",
            { { {MonsterType::InvisibleMan, MonsterType::Dracula}, 1 , 3 } }, g , "../Assets/Monster_Cards/Thief.png"),
        map(g), turnManager(t), monstersMap(m) ,pool(p){}
        
      
        
        
FortuneTeller::FortuneTeller(ItemPool& p,
        GameMap& g ,
        TurnManager& t,
        std::unordered_map<MonsterType, Monster*>& m, std::string path) : Monstercard ("Fortune teller", 3, "Place Maleva at Camp.",
            { {{MonsterType::Frenzied}, 1, 2} }, "Maleva", "Camp", g , "../Assets/Monster_Cards/FortuneTeller.png"),
        map(g), turnManager(t), monstersMap(m) ,pool(p) {}


    
EgyptianExpert ::EgyptianExpert (ItemPool& p,
            GameMap& g ,
            TurnManager& t,
            std::unordered_map<MonsterType, Monster*>& m, std::string path) : Monstercard ("Egyptian Expert", 3, "Place Prof. Pearson at Cave.",
                { {{MonsterType::Dracula, MonsterType::Frenzied}, 2, 2} }, "Prof. Pearson", "Cave", g ,"../Assets/Monster_Cards/EgyptianExpert.png"),
                map(g), turnManager(t), monstersMap(m) ,pool(p) {}
                
 HurriedAssistant::HurriedAssistant (ItemPool& p,
                    GameMap& g ,
                    TurnManager& t,
                    std::unordered_map<MonsterType, Monster*>& m, std::string path) : Monstercard ("Hurried Assistant", 3, "Place Fritz at Tower.",
                        { {{MonsterType::Dracula }, 1, 2} }, "Fritz", "Tower", g , "../Assets/Monster_Cards/HurriedAssistant.png"),
                        map(g), turnManager(t), monstersMap(m) ,pool(p){}
                        
 TheIchthyologist::TheIchthyologist(ItemPool& p,
                            GameMap& g ,
                            TurnManager& t,
                            std::unordered_map<MonsterType, Monster*>& m, std::string path) : Monstercard ("Former employer", 3, "Place Dr. Cranly at Laboratory.",
                                { {{MonsterType::Frenzied}, 1, 2} }, "Dr. Reed", "Institute", g , "../Assets/Monster_Cards/TheIchtyologist.png"),
                                map(g), turnManager(t), monstersMap(m) ,pool(p) {} 

 OnTheMove::OnTheMove(ItemPool& p,
                    GameMap& g ,
                    TurnManager& t,
                    std::unordered_map<MonsterType, Monster*>& m, std::string path) : Monstercard ("On The Move", 3, "Frenzy Marker on the next Monster , Every Villager Moves closer to their Safe place .",
                     { {{MonsterType::Frenzied}, 3, 2} },  g , "../Assets/Monster_Cards/OnTheMove.png"),
                     map(g), turnManager(t), monstersMap(m) ,pool(p) {} 


std::string Monstercard::get_card_name() const{return card_name;}
int Monstercard::get_item_count() const{ return item_count;}
std::string Monstercard::get_Event() const { return event_text;}
const std::vector<Strike>& Monstercard::get_strikes() const{return strikes;}
std::string Monstercard::get_character_name() const {return character_name;}
std::string Monstercard::get_destination_location() const { return destination_location;}
CardType Monstercard::get_type() const { return type;}
                        
                        
void FormTheBat::play_monster_card(Game& game ,Monster* frenziedMonster  ,std::vector<Villager*>& all_villagers ) {
                        
        if (!monstersMap.count(MonsterType::Dracula)) {
            //Dracula not found in monstersMap!
            return;
        }
        
        Monster* dracula = monstersMap[MonsterType::Dracula];
        if (!dracula) {
            //Dracula pointer is null!
            return;
        }
        
        Hero* hero = turnManager.get_active_hero();
        if (!hero) {
            //active hero is null!
            return;
        }
        
        if (!dracula->is_alive()) {
            //Dracula is dead, skipping move!
            return;
        }
        
        dracula->set_location(hero->GetCurrentLocation());
        std::string HeroLoc = turnManager.get_active_hero()->GetCurrentLocation()->get_name();
        GAME_LOG_OBJ(game , "Dracula moved to Heros location :" + HeroLoc + "\n" );
        
        play_strike(game ,map, turnManager, pool, monstersMap, frenziedMonster );
        place_items(pool);     
       
    }
    
    
void Sunrise::play_monster_card(Game& game ,Monster* frenziedMonster , std::vector<Villager*>& all_villagers){
        Monster* dracula = monstersMap[MonsterType::Dracula];
        if (dracula && dracula->is_alive()) {
            Location* crypt = map.get_location_by_name("Crypt");
            if (crypt) {
                dracula->set_location(crypt);
            }
        }  
        play_strike(game ,map, turnManager, pool, monstersMap , frenziedMonster);
        place_items(pool);  
    }
     
void Thief::play_monster_card(Game& game ,Monster* frenziedMonster , std::vector<Villager*>& all_villagers) {

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
        }
    }
    play_strike(game ,map, turnManager, pool, monstersMap, frenziedMonster);
    place_items(pool);
  
}
                    
void TheInnocent::play_monster_card(Game& game ,Monster* frenziedMonster ,std::vector<Villager*>& all_villagers) {
 
    place_or_move_villager( all_villagers);                  
    play_strike(game ,map, turnManager, pool, monstersMap, frenziedMonster);
    place_items(pool);
}
 
void HurriedAssistant::play_monster_card(Game& game ,Monster* frenziedMonster , std::vector<Villager*>& all_villagers) {

    place_or_move_villager(all_villagers);                                  
    play_strike(game ,map, turnManager, pool, monstersMap , frenziedMonster);
    place_items(pool);   
}

void EgyptianExpert::play_monster_card(Game& game ,Monster* frenziedMonster, std::vector<Villager*>& all_villagers) {
    
    place_or_move_villager(all_villagers);                                
    play_strike(game , map, turnManager, pool, monstersMap , frenziedMonster );
    place_items(pool);

}

void FortuneTeller::play_monster_card(Game& game ,Monster* frenziedMonster , std::vector<Villager*>& all_villagers) {

    place_or_move_villager(all_villagers);                  
    play_strike(game , map, turnManager, pool, monstersMap , frenziedMonster);
    place_items(pool);
 
}
void FormerEmoloyer::play_monster_card(Game& game ,Monster* frenziedMonster , std::vector<Villager*>& all_villagers) {
    place_or_move_villager(all_villagers);                  
    play_strike(game ,map, turnManager, pool, monstersMap , frenziedMonster);
    place_items(pool);
 
}
void TheDelivary::play_monster_card(Game& game,Monster* frenziedMonster , std::vector<Villager*>& all_villagers) {

    place_or_move_villager(all_villagers);                  
    place_items(pool);
    play_strike(game ,map, turnManager, pool, monstersMap , frenziedMonster);
    
    
}      

void TheIchthyologist::play_monster_card( Game& game, Monster* frenziedMonster , std::vector<Villager*>& all_villagers) {

    place_or_move_villager(all_villagers);                  
    play_strike(game, map, turnManager, pool, monstersMap , frenziedMonster);
    place_items(pool);
     
}  
  
void OnTheMove::move_all_villagers_toward_safety() {
    const auto& allLocations = map.get_locations();

    std::vector<Villager*> villagersToMove;
    for (const auto& locPtr : allLocations) {
        for (Villager* v : locPtr->get_villagers()) {
            Location* current = v->get_currentLocation();
            Location* safe = v->get_safeplace();

            if (current != safe) {
                villagersToMove.push_back(v);
            }
        }
    }

    for (Villager* v : villagersToMove) {
        Location* nextStep = map.find_next_step(v->get_currentLocation(), v->get_safeplace());
        if (nextStep && nextStep != v->get_currentLocation()) {
            v->MoveTo(nextStep, v->get_name());
        }
    }
}


void OnTheMove::play_monster_card( Game& game, Monster* frenziedMonster , std::vector<Villager*>& all_villagers) {
       game.Changing_frenzy_marker();
       move_all_villagers_toward_safety();
       play_strike(game, map, turnManager, pool, monstersMap , frenziedMonster);
       place_items(pool);
       
} 

int Monstercard::show_item_block_window(Hero* h) {
    const auto& items = h->GetItems();
    int selectedIndex = -2; 

    int screenW = GetScreenWidth();
    int screenH = GetScreenHeight();
    int boxWidth = 500;
    int boxHeight = 100 + (int)items.size() * 60 + 80;
    int boxX = (screenW - boxWidth) / 2;
    int boxY = (screenH - boxHeight) / 2;

    std::string heroName = h->GetName();
    std::string title = "Dracula is attacking " + heroName + "!";

    while (selectedIndex == -2 && !WindowShouldClose()) {
        BeginDrawing();

        DrawRectangleRounded({(float)boxX, (float)boxY, (float)boxWidth, (float)boxHeight}, 0.2f, 10, DARKGRAY);
        DrawRectangleRoundedLinesEx({(float)boxX, (float)boxY, (float)boxWidth, (float)boxHeight}, 0.2f, 8, 3.0f, WHITE);

        DrawText(title.c_str(), boxX + 40, boxY + 20, 24, RED);
        DrawText("Use an item to block?", boxX + 40, boxY + 50, 20, RAYWHITE);

        for (size_t i = 0; i < items.size(); ++i) {
            Rectangle btn = {(float)boxX + 20, (float)boxY + 90 + (float)i * 60, (float)boxWidth - 40, 50};
            DrawRectangleRec(btn, LIGHTGRAY);
            DrawText(
                (std::to_string(i+1) + ". " + items[i].getName() + 
                 " (" + items[i].color_to_string(items[i].getColor()) + ")").c_str(),
                boxX + 30, boxY + 100 + (int)i * 60, 20, BLACK
            );

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), btn)) {
                selectedIndex = (int)i;
            }
        }

        Rectangle noBtn = {(float)boxX + 20, (float)boxY + 90 + (float)items.size() * 60 + 20, (float)boxWidth - 40, 50};
        DrawRectangleRec(noBtn, MAROON);
        DrawText("Don't use any item", boxX + 30, boxY + 100 + (int)items.size() * 60 + 20, 20, WHITE);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), noBtn)) {
            selectedIndex = -1;
        }

        EndDrawing();
    }

    return selectedIndex;
}

void Monstercard::play_strike(Game& game,
                               GameMap& map,
                               TurnManager& turnManager,
                               ItemPool& pool,
                               std::unordered_map<MonsterType, Monster*>& monstersMap,
                               Monster* frenziedMonster) {
    for (const Strike& strike : strikes) {
        int moves = strike.get_move_count();
        int dice = strike.get_dice_count();
        const auto& monster_list = strike.get_monsters();


        Dice d(3);
        std::vector<DiceFace> results = d.roll(dice);
        last_dice_result.clear();

        bool hasFrenzied = false;
        bool terrorAlreadyIncreased = false;
        for (MonsterType type : monster_list) {
            if (type == MonsterType::Frenzied) {
                hasFrenzied = true;
                continue; 
            }
            Monster* m = monstersMap[type];
            if ( !m || !m->is_alive()) {
                GAME_LOG_OBJ(game , "Monster is dead . \n");
                continue;
            }

            GAME_LOG_OBJ(game , "---MONSTER MOVES FROM STRIKE---\n");

            for (int i = 0; i < moves; ++i) {
                Location* target = nullptr;

                if (type == MonsterType::Dracula) {
                    target = m->find_nearest_target(m->get_location());
                    GAME_LOG_OBJ(game , m->get_name() + "s target location : "  + target->get_name() );

                } else if (type == MonsterType::InvisibleMan) {
                    target = m->find_nearest_villager(m->get_location());
                    if (target) {
                        Location* nextStep = m->find_next_step(target);
                        if (nextStep) {
                            m->set_location(nextStep);
                            GAME_LOG_OBJ(game ,  m->get_name() + "s target(villager) location " + target->get_name() + "\n");
                        }
                    }
                }

                if (target) {
                    m->move_towards(1);
                 
                } else {
                   
                }
            }

            Location* currentLoc = m->get_location();
            bool nearHero = !currentLoc->get_heroes().empty();
            bool nearVillager = !currentLoc->get_villagers().empty();

             if (type == MonsterType::Dracula && (nearHero || nearVillager)) {
               std::string logMsg = "Dracula presence increased \n terror level";
               GAME_LOG_OBJ(game, logMsg);

                Game::increase_terror_level();
                terrorAlreadyIncreased = true;
            }

            bool invisiblePowerTriggered = false;

            GAME_LOG_OBJ(game , " Dice Result :");
            for (DiceFace face : results) {
                switch (face) {
                     case DiceFace::Power:
                        GAME_LOG_OBJ( game , "[!POWER!]\n");
                        if (type == MonsterType::InvisibleMan) invisiblePowerTriggered = true;
                        else if (type == MonsterType::Dracula) {
                            m->special_power(turnManager.get_active_hero());   
                            GAME_LOG_OBJ(game , "Dracula uses Dark charm ! \n");
                            GAME_LOG_OBJ(game , "Pulling " + turnManager.get_active_hero()->GetName() + " to " + m->get_location()->get_name() + '\n');

                        }

                        break;

                    case DiceFace::Attack:
                     GAME_LOG_OBJ( game , "[*ATTACK*]\n");

                        if (type == MonsterType::Dracula) {
                            auto target = m->attack(); // (hero, villager)
                            if (target.first && !target.second) {
                                Hero* h = target.first;
                                GAME_LOG_OBJ(game, "Dracula attacks " + h->GetName() + "!");

                                if (h->has_items()) {
                                 int chosenIndex = show_item_block_window(h);

                                if (chosenIndex >= 0) {//Item used to block the attack!
                                    const auto& items = h->GetItems();
                                    h->remove_item_by_index(chosenIndex);
                                    pool.add_item(items[chosenIndex]);
                                } else { //No item used. Dracula's attack succeeds!   
                                    send_hero_to_hospital(h,map);
                                    if (!terrorAlreadyIncreased) {
                                        Game::increase_terror_level();
                                        terrorAlreadyIncreased = true;
                                    }
                                }
                            } else {//hero has no items. Dracula's attack succeeds!
                                send_hero_to_hospital(h,map);
                                if (!terrorAlreadyIncreased) {
                                    Game::increase_terror_level();
                                    terrorAlreadyIncreased = true;
                                }
                            }

                            } else if (target.second) {
                                Villager* v = target.second;
                               GAME_LOG_OBJ(game, "Dracula attacks " + v->get_name() + "!");
                                remove_villager(v);
                                if (!terrorAlreadyIncreased) {
                                    Game::increase_terror_level();
                                    terrorAlreadyIncreased = true;
                                }
                            }
                        } else if (type == MonsterType::InvisibleMan) {
                            auto kv = m->attack(); // (nullptr, villager)
                            if (kv.second) {
                                GAME_LOG_OBJ(game , "Invisible Man kills " + kv.second->get_name() + '\n');
                                remove_villager(kv.second);
                                Game::increase_terror_level();
                            }
                        }

                        break;

                    case DiceFace::empty:
                      GAME_LOG_OBJ (game ,  "[Empty]\n");
                        break;
                }
            }

            if (type == MonsterType::InvisibleMan && invisiblePowerTriggered) {
                Location* target = m->find_nearest_villager(m->get_location());
                if (target) {
                    Location* nextStep = m->find_next_step(target);
                    if (nextStep) {
                        m->set_location(nextStep);
                        std::string logMsg = "Power Dice : makes invisible man\n move to :" + target->get_name() + "\n";
                        GAME_LOG_OBJ(game, logMsg);

                    }
                } else {
                    GAME_LOG_OBJ( game ,"Power Dice : invisible man found no villager.\n");
                }
            }   
            
        }
        
        if (hasFrenzied && frenziedMonster && frenziedMonster->is_alive()) {
              
            frenzied_strike( game,moves, frenziedMonster, frenziedMonster->get_type(), results, terrorAlreadyIncreased, map, turnManager, pool);
        }    
    }
}

bool Monstercard::has_frenzied_strike() const {
    for (const Strike& s : strikes) {
        const std::vector<MonsterType>& monsters = s.get_monsters();
        if (std::find(monsters.begin(), monsters.end(), MonsterType::Frenzied) != monsters.end()) {
            return true;
        }
    }
    return false;
}

void Monstercard::send_hero_to_hospital(Hero* h , GameMap& map) {
    Location* hospital = map.get_location_by_name("Hospital");
    h->MoveTo(hospital);
} 
MonstercardDeck::MonstercardDeck(){}

void MonstercardDeck::addCard(std::unique_ptr<Monstercard> card) {
    cards.push_back(std::move(card));
}

int MonstercardDeck::remaining_cards(){   return static_cast<int>(cards.size());}

bool MonstercardDeck::is_empty() const {
    return cards.empty();
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

Villager* Monstercard::create_villager(const std::string& name, const std::string& locName , std::vector<Villager*>& all_villagers) {
    Location* loc = map.get_location_by_name(locName);
    if (!loc) {
        return nullptr;
    }

    Villager* v = new Villager(map , name, nullptr, loc ,"") ; //safeplace = null 
    all_villagers.push_back(v); 
    return v;
}
void Monstercard::remove_villager(Villager* v) {
    Location* loc = v->get_currentLocation();
    if (loc) {
        auto& villagers = loc->get_villagers();
        villagers.erase(std::remove(villagers.begin(), villagers.end(), v), villagers.end());
    }

    v->removevillager(v);  
    v->set_currentLocation(nullptr);

}

void Monstercard:: place_items(ItemPool& pool )  {
    placed_items.clear();

    int itemCount = get_item_count();
    auto newItems = pool.draw_random_items(itemCount);

    for ( auto& item : newItems) {
        Location* loc = map.get_location_by_name(item.getLocationName());
 
        item.loadTexture();
        if (loc) {
            
            loc->add_item(item );
            placed_items.push_back({item, loc}); 
        }
    }

    has_items_placed = true;
}


void Monstercard::place_or_move_villager(std::vector<Villager*>& all_villagers) {
    if (character_name.empty() || destination_location.empty())
        return;

    std::string name = character_name;
    std::string dest = destination_location;

    Location* targetLoc = map.get_location_by_name(dest);
    if (!targetLoc) {
        return;
    }

    Villager* v = nullptr;
    for (Villager* vill : all_villagers) {
        if (vill->get_name() == name) {
            v = vill;
            break;
        }
    }

    if (v) {
        v->set_currentLocation(targetLoc);
    } else {
        v = create_villager(name, dest,  all_villagers );
        if (v) {
        }
    }
    if (v) {
        affected_villager = v; 
        
        has_villager_event = true;
    }
}


void Monstercard::frenzied_strike(Game& game ,int moves, Monster* m,
    MonsterType type,
    std::vector<DiceFace>& results,
    bool& terrorAlreadyIncreased,
    GameMap& map,
    TurnManager& turnManager,
    ItemPool& pool) {
    
           
            GAME_LOG_OBJ( game , "[Frenzied Monster is :" + m->get_name() + " ]" );
            for (int i = 0; i < moves; ++i) {
                Location* target = nullptr;

                if (type == MonsterType::Dracula) {
                    target = m->find_nearest_target(m->get_location());
                      GAME_LOG_OBJ(game ,m->get_name() + "followed targets as Frenzied  \n to " + target->get_name() + "\n");
                } else if (type == MonsterType::InvisibleMan) {
                    target = m->find_nearest_villager(m->get_location());
                    if (target) {
                        Location* nextStep = m->find_next_step(target);
                        if (nextStep) {
                            m->set_location(nextStep);
                            GAME_LOG_OBJ(game ,m->get_name() + "followed villagers again as Frenzied to " + target->get_name() + "\n");
                        }
                    }
                }

                if (target) {
                    m->move_towards(1);
                    GAME_LOG_OBJ(game ,m->get_name() + "s location : " + m->get_location()->get_name() + "\n");
           
                } else {
                    GAME_LOG_OBJ(game , m->get_name() + " found no target to move toward.\n");
                    break;
                }
            }
    bool invisiblePowerTriggered = false;
    GAME_LOG_OBJ(game , "results of Dice for Frenzied Monster : ");
    for (DiceFace face : results) {
        switch (face) {
            case DiceFace::Power:
        
                if (type == MonsterType::InvisibleMan) {
                    invisiblePowerTriggered = true;
                }
                else if (type == MonsterType::Dracula) {
                            m->special_power(turnManager.get_active_hero());   
                            GAME_LOG_OBJ(game , "Dracula uses Dark charm !" + '\n');
                            GAME_LOG_OBJ(game , "Pulling " + turnManager.get_active_hero()->GetName() + "to" + m->get_location()->get_name() + '\n');


                }
                break;
            case DiceFace::Attack:
                     GAME_LOG_OBJ( game , "[*ATTACK*]\n");

                        if (type == MonsterType::Dracula) {
                            auto target = m->attack(); // (hero, villager)
                            if (target.first && !target.second) {
                                Hero* h = target.first;
                                GAME_LOG_OBJ(game, "Dracula attacks " + h->GetName() + "!");

                                if (h->has_items()) {
                                 int chosenIndex = show_item_block_window(h); 

                                if (chosenIndex >= 0) { //Item used to block the attack!
                                    const auto& items = h->GetItems();
                                    h->remove_item_by_index(chosenIndex);
                                    pool.add_item(items[chosenIndex]);
                                } else { //No item used. Dracula's attack succeeds!
                                    send_hero_to_hospital(h,map);
                                    if (!terrorAlreadyIncreased) {
                                        Game::increase_terror_level();
                                        terrorAlreadyIncreased = true;
                                    }
                                }
                            } else { //hero has no items. Dracula's attack succeeds!
                                send_hero_to_hospital(h,map);
                                if (!terrorAlreadyIncreased) {
                                    Game::increase_terror_level();
                                    terrorAlreadyIncreased = true;
                                }
                            }


                            } else if (target.second) {
                                Villager* v = target.second;
                               GAME_LOG_OBJ(game, "Dracula attacks " + v->get_name() + "!");
                                remove_villager(v);
                                if (!terrorAlreadyIncreased) {
                                    Game::increase_terror_level();
                                    terrorAlreadyIncreased = true;
                                }
                            }
                        } else if (type == MonsterType::InvisibleMan) {
                            auto kv = m->attack(); // (nullptr, villager)
                            if (kv.second) {
                                GAME_LOG_OBJ(game , "Invisible Man kills " + kv.second->get_name() + '\n');
                                remove_villager(kv.second);
                                Game::increase_terror_level();
                            }
                        }

                 break;

            case DiceFace::empty:
                GAME_LOG_OBJ(game ,  "Empty\n");
                break;
        }
    }

    if (type == MonsterType::InvisibleMan && invisiblePowerTriggered) {
        Location* target = m->find_nearest_villager(m->get_location());
        if (target) {
            Location* nextStep = m->find_next_step(target);
            if (nextStep) {
                m->set_location(nextStep); 
                GAME_LOG_OBJ(game ,  m->get_name() + "Power Dice : makes frenzied invisible man move to :" + target->get_name() + "\n");
            }
         } else {
            GAME_LOG_OBJ( game ,  "Power Dice : frenzied invisible man found no target . \n");
        }
    }
}


Texture2D Monstercard::get_texture() const { return texture; }
void MonstercardDeck::removeCardByName(const std::string& cardName) {

   for (auto it = cards.begin(); it != cards.end(); ++it) {
        if ((*it)->get_card_name() == cardName) {
            cards.erase(it);
            break;
        }
    }
}

std::vector<std::string> MonstercardDeck::get_drawncardsName(){ return drawncards; }
