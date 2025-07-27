#include <string>
#include <map>
#include <iomanip>
#include <set>
#include <limits>
#include <utility>
#include "Game.hpp"
#include "Villager.hpp"
#include "Menu.hpp"

using namespace std;

Game::Game() {
    InitWindow(1000 +400 , 1000 , "The Horrified");

    // SetWorkingDirectory(GetApplicationDirectory());

     SetTargetFPS(60);
    
    map.build_map(); 
    menu = make_unique<Menu>(*this) ;

    dracula = std::make_unique<Dracula>(map.get_location_by_name("Cave"));
    invisibleMan = std::make_unique<InvisibleMan>(map.get_location_by_name("Barn"));

    monstersMap[MonsterType::Dracula] = dracula.get();
    monstersMap[MonsterType::InvisibleMan] = invisibleMan.get();

    frenziedMonster = dracula.get();   // frenziedMonster = dracula;

    monstersMap[MonsterType::Frenzied] = frenziedMonster;

    initializaMDeck();
    initializaDeck() ; 
}

void Game::initialize(const PlayerSelection &p1, const PlayerSelection &p2){

    heroes.clear() ;

    Hero* h1 = nullptr ; Hero* h2 = nullptr ;

    if (p1.heroType == "mayor") {
        mayor = std::make_unique<Mayor>(map) ;
        h1 = mayor.get() ; 
    }
    else if (p1.heroType == "archaeologist") {
        archaeologist = std::make_unique<Archaeologist>(map);
        h1 = archaeologist.get() ; 
    }
    else if (p1.heroType == "courier") {
        courier = std::make_unique<Courier>(map , turnManager) ;
        h1 = courier.get() ; 
    }
    else if (p1.heroType == "scientist") {
        scientist = std::make_unique<Scientist>(map) ;
        h1 = scientist.get() ; 
    }
    if (p2.heroType == "mayor") {
        mayor = std::make_unique<Mayor>(map) ;
        h2 = mayor.get() ;
    } 
    else if (p2.heroType == "archaeologist") {
        archaeologist = std::make_unique<Archaeologist>(map);
        h2 = archaeologist.get() ; 
    } 
    else if (p2.heroType == "courier") {
        courier = std::make_unique<Courier>(map , turnManager) ;
        h2 = courier.get() ; 
    } 
    else if (p2.heroType == "scientist") {
        scientist = std::make_unique<Scientist>(map) ;
        h2 = scientist.get() ;
    } 
    if(p1.garlicTime > p2.garlicTime){
        heroes.push_back(h2) ;
        heroes.push_back(h1) ;
    }else{
        if(h1) heroes.push_back(h1) ; 
        if(h2) heroes.push_back(h2) ; 
    }

   
    player1 = {p1.name , h1} ; 
    player2 = {p2.name , h2} ;

    turnManager = TurnManager(heroes);
    
    initializaDeck() ; //age to constructor bood onvaght turnmanagar null mifrestad
    initializaMDeck();


    for(Hero* hero : turnManager.get_heroes()){
        getNewCard(hero) ; 
    }
}

PlayerInfo Game::getPlayer1() const{ return player1; }
PlayerInfo Game::getPlayer2() const { return player2 ;}

std::string Game::checkString(std::string str){
    for (char &c : str) 
        c = tolower(c); 
    return str;
}

void Game::start() {

     menu->SetState(std::make_unique<MenuState>());

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        
        
        menu->renderCurrentState();
        
        EndDrawing();
    }
  
    CloseWindow();

    for(Hero* hero : turnManager.get_heroes()){
        getNewCard(hero) ; 
    }

}

void Game::hero_phase(Hero* hero) {

    hero->DisplayInfo() ;        

    play_hero_Action(hero) ;

    if(Villager::AnyVillagerInSafePlace()){
        Villager::removeVillager() ;
       cout << hero->GetName() << " got one perk card from moving a villager to its safeplace!\n" ; 
    }

    hero->resetMaxActions() ;
}


