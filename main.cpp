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
            cout << "what action do you want to play this turn ? " ;
            cin >> chosenAction ; 
            if(h.PerformTheAction(chosenAction)){
                cout << "actions left: " << h.GetRemainingActions() << "/4\n" ;
                if(chosenAction == "Move"){
                    string chosenPlace ; 
                    cout << "Which neighboring place do you want to move to? " ;
                    cin >> chosenPlace ;
                    Location* currentLoc = h.GetCurrentLocation() ; 
                    Location* chosenLocation = map.find_location_by_name(chosenPlace);

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

                                        Location* chosenLocation = map.find_location_by_name(chosenPlace) ;  
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
                //else if(){} //another action 
            } // end if can play an action    
        } //end while
    }//end try
    catch(exception& e){
        cout << e.what() ; 
    }

} //end main
    