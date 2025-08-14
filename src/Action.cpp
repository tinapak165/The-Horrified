#include "Action.hpp"

void HeroAction::DrawPanel()
{
    float panelX = 80, panelY = 80, panelWidth = 600, panelHeight = 400;
    DrawRectangleRec({panelX, panelY, panelWidth, panelHeight}, Fade(DARKGRAY, 0.95f));
    DrawRectangleLinesEx({panelX, panelY, panelWidth, panelHeight}, 3, RAYWHITE);
}

bool HeroAction::drawCancelButton(){
    ClickableText Backbutton("Cancel" , {100 , 400} , 20 , RAYWHITE) ;
    Backbutton.Draw() ; 
    if(Backbutton.isClicked()) 
        return true ; 
    return false ;
}

bool HeroAction::drawDoneButton(){
    ClickableText button("Done" , {250 , 400} , 20 , RAYWHITE) ;
    button.Draw() ; 
    if(button.isClicked()) 
        return true ; 
    return false ;
}

void HeroAction::DrawMessage(int y , Color color){
    DrawText(message.c_str(), 100, y, 20, color);
}
void HeroAction::DrawTypingText(const std::string &text) {

    DrawText(text.c_str(), 120, 180, 28, BLUE);
    if ((int)(GetTime() * 2) % 2 == 0) {  
        int textWidth = MeasureText(text.c_str(), 28);
        DrawText("|", 120 + textWidth + 2, 180, 28, BLUE);
    }
}

void HeroAction::set_message(std::string msg){ message = msg ; }
std::string HeroAction::get_message(){ return message; }

