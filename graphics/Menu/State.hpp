#ifndef STATE_H
#define STATE_H
#include <raylib.h>
#include <iostream>
#include "button.hpp"
#include "menu.hpp"

class Menu ;

class State{
    private:
        Texture2D background ; 

    public :
        State(const std::string&) ; 
        Texture2D get_background() const ; 
        virtual void displayState(Menu&) = 0 ; 
        virtual ~State() ; 
};

class StartState : public State {
    private:
        Button startButton ; 
        Button exitButton ; 
    public:
        StartState() ; 
        void displayState(Menu&) override ;  
};

class ExitState : public State{
    private:
        ClickableText YesText;
        ClickableText NoText;
        Sound goodbyeSound;
        bool soundPlayed = false;

    public:
        ExitState();
        void displayState(Menu&) override;
        ~ExitState();
} ; 


#endif