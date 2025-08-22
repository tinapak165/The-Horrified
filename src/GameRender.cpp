#include "GameRender.hpp"

GameRender::GameRender(Game& game) : game(game) {
    draculaMat = LoadTexture("../Assets/Monster_Mat/DraculaMat.png");
    invisibleManMat = LoadTexture("../Assets/Monster_Mat/InvisibleManMat.png");
    coffinTex = LoadTexture("../Assets/Items/Coffins/Coffin.png"); 
    smashedCoffinTex = LoadTexture("../Assets/Items/Coffins/SmashedCoffin.png");

}

void GameRender::draw() {

    if(handleDisplays())
        return ;
        
    draw_map();
    draw_heroes() ;
    draw_sidebar() ;
    draw_location_icon() ;
    draw_villagers();
    draw_monsters();
    draw_coffins();
    draw_users() ;
    draw_action_panel() ;
    draw_collected_items() ;
    draw_played_Perkcards() ;  
    draw_saveGame() ;
    draw_villagerButton() ;
    Draw_Backtomenu();
    Draw_HelpButton();
    renderTerrorLevel(game.get_terror_level());
}

void GameRender::draw_map() {
    game.get_map().draw_map();   
}
bool GameRender::handleDisplays()
{
    if(showingHeroInfo && currentHero != nullptr) {
        currentHero->DisplayInfo();   
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            showingHeroInfo = false;
            currentHero = nullptr;
        }
        return true; 
    }

    if(currentAction && currentHero){
        bool done = currentAction->update() ; 
        currentAction->draw() ; 
        if(done){
            currentAction = nullptr ; 
            currentHero = nullptr ; 
        }
        return true ;
    }

    if(selectedLocation){
        selectedLocation->draw_info_panel() ; 
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            selectedLocation = nullptr ; 
        }
        return true;
    }
    if (ShowitemButton && currentHero) {
        currentHero->DisplayItem(); 
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            ShowitemButton = false;
            currentHero = nullptr;
        }
        return true;
    }
    if (ShowPLAYEDPerkButton && currentHero) {
        currentHero->displayPlayedCards(); 
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            ShowPLAYEDPerkButton = false;
            currentHero = nullptr;
        }
        return true;
    }
    if(ShowHelp){
        game.Help();
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            ShowHelp = false ;
        return true;
    }

    if (savegame && currentHero) {
        SaveManager save(game);

        if (!fileSaved) {
            filename = save.generateNextFile();
            save.registerSaveFiles(filename) ;
            save.saveGame(filename);
            fileSaved = true;
        }

        std::string text = "Game saved to: " + filename;
        DrawText(text.c_str(), 1095, 355, 20, GREEN);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            currentHero = nullptr;
            savegame = false;
            fileSaved = false;  
            filename = "";
        }
        return true; 
    }

    if(showingVillagerInfo){
        Villager::DisplayInfo() ;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            showingVillagerInfo = false;
        }
        return true;
    }
    return false ;
}
void GameRender::Draw_Backtomenu() {

    std::unique_ptr<ClickableText> BackToMenu = std::make_unique<ClickableText>("Back to menu", Vector2{100, 900} ,30, WHITE);

    BackToMenu->Draw() ;

    if(BackToMenu->isClicked()){
        ClearBackground(BLACK);
        game.ResetGame();
        game.ready();
        game.get_menu()->SetState(std::move(std::make_unique<MenuState>())) ;
    }
}
void GameRender::draw_sidebar() {
    Rectangle mapRect = game.get_map().get_drawn_rect();

    int sidebarX = mapRect.x + mapRect.width + 10;
    int sidebarY = mapRect.y; 
    int sidebarWidth = 400;
    int sidebarHeight = mapRect.height;

    DrawRectangle(sidebarX, mapRect.y, sidebarWidth, sidebarHeight, Fade(BLACK, 0.5f));

    const auto& card = game.get_current_card();
    int cardBoxY = mapRect.y ;
    int cardBoxHeight = 290;

    if (card) {
        DrawText("Monster Card:", sidebarX + 20, cardBoxY + 10, 20, RED);

        Texture2D tex = card->get_texture();
        if (tex.id != 0) {
            float aspect = (float)tex.width / (float)tex.height;
            float destHeight = cardBoxHeight - 60;
            float destWidth = destHeight * aspect;

            float destX = sidebarX + (sidebarWidth - destWidth) / 2 - 50;
            float destY = cardBoxY + 40;

            Rectangle src = {0, 0, (float)tex.width, (float)tex.height};
            Rectangle dest = {destX, destY, destWidth, destHeight};
            DrawTexturePro(tex, src, dest, {0,0}, 0.0f, WHITE);

        
            float boxWidth  = destWidth;
            float boxHeight = 70; 
            float boxX = destX;
            float boxY = destY + destHeight + 15; 

            DrawRectangleRounded({boxX, boxY, boxWidth, boxHeight}, 0.2f, 6, GRAY);

        
            auto dracula = game.get_dracula();
            auto invisibleMan = game.get_invisibleMan();

            if (dracula) {
                int destroyed = 0;
                for (const auto& entry : dracula->get_coffins_map()) {
                    if (entry.second) destroyed++;
                }
                DrawText(("Coffins: " + std::to_string(destroyed) + "/4").c_str(),
                        boxX + 10, boxY + 10, 18, BLACK);
            }

            if (invisibleMan) {
                int collected = invisibleMan->get_evidence_count();
                DrawText(("Evidence: " + std::to_string(collected) + "/5").c_str(),
                        boxX + 10, boxY + 35, 18, BLACK);
            }
        }

    } 
 
    float padding = 10.0f;
    float logBoxX = sidebarX ;  
    float logBoxY = sidebarY + sidebarHeight / 2 ;   
    float logBoxWidth  = sidebarWidth - 2*padding; 
    float logBoxHeight = sidebarHeight / 2 - 2*padding; 

    float effectBoxWidth  = std::min(sidebarWidth - 2*padding, sidebarWidth  - padding);
    float effectBoxHeight = std::min(logBoxHeight - 2*padding, sidebarHeight - logBoxY - padding);

    float effectBoxX = sidebarX + padding ;
    float effectBoxY = logBoxY + padding - 100; 

    DrawRectangleRounded({effectBoxX, effectBoxY, effectBoxWidth - 100, effectBoxHeight}, 
                        0.15f, 6, GRAY);

    
    DrawText("MonsterCard Effects :", effectBoxX + 10, effectBoxY + 10, 20, RED);

    int y = effectBoxY + 30;   
    int maxLines = (effectBoxHeight - 20) / 25; 
    int count = 0;

    for (const auto& log : game.get_logs()) {
        std::istringstream iss(log);
        std::string word, currentLine;

        while (iss >> word) {
            if (currentLine.length() + word.length() + 1 <= 32) {
                if (!currentLine.empty()) currentLine += " ";
                currentLine += word;
            } else {
                
                DrawText( currentLine.c_str(),effectBoxX , y, 16, RAYWHITE);
                y += 24;
                count++;
                if (count >= maxLines) return;
                currentLine = word;
            }
        }

        if (!currentLine.empty()) {
           
            DrawText(currentLine.c_str(),effectBoxX , y, 16, RAYWHITE);
            y += 24;
            count++;
            if (count >= maxLines) return;
        }
    }

}

