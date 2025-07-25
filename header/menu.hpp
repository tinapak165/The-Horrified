#ifndef MENU_H
#define MENU_H
#include "State.hpp"
#include "Game.hpp"
class State ; 

class Menu{
    private : 
        Game& game ; 
        std::unique_ptr<State> current_state ; 
    public:
        Menu(Game&) ; 
        void SetState(std::unique_ptr<State>) ; 
        void renderCurrentState(); 
        State* getState(); 
        void startGame(const PlayerSelection&, const PlayerSelection&) ;
};

#endif