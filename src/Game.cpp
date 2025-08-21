#include "Game.hpp"

using namespace std;

int Game::terror_Level = 0; 
Game::Game() {
    InitWindow(1400, 1000, "The Horrified");

    InitAudioDevice();
    music = LoadMusicStream("../Assets/Music/music.ogg");
    PlayMusicStream(music);
    SetTargetFPS(60);

    ready();
}

void Game::ready(){

    map.build_map(); 
    menu = make_unique<Menu>(*this) ;
    
    dracula = std::make_unique<Dracula>(map.get_location_by_name("Crypt"));
    invisibleMan = std::make_unique<InvisibleMan>(map.get_location_by_name("Inn"));

    monstersMap[MonsterType::Dracula] = dracula.get();
    monstersMap[MonsterType::InvisibleMan] = invisibleMan.get();

    frenziedMonster = dracula.get();

    monstersMap[MonsterType::Frenzied] = frenziedMonster;

    initializaMDeck();
}

void Game::initialize(const PlayerSelection &p1, const PlayerSelection &p2){

    Factory herofactory(*this) ;
    auto h1_unique = herofactory.createHero(p1.heroType) ;
    auto h2_unique = herofactory.createHero(p2.heroType) ;

    Hero* h1 = h1_unique.get() ; 
    Hero* h2 = h2_unique.get()  ;

    if(h1_unique) heroStorage.push_back(std::move(h1_unique)); //avoid dangling
    if(h2_unique) heroStorage.push_back(std::move(h2_unique));


    if(p1.garlicTime > p2.garlicTime) {
        if(h2) heroes.push_back(h2);
        if(h1) heroes.push_back(h1);
    } else {
        if(h1) heroes.push_back(h1);
        if(h2) heroes.push_back(h2);
    }

    player1 = {p1.name , h1} ; 
    player2 = {p2.name , h2} ;

    turnManager = TurnManager(heroes);

    initializaDeck() ;

    for(Hero* hero : turnManager.get_heroes())
        getNewCard(hero) ; 
}

PlayerInfo Game::getPlayer1() const{ return player1; }
PlayerInfo Game::getPlayer2() const { return player2 ;}

void Game::setPlayer1(const std::string& p1 , Hero* h){ player1.name = p1 ; player1.hero = h ;}
void Game::setPlayer2(const std::string& p2 , Hero* h){ player2.name = p2 ;  player2.hero = h ;}

