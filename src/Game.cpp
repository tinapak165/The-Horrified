#include <string>
#include <map>
#include <iomanip>
#include <set>
#include <limits>
#include <utility>
#include "Game.hpp"
#include "villager.hpp"
#include "Menu.hpp"

using namespace std;

Game::Game() {
    InitWindow(1000, 1000, "The Horrified");

    // SetWorkingDirectory(GetApplicationDirectory());

    SetTargetFPS(60);
    

    map.build_map(); 
    menu = make_unique<Menu>(*this) ;

    
    dracula = new Dracula(map.get_location_by_name("Cave")); 
    invisibleMan = new InvisibleMan(map.get_location_by_name("Barn"));

    monstersMap[MonsterType::Dracula] = dracula;
    monstersMap[MonsterType::InvisibleMan] = invisibleMan;
    frenziedMonster = dracula;
    monstersMap[MonsterType::Frenzied] = frenziedMonster;

    initializaMDeck();
    initializaDeck() ; 

}
void Game::initialize(const PlayerSelection &p1, const PlayerSelection &p2){

    vector<Hero*> heroes;

    if (p1.heroType == "mayor") {
        mayor = new Mayor(map);
        heroes.push_back(mayor);
    }
    else if (p1.heroType == "archaeologist") {
        archaeologist = new Archaeologist(map);
        heroes.push_back(archaeologist);
    }
    else if (p1.heroType == "courier") {
        courier = new Courier(map , turnManager);
        heroes.push_back(courier);
    }
    else if (p1.heroType == "scientist") {
        scientist = new Scientist(map);
        heroes.push_back(scientist);
    }
    if (p2.heroType == "mayor") {
        mayor = new Mayor(map);
        heroes.push_back(mayor);
    } 
    else if (p2.heroType == "archaeologist") {
        archaeologist = new Archaeologist(map);
        heroes.push_back(archaeologist);
    } 
    else if (p2.heroType == "courier") {
        courier = new Courier(map , turnManager);
        heroes.push_back(courier);
    } 
    else if (p2.heroType == "scientist") {
        scientist = new Scientist(map);
        heroes.push_back(scientist);
    } 
    turnManager = TurnManager(heroes);
}

std::string Game::checkString(std::string str) {
    for (char &c : str) {
        c = tolower(c);
    }
    return str;
}
void Game::start() {
    menu->SetState(std::make_unique<MenuState>());
    GameRender gamerender(*this);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

           
        menu->renderCurrentState();

        if (menu->getState() == nullptr)
            gamerender.draw();

        EndDrawing();
    }

    CloseWindow();
}


          
 

void Game::initializaDeck(){
    for(int i = 0 ; i < 3 ; i++){
        PerkDeck.addCard(std::make_unique<Repelcard>(dracula, invisibleMan, map));
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


void Game::play_hero_Action(Hero *h){
    while(true){
        string chosenAction ; 
        cout << "what action do you want to play this turn(Move, Special , Guide , Pickup , Advance ,Defeat , Perk , Help , Quit)? " ;
        cin >> chosenAction ; 
        if(checkString(chosenAction) == "help")
            h->DisplayActions() ;
        if(checkString(chosenAction) == "quit")
            break ;
        if(checkString(chosenAction) == "perk"){
            ChoosePerkCardANDplay(h) ;
            continue;
        }   
        if(h->PerformTheAction(checkString(chosenAction))){
            cout << "actions left: " << h->GetRemainingActions() << '/' << h->getMaxActions() << '\n' ;

            if(checkString(chosenAction) == "move"){
                h->MoveAction(map , h) ;                     
            }
            else if(checkString(chosenAction) == "guide"){
                h->GuideAction(h , map) ; 
            }
            else if(checkString(chosenAction) == "pickup"){
                h->PickupItems() ;
                h->DisplayItem() ; 
            } 
            else if(checkString(chosenAction) == "special"){
                    h->Special(h , map)  ;
            }
            else if(checkString(chosenAction) == "advance"){ 
                h->AdvanceAction(h , dracula , pool , map , invisibleMan) ; 
            }
            else if(checkString(chosenAction) == "defeat"){
                h->DefeatAction(h , invisibleMan , dracula) ; 
            }
        } 
    }    
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

        if(chosencard->get_name() == "Break of Dawn"){
            skipMonsterPhase = true ;
            chosencard->play() ; 
        }
        else if(chosencard->get_name() == "Late into the Night")
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
        Texture2D itemTex = item.getTexture();
        if (loc) {
            loc->add_item(item , itemTex);
            std::cout << "Placed " <<" " << item.getName() <<  " at " << item.getLocationName() << std::endl;
        }
    }
}


void Game::monster_phase() {
    
    Location* loc = dracula->get_location();
    Location* loc2 = invisibleMan->get_location();
    
    if (loc)
        std::cout << "Dracula's location: " << loc->get_name() << "\n";
        else
        std::cout << "Dracula has no location. Probably Dead yay!\n";
    
    if (loc2)
        std::cout << "Invisible Man's location: " << loc2->get_name() << "\n";
        else
        std::cout << "Invisible Man has no location.\n";
        
        monster_dice();
        
}

void Game::send_hero_to_hospital(Hero* h) {
    Location* hospital = map.get_location_by_name("Hospital");
    h->MoveTo(hospital);
}
// دسترسی به map
GameMap& Game::get_map() {
    return map;
}

// دسترسی به monster map
std::unordered_map<MonsterType, Monster*>& Game::get_monsters() {
    return monstersMap;
}


// دسترسی به کارت فعلی
Monstercard* Game::get_current_card() const {
    return current_card.get();
}

// turn manager
TurnManager& Game::get_turnManager() {
    return turnManager;
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

                itemStr +=   name  + "(" + to_string(cnt) + "),";
            }
            if (!itemStr.empty()) itemStr.pop_back();  
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
}
void Game::increase_terror_level() {
    terror_Level++;
    std::cout << "Terror Level increased to " << terror_Level << "!\n";
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
    pool.add_item(item);  
}

