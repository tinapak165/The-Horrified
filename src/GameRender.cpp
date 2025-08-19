#include "GameRender.hpp"
#include "Game.hpp"
#include "ActionButton.hpp"
#include "SaveManager.hpp"
GameRender::GameRender(Game& game) : game(game) {
    draculaMat = LoadTexture("../Assets/Monster_Mat/DraculaMat.png");
    invisibleManMat = LoadTexture("../Assets/Monster_Mat/InvisibleManMat.png");
    coffinTex = LoadTexture("../Assets/Items/Coffins/Coffin.png"); 
      smashedCoffinTex = LoadTexture("../Assets/Items/Coffins/SmashedCoffin.png");

}

void GameRender::draw() {
     if(showingHeroInfo && currentHero != nullptr) {
        currentHero->DisplayInfo();   
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            showingHeroInfo = false;
            currentHero = nullptr;
        }
        return; 
    }

    if(currentAction && currentHero){
        bool done = currentAction->update() ; 
        currentAction->draw() ; 
        if(done){
            currentAction = nullptr ; 
            currentHero = nullptr ; 
        }
        return  ;
    }

    if(selectedLocation){
        selectedLocation->draw_info_panel() ; 
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            selectedLocation = nullptr ; 
        }
        return ;
    }
    if (ShowitemButton && currentHero) {
        currentHero->DisplayItem(); 
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            ShowitemButton = false;
            currentHero = nullptr;
        }
        return;
    }
    if (ShowPLAYEDPerkButton && currentHero) {
        currentHero->displayPlayedCards(); 
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            ShowPLAYEDPerkButton = false;
            currentHero = nullptr;
        }
        return;
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
        DrawText(text.c_str(), 100, 100, 30, GREEN);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            currentHero = nullptr;
            savegame = false;
            fileSaved = false;  
            filename = "";
        }
        return;
    }
    if(showingVillagerInfo){
        Villager::DisplayInfo() ;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            showingVillagerInfo = false;
        }
        return ;
    }
    
    
    draw_map();
    draw_heroes() ;
    draw_location_icon() ;
    
    draw_villagers();
    
    draw_monsters();
    draw_coffins();

    draw_sidebar() ;
    draw_users() ;
    draw_action_panel() ;
    draw_collected_items() ;
    draw_played_Perkcards() ;  
    draw_saveGame() ;
    draw_villagerButton() ;
    renderTerrorLevel(game.get_terror_level());
    
}

void GameRender::draw_map() {
    game.get_map().draw_map();
}
// void GameRender::draw_monster_objects(){
    
    //     static int lastDestroyed = -1;
    //     static int lastCollected = -1;
    //     auto dracula = game.get_dracula();
    //     auto invisibleMan = game.get_invisibleMan();
    //     Location* Dloc = dracula->get_location();
    //     Location* Iloc = invisibleMan->get_location();
    //     if (dracula) {
    //         int destroyed = 0;
    //         for (const auto& entry : dracula->get_coffins_map()) {
    //             if (entry.second) destroyed++;
    //         }
    //         if (destroyed != lastDestroyed) { // فقط وقتی تغییر کرد
    //         std::cout << "[DEBUG] Reached before GAME_LOG" << std::endl;
    //         GAME_LOG_OBJ(game , "Dracula location : " + Dloc->get_name());
    //         GAME_LOG_OBJ(game, "Coffins destroyed (Dracula): " + std::to_string(destroyed) + "/4");
    //         std::cout << "[DEBUG] Passed after GAME_LOG" << std::endl;
    //             lastDestroyed = destroyed;
    //         }
    //     }
    //     if (invisibleMan) {
    //     int collected = invisibleMan->get_evidence_count();
    //     if (collected != lastCollected) { // فقط وقتی تغییر کرد
    //         GAME_LOG_OBJ(game, "Evidence collected (Invisible Man): " + std::to_string(collected) + "/5");
    //         lastCollected = collected;
    //     }
    // }
 