std::string HeroAction::type(std::string input){
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

bool HeroAction::handleShouldClose()
{
    if (shouldClose) {
        messageTimer += GetFrameTime();
        if (messageTimer >= 1.0f) {
            return true; 
        }
        return false; 
    }  
    return false ;
}

void HeroAction::set_ShouldClose(bool val){ shouldClose = val ; }
bool HeroAction::get_shouldClose(){ return shouldClose ;}

MoveAction::MoveAction(GameMap &map, Hero *hero): map(map) , hero(hero){
    set_message("Which neighboring place do you want to move to?");
    chosenPlace.clear();
}

bool MoveAction::update(){

    if(handleShouldClose()) return true ;

    Location* currentLoc = hero->GetCurrentLocation();

    if (typing) {

        chosenPlace = type(chosenPlace) ;

        if (IsKeyPressed(KEY_ENTER)) {
            chosenLocation = map.get_location_by_name(chosenPlace);

            if ( (chosenLocation && currentLoc->findNeighbor(chosenPlace)) ) {
                typing = false;

                if (hero->hasvillagerHere()) {
                    askVillager = true;
                    set_message("Some villagers are with you. Move them too? [Y/N]");
                } else 
                    moveFinished = true;
            } else {
                set_message("Invalid location! Where do you want to go?");
                chosenPlace.clear();
            }
        }
    }
    if (askVillager) {
        if (IsKeyPressed(KEY_Y)) {
            moveWithVillager = true;
            askVillager = false;
            moveFinished = true;
        }
        else if (IsKeyPressed(KEY_N)) {
            moveWithVillager = false;
            askVillager = false;
            moveFinished = true;
        }
    }

    if (moveFinished) {
        if (moveWithVillager) 
            hero->MoveTo(chosenLocation, hero->villagerHere());
        else 
            hero->MoveTo(chosenLocation);
        
        hero->SetRemainingActions(hero->GetRemainingActions() -1) ;
        return true;
    }
    return false; 
}

void MoveAction::draw(){
    DrawPanel() ;

    if(drawCancelButton()){
        set_message("Move canceled");
        set_ShouldClose(true) ;
    }

    DrawText("[Playing Move Action]" , 115 , 105 , 24 , RAYWHITE) ;
    DrawMessage(130 , RAYWHITE) ;
    if(typing) 
        DrawTypingText(chosenPlace) ;
}

HelpAction::HelpAction(Hero * hero): hero(hero){}

bool HelpAction::update(){

    hero->DisplayActions();
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
        return true;
    return false;
}
void HelpAction::draw() {}

PickUpAction::PickUpAction(Hero* h) : hero(h) {
    set_message("Click an item to pick up");
    itemList = &hero->GetCurrentLocation()->get_items();
    if (itemList->empty()) {
        set_message("No items to pick up!");
        set_ShouldClose(true) ;
    }
}

bool PickUpAction::update() {

    if(handleShouldClose()) return true ;

    for (size_t i = 0; i < itemHitboxes.size(); ++i) {
        if (CheckCollisionPointRec(GetMousePosition(), itemHitboxes[i]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            hero->GetItems().push_back((*itemList)[i]);
            set_message("Picked up " + (*itemList)[i].getName());
            
            itemList->erase(itemList->begin() + i);
            ChoseAnItem = true ; 

            if (itemList->empty()) {
                set_message("No more items.");
                set_ShouldClose(true);
                hero->SetRemainingActions(hero->GetRemainingActions() - 1);
            }
        }
    }
    return false;
}

void PickUpAction::draw() {

    DrawPanel() ; 
    if(drawCancelButton()){
        set_message("PickUp canceled");
        if(ChoseAnItem)
                hero->SetRemainingActions(hero->GetRemainingActions() - 1);
        set_ShouldClose(true) ;
    }
    int y = 120;

    DrawMessage(y , RAYWHITE);

    if(drawDoneButton()){
        set_message("PickUp done");
        hero->SetRemainingActions(hero->GetRemainingActions() - 1);
        set_ShouldClose(true) ;
    } 
    y += 30;

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

ChoosePerkCardAction::ChoosePerkCardAction(Hero* h , Game& game) : hero(h) , game(game) {}

bool ChoosePerkCardAction::update() {

    auto& availablePerks = hero->GetAvailablePerkCards();

    if (!done && availablePerks.empty()) {
        set_message("No perk cards available!");
        done = true;
        return false;
    }
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
            if (CheckCollisionPointRec(GetMousePosition(), cardRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {

                currentCard = std::move(availablePerks[i]);
                availablePerks.erase(availablePerks.begin() + i);                
                set_message("playing: " + currentCard->get_name());
                if (currentCard->get_name() == "Break of Dawn") {
                    game.set_skipMonsterPhase(true);
                }

                return false;
            }
        }
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            set_message("Perkcard canceled");
            done = true;
            return false;
        }        
    }

    if (done) { 
        frameCounter++;
        if (frameCounter >= 60) {
            return true;
        }
    }
    return false;
}


void ChoosePerkCardAction::draw() {

    DrawPanel() ;
    DrawText("[Playing Perk]", 120 , 105, 28, RAYWHITE);
    if (currentCard) {
        currentCard->draw(); 
        return;
    }
    DrawText("Choose a Perk Card:", 120, 135, 28, YELLOW);

    auto& availablePerks = hero->GetAvailablePerkCards();

    for (size_t i = 0; i < availablePerks.size(); ++i) {
        Rectangle cardRect = {110.0f + i * 220.0f, 160.0f, 200.0f, 300.0f};
        DrawTexturePro(
            availablePerks[i]->get_texture(),
            {0, 0, (float)availablePerks[i]->get_texture().width, (float)availablePerks[i]->get_texture().height},
            cardRect,
            {0, 0},
            0.0f,
            WHITE
        );
    }
    DrawMessage(155 , GREEN) ;
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
    DrawPanel() ;
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
            if(item.getColor() == ItemColor::Red) 
                availableRedItems.push_back(item);
        }
        totalStrength = 0 ; 
        selectedItems.clear() ; 
        set_message("Select Red items with total strength >= 6 to destroy coffin.");
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
            set_message("Select an item to place as evidence against Invisible Man.");
    }
    else{
        mode = Mode::None ; 
        set_message("You cannot perform advance action here.");
    }

}
bool AdvanceAction::update() {

    if(handleShouldClose()) return true ; 
    if (mode == Mode::None) {
        set_ShouldClose(true);
        return false;
    }

    if (waitingForAbility) {
        if (IsKeyPressed(KEY_Y)) {
            pendingAbilityItem.setStrength(pendingAbilityItem.getStrength() + 1);
            set_message("Item boosted.");
            waitingForAbility = false;
        }
        else if (IsKeyPressed(KEY_N)) {
            set_message("No boost applied.");
            waitingForAbility = false;
        }
        else 
            return false;
        

        selectedItems.push_back(pendingAbilityItem);
        totalStrength += pendingAbilityItem.getStrength();
        hero->removeItems(pendingAbilityItem);

        if (totalStrength >= 6) {
            dracula->destroy_coffin_at(hero->GetCurrentLocation()->get_name());
            for (auto& item : selectedItems) {
                pool.add_item(item);
            }
            hero->SetRemainingActions(hero->GetRemainingActions() -1); 
            set_message("Coffin destroyed successfully!");
            set_ShouldClose(true);
        }
        else 
            set_message("Select more red items (total strength >= 6)");

        return false;
    }

    if (mode == Mode::ForDracula) {
        if (availableRedItems.empty()) {
            set_message("You have no red items!");
            set_ShouldClose(true);
            return false;
        }

        hoveredIndex = -1;

        for (size_t i = 0; i < availableRedItems.size(); ++i) {
            Rectangle rect = { 100.0f, 150.0f + i * 30.0f, 300, 30.0f };
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
                set_message("Do you want to boost " + chosen.getName() + "? [Y/N]");
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
                set_message("Coffin destroyed successfully!");
                set_ShouldClose(true);
            }
            else 
                set_message("Select more red items (total strength >= 6)");

        }
    }

    // InvisibleMan:
    else if (mode == Mode::ForInvisibleMan) {
        if (evidenceItems.empty()) {
            set_message("You have no valid evidence items!");
            set_ShouldClose(true);
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
                set_message("Evidence placed successfully.");
                evidencePlaced = true;
                set_ShouldClose(true);
            } else 
                set_message("Evidence from that location already exists. Choose another.");
        }
    }
    return false;
}

