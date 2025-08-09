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
        return true;
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

AdvanceAction::AdvanceAction(Hero * h, Dracula * dra, ItemPool& i, GameMap & map, InvisibleMan* invisi):
    hero(h) , dracula(dra) , pool(i) , map(map) , invisibleman(invisi){

    Location* current = hero->GetCurrentLocation() ;
    std::string locName = current->get_name();

    if(locName == "Cave" || locName == "Dungeon" || locName == "Crypt" || locName == "Graveyard" ){
        mode = Mode::ForDracula ;
        auto items = hero->GetItems() ;
        for(auto& item : items){
            if(item.getColor() == ItemColor::Blue) 
                availableRedItems.push_back(item);
        }
        totalStrength = 0 ; 
        selectedItems.clear() ; 
        message = "Select Red items with total strength >= 6 to destroy coffin.";
    }
    else if(h->GetCurrentLocation() == map.get_location_by_name("Precinct")) { 
        mode = Mode::ForInvisibleMan ;
        auto items = hero->GetItems();
            for (auto& item : items) {
                std::string loc = item.getLocationName();
                if (loc == "Inn" || loc == "Barn" || loc == "Institute" || loc == "Laboratory" || loc == "Mansion") 
                    evidenceItems.push_back(item);
            }
            evidencePlaced = false;
            message = "Select an item to place as evidence against Invisible Man.";
    }
    else{
        mode = Mode::None ; 
        message = "You cannot perform advance action here.";
    }

}
bool AdvanceAction::update() {

    if (shouldClose) {
        messageTimer += GetFrameTime();
        if (messageTimer >= 2.5f) {
            messageTimer = 0.0f;
            shouldClose = false;
            return true;
        }
        return false;
    }

    if (mode == Mode::None) {
        shouldClose = true;
        return false;
    }

    //  اگر منتظر پاسخ Y/N هستیم:
    if (waitingForAbility) {
        if (IsKeyPressed(KEY_Y)) {
            pendingAbilityItem.setStrength(pendingAbilityItem.getStrength() + 1);
            message = "Item boosted.";
            waitingForAbility = false;
        }
        else if (IsKeyPressed(KEY_N)) {
            message = "No boost applied.";
            waitingForAbility = false;
        }
        else {
            return false;  // منتظر کلید
        }

        selectedItems.push_back(pendingAbilityItem);
        totalStrength += pendingAbilityItem.getStrength();
        hero->removeItems(pendingAbilityItem);

        if (totalStrength >= 6) {
            dracula->destroy_coffin_at(hero->GetCurrentLocation()->get_name());
            for (auto& item : selectedItems) {
                pool.add_item(item);
            }
            hero->SetRemainingActions(hero->GetRemainingActions() -1); 
            message = "Coffin destroyed successfully!";
            shouldClose = true;
        }
        else {
            message = "Select more red items (total strength >= 6)";
        }

        return false;
    }

    // حالت Dracula:
    if (mode == Mode::ForDracula) {
        if (availableRedItems.empty()) {
            message = "You have no red items!";
            shouldClose = true;
            return false;
        }

        hoveredIndex = -1;
        float startX = 100.0f, startY = 150.0f, height = 30.0f;

        for (size_t i = 0; i < availableRedItems.size(); ++i) {
            Rectangle rect = { startX, startY + i * height, 300, height };
            if (CheckCollisionPointRec(GetMousePosition(), rect)) {
                hoveredIndex = (int)i;
                break;
            }
        }

        if (hoveredIndex != -1 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Item chosen = availableRedItems[hoveredIndex];
            availableRedItems.erase(availableRedItems.begin() + hoveredIndex);
            hoveredIndex = -1;

            if (hero->HasAbility()) {
                pendingAbilityItem = chosen;
                message = "Do you want to boost " + chosen.getName() + "? [Y/N]";
                waitingForAbility = true;
                return false;
            }

            selectedItems.push_back(chosen);
            totalStrength += chosen.getStrength();
            hero->removeItems(chosen);

            if (totalStrength >= 6) {
                dracula->destroy_coffin_at(hero->GetCurrentLocation()->get_name());
                for (auto& item : selectedItems) {
                    pool.add_item(item);
                }
                hero->SetRemainingActions(hero->GetRemainingActions() -1); 
                message = "Coffin destroyed successfully!";
                shouldClose = true;
            }
            else {
                message = "Select more red items (total strength >= 6)";
            }
        }
    }

    // InvisibleMan:
    else if (mode == Mode::ForInvisibleMan) {
        if (evidenceItems.empty()) {
            message = "You have no valid evidence items!";
            shouldClose = true;
            return false;
        }

        hoveredEvidenceIndex = -1;
        float startX = 100.0f, startY = 150.0f, height = 30.0f;

        for (size_t i = 0; i < evidenceItems.size(); ++i) {
            Rectangle rect = { startX, startY + i * height, 300, height };
            if (CheckCollisionPointRec(GetMousePosition(), rect)) {
                hoveredEvidenceIndex = (int)i;
                break;
            }
        }

        if (hoveredEvidenceIndex != -1 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !evidencePlaced) {
            Item selected = evidenceItems[hoveredEvidenceIndex];
            bool success = invisibleman->add_evidence(selected.getLocationName());
            if (success) {
                hero->removeItems(selected);
                pool.add_item(selected);
                hero->SetRemainingActions(hero->GetRemainingActions() -1);
                message = "Evidence placed successfully.";
                evidencePlaced = true;
                shouldClose = true;
            } else {
                message = "Evidence from that location already exists. Choose another.";
            }
        }
    }

    return false;
}

