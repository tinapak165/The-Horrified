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

#include "Tools.hpp"
#include "Menu.hpp"
class Menu ;

class State{
    private:
        Texture2D background ; 
        Font font;
    public :
        State(const std::string&) ; 
        Texture2D get_background() const ; 
        Font get_Font() const ;
        virtual void render(Menu&) = 0 ;
        virtual ~State(); 
};

class MenuState : public State {
    private:
        std::unique_ptr<Button> startButton ; 
        std::unique_ptr<Button> exitButton ;
        std::unique_ptr<Button> continueButton;
    public:
        MenuState() ; 
        void render(Menu&) override ;  
};

class ExitState : public State{
    private:
        std::unique_ptr<ClickableText> YesText ;
        std::unique_ptr<ClickableText> NoText ;

    public:
        ExitState();
        void render(Menu&) override;
}; 

class NameInputState : public State {
    private:
        std::unique_ptr<TextBox>nameBox1 ;std::unique_ptr<TextBox> nameBox2;
        std::unique_ptr<TextBox>timeBox1 ; std::unique_ptr<TextBox>timeBox2 ; 
        Rectangle continueButton;
        Font font;

    public:
        NameInputState();
        void render(Menu&) override;
};

class ChooseCharacterState : public State{
    private:
        PlayerSelection player1 ; 
        PlayerSelection player2 ; 
        bool readyToStart = false;
        double selectionTime = 0.0;


        bool player1First;
        enum class PlayerTurn {PLAYER1 , PLAYER2} ;
        PlayerTurn currentTurn ; 
        std::vector<bool> selectedHeroes; 

        std::vector<std::unique_ptr<Button>> heroButtons;
        const std::vector<std::string> heroNames = {"mayor", "archaeologist", "courier", "scientist"};
        
        ClickableText instructionText; 
        std::string selectedMessage; 

    public:

        ChooseCharacterState(const PlayerSelection&, const PlayerSelection&);
        void render(Menu&) override;
};

class ContinueState : public State{
    private:
        std::vector<ClickableText> fileButtons;
        bool fileselected = false ;
        std::string selectedFile ;
    public:
        ContinueState() ;
        void render(Menu&) override;

};

#endif