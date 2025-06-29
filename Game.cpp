#include <string>
#include <map>
#include <iomanip>
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
    
    
    
    // اینجا قهرمان ها ساخته شدند
    choose_character(); 
    
    
    
    // اضافه کردن هیولاها
    
    dracula = new Dracula(map.get_location_by_name("Cave"));
    
    // invisibleMan = new InvisibleMan(map.("Barn"));

    monstersMap[MonsterType::Dracula] = dracula;
    // monstersMap[MonsterType::InvisibleMan] = invisibleMan;

    
    
    
}    

Game::~Game() {
    for (Hero* h : turnManager.get_heroes())
    delete h;
}    

// درست کار میکند
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
    cout << "what action do you want to play this turn(Move, Guide , Pickup , Advance ,Defeat , Perk , Help , Quit) ? " ;
    cin >> chosenAction ; 
    if(chosenAction == "Help")
        h->DisplayActions() ;
    if(chosenAction == "Quit")
        break ;
    if(chosenAction == "Perk")
        playPerkCard(h) ;
        
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
                    }else
                        cerr << "wrong answer!\n" ;    
                }
                else
                    cerr << "what you have chosen is not a neighboring place!\n";
                    
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
                            cin >> chosenvillager ;  
                            bool found = false ; 
                            for(auto *v : h->villagerHere()){
                                if(chosenvillager == v->get_name()){
                                    cout << "Which neighboring place do you want to move them? " ;
                                    cin >> chosenPlace ; 
                                    if(currentLoc->findNeighbor(chosenPlace)){

                                        Location* chosenLocation = map.get_location_by_name(chosenPlace) ;  
                                        v->MoveTo(chosenLocation , chosenvillager) ;
                                        //cout << chosenvillager << " has been guided to " << chosenPlace << '\n' ;
                                        found = true ; 
                                        break ;
                                    }else throw invalid_argument( "what you have chosen is not a neighboring place!\n");   
                                }
                            } 
                            if(!found) throw invalid_argument("villager not found!") ; 

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
                            cin >> chosenvillager ; 
                            bool found = false ; 
                            for(auto *v : availableVillager){
                                if(chosenvillager == v->get_name()){
                                    v->MoveTo(currentLoc , chosenvillager) ;
                                    found = true ;
                                    break ;  
                                    } 
                                }
                                if(!found) throw invalid_argument("villager not found!") ;
                            }

                    }else throw invalid_argument("wrong answer!\n");        
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

                    }else throw invalid_argument("what you have chosen is not a neighboring place!\n") ;
  
                }
                else if(chosenAction == "Advance"){ //for the monster missions
                    //for dracula
                    Location* current = h->GetCurrentLocation();
                    std::string locName = current->get_name();
                
                    // آیا هیرو در یکی از مکان‌های تابوت هست؟
                    if (locName == "Cave" || locName == "Dungeon" || locName == "Crypt" || locName == "Graveyard") {
                        std::cout << "To destroy Dracula's coffin, use red items with total strength >= 6.\n";
                        int totalStrength = h->AdvanceActionForDracula(); 
                        
                        if (totalStrength >= 6) {
                            dracula->destroy_coffin_at(locName); // توابع Dracula همین‌طور باقی می‌مونن
                        } else {
                            std::cout << "Advance action failed Not enough red item strength.\n";
                        }


                    }
                    //for invisible man
                    else if(h->GetCurrentLocation() == map.get_location_by_name("Precinct")) { // در مکانی که باید آیتم هارو بزاره بود
                        h->AdvanceActionForInvisibleMan() ;
                    }
                    else cerr << "you can not do advance action unless you are in coffin places or search locations\n" ; 
                
                }
                else if(chosenAction == "Defeat"){
                    // اگر در همه لوکبشن های تابوت Advance بکار برده شد == 
                    //امکان شکست هیولا 
                    //از تابع can be defeated دراکولا استفاده شود
                    //1-اگر قهرمان در لوکیشنی که دراکولا قرار دارد قرار داشت
                    //2- استفاده از آیتم های زرد برای نابودی دراکولا
                    //3- استفاده از آیتم های قرمز با مجموع 9 یا بالاتر برای نابودی نامرئی

                    Location* heroLoc = h->GetCurrentLocation();

                    
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
                    }
                

                }
            } // end if can play an action 
    }    
}





