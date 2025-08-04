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
    InitWindow(1400  , 1000 , "The Horrified");


    // SetWorkingDirectory(GetApplicationDirectory());

     SetTargetFPS(60);
    
    map.build_map(); 
    menu = make_unique<Menu>(*this) ;

    dracula = std::make_unique<Dracula>(map.get_location_by_name("Cave"));
    invisibleMan = std::make_unique<InvisibleMan>(map.get_location_by_name("Barn"));

    monstersMap[MonsterType::Dracula] = dracula.get();
    monstersMap[MonsterType::InvisibleMan] = invisibleMan.get();

    frenziedMonster = dracula.get();  
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
    distribute_initial_items() ;
    menu->SetState(std::make_unique<MenuState>());
    GameRender gamerender(*this);

    while (!WindowShouldClose()) {
        BeginDrawing();
       //ClearBackground(RAYWHITE);
        if(menu->getState() != nullptr){
            menu->renderCurrentState();
        }
        else{
            if(currentPhase == Phase::HeroPhase){
                if(!heroTurnInProgress){
                    activeHero = turnManager.get_active_hero();
                    std::cout << "It's " << activeHero->GetName() << "'s turn!\n";
                    heroTurnInProgress = true ; 
             
                }
                bool phaseDone = hero_phase(activeHero, &gamerender) ;

                if (phaseDone) {

                    heroTurnInProgress = false;
                    turnManager.next_turn();

                    currentPhase = Phase::MonsterPhase;
                }
            }
            else if(currentPhase == Phase::MonsterPhase){
                if(!ShouldSkipMonsterPhase()){
                    monster_phase() ;
                }else{
                    std::cout <<  "monster phase skipped due to perk\n" ;
                    set_skipMonsterPhase(false) ;
                }
                currentPhase = Phase::HeroPhase ;
            }
            gamerender.draw();

        }
        EndDrawing();


        

if (terror_Level >= 6 || (deck.is_empty() && !both_monsters_defeated()) || both_monsters_defeated()) {
    std::string reason;
    if (terror_Level >= 6) reason = "Terror level reached 6!";
    else if (deck.is_empty() && !both_monsters_defeated()) reason = "No more Monster Cards!";
    else reason = "You win!";

    // حلقه‌ی گیم‌اور
    bool exitRequested = false;
    while (!WindowShouldClose() && !exitRequested) {
        BeginDrawing();
        gamerender.draw();  // نقشه رو همچنان نشون می‌دیم
        DrawGameOverPopup(reason);
        EndDrawing();

        if (IsKeyPressed(KEY_ENTER)) exitRequested = true;
    }

    CloseWindow(); // حالا دیگه پنجره رو ببند
    return;
     }

   }
 }

void Game::set_currentPhase(Phase newPhase){ currentPhase = newPhase ; }

void Game::set_HeroTurnInProgress(bool val){ heroTurnInProgress = val ; }

bool Game::hero_phase(Hero* hero , GameRender* render) {

    if (hero->GetRemainingActions() > 0) {
        return false;  
    }

    // if(Villager::AnyVillagerInSafePlace()){
    //     Villager::removeVillager() ;
    //    cout << hero->GetName() << " got one perk card from moving a villager to its safeplace!\n" ; 
    // }
    render->draw() ;
    hero->resetMaxActions() ;
    return true ;
}





void Game::initializaDeck(){
    for(int i = 0 ; i < 3 ; i++){
        // perkDeck.addCard(std::make_unique<Repelcard>(dracula.get(), invisibleMan.get(), map));
        //  perkDeck.addCard(std::make_unique<Hurrycard>(turnManager.get_heroes(), map)) ; 
        // perkDeck.addCard(std::make_unique<LateintotheNightCARD>()) ;
        // perkDeck.addCard(std::make_unique<BreakofDawnCARD>(pool , map)) ;
         perkDeck.addCard(std::make_unique<OverstockCard>( turnManager.get_heroes(), pool , map)) ;
        // perkDeck.addCard(std::make_unique<LateintotheNightCARD>()) ;
        // perkDeck.addCard(std::make_unique<VisitfromtheDetectiveCARD>(invisibleMan.get() , map)) ;     
    }
    // perkDeck.addCard(std::make_unique<LateintotheNightCARD>()) ;
  
}
void Game::getNewCard(Hero* hero){
    auto card = perkDeck.drawcard() ; 
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
    auto items = pool.draw_random_items(12);
    
    for (auto& item : items) {
       item.loadTexture() ; 
        Location* loc = map.get_location_by_name(item.getLocationName());
        if (loc) {
            loc->add_item(item);
        }
    }
}


