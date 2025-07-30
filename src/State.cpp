#include "State.hpp"
#include "Menu.hpp"
#include "GameRender.hpp"
#include "HeroPhaseState.hpp"

#include <iostream>
#include <cstring>

State::State(const std::string& bgPath) {
    background = LoadTexture(bgPath.c_str());
}

State::~State(){
    UnloadTexture(background) ;
}

Texture2D State::get_background() const{
    return background;
}


MenuState::MenuState() : State("../Assets/Menu/Background.png"), 
startButton(std::make_unique<Button>("../Assets/Menu/Startgame.png", Vector2{170, 300} , 1.0f)),
exitButton(std::make_unique<Button>("../Assets/Menu/Exit.png", Vector2{170, 500} , 1.0f)){}



 





 




  


// // class SetupState : public State {
// // public:
// //     void update(Menu& menu) override {
// //         // پس از آماده‌سازی سریع به فاز قهرمان می‌رویم
// //         menu.SetState(std::make_unique<HeroPhaseState>());
// //     }

// //     void playState(Menu& menu) override {
// //         ClearBackground(DARKGRAY);
// //         DrawText("Setup Game...", 100, 100, 30, WHITE);
// //     }
// // };
// void MenuState::render(Menu& menu)  {
//     DrawTexture(get_background(), 0, 0, WHITE);
    
//     Vector2 mouse = GetMousePosition();
//     bool click = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    
//     startButton->Draw(mouse);
//     exitButton->Draw(mouse);
    
//     if (startButton->isPressed(mouse, click)) {
//         auto newstate = std::make_unique<NameInputState>() ;
//         menu.SetState(std::move(newstate)); 
//         return ; 
//     }
//     if (exitButton->isPressed(mouse, click)) {
//         auto newstate = std::make_unique<ExitState>() ;
//         menu.SetState(std::move(newstate)) ;
//         return ; 
//     }
// }


// MenuState.cpp
void MenuState::render(Menu& menu)  {
        DrawTexture(get_background(), 0, 0, WHITE);

        Vector2 mouse = GetMousePosition();
        bool click = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

        startButton->Draw(mouse);
        exitButton->Draw(mouse);

        if (startButton->isPressed(mouse, click)) {
            auto newstate = std::make_unique<NameInputState>() ;
            menu.SetState(std::move(newstate)); 
            return ; 
        }
        if (exitButton->isPressed(mouse, click)) {
            auto newstate = std::make_unique<ExitState>() ;
            menu.SetState(std::move(newstate)) ;
            return ; 
        }
    }





ExitState::ExitState() 
    : State("../Assets/Menu/Background.png"),
      YesText(std::make_unique<ClickableText>("Yes", Vector2{280, 400}, 30, DARKGRAY)),
      NoText(std::make_unique<ClickableText>("No", Vector2{480, 400}, 30, DARKGRAY) )
     /*soundPlayed(false) */ {
    // goodbyeSound = LoadSound("Assets/goodbye.wav");
}

void ExitState::render(Menu& menu) {
    DrawTexture(get_background(), 0, 0, WHITE);

    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.6f));
    DrawText("Are you sure you want to exit?", 200, 200, 30, WHITE);

    Vector2 mouse = GetMousePosition();
    bool click = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

    YesText->Draw(mouse);
    NoText->Draw(mouse);

    if (YesText->isClicked(mouse, click)) {
        // if (!soundPlayed) {
        //     PlaySound(goodbyeSound);
        //     soundPlayed = true;
        // }
        WaitTime(0.5);
        CloseWindow();
    }

    if (NoText->isClicked(mouse, click)) {
        auto newstate = std::make_unique<MenuState>() ; 
        menu.SetState(std::move(newstate));
        return ; 
    }
}


// ExitState::~ExitState() {
//     UnloadSound(goodbyeSound);
// }

SetupState::SetupState() : State("nothing"){}
void SetupState::render(Menu& menu){

}


