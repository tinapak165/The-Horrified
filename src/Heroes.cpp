#include "Heroes.hpp"
#include <iostream>
#include "Hero.hpp"
using namespace std ; 

Archaeologist:: Archaeologist(GameMap& Map): Hero("archaeologist" , 4 , Map.get_location_by_name("Docks") , "can take any number of items from adjacent locations." , "../Assets/Heros/Archaeologist.png") {
    Map.get_location_by_name("Docks")->add_hero(this , this->getTexture()) ; 
    loadTexture();
}

void Archaeologist::StartSpecial(GameMap & m){
    map = &m;
    typing = true;
    showingMessage = false;
    chosenPlace.clear();
    message.clear();
    validInput = false;
    chosenLocation = nullptr;
    
}

void Archaeologist::UpdateSpecial(bool &done){

    Location* heroLoc = GetCurrentLocation();

    if (showingMessage) {
        if (GetTime() - messageStartTime >= 1.5) {
            showingMessage = false;
            message.clear();

            if (autoCompleteWithoutItems) {
                autoCompleteWithoutItems = false ;
                done = true ;
            }
            else 
                typing = true;
        }
        return ;
    }
    if (typing) {
        int key = GetCharPressed();
        while (key > 0) {
            if (key >= 32 && key <= 125)
                chosenPlace += (char)key;
            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE) && !chosenPlace.empty()) {
            chosenPlace.pop_back();
        }

        if (IsKeyPressed(KEY_ENTER)) {
            if (heroLoc->findNeighbor(chosenPlace)) {
                chosenLocation = map->get_location_by_name(chosenPlace);
                Special(chosenLocation);
                validInput = true;
            } else {
                message = "Invalid neighboring location!";
                validInput = false;
                chosenPlace.clear() ;
            }

            typing = false;
            showingMessage = true;
            messageStartTime = GetTime();
        }
    } 
    if (pickingItems && itemList) {

        if (pickingItems && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
            CheckCollisionPointRec(GetMousePosition(), doneButtonBox)) {
            
            pickingItems = false;
            message = "Finished picking items.";
            done = true;
        }

        for (size_t i = 0; i < itemHitboxes.size(); ++i) {
            if (CheckCollisionPointRec(GetMousePosition(), itemHitboxes[i]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                GetItems().push_back((*itemList)[i]);
                message = "Picked up " + (*itemList)[i].getName();
                itemList->erase(itemList->begin() + i);

                if (itemList->empty()) {
                    pickingItems = false;
                    message += ". No more items.";
                    done = true ;
                }
                break;
            }
        }
    }
    if(done){
        SetRemainingActions(GetRemainingActions() -1) ;
        return;
    }
}

void Archaeologist::DisplayInfo() const {
    float panelX = 210;
    float panelY = 90;
    float panelWidth = 750;
    float panelHeight = 190;

    DrawRectangle(panelX, panelY, panelWidth, panelHeight, Fade(DARKGRAY, 0.1f));
    DrawRectangleLines(panelX, panelY, panelWidth, panelHeight, GRAY);

    float textX = panelX + 20;
    float textY = panelY + 20;

    DrawText(GetName().c_str(), textX, textY, 25, YELLOW);
    textY += 40;

    string location = "Location: " + GetCurrentLocation()->get_name();
    DrawText(location.c_str(), textX, textY, 20, WHITE);
    textY += 30;

    string actions = "Actions: " + std::to_string(GetRemainingActions()) + " / 4";
    DrawText(actions.c_str(), textX, textY, 20, WHITE);
    textY += 30;

    string special = "Special: " + GetSpecialActionInfo();
    DrawText(special.c_str(), textX, textY, 20, WHITE);
}

void Archaeologist::Special(Location* chosenplace){ //amade sazi

    currentTargetLocation = chosenplace ;

    itemList = &chosenplace->get_items() ;
    
    itemHitboxes.clear();
    message.clear() ;

    if(itemList->empty()) {
        message = "no item available in " + chosenplace->get_name() ; 
        pickingItems = false ; 
        showingMessage = true ;
        messageStartTime = GetTime() ;
        autoCompleteWithoutItems = true ;
        return ;  
    }
    pickingItems = true ;  
}