void AdvanceAction::draw() {
    
    float panelX = 80, panelY = 80, panelWidth = 600, panelHeight = 400;
    DrawRectangleRec({panelX, panelY, panelWidth, panelHeight}, Fade(DARKGRAY, 0.95f));
    DrawRectangleLinesEx({panelX, panelY, panelWidth, panelHeight}, 3, RAYWHITE);

    if (shouldClose && (message ==  "Evidence placed successfully." || message == "Coffin destroyed successfully!")) {
        DrawText(message.c_str(), panelX + 20, panelY + 15, 30, GREEN);
        return;
    }

    DrawText(message.c_str(), panelX + 20, panelY + 15, 20, WHITE);

    float x = panelX + 20;
    float y = panelY + 60;
    float lineHeight = 30;

    if (mode == Mode::ForDracula) {

        std::string strengthText = "Total Strength: " + std::to_string(totalStrength);
        DrawText(strengthText.c_str(), x, y, 20, BLACK);
        y += lineHeight;

        for (size_t i = 0; i < availableRedItems.size(); ++i) {
            Color textColor = (hoveredIndex == static_cast<int>(i)) ? YELLOW : WHITE;

            const Item& item = availableRedItems[i];
            std::string text = item.getName() + " (strength: " + std::to_string(item.getStrength()) + ")";
            DrawText(text.c_str(), x, y + i * lineHeight, 20, textColor);

        }

        y += availableRedItems.size() * lineHeight + 20;
        if (!selectedItems.empty()) {
            DrawText("Selected Items:", x, y, 20, BLACK);
            y += lineHeight;
            for (const auto& item : selectedItems) {
                std::string text = item.getName() + " (strength: " + std::to_string(item.getStrength()) + ")";
                DrawText(text.c_str(), x, y, 20, GREEN);
                y += lineHeight;
            }
        }

    } else if (mode == Mode::ForInvisibleMan) {

        for (size_t i = 0; i < evidenceItems.size(); ++i) {
            Color textColor = (hoveredEvidenceIndex == static_cast<int>(i)) ? YELLOW : WHITE;

            const Item& item = evidenceItems[i];
            std::string text = item.getName() + " (from: " + item.getLocationName() + ")";
            DrawText(text.c_str(), x, y + i * lineHeight, 20, textColor);
        }
    }

    Color messageColor = shouldClose ? GREEN : (mode == Mode::None ? RED : WHITE);
    DrawText(message.c_str(), panelX + 20, panelY + 15, 20, messageColor);
}

