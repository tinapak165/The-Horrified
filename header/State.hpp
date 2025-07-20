#ifndef STATE_H
#define STATE_H

#include <raylib.h>
#include <iostream>
#include <vector>
#include <memory>

struct PlayerSelection {
    std::string name;
    std::string heroType;
    std::string garlicTime;
};

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
        virtual ~State(); 
  
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

    public:
        NameInputState();
        void playState(Menu&) override;
};

class ChooseCharacterState : public State{
    private:
        PlayerSelection player1 ; 
        PlayerSelection player2 ; 

        bool player1First;
        std::string* currentPlayer;
        std::vector<bool> selectedHeroes; 

        std::vector<std::unique_ptr<Button>> heroButtons;
        const std::vector<std::string> heroNames = {"mayor", "archaeologist", "courier", "scientist"};
        
        ClickableText instructionText; 
        std::string selectedMessage; 
    public:

        ChooseCharacterState(const PlayerSelection& p1, const PlayerSelection& p2);
        void playState(Menu&) override;
};

#endif