void GameRender::draw_monsters() {
    const float monsterSize = 50.0f; 
    const float spacing = 30.0f;  
    const float offsetY = -monsterSize - 5.0f;

    Texture2D mapTex = game.get_map().get_mapTexture();
    float mapScale = std::min(
        (float)GetScreenWidth() / mapTex.width,
        (float)GetScreenHeight() / mapTex.height
    );
    float mapDrawX = (GetScreenWidth() - mapTex.width * mapScale) / 2.0f;
    float mapDrawY = (GetScreenHeight() - mapTex.height * mapScale) / 2.0f;

    std::unordered_map<Location*, std::vector<Monster*>> monstersAtLocation;

    for (const auto& kv : game.get_monsters()) {
        if (!kv.second || !kv.second->get_location()) continue;

        auto& vec = monstersAtLocation[kv.second->get_location()];
        if (std::find(vec.begin(), vec.end(), kv.second) == vec.end()) {
            vec.push_back(kv.second);
        }
    }

    Monster* frenzied = game.get_frenzied_monster();
    bool frenziedDrawn = false;

   
    for (const auto& [loc, monsters] : monstersAtLocation) {
        Rectangle baseArea = loc->get_clickable_area();
        Vector2 locPos = {
            mapDrawX + baseArea.x * mapScale,
            mapDrawY + baseArea.y * mapScale
        };

        float currentOffsetY = offsetY;

        for (Monster* monster : monsters) {
            Texture2D tex = monster->getTexture();
            Rectangle src = { 0, 0, (float)tex.width, (float)tex.height };

            Rectangle dest = {
                locPos.x,
                locPos.y + currentOffsetY,
                monsterSize,
                monsterSize
            };

            DrawTexturePro(tex, src, dest, {0, 0}, 0.0f, WHITE);

            if (monster == frenzied && !frenziedDrawn) {
                DrawRectangleLinesEx(dest, 2.0f, RED);
                frenziedDrawn = true;
            }

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), dest)) {
                selectedMonsterMat = monster->get_type();  
            }

            currentOffsetY -= spacing;
        }
    }

   if (selectedMonsterMat != MonsterType::None) {
    Texture2D* matTex = nullptr;
    if (selectedMonsterMat == MonsterType::Dracula) 
        matTex = &draculaMat;
    else if (selectedMonsterMat == MonsterType::InvisibleMan) 
        matTex = &invisibleManMat;

    if (matTex) {
        float matW = 500;
        float matH = 500 * ((float)matTex->height / matTex->width);
        float matX = (GetScreenWidth() - matW) / 2;
        float matY = (GetScreenHeight() - matH) / 2;

        Rectangle matArea = {matX, matY, matW, matH};
        DrawTexturePro(*matTex, {0, 0, (float)matTex->width, (float)matTex->height}, matArea, {0, 0}, 0, WHITE);

        Rectangle closeBtn = { matX + matW - 40, matY + 10, 30, 30 };
        DrawRectangleRec(closeBtn, MAROON);
        DrawText("X", closeBtn.x + 7, closeBtn.y + 2, 24, WHITE);

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            Vector2 mp = GetMousePosition();
            if (CheckCollisionPointRec(mp, closeBtn)) {
                selectedMonsterMat = MonsterType::None;
            }
        }
     }
  }
}
void GameRender::draw_villagers() {
    const float villagerSize = 90.0f;  
    const float spacing = 10.0f;
    const float textOffsetY = 5.0f;   
    const int fontSize = 16;          

    Texture2D mapTex = game.get_map().get_mapTexture();
    float mapScale = std::min(
        (float)GetScreenWidth() / mapTex.width,
        (float)GetScreenHeight() / mapTex.height
    );
    float mapDrawX = (GetScreenWidth() - mapTex.width * mapScale) / 2.0f;
    float mapDrawY = (GetScreenHeight() - mapTex.height * mapScale) / 2.0f;

    for (const auto& loc : game.get_map().get_locations()) {
        Rectangle baseArea = loc->get_clickable_area();
        Vector2 locPos = {
            mapDrawX + baseArea.x * mapScale,
            mapDrawY + baseArea.y * mapScale
        };

        float currentOffsetX = 0.0f;

        for (Villager* v : loc->get_villagers()) {
            Texture2D tex = v->getTexture();
            Rectangle src = { 0, 0, (float)tex.width, (float)tex.height };
            Rectangle dest = {
                locPos.x + currentOffsetX,
                locPos.y,
                villagerSize,
                villagerSize
            };

            DrawTexturePro(tex, src, dest, {0, 0}, 0.0f, WHITE);

            int textWidth = MeasureText(v->get_name().c_str(), fontSize);
            int textX = dest.x + (villagerSize - textWidth) / 2;  // وسط‌چین زیر عکس
            int textY = dest.y + villagerSize + textOffsetY;

            DrawRectangle(textX - 2, textY - 2, textWidth + 4, fontSize + 4, Fade(BLACK, 0.5f));
            DrawText(v->get_name().c_str(), textX, textY, fontSize, WHITE);

            currentOffsetX += villagerSize + spacing;
        }
    }
}