void Game::hero_phase(Hero* hero) {

    hero->DisplayInfo() ;
    play_hero_Action(hero) ;
    hero->resetMaxActions() ;

}


void  Game::start() { 
    std::cout << "Number of heroes: " << turnManager.get_heroes().size() << "\n";

while (true) {
        // ۱. فاز قهرمان
        Hero* activeHero = turnManager.get_active_hero();
        std::cout << "It's " << activeHero->GetName() << "'s turn!\n";
        hero_phase(activeHero);

        // ۲. فاز هیولا
        
        monster_phase();

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

void Game::playPerkCard(Hero * hero){
    PerkDeck p ; 
    Perkcards p2 ;
    p2 = p.get_random_card() ;
    hero->playedPerk(p2) ; 
    hero->displaycards() ;
    cout << p2 << endl;
    if(p2.get_Event() == "Hurry"){
            string firstMove , secondMove ; 
            p.display_the_card(p2) ; 
            cout << "Mayor..where do you want to move first? " ;
            cin >> firstMove ; 
            Location* currentLoc = mayor->GetCurrentLocation() ; 
            Location* firstMoveLoc = map.get_location_by_name(firstMove);
            if(currentLoc->findNeighbor(firstMove)) // اگر محلی که انتخاب شده همسایه بود
                mayor->MoveTo(firstMoveLoc) ;        
            else cerr << "what you have chosen is not a neighboring place!!\n" ;

            cout << "Mayor..what is your second place to move? " ;
            cin >> secondMove ;
            Location* secondMoveLoc = map.get_location_by_name(secondMove);
            if(currentLoc->findNeighbor(secondMove)) // اگر محلی که انتخاب شده همسایه بود
                mayor->MoveTo(secondMoveLoc) ;        
            else cerr << "what you have chosen is not a neighboring place!!\n" ; 

            cout << "--------------\n" ;
            string AfirstMove , AsecondMove ; 
            cout << "Archaeologist..where do you want to move first? " ;
            cin >> AfirstMove ; 
            Location* AcurrentLoc = archaeologist->GetCurrentLocation() ; 
            Location* AfirstMoveLoc = map.get_location_by_name(AfirstMove);
            if(AcurrentLoc->findNeighbor(AfirstMove)) // اگر محلی که انتخاب شده همسایه بود
                archaeologist->MoveTo(AfirstMoveLoc) ;        
            else cerr << "what you have chosen is not a neighboring place!!\n" ;

            cout << "Archaeologist..what is your second place to move? " ;
            cin >> AsecondMove ;
            Location* AsecondMoveLoc = map.get_location_by_name(AsecondMove);
            if(AcurrentLoc->findNeighbor(AsecondMove)) // اگر محلی که انتخاب شده همسایه بود
                archaeologist->MoveTo(AsecondMoveLoc) ;        
            else cerr << "what you have chosen is not a neighboring place!!\n" ;     
        }
        else if (p2.get_Event() == "Repel"){
            p.display_the_card(p2) ;
            //dracula->move_towards(2) ;
           //invisibleMan->move_towards(2) ; 
        }

        else if(p2.get_Event() == "Late into the Night"){

            p.display_the_card(p2) ;
            hero->SetRemainingActions(hero->GetRemainingActions() + 2) ;
            hero->DisplayInfo() ; 
        }
        else if(p2.get_Event() == "Break of Dawn."){
            //آیتم بصورت رندوم نمیاد!!!!
            //فاز هیولا بعدی رد میشود !؟
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
        else if(p2.get_Event() == "Overstock"){
            //آیتم بصورت رندوم نمیاد!!!!
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
}

bool Game::both_monsters_defeated() {
     return monstersMap[MonsterType::Dracula]->is_defeated() &&
            monstersMap[MonsterType::InvisibleMan]->is_defeated();
}



void Game::monster_phase() {

    if (deck.is_empty()) {
        std::cout << "\n Monster deck is empty. Players lose!\n";
        game_over = true;
        return;
    }


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
                            auto [hero, villager] = dracula->attack();
                            if (hero) {
                                std::cout << "Dracula attacks " << hero->GetName() << "!\n";
                                send_hero_to_hospital(hero);
                            }
                            
                            if (villager) {
                                std::cout << "Dracula destroys " << villager->get_name() << "!\n";
                                remove_villager(villager);
                            }
                        }
                    }
                    // مرد نامرئی
                    else if (type == MonsterType::InvisibleMan) {
                        if (face == DiceFace::Attack) {
                            m->attack();
                        }
                    }
                    if (monstersMap.count(MonsterType::InvisibleMan)) {
                                            Monster* invisibleMan = monstersMap[MonsterType::InvisibleMan];
                                            Location* target = invisibleMan->find_nearest_villager(invisibleMan->get_location());
                                            if (target) {
                                                invisibleMan->move_towards(2);
                                                std::cout << "Invisible Man sneaks closer to target!\n";
                                            }
                                        }
                }
            }
        }
    }

 }

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