void Game::monster_phase() {
    this->clear_logs();
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

int Game::terror_Level = 0;

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
    // if (frenziedMonster == dracula.get())
        frenziedMonster = invisibleMan.get();
    // else if (frenziedMonster == invisibleMan.get())
    //     frenziedMonster = dracula.get();
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
        current_card = std::move(drawnCard);
        std::cout << *current_card; 

        current_card->play_monster_card(*this, frenziedMonster, all_villagers);
        
        if (current_card->has_frenzied_strike()) {
            Changing_frenzy_marker();
        }  
        WaitTime(2.0f);
       

    } catch (const std::exception& e) {
        std::cerr << "Exception occurred: " << e.what() << std::endl;
    }
}



void Game::initializaMDeck(){
    // for (int i =0 ; i <3 ; i++){       
    // deck.addCard(std::make_unique<FormTheBat>( pool, map ,  turnManager ,  monstersMap , "../Assets/Monster_Cards/FormOfTheBat.png")) ;     
    // deck.addCard(std::make_unique<Thief>( pool, map ,  turnManager ,  monstersMap,  "../Assets/Monster_Cards/Thief.png"));
    // deck.addCard(std::make_unique<Sunrise>( pool, map ,  turnManager ,  monstersMap , "../Assets/Monster_Cards/Sunrise.png")) ;
    // deck.addCard(std::make_unique<OnTheMove>( pool, map ,  turnManager ,  monstersMap , "../Assets/Monster_Cards/OnTheMove.png")) ;
    // deck.addCard(std::make_unique<TheIchthyologist>( pool, map ,  turnManager ,  monstersMap , "../Assets/Monster_Cards/TheIchtyologist.png")) ;
    // deck.addCard(std::make_unique<TheDelivary>( pool, map ,  turnManager ,  monstersMap , "../Assets/Monster_Cards/TheDelivery.png")) ;
    // }

    // deck.addCard(std::make_unique<TheInnocent>( pool, map ,  turnManager ,  monstersMap , "../Assets/Monster_Cards/TheInnocent.png")) ;
    // deck.addCard(std::make_unique<FormerEmoloyer>( pool, map ,  turnManager ,  monstersMap , "../Assets/Monster_Cards/FomerEmployer.png")) ;
    // deck.addCard(std::make_unique<FortuneTeller>( pool, map ,  turnManager ,  monstersMap , "../Assets/Monster_Cards/FortuneTeller.png"));
    deck.addCard(std::make_unique<EgyptianExpert>( pool, map ,  turnManager ,  monstersMap , "../Assets/Monster_Cards/EgyptianExpert.png")) ;
    deck.addCard(std::make_unique<HurriedAssistant>( pool, map ,  turnManager ,  monstersMap , "../Assets/Monster_Cards/HurriedAssistant.png")) ;
   
}

std::vector<Villager*>& Game::get_all_villagers() { return all_villagers; }
void Game::add_villager(Villager* v) { all_villagers.push_back(v); }

void Game::log(const std::string& message) {
    logs.push_back(message);
    if (logs.size() > 50) // حداکثر ۵۰ خط
        logs.erase(logs.begin());
}

void Game::clear_logs() {
    logs.clear();
}

void Game::DrawGameOverPopup(const std::string& message) {
    int screenW = GetScreenWidth();
    int screenH = GetScreenHeight();

    // فقط یه باکس بدون تاریک کردن زمینه
    int boxWidth = 400;
    int boxHeight = 200;
    int boxX = (screenW - boxWidth) / 2;
    int boxY = (screenH - boxHeight) / 2;

    DrawRectangleRounded({(float)boxX, (float)boxY, (float)boxWidth, (float)boxHeight}, 0.2f, 10, DARKGRAY);
   DrawRectangleRoundedLinesEx({(float)boxX, (float)boxY, (float)boxWidth, (float)boxHeight}, 0.2f, 8, 4.0f, WHITE);


    DrawText("Game Over!", boxX + 100, boxY + 30, 30, RED);
    DrawText(message.c_str(), boxX + 40, boxY + 80, 20, RAYWHITE);
    DrawText("Press ENTER to Exit", boxX + 80, boxY + 140, 20, YELLOW);
}

Game::~Game(){
    if(frenziedMonster)
        delete frenziedMonster ;
     pool.unload_in_use_items() ;
     
}