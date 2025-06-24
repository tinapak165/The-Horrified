#include "Game.hpp"
#include <iostream>
using namespace std ; 
Game::Game() {
    // ساخت نقشه ثابت
    map.build_map();
   
    Hero* mayor = new Mayor(map);
    Hero* archaeologist = new Archaeologist(map);

    turnManager =  TurnManager(archaeologist , mayor) ;

        new villager("Dr.Cranley" , map.get_location_by_name("Precinct") , nullptr) ;  //null میذاریم چون فعلا در لوکیشنی قرار نگرفته اند 
        new villager("Dr.Reed" , map.get_location_by_name("Camp") , map.get_location_by_name("Docks")) ;  //for testing
        new villager("Prof.Pearson" , map.get_location_by_name("Museum") , nullptr) ; 
        new villager("Maleva" , map.get_location_by_name("Shop") , nullptr); 
        new villager("Fritz" , map.get_location_by_name("Institute"), nullptr) ; 
        new villager("Willbur & Chick" , map.get_location_by_name("Dungeon") , nullptr) ;
        new villager("Maria" , map.get_location_by_name("Camp") , nullptr) ;
 

    //  اضافه کردن هیولاها
    Monster* dracula = new Dracula(map.get_location_by_name("Cave")); 
    // InvisibleMan* invisibleMan = new InvisibleMan(map.get_lo("Barn"));
    monstersMap[MonsterType::Dracula] = dracula;
    // monstersMap[MonsterType::InvisibleMan] = invisibleMan;
}

void  Game::start() {
   while (true) {
        // ۱. فاز قهرمان
        Hero* activeHero = turnManager.get_active_hero();
        cout << ">>> Before action: " << activeHero->GetName() << "\n";
        hero_phase(activeHero);

        // بعد از فاز هیولا، نوبت رو عوض می‌کنیم
        turnManager.next_turn();

        // بلافاصله چک و چاپ می‌کنیم
        Hero* next = turnManager.get_active_hero();
        cout << ">>> Next turn will be: " << next->GetName() << "\n\n";
        

   } //end while

        // cout << "It's " << activeHero->GetName() << "'s turn!\n";
        // hero_phase(activeHero);
/*
        // ۲. فاز هیولا
        
        monster_phase();

        // ۳. بررسی پایان بازی
        if (terrorLevel >= 6) {
            cout << "Game Over! Terror level reached 6.\n";
            break;
        }
        if (deck.is_empty()) {
            cout << "Game Over! No more Monster Cards.\n";
            break;
        }
        if (both_monsters_defeated()) {
            cout << "You win! Both monsters defeated!\n";
            break;
        }

        // ۴. رفتن به نوبت قهرمان بعدی
        turnManager.next_turn();

    }
*/

}

void Game::hero_phase(Hero* h) {

    h->DisplayInfo() ;
    playAction(h) ;
    // !ری ست کردن تعداد اکشن ها بعد از هر فاز!

}

