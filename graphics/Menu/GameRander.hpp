#ifndef GAMERENDER_HPP
#define GAMERENDER_HPP


#include "Game.hpp"

class GameRender {
public:
    GameRender(Game& game);

    void draw();              // کل صفحه رو رسم می‌کنه
    void draw_monsters();
    void draw_villagers();
    void draw_items();
    void draw_map();          // فقط نقشه و آیکون‌ها
    void draw_monster_card(); // اگر کارت فعاله، نشونش بده

private:
    Game& game;
};

#endif
