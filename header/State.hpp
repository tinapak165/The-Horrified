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
        virtual void playState(Menu&) = 0 ; 
        virtual ~State() ; 
};

class MenuState : public State {
    private:
        Button startButton ; 
        Button exitButton ; 
    public:
        MenuState() ; 
        void playState(Menu&) override ;  
};

class ExitState : public State{
    private:
        ClickableText YesText;
        ClickableText NoText;
        Sound goodbyeSound;
        bool soundPlayed = false;

    public:
        ExitState();
        void playState(Menu&) override;
        ~ExitState();
}; 

class NameInputState : public State {
    private:
        TextBox nameBox1, nameBox2;
        TextBox timeBox1, timeBox2;
        Rectangle continueButton;

        std::string name1, name2;
        std::string garlicTime1, garlicTime2;

    public:
        NameInputState();
        void playState(Menu&) override;
};

#endif