DefeatAction::DefeatAction(Hero * h , InvisibleMan *i, Dracula * d) : hero(h) , invisibleMan(i) , dracula(d){

    if(i && i->get_location() == h->GetCurrentLocation() ){ 
        mode = Mode::ForInvisibleMan ;
         if (invisibleMan->can_be_defeated()) {
            message = "You are ready to defeat the Invisible Man! Use Red items (total strength >= 9).";
            auto items = hero->GetItems() ;
            for(auto& item : items){
                if(item.getColor() == ItemColor::Blue)
                availableItems.push_back(item) ;
            }
        }
        else{
            message = "you can not defeat invisible man." ;
            shouldClose = true ; 
        }
    }
    else if (d && d->get_location() == hero->GetCurrentLocation()) {
        mode = Mode::ForDracula;
        if(dracula->can_be_defeated()){
            auto allItems = hero->GetItems();
            for (auto& item : allItems) {
                if (item.getColor() == ItemColor::Yellow)
                    availableItems.push_back(item);
            }
            message = "Defeat Dracula: select yellow items (total strength >= 6)";
        }else{
            message = "You must destroy all coffins first to defeat Dracula." ;
        }
    }
    else{
        mode = Mode::None ; 
        message = "No monster here to defeat." ;
        shouldClose = true ;
    }
    if(availableItems.empty()){
        message = "you have no item to defeat!" ; 
        shouldClose = true ; 
    }
}

bool DefeatAction::update(){

    if (shouldClose) {
        messageTimer += GetFrameTime();
        if (messageTimer >= 2.5f) {
            messageTimer = 0.0f;
            shouldClose = false;
            return true;
        }
        return false;
    }

    hoveredIndex = -1;
    float startX = 100.0f;
    float startY = 150.0f;
    float height = 30.0f;

    for(size_t i = 0 ; i < availableItems.size() ; i++){
        Rectangle rect = {startX , startY + i * height , 300 , height }; 
        if (CheckCollisionPointRec(GetMousePosition(), rect)) {
            hoveredIndex = (int)i;
            break;
        }
    }

    if(hoveredIndex != -1 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        Item chosen = availableItems[hoveredIndex] ; 
        availableItems.erase(availableItems.begin() + hoveredIndex) ;
        hoveredIndex = -1 ; 

        selectedItems.push_back(chosen) ;
        totalStrength += chosen.getStrength() ; 
        hero->removeItems(chosen) ;

        if(mode == Mode::ForInvisibleMan){
            if(totalStrength >= 9){
                invisibleMan->set_location(nullptr) ;
                message = "invisible Man defeated!" ; 
                hero->SetRemainingActions(hero->GetRemainingActions() -1); ///////////
                shouldClose = true ;                 
            }else if(availableItems.empty()){
                message = "Defeat failed! Not enough total strength.";
                shouldClose = true;
            }
            else{
                message = "select more items , total strength: " + std::to_string(totalStrength) ; 
            }
        }
        else if(mode == Mode::ForDracula){
            if(totalStrength >= 6){
                dracula->set_location(nullptr) ; 
                message = "dracula defeated!" ; 
                hero->SetRemainingActions(hero->GetRemainingActions() -1);
                shouldClose = true ;                 
            }else if(availableItems.empty()){
                message = "Defeat failed! Not enough total strength.";
                shouldClose = true;
            }
            else{
                message = "select more items , total strength: " + std::to_string(totalStrength) ; 
            }

        }

    }

    return false ;
}
void DefeatAction::draw() {
    float panelX = 80, panelY = 80, panelWidth = 800, panelHeight = 450;
    DrawRectangleRec({panelX, panelY, panelWidth, panelHeight}, Fade(DARKGRAY, 0.95f));
    DrawRectangleLinesEx({panelX, panelY, panelWidth, panelHeight}, 3, RAYWHITE);

    if (shouldClose && (message == "invisible Man defeated!" || message == "dracula defeated!")) {
        DrawText(message.c_str(), panelX + 20, panelY + 15, 30, GREEN);
        return;
    }

    Color msgColor = shouldClose ? GREEN : (mode == Mode::None ? RED : WHITE);
    DrawText(message.c_str(), panelX + 20, panelY + 15, 20, msgColor);

    float x = panelX + 20;
    float y = panelY + 60;
    float lineHeight = 30;

    std::string strengthText = "Total Strength: " + std::to_string(totalStrength);
    DrawText(strengthText.c_str(), x, y, 20, WHITE);
    y += lineHeight;

    for (size_t i = 0; i < availableItems.size(); ++i) {
        Color textColor = (hoveredIndex == static_cast<int>(i)) ? YELLOW : WHITE;
        const Item& item = availableItems[i];
        std::string text = item.getName() + " (strength: " + std::to_string(item.getStrength()) + ")";
        DrawText(text.c_str(), x, y + i * lineHeight, 20, textColor);
    }

    y += availableItems.size() * lineHeight + 20;

    // نمایش آیتم‌های انتخاب شده
    if (!selectedItems.empty()) {
        DrawText("Selected Items:", x, y, 20, GREEN);
        y += lineHeight;
        for (const auto& item : selectedItems) {
            std::string text = item.getName() + " (strength: " + std::to_string(item.getStrength()) + ")";
            DrawText(text.c_str(), x, y, 20, GREEN);
            y += lineHeight;
        }
    }
}

