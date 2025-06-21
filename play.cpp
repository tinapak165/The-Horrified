#include "Hero.hpp"
#include "Archaeologist.hpp"
#include "GameMap.hpp"
#include "Mayor.hpp"
#include "villager.hpp"
#include "perkcardsDeck.hpp"
#include "location.hpp"
#include <stdexcept>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std ; 

class Hero ; 
class Villager ; 
class GameMap ; 

int main(){
    GameMap map ; 
    map.build_map() ;

    villager DrCranley("Dr.Cranley" , map.find_location_by_name("Precinct")) ;  
    villager DrReed("Dr.Reed" , map.find_location_by_name("Camp")) ;
    villager ProfPearson("Prof.Pearson" , map.find_location_by_name("Museum")) ; 
    villager Maleva("Maleva" , map.find_location_by_name("Shop"));
    villager Fritz("Fritz" , map.find_location_by_name("Institute")) ; 
    villager WillburChick("Willbur & Chick" , map.find_location_by_name("Dungeon")) ;
    villager Maria("Maria" , map.find_location_by_name("Camp")) ;

    //Maria.MoveTo(map.find_location_by_name("Camp") , "Maria") ; moving to its safeplace for checking

    Mayor m(map) ; 
    m.DisplayInfo() ;
    cout << endl ; 

    Archaeologist a(map) ;

    PerkDeck p ; 
    Perkcards p2 ; 
    //if on the hero's turn villager moved to its safeplace, play perkcard
    if(villager::AnyVillagerInSafePlace()){
        p2 = p.get_random_card() ;
        cout << p2 << endl;
        if(p2.get_Event() == "Hurry."){
            string firstMove , secondMove ; 
            p.display_the_card(p2) ; 
            cout << "Mayor..where do you want to move first? " ;
            cin >> firstMove ; 
            Location* currentLoc = m.GetCurrentLocation() ; 
            Location* firstMoveLoc = map.find_location_by_name(firstMove);
            if(auto* dest = currentLoc->findNeighbor(firstMove)) // اگر محلی که انتخاب شده همسایه بود
                m.MoveTo(firstMoveLoc) ;        
            else cerr << "what you have chosen is not a neighboring place!!\n" ;

            cout << "Mayor..what is your second place to move? " ;
            cin >> secondMove ;
            Location* secondMoveLoc = map.find_location_by_name(secondMove);
            if(auto* dest = currentLoc->findNeighbor(secondMove)) // اگر محلی که انتخاب شده همسایه بود
                m.MoveTo(secondMoveLoc) ;        
            else cerr << "what you have chosen is not a neighboring place!!\n" ; 

            cout << "--------------\n" ;
            string AfirstMove , AsecondMove ; 
            cout << "Archaeologist..where do you want to move first? " ;
            cin >> AfirstMove ; 
            Location* AcurrentLoc = a.GetCurrentLocation() ; 
            Location* AfirstMoveLoc = map.find_location_by_name(AfirstMove);
            if(auto* dest = AcurrentLoc->findNeighbor(AfirstMove)) // اگر محلی که انتخاب شده همسایه بود
                a.MoveTo(AfirstMoveLoc) ;        
            else cerr << "what you have chosen is not a neighboring place!!\n" ;

            cout << "Archaeologist..what is your second place to move? " ;
            cin >> AsecondMove ;
            Location* AsecondMoveLoc = map.find_location_by_name(AsecondMove);
            if(auto* dest = AcurrentLoc->findNeighbor(AsecondMove)) // اگر محلی که انتخاب شده همسایه بود
                a.MoveTo(AsecondMoveLoc) ;        
            else cerr << "what you have chosen is not a neighboring place!!\n" ;     
        }
        else if (p2.get_Event() == "Repel."){}

        else if(p2.get_Event() == "Late into the Night."){
            //فرض کنیم بازیکنی که نوبتشه شهردار هست (!fix!)
            p.display_the_card(p2) ;
            m.SetRemainingActions(m.GetRemainingActions() + 2) ;
            m.DisplayInfo() ; 
        }
    }
    
}