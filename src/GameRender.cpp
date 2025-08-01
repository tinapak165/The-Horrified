#include "GameRender.hpp"

GameRender::GameRender(Game& game) : game(game) {}

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
    if (ShowAvailablePerkButton && currentHero) {
        currentHero->displayavailblecards(); 
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            ShowAvailablePerkButton = false;
            currentHero = nullptr;
        }
        return;
    }
    if(savegame && currentHero){
        game.SaveGame();
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            currentHero = nullptr ; savegame = false  ;
        }
    }
     draw_map();
    draw_heroes() ;
    draw_sidebar() ;
    draw_location_icon() ;
    draw_villagers();
    draw_monsters();

    draw_users() ;
    draw_action_panel() ;
    draw_collected_items() ;
    draw_played_Perkcards() ;  
    draw_available_Perkcards() ;
    draw_saveGame() ;
}

void GameRender::draw_map() {
    game.get_map().draw_map();   
}
void GameRender::draw_sidebar() {
    Rectangle mapRect = game.get_map().get_drawn_rect();

    int sidebarX = mapRect.x + mapRect.width + 10;
    int sidebarWidth = 400;
    int sidebarHeight = mapRect.height;

    // پس‌زمینه ساده برای sidebar
    DrawRectangle(sidebarX, mapRect.y, sidebarWidth, sidebarHeight, Fade(BLACK, 0.15f));

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
        } else {
            DrawText("Texture not loaded!", sidebarX + 20, cardBoxY + 50, 20, RED);
        }
    } else {
        DrawText("No Monster Card", sidebarX + 20, cardBoxY + 10, 20, GRAY);
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
}

void GameRender::draw_villagers() {
    const float villagerSize = 90.0f;  
    const float spacing = 10.0f;
    const float textOffsetY = 5.0f;    // فاصله کم بین عکس و اسم
    const int fontSize = 16;           // فونت کوچیک‌تر

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

void GameRender::draw_monster_card() {
    const auto& card = game.get_current_card();
    if (!card) return;

    Texture2D tex = card->get_texture();
    Rectangle src = { 0, 0, (float)tex.width, (float)tex.height };
    Rectangle dest = { 620, 20, 200, 300 }; // کنار نقشه، بالا سمت راست
    Vector2 origin = { 0, 0 };

    DrawTexturePro(tex, src, dest, origin, 0.0f, WHITE);
}
void GameRender::draw_heroes() {
    const float heroSize = 100.0f; 
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
        h->GuideAction(h, game.get_map());
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
void GameRender::draw_played_Perkcards(){

    Rectangle perkButton = { 750, 180, 195, 40 }; 
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

GameRender::~GameRender(){
    if(currentHero) delete currentHero ; 
    if(selectedLocation) delete selectedLocation ; 
}
