#ifndef STATE_H
#define STATE_H
#include <raylib.h>
#include <iostream>
#include <vector>
#include <memory>
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
        // Sound goodbyeSound;
        // bool soundPlayed = false;

    public:
        ExitState();
        void playState(Menu&) override;
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

class ChooseCharacterState : public State{
    private:
        std::string player1Name;
        std::string player1GarlicTime;
        std::string player2Name;
        std::string player2GarlicTime;

        std::string player1Hero;
        std::string player2Hero;

        bool player1First;
        std::string* currentPlayer;
        
        std::vector<std::unique_ptr<Button>> heroButtons;
        std::vector<bool> availableHeroes = {true, true, true, true};
        const std::vector<std::string> heroNames = {"mayor", "archaeologist", "courier", "scientist"};
        
        ClickableText instructionText; 
    public:
        ChooseCharacterState(const std::string& p1Name, const std::string& p1GarlicTime, const std::string& p2Name, const std::string& p2GarlicTime);
        void playState(Menu&) override;
};

#endif