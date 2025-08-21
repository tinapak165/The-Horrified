#include "State.hpp"
#include "Menu.hpp"
#include <iostream>
#include <cstring>

State::State(const std::string& bgPath) {
    background = LoadTexture(bgPath.c_str());
    font = LoadFont("../Assets/font.ttf");
}

State::~State(){
    UnloadTexture(background) ;
    UnloadFont(font);
}

Texture2D State::get_background() const{ return background; }
Font State::get_Font() const{ return font; }

MenuState::MenuState() : State("../Assets/Menu/firstbackground.png"), 
      startButton(std::make_unique<Button>("../Assets/Menu/Startgame.png", Vector2{500, 500} , 0.50f)),
      exitButton(std::make_unique<Button>("../Assets/Menu/Exit.png", Vector2{500, 700} , 0.5f)),
      continueButton(std::make_unique<Button>("../Assets/Menu/continue2.png", Vector2{500, 600} , 0.5f)) {}

void MenuState::render(Menu& menu)  {
        DrawTexture(get_background(), 0, 0, WHITE);

        startButton->Draw();
        exitButton->Draw();
        continueButton->Draw();

        if (startButton->isPressed()) {
            menu.getGame().distribute_initial_items() ;
            menu.SetState(std::move(std::make_unique<ExplainationState>())); 
            return ; 
        }
        if (exitButton->isPressed()) {
            menu.SetState(std::move(std::make_unique<ExitState>())) ;
            return ; 
        }
        if(continueButton->isPressed()){
            menu.SetState(std::make_unique<ContinueState>()) ;
            return ;        
        }
        
    }

ExitState::ExitState() 
    : State("../Assets/Menu/background1.png"),
      YesText(std::make_unique<ClickableText>("Yes", Vector2{280, 400}, 30, DARKGRAY)),
      NoText(std::make_unique<ClickableText>("No", Vector2{480, 400}, 30, DARKGRAY) )
     {}

void ExitState::render(Menu& menu) {
    DrawTexture(get_background(), 0, 0, WHITE);

    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.6f));
    DrawText("Are you sure you want to exit?", 200, 200, 30, WHITE);

    YesText->Draw();
    NoText->Draw();

    if (YesText->isClicked()) {
        WaitTime(0.5);
        CloseWindow();
    }

    if (NoText->isClicked()) {
        menu.SetState(std::move(std::make_unique<MenuState>()));
        return ; 
    }
}

NameInputState::NameInputState() : State("../Assets/Menu/background3.png") ,
    nameBox1(std::make_unique<TextBox>(Rectangle{100, 150, 300, 40}, TextBox::ANY)) ,
    nameBox2(std::make_unique<TextBox>(Rectangle{100, 350, 300, 40 }, TextBox::ANY)) ,
    timeBox1(std::make_unique<TextBox>(Rectangle{100, 250, 300, 40}, TextBox::NUMBERS_ONLY)) ,
    timeBox2(std::make_unique<TextBox>(Rectangle{100, 450, 300, 40}, TextBox::NUMBERS_ONLY)) ,    
    continueButton{120, 520, 200, 50}  {}

void NameInputState::render(Menu& menu) {
    DrawTexture(get_background(), 0, 0, WHITE);
    std::unique_ptr<ClickableText> BackToMenu = std::make_unique<ClickableText>("Back to menu", Vector2{100, 900} ,30, RED);

    Vector2 mousePos = GetMousePosition();
    bool mouseClicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

    BackToMenu->Draw() ;

    if(BackToMenu->isClicked()){
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
        DrawTextEx(get_Font() , labels[i], {boxes[i]->rect.x, boxes[i]->rect.y - 30}, 25 , 0 , RED) ;
        
        DrawRectangleRec(boxes[i]->rect, boxes[i]->active ? LIGHTGRAY : GRAY);
        DrawRectangleLinesEx(boxes[i]->rect, 2, boxes[i]->active ? RED : DARKGRAY);
        
        if (!boxes[i]->text.empty() || boxes[i]->active) {
            DrawText(boxes[i]->text.c_str(), boxes[i]->rect.x + 10, boxes[i]->rect.y + 10, 20, BLACK);
        }
        
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
            menu.SetState(std::move(std::make_unique<ChooseCharacterState>(p1 , p2) )) ;
            return ; 
        }  
    }
}

