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


void PickUpAction::draw() {
    DrawRectangle(100, 100, 750, 250, Fade(DARKGRAY, 0.85f));
    DrawText("[Playing Pickup Action]", 120 , 105, 28, RAYWHITE);
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


ChoosePerkCardAction::ChoosePerkCardAction(Hero* h , Game& game) : hero(h) , game(game) {}

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
bool ChoosePerkCardAction::update() {
    mousePos = GetMousePosition(); 
    auto& availablePerks = hero->GetAvailablePerkCards();

    if (!done && availablePerks.empty()) {
        message = "No perk cards available!";
        done = true;
        return false;
    }
        // اگر کارت انتخاب شده، باید play بشه
    if (currentCard) {
        currentCard->play(hero);

        if (currentCard->isDone()) {
            hero->addPlayedCards(std::move(currentCard));
            done = true;
        }

        return false;
    }
    if(!done){
        for (size_t i = 0; i < availablePerks.size(); i++) {
            Rectangle cardRect = {100.0f + i * 220.0f, 200.0f, 200.0f, 300.0f};
            if (CheckCollisionPointRec(mousePos, cardRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {

                currentCard = std::move(availablePerks[i]);
                availablePerks.erase(availablePerks.begin() + i);                
                message = "playing: " + currentCard->get_name();
                if (currentCard->get_name() == "Break of Dawn") {
                    game.set_skipMonsterPhase(true);
                }

                return false;
            }
        }
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            message = "Perkcard canceled";
            done = true;
            return false;
        }        
    }

    if (done) { //delay
        frameCounter++;
        if (frameCounter >= 60) {
            return true;
        }
    }

    return false;
}


void ChoosePerkCardAction::draw() {

    DrawRectangle(100, 100, 750, 500, Fade(DARKGRAY, 0.85f));
    DrawText("[Playing Perk]", 120 , 105, 28, RAYWHITE);
    if (currentCard) {
        currentCard->draw(); 
        return;
    }
    DrawText("Choose a Perk Card:", 120, 135, 28, YELLOW);

    auto& availablePerks = hero->GetAvailablePerkCards();

    for (size_t i = 0; i < availablePerks.size(); ++i) {
        Rectangle cardRect = {120.0f + i * 220.0f, 200.0f, 200.0f, 300.0f};
        DrawTexturePro(
            availablePerks[i]->get_texture(),
            {0, 0, (float)availablePerks[i]->get_texture().width, (float)availablePerks[i]->get_texture().height},
            cardRect,
            {0, 0},
            0.0f,
            WHITE
        );
    }

    if (!message.empty()) {
        DrawText(message.c_str(), 120, 155, 24, GREEN);
    }
}

SpecialAction::SpecialAction(Hero * hero , GameMap& map): hero(hero) , map(map) {
    hero->StartSpecial(map) ;
}

bool SpecialAction::update() {

    if(specialFinished) return true ;

    hero->UpdateSpecial(specialFinished) ;

    return specialFinished ;
}

void SpecialAction::draw() {

    if(!specialFinished)
        hero->DrawSpecial() ;
    
}