void AdvanceAction::draw() {

    DrawPanel() ;

    if (( get_shouldClose() && get_message() == "Evidence placed successfully." || get_message() == "Coffin destroyed successfully!")) {
        DrawMessage(95 , GREEN) ;
        return;
    }

    float y = 140;

    if (mode == Mode::ForDracula) {

        set_message("Total Strength: " + std::to_string(totalStrength));
        DrawMessage(140 , BLACK) ;
        y += 30;

        for (size_t i = 0; i < availableRedItems.size(); ++i) {
            Color textColor = (hoveredIndex == static_cast<int>(i)) ? YELLOW : WHITE;

            const Item& item = availableRedItems[i];
            set_message( item.getName() + " (strength: " + std::to_string(item.getStrength()) + ")");
            DrawMessage( 140 + i * 30 , textColor) ;

        }

        y += availableRedItems.size() * 30 + 20;
        if (!selectedItems.empty()) {
            DrawText("Selected Items:", 100, y, 20, BLACK);
            y += 30;
            for (const auto& item : selectedItems) {
                set_message( item.getName() + " (strength: " + std::to_string(item.getStrength()) + ")");
                DrawMessage(140 , GREEN) ;
                y += 30;
            }
        }

    } else if (mode == Mode::ForInvisibleMan) {

        for (size_t i = 0; i < evidenceItems.size(); ++i) {
            Color textColor = (hoveredEvidenceIndex == static_cast<int>(i)) ? YELLOW : WHITE;

            const Item& item = evidenceItems[i];
            set_message( item.getName() + " (from: " + item.getLocationName() + ")");
            DrawMessage(y + i * 30 , textColor) ;
        }
    }

    Color messageColor = get_shouldClose() ? GREEN : (mode == Mode::None ? RED : WHITE);
    DrawMessage( 140 , messageColor) ;
}

