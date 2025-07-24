#include "Action.hpp"

MoveAction::MoveAction(GameMap &map, Hero *hero): map(map) , hero(hero){}

bool MoveAction::update(){
    Location* currentLoc = hero->GetCurrentLocation();

    std::string ans ; 

    if (typing) {

        int key = GetCharPressed();
        while (key > 0) {
            if (key >= 32 && key <= 125) {
                chosenPlace += (char)key;
            }
            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE) && !chosenPlace.empty()) {
            chosenPlace.pop_back();
        }

        if (IsKeyPressed(KEY_ENTER)) {
            chosenLocation = map.get_location_by_name(chosenPlace);
            if (chosenLocation && currentLoc->findNeighbor(chosenPlace)) {
                validInput = true;
                typing = false;

                if (hero->hasvillagerHere()) {
                    askVillager = true;
                    message = "Some villagers are with you. Move them too? [Y/N]";
                } else {
                    moveFinished = true;
                }
            } else {
                message = "Invalid location or not a neighbor! Where do you want to go?";
                chosenPlace.clear();
                typing = true ; 
            }
        }
    } else if (askVillager) {
        if (IsKeyPressed(KEY_Y)) {
            moveWithVillager = true;
            askVillager = false;
            moveFinished = true;
        } else if (IsKeyPressed(KEY_N)) {
            moveWithVillager = false;
            askVillager = false;
            moveFinished = true;
        }
    }

    if (moveFinished && validInput && chosenLocation) {
        if (moveWithVillager) {
            hero->MoveTo(chosenLocation, hero->villagerHere());
        } else {
            hero->MoveTo(chosenLocation);
        }

        hero->SetRemainingActions(hero->GetRemainingActions() -1) ;
        return true; // action finished
    }

    return false; 
}


void MoveAction::draw(){
    DrawRectangle(100, 100, 750, 250, Fade(DARKGRAY, 0.8f));
    DrawText("[Playing Move Action]" , 120 , 105 , 24 , RAYWHITE) ;
    DrawText(message.c_str(), 120, 130, 24, RAYWHITE);
    if (typing) {
        DrawText(chosenPlace.c_str(), 120, 180, 28, YELLOW);
    }
}

HelpAction::HelpAction(Hero * hero): hero(hero){}

bool HelpAction::update(){

    hero->DisplayActions();
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
        return true;
    return false;
}
void HelpAction::draw() {}