void Game::locationOverview(){
    cout << "-----------------------Location Overview-----------------------------------\n"; 
    cout << left << "| " << setw(13) << "Location" << setw(20) << "Item" << setw(20) << "Monsters" << setw(20) << "Villagers" << "|\n" ;
    cout << right <<"----------------------------------------------------------------------------\n" ; 
 
    for(const auto& locPtr : map.get_locations()){
        Location* loc = locPtr.get() ; 

        string itemStr ; 
        const auto items = loc->get_items() ;
        if(items.empty())
            itemStr = "-" ; 
        else{
            std::map< std::string , int> itemcount ;
            for(const auto & item : items)
                itemcount[item.getName()]++ ;
            for(const auto& pair : itemcount)
                itemStr+= pair.first + "(" + to_string(pair.second) +"), " ;
            if(!itemStr.empty())
                itemStr.pop_back() , itemStr.pop_back() ;   
        }
        string monStr ;
        const auto monsters = loc->get_monsters() ;
        if(monsters.empty())
            monStr = "-" ; 
        else{
            for(const auto& m : monsters)
                monStr+= m->get_name() + ", " ;
            
            monStr.pop_back() ; monStr.pop_back() ;
        }

        string villagerStr;
        const auto& villagers = loc->get_villagers();
        if (villagers.empty()) 
            villagerStr = "-";
        else {
            for (const auto& v : villagers)
                villagerStr += v->get_name() + ", ";
            villagerStr.pop_back(); villagerStr.pop_back();
        }
        cout << left << "| " << setw(13) << loc->get_name()
             << setw(20) << itemStr << setw(20) << monStr << setw(20) << villagerStr << "|\n";
    }
    // نمایش تعداد تابوت های خراب شده +  آیتم های مرد نامرئی
  cout << "---------------------------------------------------------------------------\n" ;  
}


void Game::test() {
    
            Hero* activeHero = turnManager.get_active_hero();
        std::cout << "It's " << activeHero->GetName() << "'s turn!\n";
        


        if (terrorLevel >= 6 || deck.is_empty() || both_monsters_defeated()) {
            
            game_over;
        }
        turnManager.next_turn();
   
}

void Game::send_hero_to_hospital(Hero* h) {
    Location* hospital = map.get_location_by_name("Hospital");
    h->MoveTo(hospital);
}

void Game::remove_villager(villager* v) {
    v->set_currentLocation(nullptr); // فرض بر اینکه set_location(nullptr) یعنی حذف
}