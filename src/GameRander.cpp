#include "GameRander.hpp"

GameRender::GameRender(Game& game) : game(game) {}

void GameRender::draw() {
    if (showingHeroInfo && currentHero != nullptr) {
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

    
    draw_map();
    draw_heroes() ;
    draw_location_icon() ;
    draw_items();
    draw_villagers();
    draw_monsters();
    draw_monster_card();
    draw_users() ;
    draw_action_panel() ; 
}

void GameRender::draw_map() {
    game.get_map().draw_map();   
}

void GameRender::draw_monsters() {
    const float monsterSize = 28.0f; 
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
        monstersAtLocation[kv.second->get_location()].push_back(kv.second);
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
                frenziedDrawn = true; // فقط یک بار بکشه
            }

            currentOffsetY -= spacing;
        }
    }
}


void GameRender::draw_villagers() {
    for (const auto& loc : game.get_map().get_locations()) {
        Rectangle area = loc->get_clickable_area();
        float offsetX = 8;
        float offsetY = 30;
        float spacing = 18.0f;
        int i = 0;

        for (Villager* v : loc->get_villagers()) {
            Texture2D tex = v->getTexture();
            Rectangle src = { 0, 0, (float)tex.width, (float)tex.height };
            Rectangle dest = { area.x + offsetX + i * (18 + spacing), area.y + offsetY, 18, 18 };
            DrawTexturePro(tex, src, dest, {0, 0}, 0.0f, WHITE);
            ++i;
        }
    }
}

void GameRender::draw_items() {
    for (const auto& loc : game.get_map().get_locations()) {
        Rectangle area = loc->get_clickable_area();
        float offsetX = 8;
        float offsetY = 8;
        float spacing = 4.0f;

        int iconSize = 14;
        int iconsPerRow = 3;

        int i = 0;
        for (const auto& item : loc->get_items()) {
            Texture2D tex = item.getTexture();
            Rectangle src = { 0, 0, (float)tex.width, (float)tex.height };

            int row = i / iconsPerRow;
            int col = i % iconsPerRow;

            Rectangle dest = {
                area.x + offsetX + col * (iconSize + spacing),
                area.y + offsetY + row * (iconSize + spacing),
                (float)iconSize,
                (float)iconSize
            };

            DrawTexturePro(tex, src, dest, {0, 0}, 0.0f, WHITE);
            ++i;
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

    } else if (action == "Perk") {
        game.ChoosePerkCardANDplay(h);
    } else if (action == "Move") {

        currentHero = h ; 
        currentAction = std::make_unique<MoveAction>(game.get_map() , currentHero) ;

    } else if (action == "Guide") {
        h->GuideAction(h, game.get_map());
    } else if (action == "Pickup") {
        h->PickupItems();
        h->DisplayItem();
    } else if (action == "Special") {
        h->Special(h, game.get_map());
    } else if (action == "Advance") {
        h->AdvanceAction(h, game.get_dracula(), game.get_pool(), game.get_map(), game.get_invisibleMan());
    } else if (action == "Defeat") {
        h->DefeatAction(h, game.get_invisibleMan(), game.get_dracula());
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

    for (const auto& loc : game.get_map().get_locations()) {
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
            selectedLocation = loc.get();
        }
    }
}


GameRender::~GameRender(){
    if(currentHero) delete currentHero ; 
    if(selectedLocation) delete selectedLocation ; 
}

void GameRender::draw_What_Happend_In_Text(){
    // یه تابعی که اتفاقات افتاده شده توی هر فاز گیم رو بنویسه.
}