void GameRender::draw_sidebar() {
    Rectangle mapRect = game.get_map().get_drawn_rect();

    int sidebarX = mapRect.x + mapRect.width + 10;
    int sidebarY = mapRect.y; 
    int sidebarWidth = 400;
    int sidebarHeight = mapRect.height;

 // پس زمینه برای ساید بار
    DrawRectangle(sidebarX, mapRect.y, sidebarWidth, sidebarHeight, Fade(WHITE, 0.15f));

    const auto& card = game.get_current_card();
    int cardBoxY = mapRect.y + 20;
    int cardBoxHeight = 290;

    // پس‌زمینه کارت
    DrawRectangle(sidebarX + 10, cardBoxY, sidebarWidth - 20, cardBoxHeight, Fade(BLACK, 0.2f));


    if (card) {
        DrawText("Monster Card:", sidebarX + 20, cardBoxY + 10, 20, BLACK);

      Texture2D tex = card->get_texture();
if (tex.id != 0) {
    float aspect = (float)tex.width / (float)tex.height;
    float destHeight = cardBoxHeight - 60;
    float destWidth = destHeight * aspect;

    float destX = sidebarX + (sidebarWidth - destWidth) / 2 - 20;
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

    // 📦 موقعیت و ابعاد جعبه‌ی لاگ
    float padding = 10.0f;
    float logBoxX = sidebarX ;  
    float logBoxY = sidebarY + sidebarHeight / 2 ;   // نیمه پایین سایدبار
    float logBoxWidth  = sidebarWidth - 2*padding;  // فاصله از چپ و راست
    float logBoxHeight = sidebarHeight / 2 - 2*padding; 

    float effectBoxWidth  = std::min(sidebarWidth - 2*padding, sidebarWidth  - padding);
    float effectBoxHeight = std::min(logBoxHeight - 2*padding, sidebarHeight - logBoxY - padding);

    // موقعیت داخل سایدبار
    float effectBoxX = sidebarX + padding;
    float effectBoxY = logBoxY + padding;

    DrawRectangleRounded({effectBoxX, effectBoxY, effectBoxWidth - 100, effectBoxHeight}, 
                        0.15f, 6, GRAY);

    // 📝 عنوان داخل کادر
    DrawText("MonsterCard Effects :", effectBoxX + 10, effectBoxY + 10, 20, RED);

    int y = logBoxY + 70 ;
    int maxLines = (logBoxHeight  - 40 ) / 25;
    int count = 0;

    for (const auto& log : game.get_logs()) {
        std::istringstream iss(log);
        std::string word, currentLine;
      
        while (iss >> word) {
            if (currentLine.length() + word.length() + 1 <= 32) {
                if (!currentLine.empty()) currentLine += " ";
                currentLine += word;
            } else {
                DrawText(currentLine.c_str(), sidebarX, y, 16, RAYWHITE);
                y += 24;
                count++;
                if (count >= maxLines) return;
                currentLine = word;
            }
        }

        if (!currentLine.empty()) {
            DrawText(currentLine.c_str(), sidebarX, y, 16, RAYWHITE);
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

            // نشون دادن حالت Frenzied
            if (monster == frenzied && !frenziedDrawn) {
                DrawRectangleLinesEx(dest, 2.0f, RED);
                frenziedDrawn = true;
            }

            // کلیک روی هیولا برای نمایش تصویر
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

        // دکمه بستن
        Rectangle closeBtn = { matX + matW - 40, matY + 10, 30, 30 };
        DrawRectangleRec(closeBtn, MAROON);
        DrawText("X", closeBtn.x + 7, closeBtn.y + 2, 24, WHITE);

        // بستن فقط وقتی کلیک رها شد
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            Vector2 mp = GetMousePosition();
            if (CheckCollisionPointRec(mp, closeBtn) || !CheckCollisionPointRec(mp, matArea)) {
                selectedMonsterMat = MonsterType::None;
            }
        }
     }
  }
}

void GameRender::draw_saveGame()
{
    Rectangle saveGame = { 650, 60, 200, 45 }; 
    Vector2 mouse = GetMousePosition();
    bool hover = CheckCollisionPointRec(mouse, saveGame);

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
    Rectangle vill = { 650, 100, 200, 45 }; 
    Vector2 mouse = GetMousePosition();
    bool hover = CheckCollisionPointRec(mouse, vill);

    Color btnColor = hover ? LIGHTGRAY : GRAY;
    DrawRectangleRec(vill, btnColor);
    DrawText("villagers", vill.x + 10, vill.y + 10, 20, BLACK);

    if (hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        showingVillagerInfo = true ;
    }  
}
void GameRender::draw_villagers() {
    const float villagerSize = 90.0f;  
    const float spacing = 10.0f;
    const float textOffsetY = 5.0f;  // فاصله کم بین عکس و اسم
    const int fontSize = 16;       // فونت کوچیک‌تر

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

            // محاسبه متن و باکس پس‌زمینه
            int textWidth = MeasureText(v->get_name().c_str(), fontSize);
            int textX = dest.x + (villagerSize - textWidth) / 2;  // وسط‌چین زیر عکس
            int textY = dest.y + villagerSize + textOffsetY;

            DrawRectangle(textX - 2, textY - 2, textWidth + 4, fontSize + 4, Fade(BLACK, 0.5f));
            DrawText(v->get_name().c_str(), textX, textY, fontSize, WHITE);

            currentOffsetX += villagerSize + spacing;
        }
    }
}




