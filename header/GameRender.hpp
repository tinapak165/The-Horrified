#ifndef GAMERENDER_HPP
#define GAMERENDER_HPP

#include "button.hpp"
#include "Game.hpp"
#include "Action.hpp"
#include <vector>

class HeroAction ;

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
    void draw_map();          // فقط نقشه و آیکون‌ها
    void draw_monster_card(); // اگر کارت فعاله، نشونش بده
    void draw_heroes();
    void draw_users() ;
    void draw_action_panel() ; 
    void handle_action(const std::string& , Hero*) ;
    void draw_location_icon() ; 
    void draw_collected_items() ;
    void draw_sidebar() ; 
 //   void Handle_heroPhase() ;
    ~GameRender() ; 


    // HeroAction* get_currentAction() ;
    // bool get_showItemButton() ; 
    // Hero* get_currentHero() ;
    // bool get_showingHeroInfo() ;
    // Location* get_selectedLocation() ;

    // void set_currentAction(std::unique_ptr<HeroAction>) ;
    // void set_showItemButton(bool) ; 
    // void set_currentHero(Hero*) ;
    // void set_showingHeroInfo(bool) ;
    // void set_selectedLocation(Location*) ;


private:

    std::unique_ptr<HeroAction> currentAction ; 
    bool ShowitemButton = false ; 
    Hero* currentHero = nullptr ; 
    bool showingHeroInfo = false ; 
    Location* selectedLocation = nullptr ; 
    std::vector<ActionButton> actionButtons ;
    Game& game;
};

#endif