void Game::playAction(Hero *h){
    while(true){
    string chosenAction ; 
    cout << "what action do you want to play this turn(type help to display actions , end to not do any actions on this phase) ? " ;
    cin >> chosenAction ; 
    if(chosenAction == "help")
        h->DisplayActions() ;
    if(chosenAction == "end")
        break ;
        
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
                        string villagertotake ;
                        cout << "some villagers are at the same place as you. " ; 
                        h->showvillagersHere() ; 
                        cout << "\ndo you want to move the villagers with you?(yes = moving all villagers with you/no = moving alone) " ; 
                        cin >> villagertotake ; 
                        if(villagertotake == "yes")
                            h->MoveTo(chosenLocation , here) ; 
                        else
                            h->MoveTo(chosenLocation) ; 
                    }else
                        h->MoveTo(chosenLocation) ;    
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

                    // بعدا پاک شود !!
                    Item item1("Garlic", ItemColor::RED, 2, "Barn") ; //فرضی
                    Item item2("Stake", ItemColor::BLUE, 1, "Barn") ; //فرضی
                    Item item3("chert" , ItemColor::RED , 6 , "sss") ;
                    Location* heroLoc = h->GetCurrentLocation() ;
                    heroLoc->add_item(item1) ; heroLoc->add_item(item2) ; heroLoc->add_item(item3); //بهتره از قبل ست شده باشن + فرضی توی لوکیشن هیرو قرار دارن
                    // بعدا پاک شود !!
                    
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

                        // بعدا پاک شود !!
                        Item item1("Garlic", ItemColor::RED, 2, "Camp") ; //فرضی
                        Item item2("Stake", ItemColor::BLUE, 1, "Barn") ; //فرضی
                        chosenLoc->add_item(item1) ; chosenLoc->add_item(item2) ; //اشتباهه
                        //map.get_location_by_name("Camp")->add_item(item1) ; 
                        // بعدا پاک شود !!
                    
                        h->SpecialPickup(chosenLoc) ;
                        h->DisplayItem() ; 

                    }else throw invalid_argument("what you have chosen is not a neighboring place!\n") ;
  
                }
                else if(chosenAction == "Advance"){ //for the monster missions
                    //for dracula
                    if( h->GetCurrentLocation() == map.get_location_by_name("Docks") || //درستش کن به Graveyard
                        h->GetCurrentLocation() == map.get_location_by_name("Crypt") ||
                        h->GetCurrentLocation() == map.get_location_by_name("Dungeon") ||
                        h->GetCurrentLocation() == map.get_location_by_name("Cave") ){// اگر قهرمان در محل قرار گیری تابوتهای دراکولا بود
                        //چک شود تابوتی در آن مکان هست یا نه
                        cout << "for using advance action you need to have items with red color and strength >= 6.\n" ;
                        h->AdvanceActionForDracula() ;
                    }
                    //for invisible man
                    else if(h->GetCurrentLocation() == map.get_location_by_name("Docks") || // درستش کن به Inn
                        h->GetCurrentLocation() == map.get_location_by_name("Barn") ||
                        h->GetCurrentLocation() == map.get_location_by_name("Institute") ||
                        h->GetCurrentLocation() == map.get_location_by_name("Laboratory") ||
                        h->GetCurrentLocation() == map.get_location_by_name("Mansion") ) {}


                    else cerr << "you can not do advance action unless you are in coffin places\n" ; 
                
                }
                else if(chosenAction == "Defeat"){
                    // اگر در همه لوکبشن های تابوت Advance بکار برده شد == 
                    //امکان شکست هیولا 
                    //از تابع can be defeated دراکولا استفاده شود
                    //1-اگر قهرمان در لوکیشنی که دراکولا قرار دارد قرار داشت
                    //2- استفاده از آیتم های زرد برای نابودی


                }
            } // end if can play an action 


    }    
}

/* //delete from here
bool Game::both_monsters_defeated() {
     return monstersMap[MonsterType::Dracula]->is_defeated() &&
            monstersMap[MonsterType::InvisibleMan]->is_defeated();
}



void Game::monster_phase() {

    if (deck.is_empty()) {
        std::cout << "\n Monster deck is empty. Players lose!\n";
      //  game_over = true;
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
                            m->attack();
                        }
                    }
                    // مرد نامرئی
                    else if (type == MonsterType::InvisibleMan) {
                        if (face == DiceFace::Attack) {
                            m->attack();
                        }
                    }
                }
            }
        }
    }
}

}
void Game::distribute_initial_items() {
    ItemPool pool;
    auto items = pool.draw_random_items(12);
    
    for (const auto& item : items) {
        Location* loc = map.get_location_by_name(item.getLocationName());
        if (loc) {
            loc->add_item(item);
            std::cout << "Placed " << item.getName() << " at " << item.getLocationName() << "\n";
        }
    }
}




// void Game::start() {
//     while (true) {
    //         Hero* activeHero = turnManager.get_active_hero();
//         std::cout << "It's " << activeHero->GetName() << "'s turn!\n";
//         run_hero_turn(activeHero);

//         monster_phase();

//         if (terrorLevel >= 6 || deck.is_empty() || both_monsters_defeated()) {
//             end_game();
//             break;
//         }
//         turnManager.next_turn();
//     }
// }

*/ //delete here