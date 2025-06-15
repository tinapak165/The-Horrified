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
        villager DrReed("Dr.Reed" , "Docks") ; 
        villager ProfPearson("Prof.Pearson" , "Museum") ; 
        villager Maleva("Maleva" , "Docks"); 
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
                    //چک شود که ایا محلی در مکان قهرمان فعلی هست یا نه
                    cout << "Which neighboring place do you want to move to? " ;
                    cin >> chosenPlace ; 

                    if(h.hasvillagerHere()){
                        auto here = h.villagerHere() ;
                        string villagertotake ;
                        cout << "some villagers are at the same place as you. " ; 
                        h.showvillagersHere() ; 
                        cout << "\ndo you want to move the villagers with you?(yes/no) " ; 
                        cin >> villagertotake ; 
                        if(villagertotake == "yes")
                            h.MoveTo(chosenPlace , here) ; 
                        else{
                            h.MoveTo(chosenPlace) ; 
                        }
                    }else
                        h.MoveTo(chosenPlace) ; 
                    

                } 
            } 
        }
         
    }catch(exception& e){
        cout << e.what() ; 
    }
}