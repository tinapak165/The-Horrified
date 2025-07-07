#include "Game.hpp"
#include <stdexcept>

int main(){
    try{
        Game Horrified ;
        Horrified.start() ;
    }
    catch(std::exception & e){
        std::cout << e.what() ; 
    }
}