void GameRender::draw_monster_card() {
    const auto& card = game.get_current_card();
    if (!card) return;

    Texture2D tex = card->get_texture();
    Rectangle src = { 0, 0, (float)tex.width, (float)tex.height };
    Rectangle dest = { 620, 20, 200, 300 }; 
    Vector2 origin = { 0, 0 };

    DrawTexturePro(tex, src, dest, origin, 0.0f, WHITE);
}
void GameRender::draw_heroes() {
    const float heroSize = 100.0f; 
    const float spacing = 30.0f; 
    const float offsetY = -heroSize - 5.0f;

    for (const auto& loc : game.get_map().get_locations()) {
        Vector2 locPos = loc->get_screenPos();
        float currentOffsetY = offsetY;

        for (Hero* hero : game.get_turnManager().get_heroes()) {
            if (!hero || hero->GetCurrentLocation() != loc.get()) continue;

            Texture2D tex = hero->getTexture();
            Rectangle src = { 0, 0, (float)tex.width, (float)tex.height };

            Rectangle dest = {
                locPos.x,
                locPos.y + currentOffsetY,
                heroSize,
                heroSize
            };

            DrawTexturePro(tex, src, dest, {0, 0}, 0.0f, WHITE);

            if (hero == game.get_turnManager().get_active_hero()) {
                DrawRectangleLinesEx(dest, 2.0f, BLACK);
            }

            currentOffsetY -= spacing;
        }
    }
}
void GameRender::draw_users(){
    auto p1 = game.getPlayer1() ;
    auto p2 = game.getPlayer2() ; 

    ClickableText user1(p1.name,{90, 80} , 40, BLACK);
    ClickableText user2(p2.name,{90, 140} , 40, BLACK);

    user1.Draw();
    user2.Draw();

    if (user1.isClicked()) {
        showingHeroInfo = true ; 
        currentHero = p1.hero ; 
    }

    if (user2.isClicked()) {
        showingHeroInfo = true ; 
        currentHero = p2.hero ; 
    } 
}


