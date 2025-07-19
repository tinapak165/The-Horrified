#ifndef MENU_H
#define MENU_H
#include "State.hpp"

class State ; 

class Menu{
    private : 
        std::unique_ptr<State> current_state ; 
    public:
        Menu() ; 
        void SetState(std::unique_ptr<State>) ; 
        void renderCurrentState(); 
};


#endif