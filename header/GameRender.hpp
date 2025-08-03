#ifndef GAMERENDER_HPP
#define GAMERENDER_HPP

#include "Button.hpp"
#include "Action.hpp"
#include <vector>


class Game;
class HeroAction;
class ActionButtons;

class GameRender {
public:

    GameRender(Game& game);
    void draw();              // کل صفحه رو رسم می‌کنه
    void draw_monsters();
    void draw_coffins(); 
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
    std::vector<ActionButton>get_actionButtons();
    void draw_available_Perkcards();
    void draw_played_Perkcards();
   

    ~GameRender() ; 
private:
    std::unique_ptr<HeroAction> currentAction = nullptr;
     bool ShowPLAYEDPerkButton = false ;
    bool ShowAvailablePerkButton = false ; 
    bool ShowitemButton = false ; 
    Hero* currentHero = nullptr ; 
    bool showingHeroInfo = false ; 
    Location* selectedLocation = nullptr ; 
    std::vector<ActionButton> actionButtons ;
    Game& game;
    MonsterType selectedMonsterMat = MonsterType::None;
    Texture2D draculaMat;
    Texture2D invisibleManMat;
    Texture2D coffinTex;
     Texture2D smashedCoffinTex; 
};

#endif