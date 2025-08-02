#include "Game.hpp"
using namespace std;

int Game::terror_Level = 0; 
Game::Game() {
    InitWindow(1000 + 400, 1000, "The Horrified");

    SetTargetFPS(60);
    
    map.build_map(); 
    menu = make_unique<Menu>(*this) ;

    dracula = std::make_unique<Dracula>(map.get_location_by_name("Cave"));
    invisibleMan = std::make_unique<InvisibleMan>(map.get_location_by_name("Barn"));

    monstersMap[MonsterType::Dracula] = dracula.get();
    monstersMap[MonsterType::InvisibleMan] = invisibleMan.get();

    frenziedMonster = dracula.get();

    monstersMap[MonsterType::Frenzied] = frenziedMonster;

    initializaDeck() ;
    initializaMDeck();
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


    for(Hero* hero : turnManager.get_heroes()){
        getNewCard(hero) ; 
    }
}

PlayerInfo Game::getPlayer1() const{ return player1; }
PlayerInfo Game::getPlayer2() const { return player2 ;}

void Game::setPlayer1(const std::string& p1 , Hero* h){ player1.name = p1 ; player1.hero = h ;}
void Game::setPlayer2(const std::string& p2 , Hero* h){ player2.name = p2 ;  player2.hero = h ;}


std::string Game::checkString(std::string str){
    for (char &c : str) 
        c = tolower(c); 
    return str;
}
void Game::start() {

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
        // if(turnManager.all_heroes_dead()){
        //     cout << "you lose! all heroes are dead\n" ;
        //     break; //show a message instead of break
        // }
    }
    CloseWindow() ;
}
void Game::set_currentPhase(Phase newPhase){ currentPhase = newPhase ; }

void Game::set_HeroTurnInProgress(bool val){ heroTurnInProgress = val ; }

bool Game::hero_phase(Hero* hero , GameRender* render) {

    if (hero->GetRemainingActions() > 0) {
        return false;  
    }

    if(Villager::AnyVillagerInSafePlace()){
        Villager::removeVillager() ;
       cout << hero->GetName() << " got one perk card from moving a villager to its safeplace!\n" ; 
    }
    render->draw() ;
    hero->resetMaxActions() ;
    return true ;
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
       perkDeck.addCard(std::make_unique<Hurrycard>(turnManager.get_heroes(), map)) ; 
       perkDeck.addCard(std::make_unique<LateintotheNightCARD>()) ;
       perkDeck.addCard(std::make_unique<BreakofDawnCARD>(pool , map)) ;
       perkDeck.addCard(std::make_unique<OverstockCard>( turnManager.get_heroes(), pool , map)) ;
       perkDeck.addCard(std::make_unique<VisitfromtheDetectiveCARD>(invisibleMan.get() , map)) ;     
    }
       perkDeck.addCard(std::make_unique<LateintotheNightCARD>()) ; 
       perkDeck.addCard(std::make_unique<OverstockCard>( turnManager.get_heroes(), pool , map)) ;

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
    monster_dice();       
}

