#include "Hero.hpp"
#include "Archaeologist.hpp"
#include "GameMap.hpp"
#include "Mayor.hpp"
#include "villager.hpp"
#include <stdexcept>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std ; 

class Hero ; 
class Villager ; 
class GameMap ; 

int main() {
    try{
        GameMap map ; 
        map.build_map() ;
        
        villager DrCranley("Dr.Cranley" , map.get_location_by_name("Precinct")) ;  
        villager DrReed("Dr.Reed" , map.get_location_by_name("Docks")) ; //wrong safeplace (!fix!)
        villager ProfPearson("Prof.Pearson" , map.get_location_by_name("Museum")) ; 
        villager Maleva("Maleva" , map.get_location_by_name("Docks")); //wrong safeplace (!fix!)
        villager Fritz("Fritz" , map.get_location_by_name("Institute")) ; 
        villager WillburChick("Willbur & Chick" , map.get_location_by_name("Dungeon")) ;
        villager Maria("Maria" , map.get_location_by_name("Camp")) ;

        Archaeologist h(map) ; 
        h.DisplayInfo() ; 
        h.DisplayActions() ;

        while (true){
            string chosenAction ; 
            cout << "what action do you want to play this turn ? " ;
            cin >> chosenAction ; 
            if(h.PerformTheAction(chosenAction)){
                cout << "actions left: " << h.GetRemainingActions() << "/4\n" ;
                if(chosenAction == "Move"){
                    string chosenPlace ; 
                    cout << "Which neighboring place do you want to move to? " ;
                    cin >> chosenPlace ;
                    Location* currentLoc = h.GetCurrentLocation() ; 
                    Location* chosenLocation = map.get_location_by_name(chosenPlace);

                    if(currentLoc->findNeighbor(chosenPlace)){ //اگر خونه ای که انتخاب کرده واقعا همسایه فعلی بود
                        if(h.hasvillagerHere()){//چک شود که ایا محلی در مکان قهرمان فعلی هست یا نه
                        auto here = h.villagerHere() ; // vector of villagers in the same place
                        string villagertotake ;
                        cout << "some villagers are at the same place as you. " ; 
                        h.showvillagersHere() ; 
                        cout << "\ndo you want to move the villagers with you?(yes = moving all villagers with you/no = moving alone) " ; 
                        cin >> villagertotake ; 
                        if(villagertotake == "yes")
                            h.MoveTo(chosenLocation , here) ; 
                        else
                            h.MoveTo(chosenLocation) ; 
                    }else
                        h.MoveTo(chosenLocation) ;    
                    }
                    else
                        cerr << "what you have chosen is not a neighboring place!\n";
                    
                }
                else if(chosenAction == "Guide"){
                    string chosenPlace , mode ; 
                    Location* currentLoc = h.GetCurrentLocation() ; 
                    cout << "Guide:\n" 
                         << "current -> move a villager from your location to a neighbor\n"
                         << "neighbor -> move a villager from a neighbor to your location\n"
                         << "choose: ";
                    
                    cin >> mode ; 

                    if(mode == "current"){
                        if(h.hasvillagerHere()){
                            cout << "some villagers are at the same place as you: " ;
                            h.showvillagersHere() ;
                            cout << "\nwho do you want to move? " ; 
                            string chosenvillager ;
                            cin >> chosenvillager ;  
                            bool found = false ; 
                            for(auto *v : h.villagerHere()){
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
                        Location* currentLoc = h.GetCurrentLocation() ;
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
                    Location* heroLoc = h.GetCurrentLocation() ;
                    heroLoc->add_item(item1) ; heroLoc->add_item(item2) ; heroLoc->add_item(item3); //بهتره از قبل ست شده باشن + فرضی توی لوکیشن هیرو قرار دارن
                    // بعدا پاک شود !!
                    
                    h.PickupItems() ;
                    h.DisplayItem() ; 
                } 
                else if(chosenAction == "Special"){
                    Location* heroLoc = h.GetCurrentLocation() ; 
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
                    
                        h.SpecialPickup(chosenLoc) ;
                        h.DisplayItem() ; 

                    }else throw invalid_argument("what you have chosen is not a neighboring place!\n") ;
  
                }
                else if(chosenAction == "Advance"){ //for the monster missions
                    //for dracula
                    if( h.GetCurrentLocation() == map.get_location_by_name("Docks") || //درستش کن به Graveyard
                        h.GetCurrentLocation() == map.get_location_by_name("Crypt") ||
                        h.GetCurrentLocation() == map.get_location_by_name("Dungeon") ||
                        h.GetCurrentLocation() == map.get_location_by_name("Cave") ){// اگر قهرمان در محل قرار گیری تابوتهای دراکولا بود
                        //چک شود تابوتی در آن مکان هست یا نه
                        cout << "for using advance action you need to have items with red color and strength >= 6.\n" ;
                        h.AdvanceActionForDracula() ;
                    }
                    //for invisible man
                    else if(h.GetCurrentLocation() == map.get_location_by_name("Docks") || // درستش کن به Inn
                        h.GetCurrentLocation() == map.get_location_by_name("Barn") ||
                        h.GetCurrentLocation() == map.get_location_by_name("Institute") ||
                        h.GetCurrentLocation() == map.get_location_by_name("Laboratory") ||
                        h.GetCurrentLocation() == map.get_location_by_name("Mansion") ) {}


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
        } //end while
    }//end try
    catch(exception& e){
        cout << e.what() ; 
    }

} //end main
    