void GameRender::draw_collected_items(){
    Rectangle itemButton = { 750, 120, 170, 40 }; 
    Vector2 mouse = GetMousePosition();
    bool hover = CheckCollisionPointRec(mouse, itemButton);

    Color btnColor = hover ? LIGHTGRAY : GRAY;
    DrawRectangleRec(itemButton, btnColor);
    DrawText("Items collected", itemButton.x + 10, itemButton.y + 10, 20, BLACK);

    if (hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        ShowitemButton = true;
        currentHero = game.get_turnManager().get_active_hero(); 
    }

}

     
  



void GameRender::draw_heroes() {
    const float heroSize = 100.0f; // سایز مناسب‌تر
    const float spacing = 30.0f;  // فاصله بین چند هیرو در یک مکان
    const float offsetY = -heroSize - 5.0f; // کمی بالاتر از لوکیشن

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

    ClickableText user1(p1.name,{90, 90} , 40, BLACK);
    ClickableText user2(p2.name,{90, 150} , 40, BLACK);

    Vector2 mouse = GetMousePosition();

    user1.Draw(mouse);
    user2.Draw(mouse);

    if (user1.isClicked(mouse, IsMouseButtonPressed(MOUSE_LEFT_BUTTON))) {
        showingHeroInfo = true ; 
        currentHero = p1.hero ; 
    }

    if (user2.isClicked(mouse, IsMouseButtonPressed(MOUSE_LEFT_BUTTON))) {
        showingHeroInfo = true ; 
        currentHero = p2.hero ; 
    } 
}


void GameRender::draw_action_panel() {
    Hero* activeHero = game.get_turnManager().get_active_hero();

    std::string heroName = activeHero->GetName();
    int remaining = activeHero->GetRemainingActions();
    int maxActions = activeHero->getMaxActions();

    std::string infoText = heroName + " | Actions left: " + std::to_string(remaining) + "/" + std::to_string(maxActions);

    std::vector<ActionButton> actionButtons = {
        {"Move", {50, 500, 120, 40}},
        {"Special", {190, 500, 120, 40}},
        {"Guide", {330, 500, 120, 40}},
        {"Pickup", {50, 550, 120, 40}},
        {"Advance", {190, 550, 120, 40}},
        {"Defeat", {330, 550, 120, 40}},
        {"Perk", {50, 600, 120, 40}},
        {"Help", {190, 600, 120, 40}},
        {"Quit", {330, 600, 120, 40}},
    };

    DrawRectangle(40, 480, 420, 180, Fade(DARKGRAY, 0.9f));
    DrawRectangleLines(40, 480, 420, 180, GRAY);
    Vector2 mousepos = GetMousePosition();

    DrawText(infoText.c_str(), 50, 460, 20, BLACK);

    bool hasActionsLeft = (remaining > 0);

    for (const auto& button : actionButtons) {
        bool hovered = CheckCollisionPointRec(mousepos, button.bounds);

        Color buttonColor;
        if (!hasActionsLeft ) {
            buttonColor = DARKGRAY;
        } else {
            buttonColor = hovered ? LIGHTGRAY : GRAY;
        }

        DrawRectangleRec(button.bounds, buttonColor);
        DrawText(button.label.c_str(), button.bounds.x + 10, button.bounds.y + 10, 20, BLACK);

        if ( hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && hasActionsLeft) { 
            handle_action(button.label, activeHero);
        }
    }
}

