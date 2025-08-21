#include "Action.hpp"

void HeroAction::DrawPanel()
{
    float panelX = 100, panelY = 75, panelWidth = 600, panelHeight = 400;
    DrawRectangleRec({panelX, panelY, panelWidth, panelHeight}, Fade(DARKGRAY, 0.95f));
    DrawRectangleLinesEx({panelX, panelY, panelWidth, panelHeight}, 3, RAYWHITE);
}

bool HeroAction::drawCancelButton(){
    ClickableText Backbutton("Cancel" , {110 , 400} , 20 , RAYWHITE) ;
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
    DrawText(message.c_str(), 110, y, 20, color);
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

    DrawText("[Playing Move Action]" , 120 , 105 , 24 , RAYWHITE) ;
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
                if (currentCard->get_name() == "Break of Dawn") 
                    game.set_skipMonsterPhase(true);

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
        if (frameCounter >= 60) 
            return true;
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
    auto& availablePerks = hero->GetAvailablePerkCards();

    for (size_t i = 0; i < availablePerks.size(); ++i) {
        Rectangle cardRect = {110.0f + i * 220.0f, 160.0f, 200.0f, 300.0f};
        DrawTexturePro(
            availablePerks[i]->get_texture(),
            {0, 0, (float)availablePerks[i]->get_texture().width, (float)availablePerks[i]->get_texture().height},
            cardRect, {0, 0}, 0.0f, WHITE);
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

    std::string locName = hero->GetCurrentLocation()->get_name();

    if(locName == "Cave" || locName == "Dungeon" || locName == "Crypt" || locName == "Graveyard" ){
        mode = Mode::ForDracula ;
        for(auto& item : hero->GetItems() ){
            if(item.getColor() == ItemColor::Red) 
                availableRedItems.push_back(item);
        }
        totalStrength = 0 ; 
        selectedItems.clear() ; 
        set_message("Select items with total strength >= 6 to destroy coffin.\n Your red items:");
    }
    else if(locName == "Precinct") { 
        mode = Mode::ForInvisibleMan ;
            for (auto& item : hero->GetItems()) {
                std::string loc = item.getLocationName();
                if (loc == "Inn" || loc == "Barn" || loc == "Institute" || loc == "Laboratory" || loc == "Mansion") 
                    evidenceItems.push_back(item);
            }
            evidencePlaced = false;
            set_message("Select an item to place as evidence against Invisible Man.");
    }
    else{
        mode = Mode::None ; 
        set_message("You can not perform advance action here.");
    }
}
void AdvanceAction::checkforDestroyingCoffin(){
    if (totalStrength >= 6) {
        dracula->destroy_coffin_at(hero->GetCurrentLocation()->get_name());
        for (auto& item : selectedItems) 
            pool.add_item(item);
            
        hero->SetRemainingActions(hero->GetRemainingActions() -1); 
        set_message("Coffin destroyed successfully!");
        set_ShouldClose(true);
    }
    else 
        set_message("Select more items (total strength >= 6)");
}
bool AdvanceAction::update(){

    if(handleShouldClose()) return true ; 

    if (mode == Mode::None) {
        set_ShouldClose(true);
        return false;
    }

    if (waitingForAbility) {
        if (IsKeyPressed(KEY_Y)) {
            pendingAbilityItem.setStrength(pendingAbilityItem.getStrength() + 1);
            set_message("Item boosted.");
        }
        else if (IsKeyPressed(KEY_N)) {
            set_message("No boost applied.");
        }
        else  return false;

        waitingForAbility = false;

        selectedItems.push_back(pendingAbilityItem);
        totalStrength += pendingAbilityItem.getStrength();
        hero->removeItems(pendingAbilityItem);

        checkforDestroyingCoffin() ;

        return false;
    }

    if (mode == Mode::ForDracula) {

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

            checkforDestroyingCoffin() ;
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

        for (size_t i = 0; i < evidenceItems.size(); ++i) {
            Rectangle rect = { 100.0f, 150.0f + i * 30.0f, 300, 30.0f };
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
                set_message("Evidence from that location already exists.Choose another.");
        }
    }
    return false;
}

void AdvanceAction::draw() {

    DrawPanel() ;

    if(drawCancelButton()){
        set_message("Advance canceled");
        set_ShouldClose(true) ;
    }
    Color messageColor = get_shouldClose() ? GREEN : (mode == Mode::None ? RED : WHITE);
    DrawMessage(120 , messageColor) ;

    float y = 145;

    if (mode == Mode::ForDracula) {

        std::string strengthMsg = "Total Strength: " + std::to_string(totalStrength);
        DrawText(strengthMsg.c_str(), 300, 400, 22, BLACK);
        y += 30;

        for (size_t i = 0; i < availableRedItems.size(); ++i) {
            Color textColor = (hoveredIndex == static_cast<int>(i)) ? YELLOW : WHITE;

            const Item& item = availableRedItems[i];
            std::string text = item.getName() + " (strength: " + std::to_string(item.getStrength()) + ")";
            DrawText(text.c_str(), 120, y + i * 30, 20, textColor);
        }
    }
    else if(mode == Mode::ForInvisibleMan) {

        for (size_t i = 0; i < evidenceItems.size(); ++i) {
            Color textColor = (hoveredEvidenceIndex == static_cast<int>(i)) ? YELLOW : WHITE;

            const Item& item = evidenceItems[i];
            std::string text = item.getName() + " (from: " + item.getLocationName() + ")";
            DrawText(text.c_str(), 120, y + i * 30, 20, textColor);
        }
    }
}

void DefeatAction::checkForStrength(int str , std::string who){
    if(totalStrength >= str){
        if(who == "dracula")  dracula->set_location(nullptr) ; 
        if(who == "invisible man")  invisibleMan->set_location(nullptr) ; 

        set_message( who + " defeated!") ; 
        hero->SetRemainingActions(hero->GetRemainingActions() -1);
        set_ShouldClose(true) ; 
    }
    else if(availableItems.empty()){
        set_message("Defeat failed! Not enough total strength.");
        set_ShouldClose(true) ; 
    }
    else set_message("select more items , total strength: " + std::to_string(totalStrength) ); 

}

DefeatAction::DefeatAction(Hero * h , InvisibleMan *i, Dracula * d) : hero(h) , invisibleMan(i) , dracula(d){

    if(invisibleMan->get_location() == h->GetCurrentLocation() ){ 
        mode = Mode::ForInvisibleMan ;
        if (invisibleMan->can_be_defeated()) {
            set_message("Defeat Invisible Man: use red items(total strength >= 9).\nYour red items:\n");
            for(auto& item : hero->GetItems() ){
                if(item.getColor() == ItemColor::Red)
                    availableItems.push_back(item) ;
            }
        }
        else{
            set_message("you can not defeat invisible man.") ;
            set_ShouldClose(true) ; 
        }
    }
    else if (dracula->get_location() == hero->GetCurrentLocation()) {
        mode = Mode::ForDracula;
        if(dracula->can_be_defeated()){
            for (auto& item : hero->GetItems()) {
                if (item.getColor() == ItemColor::Yellow)
                    availableItems.push_back(item);
            }
            set_message("Defeat Dracula: use yellow items(total strength >= 6)\nYour yellow items:\n");
        }else{
            set_message("You must destroy all coffins first to defeat Dracula.");
            set_ShouldClose(true) ;
        }
    }
    else{
        mode = Mode::None ; 
        set_message("No monster here to defeat.") ;
        set_ShouldClose(true) ; 
    }
}

bool DefeatAction::update(){

    if(handleShouldClose()) return true ;

    if (waitingForAbility) {
        if (IsKeyPressed(KEY_Y)) {
            pendingAbilityItem.setStrength(pendingAbilityItem.getStrength() + 1);
            set_message("Item boosted.");
        }
        else if (IsKeyPressed(KEY_N)) 
            set_message("No boost applied.");
        
        else  return false;

        waitingForAbility = false;

        totalStrength += pendingAbilityItem.getStrength();
        hero->removeItems(pendingAbilityItem);

        if (mode == Mode::ForInvisibleMan) 
            checkForStrength(9, "invisible man");
        else if (mode == Mode::ForDracula) 
            checkForStrength(6, "dracula");
    
        return false;
    }
    if(mode == Mode::ForDracula){
        hoveredIndex = -1;

        for (size_t i = 0; i < availableItems.size(); ++i) {
            Rectangle rect = { 100.0f, 150.0f + i * 30.0f, 300, 30.0f };
            if (CheckCollisionPointRec(GetMousePosition(), rect)) {
                hoveredIndex = (int)i;
                break;
            }
        }
        if(hoveredIndex != -1 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            Item chosen = availableItems[hoveredIndex] ; 
            availableItems.erase(availableItems.begin() + hoveredIndex) ;
            hoveredIndex = -1 ;

            if (hero->HasAbility()) {
                pendingAbilityItem = chosen;
                set_message("Do you want to boost " + chosen.getName() + "? [Y/N]");
                waitingForAbility = true;
                return false ;
            }
            totalStrength += chosen.getStrength() ; 
            hero->removeItems(chosen) ;

            checkForStrength(6 , "dracula") ;
        }
    }

    if(mode == Mode::ForInvisibleMan){
        hoveredIndex = -1;

        for (size_t i = 0; i < availableItems.size(); ++i) {
            Rectangle rect = { 100.0f, 150.0f + i * 30.0f, 300, 30.0f };
            if (CheckCollisionPointRec(GetMousePosition(), rect)) {
                hoveredIndex = (int)i;
                break;
            }
        }
        if(hoveredIndex != -1 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            Item chosen = availableItems[hoveredIndex] ; 
            availableItems.erase(availableItems.begin() + hoveredIndex) ;
            hoveredIndex = -1 ;

            if (hero->HasAbility()) {
                pendingAbilityItem = chosen;
                set_message("Do you want to boost " + chosen.getName() + "? [Y/N]");
                waitingForAbility = true;
                return false ;
            }
            totalStrength += chosen.getStrength() ; 
            hero->removeItems(chosen) ;

            checkForStrength(9 , "invisible man") ;
        }
    }
    return false ;
}
void DefeatAction::draw() {

    DrawPanel() ;

    std::string strengthMsg = "Total Strength: " + std::to_string(totalStrength);
    DrawText(strengthMsg.c_str(), 300, 400, 22, BLACK);

    if(drawCancelButton()){
        set_message("Defeat canceled");
        set_ShouldClose(true) ;
    }
    if (get_shouldClose() && (get_message() == "invisible Man defeated!" || get_message() == "dracula defeated!")) {
        DrawMessage(95 , GREEN) ;
        return;
    }

    Color msgColor = get_shouldClose() ? GREEN : (mode == Mode::None ? RED : WHITE);
    DrawMessage(95 , msgColor) ;

    float y = 140;
    y += 30;

    for (size_t i = 0; i < availableItems.size(); ++i) {
        Color textColor = (hoveredIndex == static_cast<int>(i)) ? YELLOW : WHITE;
        const Item& item = availableItems[i];
        std::string text =  item.getName() + " (strength: " + std::to_string(item.getStrength()) + ")" ;
        DrawText(text.c_str() , 120 ,y + i * 30  , 22 , textColor);
    }
    y += availableItems.size() * 30 + 20;
}

GuideAction::GuideAction(GameMap & map, Hero * hero): map(map) , hero(hero){
    input.clear();
    chosenPlace.clear();
    chosenVillager.clear();
    step = GuideStep::ChooseMode ;
    set_message("Choose mode: current / neighbor");
}
bool GuideAction::update() {

    if(handleShouldClose()) return true ;

    if (!typing) return false;

    input = type(input);

    if (IsKeyPressed(KEY_ENTER)) {
        switch (step) {
        case GuideStep::ChooseMode:
            if (input == "current" || input == "neighbor") {
                mode = input;
                step = GuideStep::ChooseVillager;
                set_message(mode == "current" ? "Enter villager name to move:" : "Choose a villager from neighbors:");
            } else 
                set_message("Invalid mode. Try again: current / neighbor");
            
            input.clear();
            break;

        case GuideStep::ChooseVillager:
            chosenVillager = input;
            if (mode == "current") {
                bool found = false;
                for (auto* v : hero->villagerHere()) {
                    if (v->get_name() == chosenVillager) {
                        step = GuideStep::ChoosePlace;
                        set_message("Enter neighbor name to move villager to:");
                        found = true;
                        break;
                    }
                }
                if (!found) set_message("Villager not found here. Try again.");
            }
            else if (mode == "neighbor") {
                for (auto* neighbor : hero->GetCurrentLocation()->get_neighbors()) {
                    for (auto* v : Villager::all()) {
                        if (v->get_name() == chosenVillager && v->get_currentLocation() == neighbor) {
                            v->MoveTo(hero->GetCurrentLocation(), chosenVillager);
                            hero->SetRemainingActions(hero->GetRemainingActions() - 1);
                            return true;
                        }
                    }
                }
                set_message("Villager not found in neighbors. Try again.");
            }
            input.clear();
            break;

        case GuideStep::ChoosePlace:
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
            } else  set_message("Not a valid neighboring location. Try again.");
            
            input.clear();
        }
    }
    return false;
}

void GuideAction::draw() {
    DrawPanel() ;
    if(drawCancelButton()){
        set_message("Guide canceled");
        set_ShouldClose(true) ;
    }
    DrawText("[Guide Action]", 120, 105, 24, RAYWHITE);
    DrawMessage(140 , YELLOW) ;
    if(typing) 
        DrawTypingText(input) ; 
}