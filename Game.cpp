#include <string>
#include <map>
#include <iomanip>
#include <set>
#include <limits>
#include <utility>

#include "Game.hpp"
#include "Mayor.hpp"
#include "Archaeologist.hpp"
#include "villager.hpp"
#include "perkcards.hpp"

using namespace std;

Game::Game() {
    // ساخت نقشه ثابت
    map.build_map(); // نقشه ی بازی
    
    // ۱۲ ایتم اولیه ی بازی قرار گرفتند
    distribute_initial_items();
    
    
    
    choose_character(); // اینجا قهرمان ها ساخته شدند
    
    
    
    // اضافه کردن هیولاها
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
        ChoosePerkCard(h) ;
        continue;
    }
        
    if(h->PerformTheAction(chosenAction)){
        cout << "actions left: " << h->GetRemainingActions() << '/' << h->getMaxActions() << '\n' ;

        if(chosenAction == "Move"){
            string chosenPlace ; 
            cout << "Which neighboring place do you want to move to? " ;
            cin >> chosenPlace ;
            Location* currentLoc = h->GetCurrentLocation() ; 
            Location* chosenLocation = map.get_location_by_name(chosenPlace);

            if(currentLoc->findNeighbor(chosenPlace)){ //اگر خونه ای که انتخاب کرده واقعا همسایه فعلی بود
                if(h->hasvillagerHere()){//چک شود که ایا محلی در مکان قهرمان فعلی هست یا نه
                    auto here = h->villagerHere() ; // vector of villagers in the same place
                        string ans ;
                        cout << "some villagers are at the same place as you. " ; 
                        h->showvillagersHere() ; 
                        cout << "\ndo you want to move the villagers with you?(yes = moving all villagers with you/no = moving alone) " ; 
                        cin >> ans ; 
                        if(ans == "yes")
                            h->MoveTo(chosenLocation , here) ; 
                        else if(ans == "no")
                            h->MoveTo(chosenLocation) ;
                        else cerr << "wrong answer\n" ; 
                    }
                    else { 
                        h->MoveTo(chosenLocation); 
                    }    
                }
                else{
                    cerr << "what you have chosen is not a neighboirng place!\n" ;  
                }
                    
                }
                else if(chosenAction == "Guide"){
                    string chosenPlace , mode ; 
                    Location* currentLoc = h->GetCurrentLocation() ; 
                    cout << "Guide:\n" 
                         << "current -> move a villager from your location to a neighbor\n"
                         << "neighbor -> move a villager from a neighbor to your location\n"
                         << "choose: ";
                    
                    cin >> mode ; 

                    if(mode == "current"){
                        if(h->hasvillagerHere()){
                            cout << "some villagers are at the same place as you: " ;
                            h->showvillagersHere() ;
                            cout << "\nwho do you want to move? " ; 
                            string chosenvillager ;
                            cin.ignore(numeric_limits<streamsize>::max(), '\n') ; 
                            getline(cin , chosenvillager) ; 
                            bool found = false ; 
                            for(auto *v : h->villagerHere()){
                                if(chosenvillager == v->get_name()){
                                    found = true ; 
                                    cout << "Which neighboring place do you want to move them? " ;
                                    cin >> chosenPlace ; 
                                    if(currentLoc->findNeighbor(chosenPlace)){

                                        Location* chosenLocation = map.get_location_by_name(chosenPlace) ;  
                                        v->MoveTo(chosenLocation , chosenvillager) ;
                                        //cout << chosenvillager << " has been guided to " << chosenPlace << '\n' ;
                                        found = true ; 
                                        break ;
                                    }else{
                                        //throw invalid_argument( "what you have chosen is not a neighboring place!\n");   
                                        cerr << "what you have chosen is not a neighboring place!\n" ; 
                                    }
                                }
                            } 
                            if(!found){
                              //  throw invalid_argument("villager not found!") ;
                                cerr << "villager not found!\n" ;
                            }  

                        }else cerr << "no villagers at your location!\n";
                    }
                    else if(mode == "neighbor"){
                        Location* currentLoc = h->GetCurrentLocation() ;
                        vector<villager*> availableVillager ;
                        for(auto *neigbor :  currentLoc->get_neighbors()){
                            for(auto *v : villager::all()){
                                if(v->get_currentLocation() == neigbor)
                                    availableVillager.push_back(v) ;                                        
                                }
                            }
                        if(availableVillager.empty()) cerr << "no villager nearby!\n" ;
                        else{
                            cout << "some villagers in the neigbors are: " ;
                            for(auto v : availableVillager)
                                cout << *(v->get_currentLocation()) << " -> " << v->get_name() << '\n';
                            string chosenvillager ; 
                            cout << "Which villager do you want to move to your location? " ;
                            cin.ignore(numeric_limits<streamsize>::max(), '\n') ; 
                            getline(cin , chosenvillager) ;  
                            bool found = false ; 
                            for(auto *v : availableVillager){
                                if(chosenvillager == v->get_name()){
                                    v->MoveTo(currentLoc , chosenvillager) ;
                                    found = true ;
                                    break ;  
                                    } 
                                }
                                if(!found){
                                   // throw invalid_argument("villager not found!") ;
                                    cerr << "villager not found!\n" ; 
                                } 
                            }

                    }else{
                      //throw invalid_argument("wrong answer!\n");   
                      cerr << "wrong answer!\n" ;
                    }      
                }
                else if(chosenAction == "Pickup"){
 
                    h->PickupItems() ;
                    h->DisplayItem() ; 

                } 
                else if(chosenAction == "Special"){
                    Location* heroLoc = h->GetCurrentLocation() ; 
                    vector<Location*> heroLocNeighbor = heroLoc->get_neighbors() ; 
                    cout << "neighboring locations: " ;
                    for(size_t i = 0 ; i <heroLocNeighbor.size() ; i++)
                        cout << heroLocNeighbor[i]->get_name() << " " ;
                    cout << endl ; 

                    cout << "Which neighboring place do you want to pick up its items? " ;
                    string chosenplace ; 
                    cin >> chosenplace ;

                    if(heroLoc->findNeighbor(chosenplace)){
                        Location* chosenLoc = map.get_location_by_name(chosenplace) ;
    
                        h->SpecialPickup(chosenLoc) ;
                        h->DisplayItem() ; 

                    }else{
                       //throw invalid_argument("what you have chosen is not a neighboring place!\n") ; 
                       cout << "what you have chosen is not a neighboring place!\n" ; 
                    } 
  
                }
                else if(chosenAction == "Advance"){ //for the monster missions
                    //for dracula
                    Location* current = h->GetCurrentLocation();
                    string locName = current->get_name();

                    if(locName == "Cave" || locName == "Dungeon" || locName == "Crypt" || locName == "Graveyard" ){// اگر قهرمان در محل قرار گیری تابوتهای دراکولا بود
                        cout << "To destroy Dracula's coffin, use red items with total strength >= 6.\n" ;
                        int totalStrength = h->AdvanceActionForDracula() ;
                        if (totalStrength >= 6) {
                            dracula->destroy_coffin_at(locName); // توابع Dracula همین‌طور باقی می‌مونن
                        } else {
                            std::cout << "Advance action failed Not enough red item strength.\n";
                        }
                    }
                    //for invisible man
                    else if(h->GetCurrentLocation() == map.get_location_by_name("Precinct")) { // در مکانی که باید آیتم هارو بزاره بود
                        h->AdvanceActionForInvisibleMan(invisibleMan) ;
                    }
                    else cerr << "you can not do advance action unless you are in coffin places or search locations\n" ; 
                
                }
                else if(chosenAction == "Defeat"){
                   
                    Location* heroLoc = h->GetCurrentLocation();
                
                    if (invisibleMan && invisibleMan->get_location() == heroLoc) {
                        if (invisibleMan->can_be_defeated()) {
                            std::cout << "You are ready to defeat the Invisible Man! Use RED items (total strength >= 9).\n";

                            int redPower = h->select_items_to_defeat(ItemColor::RED);

                            if (redPower >= 6) {
                                invisibleMan->set_location(nullptr); // شکست خورد
                                std::cout << "Invisible Man has been defeated!\n";
                            } else {
                                std::cout << "Not enough RED item power. Invisible Man survived.\n";
                                }
                            }
                        }

                    // چک کنیم آیا دراکولا همین‌جاست
                    if (dracula && dracula->get_location() == heroLoc) {
                        if (dracula->can_be_defeated()) {
                            std::cout << "You are ready to defeat Dracula! Select yellow items to attack.\n";
                            int yellowPower = h->select_items_to_defeat(ItemColor::YELLOW);
                
                            if (yellowPower >= 6) {
                                std::cout << "Dracula has been defeated!\n";
                                // امتحان کن بعدا ببین حذف میشه یا نه اررور داره فعلا
                                dracula->set_location(nullptr); 
                            } else {
                                std::cout << "Not enough yellow item power. dracula did not die.\n";
                            }
                        } else {
                            std::cout << "You must destroy all coffins first to defeat Dracula.\n";
                        }
                    }else{
                        cerr << "you can not use defeat action unless you are in monster place\n" ;
                    }
                }

            } // end if can play an action
    }    
}



