#include "State.hpp"
#include "menu.hpp"
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
      startButton("../Assets/Menu/Startgame.png", {170, 300} , 1.0f),
      exitButton("../Assets/Menu/Exit.png", {170, 500} , 1.0f){}

void MenuState::playState(Menu& menu)  {
        DrawTexture(get_background(), 0, 0, WHITE);

        Vector2 mouse = GetMousePosition();
        bool click = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

        startButton.Draw(mouse);
        exitButton.Draw(mouse);

        if (startButton.isPressed(mouse, click)) {
            //std::cout << "Start clicked\n";
            menu.SetState(new NameInputState()); 
        }
        if (exitButton.isPressed(mouse, click)) {
          //  std::cout << "Exit clicked\n";
            menu.SetState(new ExitState()) ; 
        }
    }

ExitState::ExitState() 
    : State("../Assets/Menu/Background.png"),
      YesText("Yes", {280, 400}, 30, DARKGRAY),
      NoText("No", {480, 400}, 30, DARKGRAY),
      soundPlayed(false) {
    goodbyeSound = LoadSound("Assets/goodbye.wav");
}

void ExitState::playState(Menu& menu) {
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
        menu.SetState(new MenuState());
    }
}

ExitState::~ExitState() {
    UnloadSound(goodbyeSound);
}

NameInputState::NameInputState() : State("../Assets/Menu/Background.png") {
    // کاربر اول
    nameBox1 = TextBox({100, 150, 300, 40}, TextBox::LETTERS_ONLY); // فقط حروف
    timeBox1 = TextBox({100, 250, 300, 40}, TextBox::NUMBERS_ONLY); // فقط اعداد
    
    // کاربر دوم
    nameBox2 = TextBox({100, 350, 300, 40}, TextBox::LETTERS_ONLY); // فقط حروف
    timeBox2 = TextBox({100, 450, 300, 40}, TextBox::NUMBERS_ONLY); // فقط اعداد
    
    continueButton = {300, 500, 200, 50};
}

void NameInputState::playState(Menu& menu) {
    // 1. رسم پس‌زمینه
    DrawTexture(get_background(), 0, 0, WHITE);

    // 2. دریافت وضعیت ورودی
    Vector2 mousePos = GetMousePosition();
    bool mouseClicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

    // 3. لیست باکس‌ها
    TextBox* boxes[] = {&nameBox1, &timeBox1, &nameBox2, &timeBox2};
    
    // 4. پردازش کلیک ماوس
    if (mouseClicked) {
        // غیرفعال کردن همه باکس‌ها
        for (auto box : boxes) {
            box->active = false;
        }
        
        // فعال کردن فقط باکس کلیک شده
        for (auto box : boxes) {
            if (CheckCollisionPointRec(mousePos, box->rect)) {
                box->active = true;
                break;
            }
        }
    }

    // 5. پردازش ورودی متن
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
                    isValid = isalpha(key) || key == ' '; // حروف و فاصله
                    break;
                    
                case TextBox::ANY:
                    isValid = true; // همه کاراکترها مجاز
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
        "Last garlic time (MM):", 
        "Player 2 Name:",         
        "Last garlic time (MM):"  
    };

    // 7. رسم باکس‌ها و متن
    for (int i = 0; i < 4; i++) {
        // رسم برچسب
        DrawText(labels[i], boxes[i]->rect.x, boxes[i]->rect.y - 30, 20, RED);
        
        // رسم باکس
        DrawRectangleRec(boxes[i]->rect, boxes[i]->active ? LIGHTGRAY : GRAY);
        DrawRectangleLinesEx(boxes[i]->rect, 2, boxes[i]->active ? RED : DARKGRAY);
        
        // رسم متن
        if (!boxes[i]->text.empty() || boxes[i]->active) {
            DrawText(boxes[i]->text.c_str(), boxes[i]->rect.x + 10, boxes[i]->rect.y + 10, 20, BLACK);
        }
        
        // نشانگر چشمک‌زن برای باکس فعال
        if (boxes[i]->active && ((int)(GetTime()*2) % 2 == 0)) {
            int textWidth = MeasureText(boxes[i]->text.c_str(), 20);
            DrawText("|", boxes[i]->rect.x + 10 + textWidth, boxes[i]->rect.y + 10, 20, BLACK);
        }
    }

    // 8. دکمه ادامه و اعتبارسنجی
    bool allFilled = !nameBox1.text.empty() && !timeBox1.text.empty() &&
                    !nameBox2.text.empty() && !timeBox2.text.empty();
    
    DrawRectangleRec(continueButton, allFilled ? GREEN : GRAY);
    DrawText("Continue", continueButton.x + 50, continueButton.y + 15, 20, WHITE);
    
    if (mouseClicked && CheckCollisionPointRec(mousePos, continueButton)) {
        if (allFilled)
            menu.SetState(new ChooseCharacterState(nameBox1.text , timeBox1.text , nameBox2.text , timeBox2.text)) ;
        else 
            DrawText("Please fill all fields!", 300, 550, 20, RED);  
    }
}

ChooseCharacterState::ChooseCharacterState(const std::string& p1Name, const std::string& p1Time,const std::string& p2Name, const std::string& p2Time)
    : player1Name(p1Name), player1GarlicTime(p1Time),
      player2Name(p2Name), player2GarlicTime(p2Time) , State("../Assets/Menu/Background.png") , instructionText("",{100, 50},30,BLACK) {

    player1First = std::stoi(player1GarlicTime) < std::stoi(player2GarlicTime);
    currentPlayer = player1First ? &player1Name : &player2Name;
    
    instructionText = ClickableText(*currentPlayer + ", choose your hero:", {100, 50} ,30 , RED); //draw text!!

    heroButtons.push_back(std::make_unique<Button>("../Assets/Heros/Mayor.png", Vector2{150, 150})) ;
    heroButtons.push_back(std::make_unique<Button>("../Assets/Heros/Archaeologist.png", Vector2{150, 550}) );
    heroButtons.push_back(std::make_unique<Button>("../Assets/Heros/Courier.png", Vector2{600, 150} , 0.31f)) ;
    heroButtons.push_back(std::make_unique<Button>("../Assets/Heros/Scientist.png", Vector2{600, 550})) ;

}

void ChooseCharacterState::playState(Menu& menu){
    DrawTexture(get_background() , 0 , 0 , WHITE) ;
    Vector2 mousePos = GetMousePosition() ; 
    bool mouseClicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON) ; 

    instructionText.Draw(mousePos) ; 
    for(int i = 0 ; i < heroButtons.size() ; i++){
        if(availableHeroes[i])
            heroButtons[i]->Draw(mousePos) ;
    }
    if(mouseClicked){
        for(int i = 0 ; i < heroButtons.size() ; i++){
            if(availableHeroes[i] && heroButtons[i]->isPressed(mousePos , mouseClicked)){
                if(currentPlayer == &player1Name){
                    player1Hero = heroNames[i] ; 
                    availableHeroes[i] = false ; 
                    currentPlayer = &player2Name ; 
                    instructionText = ClickableText(*currentPlayer + ", choose you hero: " , {100,50} , 30 , RED) ;
                }else{
                    player2Hero = heroNames[i] ;
               //     menu.startGame(player1Name, player1Hero, player2Name, player2Hero) ;
                        return;                
                }
            }
        }
    }
}
