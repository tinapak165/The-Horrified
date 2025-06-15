#include "Hero.hpp"
#include "Archaeologist.hpp"
#include "Mayor.hpp"
#include "villager.hpp"
#include <stdexcept>
#include <iostream>
using namespace std ; 
int main() {
    try{
        villager DrCranley("Dr.Cranley" , "Precint") ; 
        villager DrReed("Dr.Reed" , "Docks") ; //wrong safeplace (!fix!)
        villager ProfPearson("Prof.Pearson" , "Museum") ; 
        villager Maleva("Maleva" , "Docks"); //wrong safeplace (!fix!)
        villager Fritz("Fritz" , "Institute") ; 
        villager WillburChick("Willbur & Chick" , "Dungeon") ;
        villager Maria("Maria" , "Camp") ;
        
        Archaeologist h ; 
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

                    if(h.hasvillagerHere()){//چک شود که ایا محلی در مکان قهرمان فعلی هست یا نه

                        auto here = h.villagerHere() ; // vector of villagers in the same place
                        string villagertotake ;
                        cout << "some villagers are at the same place as you. " ; 
                        h.showvillagersHere() ; 
                        cout << "\ndo you want to move the villagers with you?(yes/no) " ; 
                        cin >> villagertotake ; 
                        if(villagertotake == "yes")
                            h.MoveTo(chosenPlace , here) ; 
                        else
                            h.MoveTo(chosenPlace) ; 
                    }else
                        h.MoveTo(chosenPlace) ; 
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
                            for(auto *v : villager::all()){
                                if(chosenVillager == v->get_name()){
                                    cout << "Which neighboring place do you want to move them? " ;
                                    cin >> chosenPlace ; 
                                    Maria.MoveTo(chosenPlace , chosenVillager) ; //calling a random villager
                                }
                                else
                                    throw invalid_argument("villager not found!") ; 

                            }
                        }else if(yesno == "no"){ //در اینجا از ویلیجرهای همسایه حرکت داده میشه به محل فعلی قهرمان
                            cout << "some villagers in the neigbors are: " ; 

                        }
                    }
                }
            } 
        }    
    }catch(exception& e){
        cout << e.what() ; 
    }
}