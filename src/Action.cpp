#include "Action.hpp"

MoveAction::MoveAction(GameMap &map, Hero *hero): map(map) , hero(hero){}

bool MoveAction::update(){
    Location* currentLoc = hero->GetCurrentLocation();

    std::string ans ; //ezafe kon

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

PickUpAction::PickUpAction(Hero* h) : hero(h) {}
bool PickUpAction::update() {
    mousePos = GetMousePosition();
    std::vector<Item>& ItemsAtLocation = hero->GetCurrentLocation()->get_items();

    if (!done && ItemsAtLocation.empty()) {
        message = "No items to pick up!";
        done = true;
        return false;
    }

    if (!done) {
        bool clickedOnItem = false;

        for (size_t i = 0; i < ItemsAtLocation.size(); ++i) {
            Rectangle itemRect = {120.0f, 200.0f + i * 90.0f, 300.0f, 80.0f};
            if (CheckCollisionPointRec(mousePos, itemRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                hero->GetItems().push_back(ItemsAtLocation[i]);
                message = hero->GetName() + " picked up " + ItemsAtLocation[i].getName();
                ItemsAtLocation.erase(ItemsAtLocation.begin() + i);
                return false; // ادامه بده تا بشه آیتم‌های دیگه رو هم برداشت
            }
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            message = "Pickup canceled";
            done = true;
            return false;
        }

    }

    if (done) {
        frameCounter++;
        if (frameCounter >= 60) {
            hero->SetRemainingActions(hero->GetRemainingActions() - 1);
            return true;
        }
    }

    return false;
}

void PickUpAction::draw() {
    DrawRectangle(100, 100, 750, 250, Fade(DARKGRAY, 0.85f));
    DrawText("[ Playing Pickup Action]", 120 , 105, 28, RAYWHITE);
    DrawText(message.c_str(), 120, 150, 22, YELLOW);

    std::vector<Item>& items = hero->GetCurrentLocation()->get_items();

    for (size_t i = 0; i < items.size(); ++i) {
        Rectangle itemRect = {120.0f, 200.0f + i * 90.0f, 300.0f, 80.0f};
        DrawRectangleRec(itemRect, GRAY);
        DrawText(items[i].getName().c_str(), itemRect.x + 10, itemRect.y + 10, 20, WHITE);
        
        std::string details = "(Color: " + Item::color_to_string(items[i].getColor()) + ", Str: " + std::to_string(items[i].getStrength()) + ")";
        DrawText(details.c_str(), itemRect.x + 10, itemRect.y + 40, 18, LIGHTGRAY);
    }
}

