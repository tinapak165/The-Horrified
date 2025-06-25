#include "Hero.hpp"
#include "Archaeologist.hpp"
#include "GameMap.hpp"
#include "Mayor.hpp"
#include "villager.hpp"
#include "perkcardsDeck.hpp"
#include "location.hpp"
#include "monster.hpp"
#include "Dracula.hpp"
#include "Itembag.hpp"
#include <stdexcept>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std ; 

class Hero ; 
class Villager ; 
class GameMap ; 
class Monster ;
class Dracula ;
class ItemPool ;

int main(){
    GameMap map ; 
    map.build_map() ;

    // villager DrCranley("Dr.Cranley" , map.get_location_by_name("Precinct")) ;  
    // villager DrReed("Dr.Reed" , map.get_location_by_name("Camp")) ;
    // villager ProfPearson("Prof.Pearson" , map.get_location_by_name("Museum")) ; 
    // villager Maleva("Maleva" , map.get_location_by_name("Shop"));
    // villager Fritz("Fritz" , map.get_location_by_name("Institute")) ; 
    // villager WillburChick("Willbur & Chick" , map.get_location_by_name("Dungeon")) ;
    // villager Maria("Maria" , map.get_location_by_name("Camp")) ;

    //Maria.MoveTo(map.find_location_by_name("Camp") , "Maria") ; moving to its safeplace for checking

    Monster* dracula = new Dracula(map.get_location_by_name("Cave"));

    Mayor m(map) ; 
    m.DisplayInfo() ;
    cout << endl ; 

    Archaeologist a(map) ;

    PerkDeck p ; 
    Perkcards p2 ; 
    //if on the hero's turn villager moved to its safeplace, play perkcard
   // if(villager::AnyVillagerInSafePlace()){ //place it baaaaaack
        p2 = p.get_random_card() ;
        cout << p2 << endl;
        if(p2.get_Event() == "Hurry."){
            string firstMove , secondMove ; 
            p.display_the_card(p2) ; 
            cout << "Mayor..where do you want to move first? " ;
            cin >> firstMove ; 
            Location* currentLoc = m.GetCurrentLocation() ; 
            Location* firstMoveLoc = map.get_location_by_name(firstMove);
            if(currentLoc->findNeighbor(firstMove)) // اگر محلی که انتخاب شده همسایه بود
                m.MoveTo(firstMoveLoc) ;        
            else cerr << "what you have chosen is not a neighboring place!!\n" ;

            cout << "Mayor..what is your second place to move? " ;
            cin >> secondMove ;
            Location* secondMoveLoc = map.get_location_by_name(secondMove);
            if(currentLoc->findNeighbor(secondMove)) // اگر محلی که انتخاب شده همسایه بود
                m.MoveTo(secondMoveLoc) ;        
            else cerr << "what you have chosen is not a neighboring place!!\n" ; 

            cout << "--------------\n" ;
            string AfirstMove , AsecondMove ; 
            cout << "Archaeologist..where do you want to move first? " ;
            cin >> AfirstMove ; 
            Location* AcurrentLoc = a.GetCurrentLocation() ; 
            Location* AfirstMoveLoc = map.get_location_by_name(AfirstMove);
            if(AcurrentLoc->findNeighbor(AfirstMove)) // اگر محلی که انتخاب شده همسایه بود
                a.MoveTo(AfirstMoveLoc) ;        
            else cerr << "what you have chosen is not a neighboring place!!\n" ;

            cout << "Archaeologist..what is your second place to move? " ;
            cin >> AsecondMove ;
            Location* AsecondMoveLoc = map.get_location_by_name(AsecondMove);
            if(AcurrentLoc->findNeighbor(AsecondMove)) // اگر محلی که انتخاب شده همسایه بود
                a.MoveTo(AsecondMoveLoc) ;        
            else cerr << "what you have chosen is not a neighboring place!!\n" ;     
        }
        else if (p2.get_Event() == "Repel."){
            p.display_the_card(p2) ;
            dracula->move_towards(2) ;
           //invisibleMan->move_towards(2) !!!!!!!!
        }

        else if(p2.get_Event() == "Late into the Night."){
            //فرض کنیم بازیکنی که نوبتشه شهردار هست (!fix!)
            p.display_the_card(p2) ;
            m.SetRemainingActions(m.GetRemainingActions() + 2) ;
            m.DisplayInfo() ; 
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
        else if(p2.get_Event() == "Overstock."){
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
    //}
    
}