void Archaeologist::DrawSpecial() {

    Rectangle infoPanel = {340.0f, 200.0f, 480.0f, 300.0f};
    DrawRectangleRec(infoPanel, Fade(DARKGRAY, 0.94f));
    DrawRectangleLinesEx(infoPanel, 2, GRAY);

    int x = infoPanel.x + 20;
    int y = infoPanel.y + 20;

    DrawText("Enter neighboring location to pick up its items:", x, y, 18, RAYWHITE);
    y += 30;
    DrawText(("> " + chosenPlace).c_str(), x, y, 24, BLUE);
    y += 40;

    if (!message.empty()) {
        DrawText(message.c_str(), x, y, 18, MAROON);
        y+= 30 ;
    }

    if (pickingItems && itemList) {
        // Draw "Done" button
        DrawRectangleRec(doneButtonBox, GRAY);
        if (CheckCollisionPointRec(GetMousePosition(), doneButtonBox)) {
            DrawRectangleLinesEx(doneButtonBox, 2, YELLOW);
        } else {
            DrawRectangleLinesEx(doneButtonBox, 2, WHITE);
        }

        int textWidth = MeasureText("Done", 20);
        DrawText("Done", doneButtonBox.x + (doneButtonBox.width - textWidth) / 2,
                        doneButtonBox.y + 5, 20, BLACK);

        if(itemHitboxes.size() != itemList->size())
        itemHitboxes.resize(itemList->size()) ;

        for (size_t i = 0; i < itemList->size(); ++i) {

            const Item& it = (*itemList)[i];
            std::string text = std::to_string(i + 1) + ". " + it.getName() +
                " (color: " + it.color_to_string(it.getColor()) +
                ", strength: " + std::to_string(it.getStrength()) + ")";
            
            Rectangle box = { (float)x - 5, (float)y - 2, 460.0f, 26.0f };
            itemHitboxes[i] = box ;

            Color bg = CheckCollisionPointRec(GetMousePosition(), box) ? Fade(LIGHTGRAY, 0.5f) : BLANK;
            DrawRectangleRec(box, bg);
            DrawText(text.c_str(), x, y, 18, RAYWHITE);
            y += 30;
        }

    }
}


Mayor::Mayor(GameMap& Map) : Hero("mayor" , 5 , Map.get_location_by_name("Theatre") , "No special action." , "../Assets/Heros/Mayor.png") {
    Map.get_location_by_name("Theatre")->add_hero(this , this->getTexture()) ; 
    loadTexture();
}

void Mayor::DisplayInfo()const {
    float panelX = 210;
    float panelY = 90;
    float panelWidth = 750;
    float panelHeight = 190;

    DrawRectangle(panelX, panelY, panelWidth, panelHeight, Fade(DARKGRAY, 0.1f));
    DrawRectangleLines(panelX, panelY, panelWidth, panelHeight, GRAY);

    float textX = panelX + 20;
    float textY = panelY + 20;

    DrawText(GetName().c_str(), textX, textY, 25, YELLOW);
    textY += 40;

    string location = "Location: " + GetCurrentLocation()->get_name();
    DrawText(location.c_str(), textX, textY, 20, WHITE);
    textY += 30;

    string actions = "Actions: " + std::to_string(GetRemainingActions()) + " /5";
    DrawText(actions.c_str(), textX, textY, 20, WHITE);
    textY += 30;

    string special = "Special: " + GetSpecialActionInfo();
    DrawText(special.c_str(), textX, textY, 20, WHITE);
}

void Mayor::StartSpecial(GameMap &){

    message = "this hero does not have any special action" ;
    shown = false ;  
}

void Mayor::Special(Location*){}

void Mayor::UpdateSpecial(bool &done){

    if (!shown) {
        shown = true;
        messageStartTime = GetTime();
    } else if (GetTime() - messageStartTime >= 2.0) {
        done = true;
    }

}

