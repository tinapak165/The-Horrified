#ifndef GAMERENDER_HPP
#define GAMERENDER_HPP

#include "Button.hpp"
#include "Game.hpp"
#include "Action.hpp"
#include <vector>

struct ActionButton{
    std::string label ; 
    Rectangle bounds ; 
};

class GameRender {
public:
    GameRender(Game& game);
    void draw();              // کل صفحه رو رسم می‌کنه
    void draw_monsters();
    void draw_villagers();
    void draw_items();
    void draw_map();          // فقط نقشه و آیکون‌ها
    void draw_monster_card(); // اگر کارت فعاله، نشونش بده
    void draw_What_Happend_In_Text();
    void draw_heroes();
    void draw_users() ;
    void draw_action_panel() ; 
    void handle_action(const std::string& , Hero*) ;
    void draw_location_icon() ; 
    void draw_sidebar() ;
    ~GameRender() ; 
private:
    std::unique_ptr<HeroAction> currentAction ; 
    Hero* currentHero = nullptr ; 
    bool showingHeroInfo = false ; 
    Location* selectedLocation = nullptr ; 
    std::vector<ActionButton> actionButtons ;
    Game& game;
};

#endif