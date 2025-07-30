#include "GameRender.hpp"
#include "Game.hpp"
#include "ActionButtons.hpp"
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
    if (ShowitemButton && currentHero) {
        currentHero->DisplayItem(); 
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            ShowitemButton = false;
            currentHero = nullptr;
        }
        return;
    }


    draw_map();
    // draw_sidebar();
    draw_heroes() ;
    draw_location_icon() ;
    draw_collected_items();
    draw_villagers();
    draw_monsters();
    draw_monster_card();
    draw_users() ;
   
}
void GameRender::draw_map() {
    game.get_map().draw_map();
    
  
}
void GameRender::draw_sidebar() {
    

  // اول مستطیل رسم‌شده نقشه رو می‌گیریم
Rectangle mapRect = game.get_map().get_drawn_rect();

// حالا sidebar رو دقیقاً می‌ذاریم کنار نقشه
int sidebarX = mapRect.x + mapRect.width + 10;    // فاصله 10px از نقشه
int sidebarWidth = 400;
int sidebarHeight = mapRect.height;               // هم‌اندازه با ارتفاع نقشه

// پس‌زمینه کلی sidebar
DrawRectangle(sidebarX, mapRect.y, sidebarWidth, sidebarHeight, Fade(BLACK, 0.15f));

// ========================= بخش کارت =========================
const auto& card = game.get_current_card();
int cardBoxY = mapRect.y + 20;          // با توجه به موقعیت نقشه
int cardBoxHeight = 290;
DrawRectangle(sidebarX + 10, cardBoxY, sidebarWidth - 20, cardBoxHeight, Fade(BLACK, 0.2f));

DrawText("Monster Card:", sidebarX + 20, cardBoxY + 10, 20, BLACK);
std::cout<<"before monster card draaw";
if (!card) std::cout<<"1"<<std::endl;
if (card) {
    Texture2D tex = card->get_texture();
    float aspect = (float)tex.width / (float)tex.height;
    float destHeight = cardBoxHeight - 60;
    float destWidth = destHeight * aspect;

    float destX = sidebarX + (sidebarWidth - destWidth) / 2;  // وسط‌چین
    float destY = cardBoxY + 40;

    Rectangle src = {0, 0, (float)tex.width, (float)tex.height};
    Rectangle dest = {destX, destY, destWidth, destHeight};
    DrawTexturePro(tex, src, dest, {0,0}, 0.0f, BLACK);
    std::cout<<" after monster card draaw";
}

// ========================= بخش اتفاقات =========================
int eventsBoxY = cardBoxY + cardBoxHeight + 10;
int eventsBoxHeight = sidebarHeight - (cardBoxHeight + 40);
DrawRectangle(sidebarX + 10, eventsBoxY, sidebarWidth - 20, eventsBoxHeight, Fade(BLACK, 0.2f));
DrawText("Events:", sidebarX + 20, eventsBoxY + 20, 20, BLACK);

// نمایش ۵ لاگ آخر
auto logs = game.get_last_events(5);
int y = eventsBoxY + 50;
for (const auto& log : logs) {
    DrawText(log.c_str(), sidebarX + 20, y, 16, WHITE);
    y += 22;
}
int DiceBoxY = cardBoxY + cardBoxHeight + 20;
int DiceBoxHeight = eventsBoxHeight - 40 ;
DrawRectangle(sidebarX + 10, DiceBoxY, sidebarWidth - 20, DiceBoxHeight, Fade(BLACK, 0.2f));
DrawText("Dice Result:", sidebarX + 20, eventsBoxY + 40, 20, BLACK);

    
    if (card) {
        DrawText(card->get_last_dice_result().c_str(), sidebarX + 20, 1015, 18, WHITE);
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


//  tina action panel without buttons
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
    // پس‌زمینه پنل
    DrawRectangle(40, 480, 420, 180, Fade(DARKGRAY, 0.9f));
    DrawRectangleLines(40, 480, 420, 180, GRAY);
    DrawText(infoText.c_str(), 50, 460, 20, BLACK);

    // فقط رسم دکمه‌ها (هیچ ورودی و کلیک اینجا نیست)
   // توی لوپ رسم دکمه‌ها:
for (const auto& button : actionButtons) {
    bool hovered = CheckCollisionPointRec(GetMousePosition(), button.bounds);
    Color buttonColor = (remaining > 0) ? (hovered ? LIGHTGRAY : GRAY) : DARKGRAY;
    DrawRectangleRec(button.bounds, buttonColor);
    DrawText(button.label.c_str(), button.bounds.x + 10, button.bounds.y + 10, 20, BLACK);

    if (hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && remaining > 0) {
        if (!currentAction) {  // فقط وقتی اکشن قبلی تموم شده
            if (button.label == "Pickup") {
                currentAction = std::make_unique<PickUpAction>(activeHero);
            } 
            else if (button.label == "Move") {
                currentAction = std::make_unique<MoveAction>(currentHero);
            } 
            else if (button.label == "Perk") {
                currentAction = std::make_unique<ChoosePerkCardAction>(currentHero);
            } 
            else if (button.label == "Special") {
                currentAction = std::make_unique<SpecialAction>(currentHero);
            } 
            else if (button.label == "Advance") {
                // currentAction = std::make_unique<>(currentHero);
            } 
            else if (button.label == "Quit") {
                // currentAction = std::make_unique<Quit>(currentHero);
            }
            
        }
    }
}

// توی فانکشن draw یا update بازی:
if (currentAction) {
    bool done = currentAction->update();
    currentAction->draw();
    if (done) {
        currentAction = nullptr;
        // مثلا ممکنه نوبت به بازیکن بعدی بره
    }
}


}

   void GameRender::handle_action(const std::string& action, Hero* h) {
       
       std::cout << "[renderer.handle_action] Handling action for button: " << action << std::endl;

       if (action == "Help") {
           currentAction = std::make_unique<HelpAction>(h);
           std::cout<<" [ in action = help]";
            bool done = currentAction->update(); 
                    currentAction->draw(); 
        } 
        else if (action == "Quit") { 
            game.get_turnManager().next_turn();
            return; // دیگه ادامه نمی‌دیم
        } 
        else if (action == "Perk") {
            
            
            h->SetRemainingActions(h->getMaxActions() -1);
        } 
        else if (action == "Move") {
            currentAction = std::make_unique<MoveAction>(game.get_map(), h);
        } 
        else if (action == "Guide") {
            // noy yet
            
        } 
   else if (action == "Pickup") {
            currentAction = std::make_unique<PickUpAction>(h);
             currentAction->update(); 
                    currentAction->draw(); 
        }      
        else if (action == "Special") {
            currentAction = std::make_unique<SpecialAction>(h, game.get_map());
 
                } 
                else if (action == "Defeat") {
                    //not yet
                }
                
                 if(currentAction && currentHero){
                    bool done = currentAction->update(); 
                    currentAction->draw(); 
                    if(done){
                        currentAction = nullptr; 
                        if (currentHero->GetRemainingActions() <= 0) {
                            game.get_turnManager().next_turn();
                        }
                        currentHero = nullptr; 
                    }
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


std::vector<ActionButton> GameRender::get_actionButtons(){
    return actionButtons;
}
GameRender::~GameRender(){
    if(currentHero) delete currentHero ; 
    if(selectedLocation) delete selectedLocation ; 
}