void Game::send_hero_to_hospital(Hero* h) {
    Location* hospital = map.get_location_by_name("Hospital");
    h->MoveTo(hospital);
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

void Game::set_skipMonsterPhase(bool value){ skipMonsterPhase = value ;  }

bool Game::ShouldSkipMonsterPhase() const{ return skipMonsterPhase; }

void Game::increase_terror_level() {
    terror_Level++;
    std::cout << "Terror Level increased to " << terror_Level << "!\n";
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

std::vector<std::string> Game::get_last_events(int count) {
    std::vector<std::string> result;
    int start = std::max(0, (int)event_log.size() - count);
    for (int i = start; i < event_log.size(); ++i)
        result.push_back(event_log[i]);
    return result;
}

ItemColor Game::string_to_color(const std::string& color)
{
    if(color == "Red") return ItemColor::Red ;
    if(color == "Blue") return ItemColor::Blue ;
    if(color == "Yellow") return ItemColor::Yellow ;

    return ItemColor::Reset ;
}

Hero* Game::create_hero_by_name(const std::string& name) {
    if (name == "courier") {
        courier = std::make_unique<Courier>(map, turnManager);
        return courier.get();
    }
    else if (name == "scientist") {
        scientist = std::make_unique<Scientist>(map);
        return scientist.get();
    }
    else if (name == "mayor") {
        mayor = std::make_unique<Mayor>(map);
        return mayor.get();
    }
    else if (name == "archaeologist") {
        archaeologist = std::make_unique<Archaeologist>(map);
        return archaeologist.get();
    }
    std::cerr << "Unknown hero type: " << name << "\n";
    return nullptr;
}

void Game::SaveGame(){
    ofstream file("saveGame.txt") ;
    if(!file.is_open()) return ; 

    file << "# players info\n" ; 
    file << "player1: " << getPlayer1().name  << ',' << getPlayer1().hero->GetName() << '\n';
    file << "player2: " << getPlayer2().name << ',' << getPlayer2().hero->GetName()  << '\n';

    file << "\n# Hero\n" ;
    for(const auto h : turnManager.get_heroes()){
        file << "hero: " << h->GetName() << '\n' ; 
        file << "location: " << h->GetCurrentLocation()->get_name() << '\n' ;
        file << "actions left: " << h->GetRemainingActions() << '\n' ;
        file << "items: " << '\n' ;  
        for( const auto& i : h->GetItems())
            file << i.getName() << ',' << i.color_to_string(i.getColor()) << ','
                << i.getStrength() << ',' << i.getLocationName() << ',' << i.get_TexturePath() << '\n';
        file << '\n' ;

    }
    file << "# turn info\n" ;
    file << "turn: " << turnManager.get_active_hero()->GetName() << '\n' ; 

    file << "\n# Monster\n" ; 
    file << "monster: " << dracula->get_name() << '\n' ;
    file << "location: " << dracula->get_location()->get_name()  << '\n' ;
    file << "monster: " << invisibleMan->get_name() << '\n' ;
    file << "location: " << invisibleMan->get_location()->get_name()  << '\n' ;

    file << "\n# locations:\n" ;
    for(const auto& loc : map.get_locations()){
        file << "location: " << loc->get_name() << '\n' ;
        file << "items: " ;
        for( const auto i : loc->get_items())
            file << i.getName() << ',' << i.color_to_string(i.getColor()) << ','
                << i.getStrength() << ',' << i.getLocationName() << ',' << i.get_TexturePath() << ';';

        file << '\n' ;
        file << "villagers: " ; 
        for( const auto vill : loc->get_villagers())
            file << vill->get_name() << ',' ; 
        file << '\n' ;
    }   
    DrawText("Game saved!" , 1100 , 10 , 50 , GREEN)  ;
}

void Game::LoadGame() {

    std::ifstream file("saveGame.txt");
    if (!file.is_open()) {
        std::cerr << "Could not open saveGame.txt\n";
        return;
    }
    std::string line;
    Hero* currentHero = nullptr;
    Location* currentLocation = nullptr;

    while(getline(file , line)){

        if(line.empty() || line[0] == '#') continue;

        if(line.rfind("player1:" , 0) == 0){
            string data = line.substr(9) ; 
            stringstream ss(data) ;
            string playername , heroname ;
            getline(ss, playername, ',');
            getline(ss, heroname, ',');

            Hero* h = turnManager.find_hero_by_name(heroname);
            if(!h) {
                h = create_hero_by_name(heroname) ;
                turnManager.add_hero(h);
            }
            setPlayer1(playername , h);
        }

        else if(line.rfind("player2:" , 0) == 0){
            string data = line.substr(9) ; 
            stringstream ss(data) ;
            string playername , heroname ;
            getline(ss, playername, ',');
            getline(ss, heroname, ',');

            Hero* hero = turnManager.find_hero_by_name(heroname);
            if(!hero) {
                hero = create_hero_by_name(heroname) ;
                turnManager.add_hero(hero);
            }
            setPlayer2(playername , hero);
        }
        else if(line.rfind("hero:" , 0) == 0){
            string name = line.substr(6); 
            currentHero = turnManager.find_hero_by_name(name);

            if(!currentHero){
                currentHero = create_hero_by_name(name);
                if(currentHero)
                    turnManager.add_hero(currentHero);  
            }
        }
        else if(line.rfind("location: " , 0) == 0 && currentHero){
            string name = line.substr(10) ; 
            Location* loc = map.get_location_by_name(name) ;
            currentHero->SetCurrentLocation(loc ? loc : nullptr) ;
        }
        else if(line.rfind("actions left:" , 0 ) == 0 && currentHero){
            int actions = std::stoi(line.substr(14)) ; 
            currentHero->SetRemainingActions(actions) ;
        }
        else if(line.rfind("items:" , 0 ) == 0 && currentHero){
            while(getline(file , line) && !line.empty()){
                stringstream itemStream(line);
                string name , colorStr , strengthStr , Locname , texture ;
                if(!getline(itemStream, name, ',')) continue;
                if(!getline(itemStream, colorStr, ',')) continue;
                if(!getline(itemStream, strengthStr, ',')) continue;
                if(!getline(itemStream, Locname, ',')) continue;
                if(!getline(itemStream, texture, ',')) continue;

                ItemColor color = string_to_color(colorStr);
                int strength = stoi(strengthStr);
                Item item(name , color , strength , Locname , texture);
                item.loadTexture() ;

                currentHero->addItems(item);
            }
            currentHero = nullptr ;
        }
        else if(line.rfind("turn:" , 0) == 0){
            string active_name = line.substr(6) ;
            turnManager.set_active_hero(active_name) ;
        }
        else if(line.rfind("monster:" , 0) == 0) {
            string monstername = line.substr(9); 
            getline(file , line); 
            if(line.rfind("location: " , 0 ) == 0){
                string locname = line.substr(10);
                Location* loc = map.get_location_by_name(locname);

                if(monstername == "Dracula") dracula->set_location(loc ? loc : nullptr); 
                else if(monstername == "InvisibleMan") invisibleMan->set_location(loc ? loc : nullptr); 
            
            }
        }
        else if(line.rfind("location: " , 0) == 0){
            string locname = line.substr(10) ;
            currentLocation = map.get_location_by_name(locname) ; 
        }
        else if(line.rfind("items:", 0) == 0 && currentLocation){
            string itemstr = line.substr(6);
            if(!itemstr.empty() && itemstr[0] == ' ')
                itemstr = itemstr.substr(1);

            if(itemstr.empty())
                continue;

            stringstream ss(itemstr);
            string itemData;

            while(getline(ss, itemData, ';')){
                if(itemData.empty()) continue;

                stringstream itemStream(itemData);
                string name , colorStr , strengthStr , Locname , texture ;

                if(!getline(itemStream, name, ','))  continue; 
                if(!getline(itemStream, colorStr, ',')) continue;
                if(!getline(itemStream, strengthStr, ',')) continue;
                if(!getline(itemStream, Locname, ',')) continue;
                if(!getline(itemStream, texture, ',')) continue;

                ItemColor color = string_to_color(colorStr);
                int strength = stoi(strengthStr);
                const Item item(name, color, strength, Locname, texture);
                currentLocation->add_item(item);
            }
        }
        else if(line.rfind("villagers:" , 0) == 0 && currentLocation){
            string villagerStr = line.substr(11) ; 
            stringstream ss(villagerStr) ; 
            string villName ; 
            while (getline(ss, villName, ',')) {
                if (villName.empty()) continue;

                Villager* vill = Villager::find_villager_by_name(villName);
                if(!vill) 
                    create_villager(villName , currentLocation) ;
                if(vill) 
                    currentLocation->add_villager(vill) ;   
            }
        }
    }
    cout << "game loaded\n" ;
}

Villager* Game::create_villager(const string & name, Location * current_loc){
    Villager* v = new Villager(map , name, nullptr, current_loc ,"") ; 
    all_villagers.push_back(v); 
    return v;
}

Menu *Game::get_menu(){ return menu.get(); }

Game::~Game(){
    if(frenziedMonster)
        delete frenziedMonster ;
    pool.unload_in_use_items() ;
}