void Game::start() {

    menu->SetState(std::make_unique<MenuState>());
    GameRender gamerender(*this);

    while (!WindowShouldClose()) {
        BeginDrawing();
        UpdateMusicStream(music); 
        if(menu->getState() != nullptr){
            menu->renderCurrentState();
        }
        else{
            if(currentPhase == Phase::HeroPhase){
                if(!heroTurnInProgress){
                    activeHero = turnManager.get_active_hero();
                    activeHero->resetMaxActions();
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

    if (hero->GetRemainingActions() <= 0) 
        return true;  
    
    if(Villager::AnyVillagerInSafePlace()){
        Villager::removeVillager() ;
       cout << hero->GetName() << " got one perk card from moving a villager to its safeplace!\n" ; 
        getNewCard(hero) ;
    }
    return false ;
}

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

void Game::initializaDeck(){

    for(int i = 0 ; i < 3 ; i++){
       perkDeck.addCard(std::make_unique<Repelcard>(dracula.get(), invisibleMan.get(), map)); 
       perkDeck.addCard(std::make_unique<Hurrycard>(heroes, map)) ; 
       perkDeck.addCard(std::make_unique<LateintotheNightCARD>()) ;
       perkDeck.addCard(std::make_unique<BreakofDawnCARD>(pool , map)) ;
       perkDeck.addCard(std::make_unique<OverstockCard>( pool , map)) ;
       perkDeck.addCard(std::make_unique<VisitfromtheDetectiveCARD>(invisibleMan.get() , map)) ;     
    }
       perkDeck.addCard(std::make_unique<LateintotheNightCARD>()) ; 
       perkDeck.addCard(std::make_unique<OverstockCard>( pool , map)) ;

}
void Game::initializaMDeck(){
    for (int i =0 ; i <3 ; i++){       
        deck.addCard(std::make_unique<FormTheBat>( pool, map ,  turnManager ,  monstersMap , "../Assets/Monster_Cards/FormOfTheBat.png")) ;     
        deck.addCard(std::make_unique<Thief>( pool, map ,  turnManager ,  monstersMap,  "../Assets/Monster_Cards/Thief.png"));
        deck.addCard(std::make_unique<Sunrise>( pool, map ,  turnManager ,  monstersMap , "../Assets/Monster_Cards/Sunrise.png")) ;
        deck.addCard(std::make_unique<OnTheMove>( pool, map ,  turnManager ,  monstersMap , "../Assets/Monster_Cards/OnTheMove.png")) ;
        deck.addCard(std::make_unique<TheIchthyologist>( pool, map ,  turnManager ,  monstersMap , "../Assets/Monster_Cards/TheIchtyologist.png")) ;
        deck.addCard(std::make_unique<TheDelivary>( pool, map ,  turnManager ,  monstersMap , "../Assets/Monster_Cards/TheDelivery.png")) ;
    }
    
    deck.addCard(std::make_unique<TheInnocent>( pool, map ,  turnManager ,  monstersMap , "../Assets/Monster_Cards/TheInnocent.png")) ;
    deck.addCard(std::make_unique<FormerEmoloyer>( pool, map ,  turnManager ,  monstersMap , "../Assets/Monster_Cards/FomerEmployer.png")) ;
    deck.addCard(std::make_unique<FortuneTeller>( pool, map ,  turnManager ,  monstersMap , "../Assets/Monster_Cards/FortuneTeller.png"));
    deck.addCard(std::make_unique<EgyptianExpert>( pool, map ,  turnManager ,  monstersMap , "../Assets/Monster_Cards/EgyptianExpert.png")) ;
    deck.addCard(std::make_unique<HurriedAssistant>( pool, map ,  turnManager ,  monstersMap , "../Assets/Monster_Cards/HurriedAssistant.png")) ;
        
}
void Game::getNewCard(Hero* hero){
    auto card = perkDeck.drawcard() ; 
    hero->AddAvailablePerk(std::move(card)) ;
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

GameMap& Game::get_map() {
    return map;
}

std::unordered_map<MonsterType, Monster*>& Game::get_monsters() {
    return monstersMap;
}


// دسترسی به کارت فعلی
Monstercard* Game::get_current_card() const {
    return current_card.get();
}

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
MonstercardDeck& Game::get_MonsterDeck(){
    return deck ;
}
int Game::get_terror_level()
{
    return terror_Level;
}

void Game::set_terror_level(int value)
{
    terror_Level = value ; 
}

void Game::set_skipMonsterPhase(bool value){ skipMonsterPhase = value ;  }

bool Game::ShouldSkipMonsterPhase() const{ return skipMonsterPhase; }

void Game::increase_terror_level() {
    terror_Level++;
    std::cout << "Terror Level increased to " << terror_Level << "!\n";
}

void Game::monster_objectes()  {
    static int lastDestroyed = -1;
    static int lastCollected = -1;
    Location* Dloc = dracula.get()->get_location();
    Location* Iloc = invisibleMan.get()->get_location();
    if (dracula) {
        int destroyed = 0;
        for (const auto& entry : dracula->get_coffins_map()) {
            if (entry.second) destroyed++;
        }
        if (destroyed != lastDestroyed) { // فقط وقتی تغییر کرد
           std::cout << "[DEBUG] Reached before GAME_LOG" << std::endl;
           GAME_LOG_OBJ(*this , "Dracula location : " + Dloc->get_name());
          GAME_LOG_OBJ(*this, "Coffins destroyed (Dracula): " + std::to_string(destroyed) + "/4");
           std::cout << "[DEBUG] Passed after GAME_LOG" << std::endl;
            lastDestroyed = destroyed;
        }
    } 

    if (invisibleMan) {
        int collected = invisibleMan->get_evidence_count();
        if (collected != lastCollected) { // فقط وقتی تغییر کرد
            GAME_LOG_OBJ(*this, "Evidence collected (Invisible Man): " + std::to_string(collected) + "/5");
            lastCollected = collected;
        }
    }
}
void Game::return_item(const Item& item) {
    pool.add_item(item);  
}

void Game::Changing_frenzy_marker() {
  //  if (frenziedMonster == dracula.get())
        frenziedMonster = invisibleMan.get();
  //  else if (frenziedMonster == invisibleMan.get())
      //  frenziedMonster = dracula.get();
}
Monster* Game::get_frenzied_monster() {
    return frenziedMonster;
}

ItemColor Game::string_to_color(const std::string& color)
{
    if(color == "Red") return ItemColor::Red ;
    if(color == "Blue") return ItemColor::Blue ;
    if(color == "Yellow") return ItemColor::Yellow ;

    return ItemColor::Reset ;
}

Hero* Game::create_hero_by_name(const std::string& name) {

    Factory factory(*this);

    auto hero_unique = factory.createHero(name);
    Hero* hero = hero_unique.get();
    if(hero_unique) heroStorage.push_back(std::move(hero_unique));

    return hero ;
}

std::unique_ptr<Perkcard> Game::find_perk_by_name(const std::string& name) {
    Factory factory(*this);
    auto card_unique = factory.createPerkcard(name);
    return card_unique ;
}

Villager* Game::create_villager(const string & name, Location * current_loc){
    Villager* v = new Villager(map , name, nullptr, current_loc ,"") ; 
    all_villagers.push_back(v); 
    return v;
}

Menu *Game::get_menu(){ return menu.get(); }

void Game::log(const std::string& message) {
    logs.push_back(message);
    if (logs.size() > 50)
        logs.erase(logs.begin());
}

void Game::clear_logs() {
    logs.clear();
}
const std::vector<std::string>& Game::get_logs() const { return logs; }

                    
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
    heroes.clear();
    all_villagers.clear();
    UnloadMusicStream(music); 
    CloseAudioDevice(); 
}

void Game::ResetGame() {

    heroes.clear();
    logs.clear();
    activeHero = nullptr;
    dracula = nullptr ; 
    invisibleMan = nullptr ; 
    frenziedMonster = nullptr; 
    current_card = nullptr;
    currentPhase = Phase::HeroPhase;
    heroTurnInProgress = false;
    game_over = false;
    heroTurnInProgress = false ;
    monsterPhaseDone = false;
    heroPhaseDone = false;
    skipMonsterPhase = false ;
    terrorAlreadyIncreased = false;
    terror_Level = 0;

}