void GameRender::draw_action_panel() {
    Hero* activeHero = game.get_turnManager().get_active_hero();

    std::vector<ActionButton> actionButtons = {
        {"Move", {0, 250, 90, 40}},
        {"Special", {0, 300, 90, 40}},
        {"Guide", {0, 350, 90, 40}},
        {"Pickup", {0, 400, 90, 40}},
        {"Advance", {0, 450, 90, 40}},
        {"Defeat", {0, 500, 90, 40}},
        {"Perk", {0, 550, 90, 40}},
        {"Help", {0, 600, 90, 40}},
        {"Quit", {0, 650, 90, 40}},
    };
    std::string infoText = activeHero->GetName() + " | Actions: " + std::to_string(activeHero->GetRemainingActions()) + "/" + std::to_string(activeHero->getMaxActions());

    DrawText(infoText.c_str(), 1095, 900, 20, WHITE);

    bool hasActionsLeft = (activeHero->GetRemainingActions() > 0);

    for (const auto& button : actionButtons) {
        bool hovered = CheckCollisionPointRec(GetMousePosition(), button.bounds);

        Color buttonColor;
        if (!hasActionsLeft ) 
            buttonColor = DARKGRAY;
        else 
            buttonColor = hovered ? LIGHTGRAY : WHITE;
        
        DrawRectangleRec(button.bounds, buttonColor);
        DrawText(button.label.c_str(), button.bounds.x + 3, button.bounds.y + 10, 20, BLACK);

        if ( hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && hasActionsLeft) 
            handle_action(button.label, activeHero);  
    }
}

void GameRender::handle_action(const std::string& action , Hero* h){

    currentHero = h ; 
    Factory factory(game);
    currentAction = factory.createAction(action , currentHero);
}

void GameRender::draw_location_icon() {
    float mapScale = 1.0f;
    float mapDrawX = 0.0f;
    float mapDrawY = 0.0f;

    Vector2 mousePos = GetMousePosition();
    Texture2D mapTex = game.get_map().get_mapTexture();

    mapScale = std::min(
        (float)GetScreenWidth() / mapTex.width,
        (float)GetScreenHeight() / mapTex.height
    );
    mapDrawX = (GetScreenWidth() - mapTex.width * mapScale) / 2.0f;
    mapDrawY = (GetScreenHeight() - mapTex.height * mapScale) / 2.0f;

    for ( const auto& loc : game.get_map().get_locations()) {
        Rectangle baseArea = loc->get_clickable_area();

        Vector2 screenPos = {
            mapDrawX + baseArea.x * mapScale,
            mapDrawY + baseArea.y * mapScale
        };

        loc->set_screenPos(screenPos);  

        Rectangle transformed = {
            screenPos.x,
            screenPos.y,
            baseArea.width * mapScale,
            baseArea.height * mapScale
        };

        DrawTextureEx(loc->get_icon_texture(), screenPos, 0.0f, mapScale, WHITE);

        if (CheckCollisionPointRec(mousePos, transformed) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            selectedLocation = loc.get() ;
        }
    }
}

