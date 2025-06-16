#include "Hero.hpp"
#include "Archaeologist.hpp"
#include "GameMap.hpp"
#include "Mayor.hpp"
#include "villager.hpp"
#include <stdexcept>
#include <iostream>
using namespace std ; 

class Hero ; 
class Villager ; 
class GameMap ; 

int main() {
    try{
        GameMap map ; 
        map.build_map() ;
        
        villager DrCranley("Dr.Cranley" , map.find_location_by_name("Precint")) ;  
        villager DrReed("Dr.Reed" , map.find_location_by_name("Docks")) ; //wrong safeplace (!fix!)
        villager ProfPearson("Prof.Pearson" , map.find_location_by_name("Museum")) ; 
        villager Maleva("Maleva" , map.find_location_by_name("Docks")); //wrong safeplace (!fix!)
        villager Fritz("Fritz" , map.find_location_by_name("Institute")) ; 
        villager WillburChick("Willbur & Chick" , map.find_location_by_name("Dungeon")) ;
        villager Maria("Maria" , map.find_location_by_name("Camp")) ;

        Archaeologist h(map) ; 
        h.DisplayInfo() ; 
        h.DisplayActions() ;

        while (true){
            string chosenAction ; 
            cout << "\nwhat action do you want to play this turn ? " ;
            cin >> chosenAction ; 
            if(h.PerformTheAction(chosenAction)){
                cout << "actions left: " << h.GetRemainingActions() << "/4\n" ;
                if(chosenAction == "Move"){
                    string chosenPlace ; 
                    cout << "Which neighboring place do you want to move to? " ;
                    cin >> chosenPlace ;
                    Location* chosenLocation = map.find_location_by_name(chosenPlace) ;  

                    if(h.hasvillagerHere()){//چک شود که ایا محلی در مکان قهرمان فعلی هست یا نه

                        auto here = h.villagerHere() ; // vector of villagers in the same place
                        string villagertotake ;
                        cout << "some villagers are at the same place as you. " ; 
                        h.showvillagersHere() ; 
                        cout << "\ndo you want to move the villagers with you?(yes/no) " ; 
                        cin >> villagertotake ; 
                        if(villagertotake == "yes")
                            h.MoveTo(chosenLocation , here) ; 
                        else
                            h.MoveTo(chosenLocation) ; 
                    }else
                        h.MoveTo(chosenLocation) ; 
                }
                else if(chosenAction == "Guide"){
                    string chosenPlace , yesno , chosenVillager ; 
                    if(h.hasvillagerHere()){ // حرکت دادن یک محلی که در خانه قهرمان قرار دارد به خانه همسایه
                        cout << "some villagers are at the same place as you: " ; 
                        h.showvillagersHere() ; 
                        cout << "\ndo you want to move this villagers?(yes/no) " ;
                        cin >> yesno ; 
                        if(yesno == "yes"){
                            cout << "who you want to move? " ; 
                            cin >> chosenVillager ; 
                            bool found = false ; 
                            for(auto *v : villager::all()){
                                if(chosenVillager == v->get_name()){
                                    cout << "Which neighboring place do you want to move them? " ;
                                    cin >> chosenPlace ; 
                                    Location* chosenLocation = map.find_location_by_name(chosenPlace) ;  
                                    v->MoveTo(chosenLocation , chosenVillager) ;
                                    found = true ; 
                                    break ; 
                                }
                            }
                            if(!found) throw invalid_argument("villager not found!") ; 

                        }else if(yesno == "no"){ //در اینجا از ویلیجرهای همسایه حرکت داده میشه به محل فعلی قهرمان
                            cout << "some villagers in the neigbors are: " ; 

                        }
                        else{
                            cerr << "wrong answer!!\n" ; 
                        }
                    }
                }
            } 
        }    
    }catch(exception& e){
        cout << e.what() ; 
    }
}