DefeatAction::DefeatAction(Hero * h , InvisibleMan *i, Dracula * d) : hero(h) , invisibleMan(i) , dracula(d){

    if(i && i->get_location() == h->GetCurrentLocation() ){ 
        mode = Mode::ForInvisibleMan ;
         if (invisibleMan->can_be_defeated()) {
            set_message("You are ready to defeat the Invisible Man! Use Red items (total strength >= 9).");
            auto items = hero->GetItems() ;
            for(auto& item : items){
                if(item.getColor() == ItemColor::Blue)
                availableItems.push_back(item) ;
            }
        }
        else{
            set_message("you can not defeat invisible man.") ;
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
            set_message("Defeat Dracula: select yellow items (total strength >= 6)");
        }else{
            set_message("You must destroy all coffins first to defeat Dracula.");
        }
    }
    else{
        mode = Mode::None ; 
        set_message("No monster here to defeat.") ;
        shouldClose = true ;
    }
    if(availableItems.empty()){
        set_message("you have no item to defeat!") ; 
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
                set_message("invisible Man defeated!") ; 
                hero->SetRemainingActions(hero->GetRemainingActions() -1);
                shouldClose = true ;                 
            }else if(availableItems.empty()){
                set_message("Defeat failed! Not enough total strength.");
                shouldClose = true;
            }
            else{
                set_message("select more items , total strength: " + std::to_string(totalStrength)) ; 
            }
        }
        else if(mode == Mode::ForDracula){
            if(totalStrength >= 6){
                dracula->set_location(nullptr) ; 
                set_message("dracula defeated!") ; 
                hero->SetRemainingActions(hero->GetRemainingActions() -1);
                shouldClose = true ;                 
            }else if(availableItems.empty()){
                set_message("Defeat failed! Not enough total strength.");
                shouldClose = true;
            }
            else
                set_message("select more items , total strength: " + std::to_string(totalStrength) ); 

        }

    }
    return false ;
}
void DefeatAction::draw() {

    DrawPanel() ;

    if (shouldClose && (get_message() == "invisible Man defeated!" || get_message() == "dracula defeated!")) {
        DrawMessage(95 , GREEN) ;
        return;
    }

    Color msgColor = shouldClose ? GREEN : (mode == Mode::None ? RED : WHITE);
    DrawMessage(95 , msgColor) ;

    float y = 140;
    y += 30;

    for (size_t i = 0; i < availableItems.size(); ++i) {
        Color textColor = (hoveredIndex == static_cast<int>(i)) ? YELLOW : WHITE;
        const Item& item = availableItems[i];
        set_message( item.getName() + " (strength: " + std::to_string(item.getStrength()) + ")" );
        DrawMessage(y + i * 30 , textColor) ;
    }

    y += availableItems.size() * 30 + 20;

    if (!selectedItems.empty()) {
        DrawText("Selected Items:", 100 , y, 20, GREEN);
        y += 30;
        for (const auto& item : selectedItems) {
            set_message( item.getName() + " (strength: " + std::to_string(item.getStrength()) + ")" );
            DrawMessage(y , GREEN) ;
            y += 30;
        }
    }
}

GuideAction::GuideAction(GameMap & map, Hero * hero): map(map) , hero(hero){
    set_message( "Choose mode: current/ neighbor");
}

bool GuideAction::update() {
    if (typing) {

        input = type(input) ;

        if (IsKeyPressed(KEY_ENTER)) {
            if (!step2) {
                if (input == "current" || input == "neighbor") {
                    mode = input;
                    typing = true;
                    step2 = true;
                    set_message( (mode == "current") ? "Enter villager name to move:" : "Choose a villager from neighbors:");
                    input.clear();
                } else {
                    set_message( "Invalid mode. Try again: current / neighbor" );
                    input.clear();
                }
            } else if (step2 && !step3) {
                chosenVillager = input;
                if (mode == "current") {
                    for (auto* v : hero->villagerHere()) {
                        if (v->get_name() == chosenVillager) {
                            availablePlaces = hero->GetCurrentLocation()->get_neighbors();
                            set_message("Enter neighbor name to move villager to:");
                            input.clear();
                            step3 = true;
                            return false;
                        }
                    }
                    set_message("Villager not found at your location.try again.");
                    input.clear();
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
                    set_message("Villager not found in neighbors.try again.");
                    input.clear();
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
                } else set_message( "Not a valid neighboring location.try again." );
                
                input.clear();
            }
        }
    }
    return false;
}

void GuideAction::draw() {
    DrawPanel() ;
    DrawText("[Guide Action]", 120, 105, 24, RAYWHITE);
    DrawMessage(140 , YELLOW) ;
    if(typing)
        DrawText(input.c_str(), 120, 180, 28, SKYBLUE);    
}