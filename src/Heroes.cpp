#include "Heroes.hpp"
#include <iostream>
using namespace std ; 

Archaeologist:: Archaeologist(GameMap& Map): Hero("archaeologist" , 4 , Map.get_location_by_name("Docks") , "Take any number of items from neighbor locations." , "../Assets/Heros/Archaeologist.png") {
    Map.get_location_by_name("Docks")->add_hero(this , this->getTexture()) ; 
    loadTexture();
}

bool Archaeologist::drawCancelButton(){
    ClickableText Backbutton("Cancel" , {100 , 400} , 20 , RAYWHITE) ;
    Backbutton.Draw() ; 
    if(Backbutton.isClicked()) 
        return true ; 
    return false ;
}

bool Archaeologist::drawDoneButton(){
    ClickableText button("Done" , {250 , 400} , 20 , RAYWHITE) ;
    button.Draw() ; 
    if(button.isClicked()) 
        return true ; 
    return false ;
}

void Archaeologist::DrawTypingText(const std::string &text) {

    DrawText(text.c_str(), 120, 180, 28, BLUE);
    if ((int)(GetTime() * 2) % 2 == 0) {  
        int textWidth = MeasureText(text.c_str(), 28);
        DrawText("|", 120 + textWidth + 2, 180, 28, BLUE);
    }
}

std::string Archaeologist::type(std::string input){
    int key = GetCharPressed();
        while (key > 0) {
            if (key >= 32 && key <= 125) 
                input += (char)key;
            key = GetCharPressed();
        }
        if (IsKeyPressed(KEY_BACKSPACE) && !input.empty()) 
            input.pop_back();    

    return input ;  
}

bool Archaeologist::handleShouldClose()
{
    if (shouldClose) {
        messageTimer += GetFrameTime();
        if (messageTimer >= 1.0f) {
            WaitTime(1.5f) ;
            return true; 
        }
        return false; 
    }  
    return false ;
}

void Archaeologist::StartSpecial(GameMap & m) {
    map = &m;
    chosenPlace.clear();
    message.clear();
    itemHitboxes.clear();
    chosenLocation = nullptr;
    itemList = nullptr;
    shouldClose = false;
    typing = true;            
    ChoseAnItem = false;       
}

