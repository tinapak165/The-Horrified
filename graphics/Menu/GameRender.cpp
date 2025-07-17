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

        Rectangle area = loc->get_clickable_area();
        Color dotColor = RED;
        if (monster->get_type() == MonsterType::InvisibleMan) dotColor = PURPLE;
        if (monster == game.get_frenzied_monster()) dotColor = GOLD;

        DrawCircle(area.x + area.width / 2, area.y + area.height / 2, 10, dotColor);
    }
}

void GameRender::draw_villagers() {
    for (const auto& loc : game.get_map().get_locations()) {
        for (Villager* v : loc->get_villagers()) {
            Rectangle area = loc->get_clickable_area();
            DrawCircle(area.x + 10, area.y + 10, 6, PINK);
        }
    }
}

void GameRender::draw_items() {
    for (const auto& loc : game.get_map().get_locations()) {
        for (const auto& item : loc->get_items()) {
            Rectangle area = loc->get_clickable_area();
            Color color;
            switch (item.getColor()) {
                case ItemColor::Red: color = RED; break;
                case ItemColor::Yellow: color = YELLOW; break;
                case ItemColor::Blue: color = SKYBLUE; break;
                default: color = GRAY; break;
            }
            DrawRectangle(area.x + 5, area.y + 25, 8, 8, color);
        }
    }
}

void GameRender::draw_monster_card() {
    const auto& card = game.get_current_card();
    if (!card) return;

    Texture2D cardTexture = card->get_texture();
    Rectangle source = { 0, 0, (float)cardTexture.width, (float)cardTexture.height };
    Rectangle dest = { 600, 10, 180, 270 }; // Top-right area
    Vector2 origin = { 0, 0 };

    DrawTexturePro(cardTexture, source, dest, origin, 0.0f, WHITE);
}