NameInputState::NameInputState() : State("../Assets/Menu/Background.png") ,
    nameBox1(std::make_unique<TextBox>(Rectangle{100, 150, 300, 40}, TextBox::ANY)) ,
    nameBox2(std::make_unique<TextBox>(Rectangle{100, 350, 300, 40 }, TextBox::ANY)) ,
    timeBox1(std::make_unique<TextBox>(Rectangle{100, 250, 300, 40}, TextBox::NUMBERS_ONLY)) ,
    timeBox2(std::make_unique<TextBox>(Rectangle{100, 450, 300, 40}, TextBox::NUMBERS_ONLY)) ,    
    continueButton{300, 500, 200, 50}  {}

void NameInputState::render(Menu& menu) {
    DrawTexture(get_background(), 0, 0, WHITE);
    std::unique_ptr<ClickableText> BackToMenu = std::make_unique<ClickableText>("Back to menu", Vector2{100, 900} ,30, RED);

    Vector2 mousePos = GetMousePosition();
    bool mouseClicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

    BackToMenu->Draw(mousePos) ;

    if(BackToMenu->isClicked(mousePos , mouseClicked)){
        auto newstate = std::make_unique<MenuState>() ; 
        menu.SetState(std::move(newstate)) ;
        return ; 
    }

    std::array<TextBox*,4> boxes = {nameBox1.get(), timeBox1.get(), nameBox2.get(), timeBox2.get()};
    
    if (mouseClicked) {
        for (auto box : boxes) {
            box->active = false;
        } 
        for (auto box : boxes) {
            if (CheckCollisionPointRec(mousePos, box->rect)) {
                box->active = true;
                break;
            }
        }
    }
    for (auto box : boxes) {
        if (box->active) {
            int key = GetCharPressed();
            while (key > 0) {
                bool isValid = false;
                
                switch(box->inputType) {
                    case TextBox::NUMBERS_ONLY:
                        isValid = isdigit(key);
                        break;
                        
                    case TextBox::LETTERS_ONLY:
                        isValid = isalpha(key) || key == ' '; 
                        break;
                        
                    case TextBox::ANY:
                        isValid = true; 
                        break;
                }  
                if (isValid && box->text.length() < 30) {
                    box->text += (char)key;
                }
                key = GetCharPressed();
            }

            if (IsKeyPressed(KEY_BACKSPACE) && !box->text.empty()) {
                box->text.pop_back();
            }
        }
    }
    const char* labels[] = {
        "Player 1 Name:",    
        "Last garlic time: ", 
        "Player 2 Name:",         
        "Last garlic time:"  
    };

    for (int i = 0; i < 4; i++) {
        DrawText(labels[i], boxes[i]->rect.x, boxes[i]->rect.y - 30, 20, RED);
        
        DrawRectangleRec(boxes[i]->rect, boxes[i]->active ? LIGHTGRAY : GRAY);
        DrawRectangleLinesEx(boxes[i]->rect, 2, boxes[i]->active ? RED : DARKGRAY);
        
        if (!boxes[i]->text.empty() || boxes[i]->active) {
            DrawText(boxes[i]->text.c_str(), boxes[i]->rect.x + 10, boxes[i]->rect.y + 10, 20, BLACK);
        }
        
        // نشانگر چشمک‌زن برای باکس فعال
        if (boxes[i]->active && ((int)(GetTime()*2) % 2 == 0)) {
            int textWidth = MeasureText(boxes[i]->text.c_str(), 20);
            DrawText("|", boxes[i]->rect.x + 10 + textWidth, boxes[i]->rect.y + 10, 20, BLACK);
        }
    }

    bool allFilled = !nameBox1->text.empty() && !timeBox1->text.empty() &&!nameBox2->text.empty() && !timeBox2->text.empty();
    
    DrawRectangleRec(continueButton, allFilled ? GREEN : GRAY);
    DrawText("Continue", continueButton.x + 50, continueButton.y + 15, 20, WHITE);

    PlayerSelection p1 , p2 ; 
    p1.name = nameBox1->text ; p2.name = nameBox2->text ; 
    p1.garlicTime = timeBox1->text ; p2.garlicTime = timeBox2->text ; 

    if (mouseClicked && CheckCollisionPointRec(mousePos, continueButton)) {
        if (allFilled){
            auto newstate = std::make_unique<ChooseCharacterState>(p1 , p2) ;
            menu.SetState(std::move(newstate)) ;
            return ; 
        }
        else 
            DrawText("Please fill all fields!", 300, 550, 20, RED);  
    }
}

