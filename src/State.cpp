#include "State.hpp"
#include "menu.hpp"
#include <iostream>

State::State(const std::string& bgPath) {
    background = LoadTexture(bgPath.c_str());
}

State::~State(){
    UnloadTexture(background) ;
}


Texture2D State::get_background() const{
    return background;
}

StartState::StartState() 
    : State("../Assets/Menu/Background.png"), 
      startButton("../Assets/Menu/Startgame.png", {170, 300}),
      exitButton("../Assets/Menu/Exit.png", {170, 500}){}

void StartState::displayState(Menu& menu)  {
        DrawTexture(get_background(), 0, 0, WHITE);

        Vector2 mouse = GetMousePosition();
        bool click = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

        startButton.Draw(mouse);
        exitButton.Draw(mouse);

        if (startButton.isPressed(mouse, click)) {
            std::cout << "Start clicked\n";
  //          menu.SetState(new NameInputState()); // یا هر State دیگه که ساختی
        }

        if (exitButton.isPressed(mouse, click)) {
            std::cout << "Exit clicked\n";
            menu.SetState(new ExitState) ; 
        }
    }

ExitState::ExitState() 
    : State("../Assets/Menu/Background.png"),
      YesText("Yes", {280, 400}, 30, DARKGRAY),
      NoText("No", {480, 400}, 30, DARKGRAY),
      soundPlayed(false) {
    goodbyeSound = LoadSound("Assets/goodbye.wav");
}

void ExitState::displayState(Menu& menu) {
    DrawTexture(get_background(), 0, 0, WHITE);

    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.6f));
    DrawText("Are you sure you want to exit?", 200, 200, 30, WHITE);

    Vector2 mouse = GetMousePosition();
    bool click = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

    YesText.Draw(mouse);
    NoText.Draw(mouse);

    if (YesText.isClicked(mouse, click)) {
        if (!soundPlayed) {
            PlaySound(goodbyeSound);
            soundPlayed = true;
        }
        WaitTime(0.5);
        CloseWindow();
    }

    if (NoText.isClicked(mouse, click)) {
        std::cout << "Exit failed.";
        menu.SetState(new StartState());
    }
}

ExitState::~ExitState() {
    UnloadSound(goodbyeSound);
}