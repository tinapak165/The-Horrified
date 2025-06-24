#include "Game.hpp"
#include <stdexcept>

int main(){
    try{
        Game game ;
        game.start() ;
    }
    catch(std::exception & e){
        std::cout << e.what() ; 
    }
}