ChooseCharacterState::ChooseCharacterState(const PlayerSelection& p1, const PlayerSelection& p2)
    : player1(p1) , player2(p2), State("../Assets/Menu/Background.png") , instructionText("",{100, 50},30,BLACK) {

    player1First = std::stoi(player1.garlicTime) < std::stoi(player2.garlicTime);
    currentTurn = player1First ? PlayerTurn::PLAYER1 : PlayerTurn::PLAYER2;
    
    heroButtons.push_back(std::make_unique<Button>("../Assets/Heros/Mayor.png", Vector2{150, 150})) ;
    heroButtons.push_back(std::make_unique<Button>("../Assets/Heros/Archaeologist.png", Vector2{150, 550}) );
    heroButtons.push_back(std::make_unique<Button>("../Assets/Heros/Courier.png", Vector2{600, 150} , 0.31f)) ;
    heroButtons.push_back(std::make_unique<Button>("../Assets/Heros/Scientist.png", Vector2{600, 550})) ;
    
    selectedHeroes = std::vector<bool>(heroButtons.size() , false) ; 
    selectedMessage = ""; 
}

void ChooseCharacterState::render(Menu& menu) {
    DrawTexture(get_background(), 0, 0, WHITE);

    Vector2 mousePos = GetMousePosition();
    bool mouseClicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

    ClickableText backButton("back to NameInput", {100, 900}, 30, RED);
    backButton.Draw(mousePos);
    if (backButton.isClicked(mousePos, mouseClicked)) {
        auto newstate = std::make_unique<NameInputState>() ;
        menu.SetState(std::move(newstate));
        return;
    }

    std::string currentName = (currentTurn == PlayerTurn::PLAYER1) ? player1.name : player2.name;
    std::string instruction = currentName + ", choose your hero:";
    DrawText(instruction.c_str(), 100, 50, 30, RED);
 
    if (!selectedMessage.empty()) 
        DrawText(selectedMessage.c_str(), 100, 100, 25, YELLOW);

    for (int i = 0; i < heroButtons.size(); i++) {
        if (selectedHeroes[i]) 
            heroButtons[i]->DrawWithFade(mousePos, 100);
        else
            heroButtons[i]->Draw(mousePos);      
    }

    if (mouseClicked) {
        for (int i = 0; i < heroButtons.size(); i++) {
            if (!selectedHeroes[i] && heroButtons[i]->isPressed(mousePos, mouseClicked)) {
                selectedHeroes[i] = true;

                if (currentTurn == PlayerTurn::PLAYER1) {
                    player1.heroType = heroNames[i];
                    currentTurn = PlayerTurn::PLAYER2;
                    selectedMessage = "Player 1 chose: " + player1.heroType;
                } else {
                    player2.heroType = heroNames[i];
                    currentTurn = PlayerTurn::PLAYER1 ;
                    selectedMessage += "\nPlayer 2 chose: " + player2.heroType;
                }
                break;
            }
        }
        if (!player1.heroType.empty() && !player2.heroType.empty()) {
            double selectionTime = GetTime();
            while (GetTime() - selectionTime < 2.0) { // 2 ثانیه تاخیر
                BeginDrawing();
                ClearBackground(BLACK);
                DrawText("Starting game...", 400, 500, 30, WHITE);
                EndDrawing();
            }
            menu.startGame(player1, player2);
             menu.SetState(std::make_unique<HeroPhaseState>(menu.getGame()));
            return;
        }
    }
}



MonsterPhaseState::MonsterPhaseState(): State ("../Assets/Menu/Background.png"){}



 void MonsterPhaseState::render(Menu& menu){
     
      DrawTexture(get_background(), 0, 0, WHITE);
   
       

        GameRender renderer(menu.getGame());
        renderer.draw();

        // پیام راهنما
        const char* msg = "Monster Phase complete - Press SPACE to continue";
        int textWidth = MeasureText(msg, 30);
        DrawText(msg, (GetScreenWidth() - textWidth) / 2, 100, 30, WHITE);

        // وقتی بازیکن تأیید کرد برو فاز هیرو
        if (phase_done && IsKeyPressed(KEY_SPACE)) {
            menu.SetState(std::make_unique<HeroPhaseState>(menu.getGame()));
        }

        
    
}

 