GuideAction::GuideAction(GameMap & map, Hero * hero): map(map) , hero(hero){}

bool GuideAction::update() {
    if (typing) {
        int key = GetCharPressed();
        while (key > 0) {
            if (key >= 32 && key <= 125)
                input += (char)key;
            key = GetCharPressed();
        }  

        if (IsKeyPressed(KEY_BACKSPACE) && !input.empty())
            input.pop_back();

        if (IsKeyPressed(KEY_ENTER)) {
            if (!step2) {
                if (input == "current" || input == "neighbor") {
                    mode = input;
                    typing = true;
                    step2 = true;
                    message = (mode == "current") ? "Enter villager name to move:" : "Choose a villager from neighbors:";
                    input = "";
                } else {
                    message = "Invalid mode. Try again: current / neighbor";
                    input = "";
                }
            } else if (step2 && !step3) {
                chosenVillager = input;
                if (mode == "current") {
                    for (auto* v : hero->villagerHere()) {
                        if (v->get_name() == chosenVillager) {
                            availablePlaces = hero->GetCurrentLocation()->get_neighbors();
                            message = "Enter neighbor name to move villager to:";
                            input = "";
                            step3 = true;
                            return false;
                        }
                    }
                    message = "Villager not found at your location.try again.";
                    input = "";
                } else if (mode == "neighbor") {
                    for (auto* neighbor : hero->GetCurrentLocation()->get_neighbors()) {
                        for (auto* v : Villager::all()) {
                            if (v->get_name() == chosenVillager && v->get_currentLocation() == neighbor) {
                                v->MoveTo(hero->GetCurrentLocation(), chosenVillager);
                                hero->SetRemainingActions(hero->GetRemainingActions() - 1);
                                return true;
                            }
                        }
                    }
                    message = "Villager not found in neighbors.try again.";
                    input = "";
                }
            } else if (step3) {
                chosenPlace = input;
                if (hero->GetCurrentLocation()->findNeighbor(chosenPlace)) {
                    Location* target = map.get_location_by_name(chosenPlace);
                    for (auto* v : hero->villagerHere()) {
                        if (v->get_name() == chosenVillager) {
                            v->MoveTo(target, chosenVillager);
                            hero->SetRemainingActions(hero->GetRemainingActions() - 1);
                            return true;
                        }
                    }
                } else
                    message = "Not a valid neighboring location.try again.";
                
                input = "";
            }
        }
    }

    return false;
}

void GuideAction::draw() {
    DrawRectangle(100, 100, 750, 250, Fade(DARKGRAY, 0.8f));
    DrawText("[Guide Action]", 120, 105, 24, RAYWHITE);
    DrawText(message.c_str(), 120, 140, 24, YELLOW);
    if(typing)
        DrawText(input.c_str(), 120, 180, 28, SKYBLUE);
    
}