void GameRender::handle_action(const std::string& action , Hero* h){

    if (action == "Help") {
        currentHero = h ; 
        currentAction = std::make_unique<HelpAction>(currentHero) ;
 
    } else if (action == "Quit") { 
        game.set_currentPhase(Phase::MonsterPhase) ; 
        game.set_HeroTurnInProgress(false) ; 
        game.get_turnManager().next_turn() ; 

    } else if (action == "Perk") {
        currentHero = h ; 
        currentAction = std::make_unique<ChoosePerkCardAction>(currentHero , game) ;

    } else if (action == "Move") {

        currentHero = h ; 
        currentAction = std::make_unique<MoveAction>(game.get_map() , currentHero) ;

    } else if (action == "Guide") {
        currentHero = h ; 
        currentAction = std::make_unique<GuideAction>(game.get_map() , currentHero) ;
    } else if (action == "Pickup") {

        currentHero = h ; 
        currentAction = std::make_unique<PickUpAction>(currentHero) ;

    } else if (action == "Special") {
        
        currentHero = h ; 
        currentAction = std::make_unique<SpecialAction>(currentHero , game.get_map()) ;

    } else if (action == "Advance") {

        currentHero = h ; 
        currentAction = std::make_unique<AdvanceAction>(currentHero , game.get_dracula() , game.get_pool() , game.get_map() ,game.get_invisibleMan());

    } else if (action == "Defeat") {

        currentHero = h ; 
        currentAction = std::make_unique<DefeatAction>(currentHero, game.get_invisibleMan(), game.get_dracula());
    }
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

        // آیکون لوکیشن
        DrawTextureEx(loc->get_icon_texture(), screenPos, 0.0f, mapScale, WHITE);

        // اگر کلیک شد، نمایش پنل اطلاعات
        if (CheckCollisionPointRec(mousePos, transformed) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            selectedLocation = loc.get() ;
        }
    }
}


std::vector<ActionButton> GameRender::get_actionButtons(){
    return actionButtons;
}


void GameRender::draw_played_Perkcards(){

    Rectangle perkButton = { 750 , 180, 195, 40 }; 
    Vector2 mouse = GetMousePosition();
    bool hover = CheckCollisionPointRec(mouse, perkButton);

    Color btnColor = hover ? LIGHTGRAY : GRAY;
    DrawRectangleRec(perkButton, btnColor);
    DrawText("Perkcards played", perkButton.x + 10, perkButton.y + 10, 20, BLACK);

    if (hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        ShowPLAYEDPerkButton = true;
        currentHero = game.get_turnManager().get_active_hero(); 
    }
}

void GameRender::draw_available_Perkcards(){
    Rectangle perkButton = { 750, 50, 210, 45 }; 
    Vector2 mouse = GetMousePosition();
    bool hover = CheckCollisionPointRec(mouse, perkButton);

    Color btnColor = hover ? LIGHTGRAY : GRAY;
    DrawRectangleRec(perkButton, btnColor);
    DrawText("available Perkcards", perkButton.x + 10, perkButton.y + 10, 20, BLACK);

    if (hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        ShowAvailablePerkButton = true;
        currentHero = game.get_turnManager().get_active_hero(); 
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
    
    // رسم دایره قرمز روی عدد
    DrawCircle(pos.x, pos.y, 7 , RED);
    
    
}


GameRender::~GameRender(){
    if(currentHero) delete currentHero ; 
    if(selectedLocation) delete selectedLocation ; 
    UnloadTexture(draculaMat);
    UnloadTexture(invisibleManMat);
    UnloadTexture(coffinTex); 
    UnloadTexture(smashedCoffinTex); 
}
