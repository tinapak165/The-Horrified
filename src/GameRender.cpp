#include "GameRander.hpp"

GameRender::GameRender(Game& game) : game(game) {}

void GameRender::draw() {
    draw_map();
    draw_items();
    draw_villagers();
    draw_monsters();
    draw_monster_card();
}

void GameRender::draw_map() {
    game.get_map().draw_map();
    
   
}

void GameRender::draw_monsters() {
    for (const auto& [type, monster] : game.get_monsters()) {
        if (!monster) continue;

        Location* loc = monster->get_location();
        if (!loc) continue;

        Texture2D tex = monster->getTexture();
        Rectangle src = { 0, 0, (float)tex.width, (float)tex.height };
        Rectangle area = loc->get_clickable_area();
        Rectangle dest = { area.x + 25, area.y + 5, 24, 24 };

        // رسم هیولا
        DrawTexturePro(tex, src, dest, {0, 0}, 0.0f, WHITE);

        // اگه فرنزاید بود، یه مستطیل قرمز دورش بکش
        if (monster == game.get_frenzied_monster()) {
            DrawRectangleLinesEx(dest, 2.5f, RED);
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
    for (Hero* hero : game.get_turnManager().get_heroes()) {
        if (!hero) continue;

        Location* loc = hero->GetCurrentLocation();
        if (!loc) continue;

        Texture2D tex = hero->getTexture();
        Rectangle src = { 0, 0, (float)tex.width, (float)tex.height };
        Rectangle area = loc->get_clickable_area();
        Rectangle dest = { area.x + 5, area.y + 5, 24, 24 };

        DrawTexturePro(tex, src, dest, {0, 0}, 0.0f, WHITE);

        if (hero == game.get_turnManager().get_active_hero()) {
            DrawRectangleLinesEx(dest, 2.5f, BLUE);
        }
    }
}

void GameRender::draw_What_Happend_In_Text(){
    // یه تابعی که اتفاقات افتاده شده توی هر فاز گیم رو بنویسه.
}