void Game::hero_phase(Hero* hero) {

    getNewCard(hero) ; //در ابتدای هر فاز به قهرمان یک پرک تعلق میگیرد
    hero->DisplayInfo() ;
    play_hero_Action(hero) ;

    if(villager::AnyVillagerInSafePlace()){
        villager::removeVillager() ;
        getNewCard(hero) ; 
        cout << hero->GetName() << " got one perk card from moving a villager to its safeplace!\n" ; 
    }

    hero->resetMaxActions() ;
}


void  Game::start() { 

    locationOverview() ;

    while (true) {

        // ۱. فاز قهرمان
        cout << ItemColor::BLUE << "<-----------HERO PHASE----------->\n" << ItemColor::Reset; 
        Hero* activeHero = turnManager.get_active_hero();
        std::cout << "It's " << activeHero->GetName() << "'s turn!\n";
        hero_phase(activeHero);

        graph_map_text();

        if(!skipMonsterPhase){
        // ۲. فاز هیولا
        cout << ItemColor::RED  <<  "\n<-----------MONSTER PHASE---------->\n" <<  ItemColor::Reset  ; 
        monster_phase();
        }
        else{
            cout << "\nMonster Phase skipped due to 'Break of Dawn' perk!\n";   
            skipMonsterPhase = false;     
        }

        locationOverview() ;

        // ۳. بررسی پایان بازی
        if (terror_Level >= 6) {
            std::cout << "Game Over! Terror level reached 6.\n";
            break;
        }    
        if (deck.is_empty() && +!both_monsters_defeated()) {
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
void Game::getNewCard(Hero* hero){
    p2 = p.get_random_card() ;
    hero->AddAvailablePerk(p2) ; 
}
void Game::playPerkCard(Hero* hero, string card){
    while(true) {
    if(card == "Hurry"){
            string firstMove , secondMove ; 
            p.display_the_card(p2) ; 
            cout << "Mayor..where do you want to move first? " ;
            cin >> firstMove ; 
            Location* currentLoc = mayor->GetCurrentLocation() ; 
            Location* firstMoveLoc = map.get_location_by_name(firstMove);
            if(currentLoc->findNeighbor(firstMove)) // اگر محلی که انتخاب شده همسایه بود
                mayor->MoveTo(firstMoveLoc) ;        
            else{
                cerr << "what you have chosen is not a neighboring place!!\n" ;
                continue;
            } 

            cout << "Mayor..what is your second place to move? " ;
            cin >> secondMove ;
            Location* secondMoveLoc = map.get_location_by_name(secondMove);
            if(currentLoc->findNeighbor(secondMove)) // اگر محلی که انتخاب شده همسایه بود
                mayor->MoveTo(secondMoveLoc) ;        
            else{
                cerr << "what you have chosen is not a neighboring place!!\n" ;
                continue;
            }  

            cout << "--------------\n" ;
            string AfirstMove , AsecondMove ; 
            cout << "Archaeologist..where do you want to move first? " ;
            cin >> AfirstMove ; 
            Location* AcurrentLoc = archaeologist->GetCurrentLocation() ; 
            Location* AfirstMoveLoc = map.get_location_by_name(AfirstMove);
            if(AcurrentLoc->findNeighbor(AfirstMove)) // اگر محلی که انتخاب شده همسایه بود
                archaeologist->MoveTo(AfirstMoveLoc) ;        
            else{
                cerr << "what you have chosen is not a neighboring place!!\n" ;
                continue;  
            } 

            cout << "Archaeologist..what is your second place to move? " ;
            cin >> AsecondMove ;
            Location* AsecondMoveLoc = map.get_location_by_name(AsecondMove);
            if(AcurrentLoc->findNeighbor(AsecondMove)) // اگر محلی که انتخاب شده همسایه بود
                archaeologist->MoveTo(AsecondMoveLoc) ;        
            else{
                cerr << "what you have chosen is not a neighboring place!!\n" ;
                continue;
            }      
        }
        else if (card == "Repel"){
            p.display_the_card(p2) ;
            cout << "where do you want to move the invisible man for the first move? " ; 
            string firstplace ; cin >> firstplace ;
            Location* IfirstnewLoc = map.get_location_by_name(firstplace) ;  
            if(IfirstnewLoc){
                invisibleMan->set_location(IfirstnewLoc) ; 
                cout << "invisible man moved to " << firstplace << '\n' ; 
            }
            else{
                cerr << "could not find the place!\n" ;
                continue; 
            }
            cout << "where do you want to move the invisible man for the second move? " ;
            string secondplace ; cin >> secondplace ;
            Location* IsecondnewLoc = map.get_location_by_name(secondplace) ;  
            if(IsecondnewLoc){
                invisibleMan->set_location(IsecondnewLoc) ; 
                cout << "invisible man moved to " << secondplace << '\n' ; 
            }
            else{
                cerr << "could not find the place!\n" ;
                continue; 
            }
            cout << "where do you want to move the dracula for the first move? " ; 
            string Dfirstplace ; cin >> Dfirstplace ;
            Location* DfirstLec = map.get_location_by_name(Dfirstplace) ;  
            if(DfirstLec){
                dracula->set_location(DfirstLec) ; 
                cout << "dracula moved to " << Dfirstplace << '\n' ; 
            }
            else{
                cerr << "could not find the place!\n" ;
                continue; 
            }
            cout << "where do you want to move the dracula for the second move? " ;
            string Dsecondplace ; cin >> Dsecondplace ;
            Location* DsecondLoc = map.get_location_by_name(Dsecondplace) ;  
            if(DsecondLoc){
                dracula->set_location(DsecondLoc) ; 
                cout << "dracula moved to " << Dsecondplace << '\n' ; 
            }
            else{
                cerr << "could not find the place!\n" ;
                continue; 
            }


        }

        else if(card == "Late into the Night"){
            p.display_the_card(p2) ;

            hero->SetRemainingActions(hero->GetRemainingActions() + 2) ;
            cout << hero->GetName() << " actions changed to " << hero->GetRemainingActions() << '\n' ; 
        }
        else if( card == "Break of Dawn"){
            skipMonsterPhase = true ; //فاز هیولا بعدی رد میشود 
            p.display_the_card(p2);
            ItemPool pool ;
            vector<Item> PoolItems = pool.draw_random_items(2) ;
            for(const auto i : PoolItems){
                Location* Loc = map.get_location_by_name(i.getLocationName());
                if(Loc){
                    Loc->add_item(i) ;
                    cout << "Item " << i.getName() << " placed in location " << i.getLocationName() << "\n";
                }
            }
        }
        else if(card == "Overstock"){
            p.display_the_card(p2) ;
            ItemPool pool ; 
            vector<Item> PoolItems = pool.draw_random_items(2) ;
            if(PoolItems.size() < 2) cerr << "not enough items drawn from the pool !\n" ;

            Location* LocFirst = map.get_location_by_name(PoolItems[0].getLocationName());
            if(LocFirst){
                LocFirst->add_item(PoolItems[0]) ; 
                cout << "Mayor placed " << PoolItems[0].getName() << " in the location " << PoolItems[0].getLocationName() << '\n' ;
            }
         
            Location* LocSecond = map.get_location_by_name(PoolItems[1].getLocationName());
             if(LocSecond){
                LocSecond->add_item(PoolItems[1]) ; 
                cout << "Archaeologist placed " << PoolItems[1].getName() << " in the location " << PoolItems[1].getLocationName() << '\n' ;
            }           
        }
        else if(card == "Visit from the Detective"){
            p.display_the_card(p2) ; 
            cout << "where do you want to move the invisible man? " ; 
            string place ; cin >> place ;
            Location* newLoc = map.get_location_by_name(place) ;  
            if(newLoc){
                invisibleMan->set_location(newLoc) ; 
                cout << "invisible man moved to " << place << '\n' ; 
            }
            else{
                cerr << "could not find the place!\n" ;
                continue; 
            }
        }
    break ;
    }
}
void Game::ChoosePerkCard(Hero * hero){
    vector<Perkcards>& availablePerks = hero->GetAvailablePerkCards() ;
    if(availablePerks.empty()){
        cout << "you do not have any perk cards!\n" ;
        return ;  
    }
    while(true){
        int selected = -1 ; 
        hero->displayavailblecards() ; 
        for(size_t i = 0 ; i < availablePerks.size() ; i++)
            cout << i + 1 << "." << availablePerks[i].get_Event() << '\n' ; 
            
        cout << "enter the card number to play(0 to end): ";
        cin >> selected ; 
        if(selected == 0) return ; 
        if(selected < 1 || selected > availablePerks.size()){
            cerr << "invalid selection! try again\n" ; 
            continue;
        }
        int index = selected - 1 ;
        Perkcards chosencard = availablePerks[index] ;
        playPerkCard(hero , chosencard.get_Event()) ;
        hero->addPlayedCards(chosencard) ; 
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
            std::cout << "Placed " << item.getName() << " at " << item.getLocationName() << std::endl ;
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
        
        
        // if (deck.is_empty() || !both_monsters_defeated() ){
        //     std::cout << "\nMonster deck is empty. Players lose!\n";

        //     game_over = true;
        //     return;
        // }
        
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
                villager* v = nullptr;
                for (auto* vill : villager::all()) {
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
            std::cout << "Placed " << item.getName() << " at " << item.getLocationName() << "\n";
        }
    }
    
    
    // اجرای strike
    for (const auto& strike : card.get_strikes()) {
        int moves = strike.get_move_count();
        int dice = strike.get_dice_count();
        const auto& monster_list = strike.get_monsters();
        
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

            std::cout << "---MONSTER MOVE FROM STRIKE---"<<endl;
            // حرکت دادن هیولا
            for (int i = 0; i < moves; ++i) {
                Location* target = m->find_nearest_target(m->get_location());
                if (target) {
                    m->move_towards(1);
                } else {
                    std::cout << m->get_name() << " found no target to move toward.\n";
                }
            }
            
            
            
            // تاس انداختن
            std::cout<<"---PLAYING DICE---";
            Dice d(3);
            if (dice <= 0 || dice > 3) {
                std::cout << "Invalid dice count: " << dice << "\n";
                continue; 
            }
            
            std::vector<DiceFace> results = d.roll(dice);
            bool invisiblePowerTriggered = false;

        for (DiceFace face : results) {
            std::cout << "Dice result: ";
            switch (face) {
                case DiceFace::Power:
                    std::cout << "Power\n";
                    if (type == MonsterType::Dracula) {
                        // m->special_power(turnManager.get_active_hero()); // مثل Dark Charm
                    } else if (type == MonsterType::InvisibleMan) {
                        invisiblePowerTriggered = true; // ولی بعداً اجرا می‌کنیم
                    }
                    break;

                case DiceFace::Attack:
                    std::cout << "Attack\n";
                    if (type == MonsterType::Dracula) {
                        auto kv = m->attack(); //[heroTarget, villagerTarget]

                        if (kv.first && !kv.second) {
                            std::cout << "Dracula attacks " << kv.first->GetName() << "!\n";
                        
                            if (kv.first->has_items()) {
                                std::cout << kv.first->GetName() << " has the following items:\n";
                                const auto& items = kv.first->GetItems();
                        
                                for (size_t i = 0; i < items.size(); ++i) {
                                    std::cout << i + 1 << ". " << items[i].getName() << " (" << items[i].color_to_string(items[i].getColor()) << ")\n";
                                }
                        
                                std::cout << "Do you want to use one item to block the attack? (yes/no): ";
                                std::string choice;
                                std::cin >> choice;
                        
                                if (choice == "yes" || choice == "y") {
                                    std::cout << "Select the item number to use: ";
                                    int itemIndex;
                                    std::cin >> itemIndex;
                        
                                    if (itemIndex >= 1 && itemIndex <= (int)items.size()) {
                                        kv.first->remove_item_by_index(itemIndex - 1);
                                        std::cout << "Item used to block the attack!\n";
                                    } else {
                                        std::cout << "Invalid selection. Dracula's attack succeeds.\n";
                                        // send_hero_to_hospital(heroTarget);
                                        increase_terror_level();
                                        break;
                                    }
                                } else {
                                    std::cout << "No item used. Dracula's attack succeeds.\n";
                                    // send_hero_to_hospital(heroTarget);
                                    increase_terror_level();
                                    break;
                                }
                            } else {
                                std::cout << kv.first->GetName() << " has no items. Dracula's attack succeeds.\n";
                                send_hero_to_hospital(kv.first);
                                increase_terror_level();
                                break;
                            }
                        
                        } else if (kv.second) {
                            std::cout << "Dracula attacks " << kv.second->get_name() << "!\n";
                            remove_villager(kv.second);
                            increase_terror_level();
                            break;
                        }
                        
                    } else if (type == MonsterType::InvisibleMan) {
                        // فقط اگه قبلاً اونجا بوده باشه و حمله ممکن باشه
                        auto  kv = m->attack();//[heroTarget, villagerTarget]

                        if (kv.second) {
                            std::cout << "Invisible Man kills " << kv.second->get_name() << "!\n";
                            remove_villager(kv.second);
                            increase_terror_level();

                        }
                        // به قهرمان حمله نمیکنه حتی اگه هست
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
                    m->move_towards(2);
                    std::cout << "Invisible Man Power in dice ! He is closer to villager. now he is in "<< loc2<<endl;
                    
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

void Game::remove_villager(villager* v) {
    v->removevillager(v) ;
    v->set_currentLocation(nullptr); // فرض بر اینکه set_location(nullptr) یعنی حذف
}
void Game::locationOverview(){
    cout << "-----------------------------Location Overview--------------------------------------\n"; 
    cout << left << setw(13) << "Location" << setw(20) << "Item" << setw(20) << "Monsters" << setw(20) << "Villagers" << setw(20) << "Heroes" << "\n" ;
    cout << right <<"--------------------------------------------------------------------------------------\n" ; 
 
    for(const auto& locPtr : map.get_locations()){
        Location* loc = locPtr.get() ;

        //item
        string itemStr ; 
        const auto items = loc->get_items() ;
        if(items.empty())
            itemStr = "-" ; 
        else{
            std::map<string , pair<int , ItemColor>> itemcount ;
            for(const auto & item : items){
                auto& entry = itemcount[item.getName()] ;
                entry.first++ ; entry.second = item.getColor() ; 
            }
            for(const auto& kv : itemcount){
                const auto& name = kv.first ; 
                int cnt = kv.second.first ; 
                ItemColor color = kv.second.second ; 

                itemStr +=  get_color_code(color) + name +  get_color_code(ItemColor::Reset) + "(" + to_string(cnt) + "),"  ;
            }

        }

        //monsters
        string monStr ;
        const auto monsters = loc->get_monsters() ;
        if(monsters.empty())
            monStr = "-" ; 
        else{
            for(const auto& m : monsters)
                monStr+= m->get_name() + "," ;
            
            monStr.pop_back() ;
        }

        //villagers
        string villagerStr;
        const auto& villagers = loc->get_villagers();
        if (villagers.empty()) 
            villagerStr = "-";
        else {
            for (const auto& v : villagers)
                villagerStr += v->get_name() + ",";
            villagerStr.pop_back();
        }   

        //heroes
        string HeroStr ; 
        const auto& heroes = loc->get_heroes() ; 
        if(heroes.empty())
            HeroStr = "-" ; 
        else{
            for(const auto& h : heroes)
                HeroStr+= h->GetName() + "," ; 
            HeroStr.pop_back() ;
            
        }
        cout << left << setw(13) << loc->get_name()
             << setw(20) << itemStr << setw(20) << monStr << setw(20) << villagerStr << setw(20) << HeroStr << "\n";
    }
  cout << "-------------------------------------------------------------------------------------\n" ; 
  cout << "terror level: " << terror_Level << '\n' ; 
  //collected evidences:
  //smashed coffins: 
    
}

void Game::increase_terror_level() {
    terror_Level++;
    std::cout << "Terror Level increased to " << terror_Level << "!\n";
}

villager* Game::create_villager(const std::string& name, const std::string& locName) {
    Location* loc = map.get_location_by_name(locName);
    if (!loc) {
        std::cout << "Can't move the villager '" << name << "': location '" << locName << "' not found.\n";
        return nullptr;
    }

    villager* v = new villager(map , name, nullptr, loc) ; //safeplace = null 
    std::cout << "Created new villager: " << name << " at " << locName << "\n";
    return v;
}
void Game::graph_map_text() {
    std::cout << R"(


--------------------------------GAME MAP------------------------------------- 
       
                [Precinct]-----[Inn]                                                 
                  /               \                                                   
  [Cave]----[Camp]     _______[Theatre]---------[Tower]-----[Dungeon]
                |     /       /
                |    /       /                                      \
[Abbey] ----[Mansion]----[Shop]                                      [Docks]
    |          /   |           \
    |    [Museum] [Church]    [Laboratory]
 [Crypt]            /    \               \
             [Graveyard][Hospital]        [Institute]
              
    
    )" << '\n';
std::cout<<"--------------------------------------------------------------------------------";    
}
