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
#include "GameRender.hpp"
class Menu ;
class GameRender ; 
class State{
    private:
        Texture2D background ; 

    public :
        State(const std::string&) ; 
        Texture2D get_background() const ; 
        virtual void render(Menu&) = 0 ;
        virtual ~State(); 
  
};

class MenuState : public State {
    private:
        std::unique_ptr<Button> startButton ; 
        std::unique_ptr<Button> exitButton ;
    public:
        MenuState() ; 
        void render(Menu&) override ;  
};

class ExitState : public State{
    private:
        std::unique_ptr<ClickableText> YesText ;
        std::unique_ptr<ClickableText> NoText ;
        // Sound goodbyeSound;
        // bool soundPlayed = false;

    public:
        ExitState();
        void render(Menu&) override;
}; 

class NameInputState : public State {
    private:
        
        std::unique_ptr<TextBox>nameBox1 ;std::unique_ptr<TextBox> nameBox2;
        std::unique_ptr<TextBox>timeBox1 ; std::unique_ptr<TextBox>timeBox2 ; 
        Rectangle continueButton;

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


class SetupState : public State {

    public:
        SetupState();
        void render(Menu& menu) override; // ClearBackground(DARKGRAY);DrawText("Setup Game...", 100, 100, 30, WHITE);
};

class HeroPhaseState : public State {
    private: 
        bool phase_done = false;
        std::unique_ptr<GameRender> renderer; ; 
    public:
        HeroPhaseState(Game&) ;
   //menu.SetState(std::make_unique<MonsterPhaseState>());

        void render(Menu& menu) override ;
};



class MonsterPhaseState : public State {
    private:
        bool phase_done = false;  
    public:
        MonsterPhaseState();
     // menu.SetState(std::make_unique<HeroPhaseState>());

        void render(Menu& menu) override ; // ClearBackground(RED);DrawText("Monster Phase", 100, 100, 30, WHITE);
    
};
#endif