#include "villager.hpp"
#include <iostream>
#include <stdexcept>
using namespace std ; 

int main(){
    try{
        villager v ; 
        villager DrCranley("Dr.Cranley" , "Precint") ; 
        villager DrReed("Dr.Reed" , "Camp") ; 
        villager ProfPearson("Prof.Pearson" , "Museum") ; 
        villager Maleva("Maleva" , "Shop"); 
        villager Fritz("Fritz" , "Institute") ; 
        villager WillburChick("Willbur & Chick" , "Dungeon") ;
        villager Maria("Maria" , "Camp") ;
        Maria.MoveTo("Cave" , "Maria") ; 

        if(Maria.in_the_safePlace())
            cout << "\nyes\n" ;
        else
            cout << "\nno\n" ; 

        }
        catch(exception &e){
            cout << e.what() ; 
        }

}