void Game::Changing_frenzy_marker() {
    if (frenziedMonster == dracula)
        frenziedMonster = invisibleMan;
    else if (frenziedMonster == invisibleMan)
        frenziedMonster = dracula;
}
Monster* Game::get_frenzied_monster() {
    return frenziedMonster;
}

void Game::monster_dice() {
    try {
        auto drawnCard = deck.drawcard();
        std::cout<<*drawnCard;
        drawnCard->play_monster_card(*this,frenziedMonster , all_villagers);
        if (drawnCard->has_frenzied_strike()) {
            Changing_frenzy_marker();
        }
        current_card = std::move(drawnCard); 
    } catch (const std::exception& e) {
    std::cerr << "Exception occurred: " << e.what() << std::endl;
  }
}


void Game::initializaMDeck(){
    for (int i =0 ; i <3 ; i++){       
    deck.addCard(std::make_unique<FormTheBat>( pool, map ,  turnManager ,  monstersMap)) ;     
    deck.addCard(std::make_unique<Thief>( pool, map ,  turnManager ,  monstersMap)) ;
    deck.addCard(std::make_unique<Sunrise>( pool, map ,  turnManager ,  monstersMap)) ;
    deck.addCard(std::make_unique<OnTheMove>( pool, map ,  turnManager ,  monstersMap)) ;
    }

    deck.addCard(std::make_unique<TheInnocent>( pool, map ,  turnManager ,  monstersMap)) ;
    deck.addCard(std::make_unique<TheDelivary>( pool, map ,  turnManager ,  monstersMap)) ;
    deck.addCard(std::make_unique<FormerEmoloyer>( pool, map ,  turnManager ,  monstersMap)) ;
    deck.addCard(std::make_unique<FortuneTeller>( pool, map ,  turnManager ,  monstersMap));
    deck.addCard(std::make_unique<EgyptianExpert>( pool, map ,  turnManager ,  monstersMap)) ;
    deck.addCard(std::make_unique<HurriedAssistant>( pool, map ,  turnManager ,  monstersMap)) ;
    deck.addCard(std::make_unique<TheIchthyologist>( pool, map ,  turnManager ,  monstersMap)) ;
    deck.addCard(std::make_unique<OnTheMove>( pool, map ,  turnManager ,  monstersMap)) ;
}

Game::~Game() {
    for (Hero* h : turnManager.get_heroes())
        delete h;
    for(auto& pair : monstersMap)
        delete pair.second ; 

    pool.unload_item_textures();
    
    map.unload(); 
 
}




std::vector<Villager*>& Game::get_all_villagers() { return all_villagers; }
void Game::add_villager(Villager* v) { all_villagers.push_back(v); }

void Game::cleanup() {
   pool.unload_item_textures();
    
    // بقیه منابع مثل هیروها، مانسترها، آیکون‌ها، موسیقی...
}