void GameRender::draw_collected_items(){
    Rectangle itemButton = { 900, 80, 170, 40 }; 
    bool hover = CheckCollisionPointRec(GetMousePosition(), itemButton);

    Color btnColor = hover ? LIGHTGRAY : GRAY;
    DrawRectangleRec(itemButton, btnColor);
    DrawText("Items collected", itemButton.x + 10, itemButton.y + 10, 20, BLACK);

    if (hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        ShowitemButton = true;
        currentHero = game.get_turnManager().get_active_hero(); 
    }

}
void GameRender::Draw_HelpButton()
{
    Rectangle HelpButton = { 720, 80, 170, 40 }; 
    bool hover = CheckCollisionPointRec(GetMousePosition(), HelpButton);

    Color btnColor = hover ? LIGHTGRAY : GRAY;
    DrawRectangleRec(HelpButton, btnColor);
    DrawText("Help", HelpButton.x + 10, HelpButton.y + 10, 20, BLACK);

    if (hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        ShowHelp = true;
    }
}

void GameRender::draw_played_Perkcards(){

    Rectangle perkButton = { 900, 30, 170, 40 }; 
    Vector2 mouse = GetMousePosition();
    bool hover = CheckCollisionPointRec(mouse, perkButton);

    Color btnColor = hover ? LIGHTGRAY : GRAY;
    DrawRectangleRec(perkButton, btnColor);
    DrawText("Perkcards", perkButton.x + 10, perkButton.y + 10, 20, BLACK);

    if (hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        ShowPLAYEDPerkButton = true;
        currentHero = game.get_turnManager().get_active_hero(); 
    }
}

void GameRender::draw_saveGame()
{
    Rectangle saveGame = { 720, 30, 170, 40 }; 
    bool hover = CheckCollisionPointRec(GetMousePosition(), saveGame);

    Color btnColor = hover ? LIGHTGRAY : GRAY;
    DrawRectangleRec(saveGame, btnColor);
    DrawText("save game", saveGame.x + 10, saveGame.y + 10, 20, BLACK);

    if (hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        savegame = true;
        currentHero = game.get_turnManager().get_active_hero(); 
    }  
}

void GameRender::draw_villagerButton()
{
    Rectangle vill = { 600, 30, 100, 40 }; 
    Vector2 mouse = GetMousePosition();
    bool hover = CheckCollisionPointRec(mouse, vill);

    Color btnColor = hover ? LIGHTGRAY : GRAY;
    DrawRectangleRec(vill, btnColor);
    DrawText("villagers", vill.x + 10, vill.y + 10, 20, BLACK);

    if (hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        showingVillagerInfo = true ;
    }  
}

void GameRender::draw_coffins() {

    Dracula* drac = dynamic_cast<Dracula*>(game.get_monsters()[MonsterType::Dracula]);

    const auto& coffins = drac->get_coffins_map();

    Texture2D mapTex = game.get_map().get_mapTexture();
    float mapScale = std::min(
        (float)GetScreenWidth() / mapTex.width,
        (float)GetScreenHeight() / mapTex.height
    );
    float mapDrawX = (GetScreenWidth() - mapTex.width * mapScale) / 2.0f;
    float mapDrawY = (GetScreenHeight() - mapTex.height * mapScale) / 2.0f;

    for (const auto& [locName, destroyed] : coffins) {

        Location* loc = game.get_map().get_location_by_name(locName);
        if (!loc) continue;

        Rectangle baseArea = loc->get_clickable_area();
        Vector2 locPos = {
            mapDrawX + baseArea.x * mapScale,
            mapDrawY + baseArea.y * mapScale
        };
        
        float coffinSize = 30.0f;
        Rectangle dest = { locPos.x, locPos.y - 40, coffinSize, coffinSize };
        Texture2D& coffin = destroyed ? smashedCoffinTex : coffinTex;
        DrawTexturePro(coffin, {0,0,(float)coffin.width,(float)coffin.height}, dest, {0,0}, 0, WHITE);
    }
}

const Vector2 GameRender::terrorLevelPositions[8] = {
    {135, 60},  // 0
    {195, 60},  // 1
    {255, 60},  // 2
    {315, 60},  // 3
    {375, 60},  // 4
    {435, 60},  // 5
    {495, 60},  // 6
    {555, 60}   // جمجمه
};


void GameRender::renderTerrorLevel(int terrorLevel) {

    Vector2 pos = terrorLevelPositions[terrorLevel];
    DrawCircle(pos.x, pos.y, 7 , RED);
    
}

GameRender::~GameRender()
{
    if(currentHero) delete currentHero ; 
    if(selectedLocation) delete selectedLocation ; 
    UnloadTexture(draculaMat);
    UnloadTexture(invisibleManMat);
    UnloadTexture(coffinTex); 
    UnloadTexture(smashedCoffinTex);
    actionButtons.clear();
}