void Archaeologist::UpdateSpecial(bool &done){

    if(handleShouldClose()) done = true;

    Location* heroLoc = GetCurrentLocation();

    if (typing) {
        chosenPlace = type(chosenPlace) ;

        if (IsKeyPressed(KEY_ENTER)) {
            if (heroLoc->findNeighbor(chosenPlace)) {
                typing = false;
                chosenLocation = map->get_location_by_name(chosenPlace);
                itemList = &chosenLocation->get_items() ;
                if(itemList->empty()) {
                    message = "no item available in " + chosenLocation->get_name() ; 
                    shouldClose = true ;
                }
            } else {
                message = "Invalid neighboring location!";
                chosenPlace.clear() ;
            }
        }
    } 

    for (size_t i = 0; i < itemHitboxes.size(); ++i) {
        if (CheckCollisionPointRec(GetMousePosition(), itemHitboxes[i]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            GetItems().push_back((*itemList)[i]);
            message = "Picked up " + (*itemList)[i].getName();
            itemList->erase(itemList->begin() + i);
            ChoseAnItem = true ;

            if (itemList->empty()) {
                message = "No more items.";
                shouldClose = true ;
                SetRemainingActions(GetRemainingActions() - 1);
            }
        }
    }
}

void Archaeologist::DrawSpecial() {

    int y = 120;

    if(typing)
        DrawTypingText(chosenPlace) ;

    if(drawDoneButton()){
        message = "Special done";
        SetRemainingActions(GetRemainingActions() - 1);
        shouldClose = true;
    } 
    if(drawCancelButton()){
        message = "Special canceled";
        if(ChoseAnItem)
            SetRemainingActions(GetRemainingActions() - 1);
        shouldClose = true ;
    }
    DrawText("Enter neighboring location to pick up its items:", 100, y, 18, RAYWHITE);
    y += 30;

    if (!message.empty()) {
        DrawText(message.c_str(), 100, y, 18, MAROON);
        y+= 30 ;
    }

    if (itemList) {
        // Draw items
        if (itemHitboxes.size() != itemList->size())
            itemHitboxes.resize(itemList->size());

        for (size_t i = 0; i < itemList->size(); ++i) {
            const Item& it = (*itemList)[i];
            std::string text = std::to_string(i + 1) + ". " + it.getName() + " (color: " + it.color_to_string(it.getColor()) + ", strength: " + std::to_string(it.getStrength()) + ")";
            Rectangle box = { 110, (float)y - 2, 460.0f, 26.0f };
            itemHitboxes[i] = box;

            Color bg = CheckCollisionPointRec(GetMousePosition(), box) ? Fade(LIGHTGRAY, 0.5f) : BLANK;
            DrawRectangleRec(box, bg);
            DrawText(text.c_str(), 200, y, 18, RAYWHITE);
            y += 30;
        }
    }
}



Mayor::Mayor(GameMap& Map) : Hero("mayor" , 5 , Map.get_location_by_name("Theatre") , "No special action." , "../Assets/Heros/Mayor.png") {
    Map.get_location_by_name("Theatre")->add_hero(this , this->getTexture()) ; 
    loadTexture();
}

Courier::Courier(GameMap& Map , TurnManager& m): Hero("courier" , 4 , Map.get_location_by_name("Shop") , "Move to a location where the other heroe is." , "../Assets/Heros/Courier.png") , turn(m) {
    Map.get_location_by_name("Shop")->add_hero(this , this->getTexture()) ; 
    loadTexture();
} 

void Courier::StartSpecial(GameMap &){

    heroes = turn.get_heroes() ;
    // message = "choose a hero to move to:" ;
    hoveredIndex = -1 ; 
    done = false ;
}
void Courier::UpdateSpecial(bool &done) {
    Vector2 mousepos = GetMousePosition();

    float startX = 100.0f;  
    float startY = 150.0f;
    float width = 300.0f;
    float height = 30.0f;

    hoveredIndex = -1;  // reset hovered index هر بار آپدیت

    int displayedIndex = 0; // شمارنده برای هیروهای غیر courier

    for (size_t i = 0; i < heroes.size(); i++) {
        if (heroes[i]->GetName() == "courier")
            continue;

        Rectangle heroBox = { startX, startY + displayedIndex * height, width, height };
        if (CheckCollisionPointRec(mousepos, heroBox)) {
            hoveredIndex = displayedIndex;
            break;
        }
        displayedIndex++;
    }

    if (hoveredIndex != -1 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        // انتخاب هیرو بر اساس displayedIndex
        int selectedCount = 0;
        Hero* selectedHero = nullptr;
        for (size_t i = 0; i < heroes.size(); i++) {
            if (heroes[i]->GetName() == "courier")
                continue;

            if (selectedCount == hoveredIndex) {
                selectedHero = heroes[i];
                break;
            }
            selectedCount++;
        }

        if (selectedHero) {
            MoveTo(selectedHero->GetCurrentLocation());
            SetRemainingActions(GetRemainingActions() -1) ;

            done = true;
            return;
        }
    }
}

void Courier::DrawSpecial() {
    Rectangle panel = {80, 80, 400, 300};
    DrawRectangleRec(panel, Fade(DARKGRAY, 0.9f));
    DrawRectangleLinesEx(panel, 3, RAYWHITE);

    DrawText("Select a Hero to Move To:", panel.x + 20, panel.y + 10, 22, WHITE);

    float x = panel.x + 20;
    float y = panel.y + 50;
    float lineHeight = 28;

    int displayedIndex = 0;
    for (size_t i = 0; i < heroes.size(); i++) {
        if (heroes[i]->GetName() == "courier")
            continue;

        Color textColor = (hoveredIndex == displayedIndex) ? YELLOW : WHITE;
        std::string text = heroes[i]->GetName() + " (Location: " + heroes[i]->GetCurrentLocation()->get_name() + ")";
        DrawText(text.c_str(), x, y, 20, textColor);

        y += lineHeight;
        displayedIndex++;
    }
}

Scientist::Scientist(GameMap& Map) : Hero("scientist" , 4 , Map.get_location_by_name("Institute") , "No special action.", "../Assets/Heros/Scientist.png") {
    Map.get_location_by_name("Institute")->add_hero(this , this->getTexture()) ; 
    loadTexture();
}

bool Scientist::HasAbility() { return true ; }
