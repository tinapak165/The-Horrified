#ifndef GAMERENDER_HPP
#define GAMERENDER_HPP

#include "button.hpp"
#include "Game.hpp"
#include "Action.hpp"
#include "ActionButton.hpp"
#include <vector>

class Game ; 
class ActionButtons;
class HeroAction ;

class GameRender {
public:
    GameRender(Game& game);
    void draw();              // کل صفحه رو رسم می‌کنه
    void draw_monsters();
    void draw_villagers();
    void draw_map();          // فقط نقشه و آیکون‌ها
    void draw_monster_card(); // اگر کارت فعاله، نشونش بده
    void draw_heroes();
    void draw_users() ;
    void draw_action_panel() ; 
    void handle_action(const std::string& , Hero*) ;
    void draw_location_icon() ; 
    void draw_collected_items() ;
    void draw_sidebar() ; 
    void draw_played_Perkcards() ; 
    void draw_available_Perkcards() ;
    void draw_saveGame() ; 

    ~GameRender() ; 


private:

    std::unique_ptr<HeroAction> currentAction = nullptr; 
    bool ShowitemButton = false ; 
    bool ShowPLAYEDPerkButton = false ;
    bool ShowAvailablePerkButton = false ; 
    Hero* currentHero = nullptr ; 
    bool showingHeroInfo = false ; 
    bool savegame = false  ;
    Location* selectedLocation = nullptr ; 
    std::vector<ActionButton> actionButtons ;
    Game& game;
};

#endif