ChooseCharacterState::ChooseCharacterState(const PlayerSelection& p1, const PlayerSelection& p2)
    : player1(p1) , player2(p2), State("../Assets/Menu/background2.png") , instructionText("",{100, 50},30,BLACK) {

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

    ClickableText backButton("Back to menu", {100, 900}, 30, RED);
    backButton.Draw();
    if (backButton.isClicked()) {
        auto newstate = std::make_unique<MenuState>() ;
        menu.SetState(std::move(newstate));
        return;
    }

    std::string currentName = (currentTurn == PlayerTurn::PLAYER1) ? player1.name : player2.name;
    std::string instruction = currentName + ", choose your hero:";
    DrawTextEx(get_Font() , instruction.c_str(), {100, 70}, 35 , 0, RED) ;
 
    if (!selectedMessage.empty()) 
        DrawTextEx(get_Font() , selectedMessage.c_str(), {100, 100}, 30, 0 , YELLOW) ;

    for (int i = 0; i < heroButtons.size(); i++) {
        if (selectedHeroes[i]) 
            heroButtons[i]->DrawWithFade();
        else
            heroButtons[i]->Draw();      
    }

    if (mouseClicked) {
        for (int i = 0; i < heroButtons.size(); i++) {
            if (!selectedHeroes[i] && heroButtons[i]->isPressed()) {
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
            Texture2D background = LoadTexture("../Assets/Menu/background2.png");
            while (GetTime() - selectionTime < 3.0) { 
                BeginDrawing();
                ClearBackground(RAYWHITE);
                DrawTexture(background , 0 , 0 , WHITE);
                DrawText("Welcome to the Horror World...", 400, 500, 30, WHITE);
                EndDrawing();
            }
            UnloadTexture(background);
            menu.startGame(player1, player2);
            return;
        }
    }
}

ContinueState::ContinueState() : State("../Assets/Menu/Blackscreen.jpg"){}

void ContinueState::render(Menu & menu)
{
    DrawTexture(get_background(), 0, 0, WHITE);

    ClickableText backButton("Back to menu", {100, 900}, 30, RED);
    backButton.Draw();
    if (backButton.isClicked()) {
        auto newstate = std::make_unique<MenuState>() ;
        menu.SetState(std::move(newstate));
        return;
    }

    SaveManager save(menu.getGame()) ;
    std::vector<std::string> files = save.getFiles() ;
    if(files.empty())
        std::cout << "files are empty\n" ;
    int y = 150 ; 
    for(const std::string& file : files){
        fileButtons.emplace_back(file , Vector2{120, (float)y} , 28 , GREEN);
        y+= 40 ; 
    }
    DrawTextEx(get_Font() , "select a game: " , {100 , 80} , 40 , 0 , GREEN);

    for(auto & button : fileButtons){
        button.Draw() ;
        if(button.isClicked()){
            selectedFile = button.get_text() ;
            fileselected = true ;
        }
    }
    if(fileselected && !selectedFile.empty()){
        save.loadGame(selectedFile) ;
        menu.SetState(nullptr) ;
    }
}

ExplainationState::ExplainationState(): State("../Assets/Menu/Blackscreen.jpg"){}

void ExplainationState::render(Menu & menu)
{
    DrawTexture(get_background(), 0, 0, WHITE);

    ClickableText backButton("Back to menu", {100, 900}, 30, RED);
    backButton.Draw();
    if (backButton.isClicked()) {
        menu.SetState(std::make_unique<MenuState>());
        return;
    }

    ClickableText continueButton("continue", {900, 900}, 30, RED);
    continueButton.Draw();
    if (continueButton.isClicked()) {
        menu.SetState(std::make_unique<NameInputState>());
        return;
    }
    DrawTextEx(get_Font() ,
    "Welcome to Horrified! Here's your quick-start guide:\n"
    "1. Missions:\n"
    "    Work together with fellow heroes to defeat the monsters (Dracula and the Invisible Man)\n"
    "    by completing their specific tasks (smashing coffins, gathering evidence).\n"
    "    Escort villagers to their safe places(this will reward you with a Perk card).\n"
    "    Prevent the terror level from reaching its maximum.\n"
    "2. Hero Phase:\n"
    "    Take a number of actions equal to the value on your Hero Badge.\n"
    "    You may play any number of Perk cards (playing a Perk does not cost an action).\n"
    "    Learn more about actions by clicking on Help.\n"
    "    End your turn anytime by clicking Quit\n"
    "    Villagers cannot defend themselves. If monsters attack them, they are defeated, which raises the terror level.\n"
    "    If a hero is attacked they may discard an item to avoid being defeated and sent to the hospital.\n "
    "3. Monster Phase:\n"
    "     Draw a Monster card: place items, resolve an event, roll dice then move/attack monsters\n"
    "     Each monster has unique behavior and its own defeat conditions.\n  (click on each monster to learn more.)\n"
    "     Dice results: Attack, Power or Empty\n"
    "       Attack: If a monster shares a space with a hero, it may attack\n"
    "       Power: Activates that monster's special ability:\n"
    "         Dracula-> Dark Charm: pulls the current Hero into his place\n"
    "         InvisibleMan-> Stalk Unseen: moves 2 extra places toward the nearest villager\n"
    "     You can track what happened in the sidebar\n"
    "4. Terror level:\n"
    "    The Terror rises when heroes or villagers are defeated.\n"
    "    If the track reaches the end, the town falls and you lose.\n"
    "5. Victory:\n"
    "    Complete every active monster's objectives to save the town!\n"
      , Vector2{80 , 60 } , 28 , 0 , WHITE);
}