void Mayor::DrawSpecial(){

    Rectangle infoPanel = {350, 250, 500, 100};
    DrawRectangleRec(infoPanel, Fade(DARKGRAY, 0.85f));
    DrawRectangleLinesEx(infoPanel, 2, RAYWHITE);
    DrawText(message.c_str(), infoPanel.x + 20, infoPanel.y + 35, 22, WHITE);

}

Courier::Courier(GameMap& Map , TurnManager& m): Hero("courier" , 4 , Map.get_location_by_name("Shop") , "can be moved to a location where one of the other heroes is." , "../Assets/Heros/Courier.png") , turn(m) {
    Map.get_location_by_name("Shop")->add_hero(this , this->getTexture()) ; 
    loadTexture();
} 

void Courier::DisplayInfo() const {
    float panelX = 210;
    float panelY = 90;
    float panelWidth = 750;
    float panelHeight = 190;

    DrawRectangle(panelX, panelY, panelWidth, panelHeight, Fade(DARKGRAY, 0.1f));
    DrawRectangleLines(panelX, panelY, panelWidth, panelHeight, GRAY);

    float textX = panelX + 20;
    float textY = panelY + 20;

    DrawText(GetName().c_str(), textX, textY, 25, YELLOW);
    textY += 40;

    string location = "Location: " + GetCurrentLocation()->get_name();
    DrawText(location.c_str(), textX, textY, 20, WHITE);
    textY += 30;

    string actions = "Actions: " + std::to_string(GetRemainingActions()) + " / 4";
    DrawText(actions.c_str(), textX, textY, 20, WHITE);
    textY += 30;

    string special = "Special: " + GetSpecialActionInfo();
    DrawText(special.c_str(), textX, textY, 20, WHITE);
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

void Courier::Special(Location *){}

Scientist::Scientist(GameMap& Map) : Hero("scientist" , 4 , Map.get_location_by_name("Institute") , "No special action.", "../Assets/Heros/Scientist.png") {
    Map.get_location_by_name("Institute")->add_hero(this , this->getTexture()) ; 
    loadTexture();
}

void Scientist::DisplayInfo() const {
    float panelX = 210;
    float panelY = 90;
    float panelWidth = 750;
    float panelHeight = 190;

    DrawRectangle(panelX, panelY, panelWidth, panelHeight, Fade(DARKGRAY, 0.1f));
    DrawRectangleLines(panelX, panelY, panelWidth, panelHeight, GRAY);

    float textX = panelX + 20;
    float textY = panelY + 20;

    DrawText(GetName().c_str(), textX, textY, 25, YELLOW);
    textY += 40;

    string location = "Location: " + GetCurrentLocation()->get_name();
    DrawText(location.c_str(), textX, textY, 20, WHITE);
    textY += 30;

    string actions = "Actions: " + std::to_string(GetRemainingActions()) + " / 4";
    DrawText(actions.c_str(), textX, textY, 20, WHITE);
    textY += 30;

    string special = "Special: " + GetSpecialActionInfo();
    DrawText(special.c_str(), textX, textY, 20, WHITE);
}

bool Scientist::HasAbility() { return true ; }

void Scientist::StartSpecial(GameMap &){

    message = "this hero does not have any special action" ;
    shown = false ; 
}
void Scientist::Special(Location *){}

void Scientist::UpdateSpecial(bool &done){

    if (!shown) {
        shown = true;
        messageStartTime = GetTime();
    } 
    else if (GetTime() - messageStartTime >= 2.0) {
        done = true;
    }
}

void Scientist::DrawSpecial(){
    Rectangle infoPanel = {350, 250, 500, 100};
    DrawRectangleRec(infoPanel, Fade(DARKGRAY, 0.85f));
    DrawRectangleLinesEx(infoPanel, 2, RAYWHITE);
    DrawText(message.c_str(), infoPanel.x + 20, infoPanel.y + 35, 22, WHITE);
}