void Game::initializaDeck(){
    for(int i = 0 ; i < 3 ; i++){
        perkDeck.addCard(std::make_unique<Repelcard>(dracula.get(), invisibleMan.get(), map));
         perkDeck.addCard(std::make_unique<Hurrycard>(turnManager.get_heroes(), map)) ; 
        perkDeck.addCard(std::make_unique<LateintotheNightCARD>()) ;
        perkDeck.addCard(std::make_unique<BreakofDawnCARD>(pool , map)) ;
         perkDeck.addCard(std::make_unique<OverstockCard>( turnManager.get_heroes(), pool , map)) ;
        perkDeck.addCard(std::make_unique<LateintotheNightCARD>()) ;
        perkDeck.addCard(std::make_unique<VisitfromtheDetectiveCARD>(invisibleMan.get() , map)) ;     
    }
    perkDeck.addCard(std::make_unique<LateintotheNightCARD>()) ;
  

}
void Game::getNewCard(Hero* hero){
    auto card = perkDeck.drawcard() ; 
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
        if(true){
            cout << "actions left: " << h->GetRemainingActions() << '/' << h->getMaxActions() << '\n' ;

            if(checkString(chosenAction) == "move"){
              //  h->MoveAction(map , h) ;                     
            }
            else if(checkString(chosenAction) == "guide"){
                h->GuideAction(h , map) ; 
            }
            else if(checkString(chosenAction) == "pickup"){
                // h->PickupItems() ;
                h->DisplayItem() ; 
            } 
            else if(checkString(chosenAction) == "special"){
                    // h->Special(h , map)  ;
            }
            else if(checkString(chosenAction) == "advance"){ 
                h->AdvanceAction(h , dracula.get() , pool , map , invisibleMan.get()) ; 
            }
            else if(checkString(chosenAction) == "defeat"){
                h->DefeatAction(h , invisibleMan.get() , dracula.get()) ; 
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
            loc->add_item(item );
            std::cout << "Placed " <<" " << item.getName() <<  " at " << item.getLocationName() << std::endl;
        }
    }
}


void Game::monster_phase() {
    
   
        
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
Dracula* Game::get_dracula() {
    return dracula.get();
}

InvisibleMan* Game::get_invisibleMan() {
    return invisibleMan.get();
}
ItemPool& Game::get_pool() {
    return pool;
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

void Game::set_skipMonsterPhase(bool value){
    skipMonsterPhase = value ; 
}

bool Game::ShouldSkipMonsterPhase() const{
    return skipMonsterPhase;
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
    if (frenziedMonster == dracula.get())
        frenziedMonster = invisibleMan.get();
    else if (frenziedMonster == invisibleMan.get())
        frenziedMonster = dracula.get();
}
Monster* Game::get_frenzied_monster() {
    return frenziedMonster;
}

// void Game::monster_dice() {
//     try {
//         auto drawnCard = deck.drawcard();
//         std::cout<<*drawnCard;
//         drawnCard->play_monster_card(*this,frenziedMonster , all_villagers);
//        if (drawnCard->has_frenzied_strike()) {
//             Changing_frenzy_marker();
//         }
//         current_card = std::move(drawnCard); 
//     } catch (const std::exception& e) {
//     std::cerr << "Exception occurred: " << e.what() << std::endl;
//   }
// }
void Game::monster_dice() {
    try {
        auto drawnCard = deck.drawcard();
        std::cout << *drawnCard;
        drawnCard->play_monster_card(*this, frenziedMonster, all_villagers);

        if (drawnCard->has_frenzied_strike()) {
            Changing_frenzy_marker();
        }
       
        current_card = std::move(drawnCard);
        
        GameRender gamerender(*this);
        BeginDrawing();
        ClearBackground(RAYWHITE);
        gamerender.draw_sidebar();
        gamerender.draw();   // کارت + هیولاها بعد از حرکت
        EndDrawing();
        WaitTime(1.0f); // یک مکث کوتاه که دیده بشه
        // ----------------------------------------

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

std::vector<Villager*>& Game::get_all_villagers() { return all_villagers; }
void Game::add_villager(Villager* v) { all_villagers.push_back(v); }

std::vector<std::string> Game::get_last_events(int count) {
    std::vector<std::string> result;
    int start = std::max(0, (int)event_log.size() - count);
    for (int i = start; i < event_log.size(); ++i)
        result.push_back(event_log[i]);
    return result;
}
//  void Game::changeState(std::unique_ptr<State> newState) {
//         if (currentState) currentState->exit(*this);
//         currentState = std::move(newState);
//         currentState->enter(*this);
//     }
    // void Game::updateState() {
    //     if (currentState) currentState->update(*menu);
    // }
    // void Game::renderState() {
    //     if (currentState) currentState->render(*menu);
    // }
Game::~Game(){
    if(frenziedMonster)
        delete frenziedMonster ;
     pool.unload_in_use_items() ;
}