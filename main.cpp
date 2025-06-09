#include "Hero.hpp"
#include "Archaeologist.hpp"
#include "Mayor.hpp"
#include <stdexcept>
int main(){
    try{
        Archaeologist h ; 
        h.DisplayInfo() ; 
        h.DisplayActions() ;
        while (true)
        {
            std::string chosenAction ; 
            std::cout << "\nwhat action do you want to play this turn ? " ;
            std::cin >> chosenAction ; 
            h.PerformTheAction(chosenAction) ; 
            std::cout << h.GetRemainingActions() ; 
        }
         
    }catch(std::exception& e){
        std::cout << e.what() ; 
    }
}