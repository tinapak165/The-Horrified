#ifndef GAMERENDER_HPP
#define GAMERENDER_HPP

#include "Tools.hpp"
#include "Game.hpp"
#include "Action.hpp"
#include "ActionButton.hpp"
#include "SaveManager.hpp"
#include <vector>

class Game ; 
class ActionButtons;
class HeroAction ;

class GameRender {
public:
    GameRender(Game& game);
    void draw();              
    void draw_monsters();
    void draw_coffins(); 
    void draw_villagers();
    void draw_map();        
    void draw_monster_card();
    void draw_heroes();
    void draw_users() ;
    void draw_action_panel() ; 
    void handle_action(const std::string& , Hero*) ;
    void draw_location_icon() ; 
    void draw_collected_items() ;
    void draw_sidebar() ; 
    void draw_played_Perkcards() ; 
    void draw_saveGame() ; 
    void draw_villagerButton() ; 
    void renderTerrorLevel(int terrorLevel);
    bool handleDisplays() ;     
    void Draw_Backtomenu() ;
    void Draw_HelpButton();
    void Draw_Help();

    ~GameRender() ; 


private:

    std::unique_ptr<HeroAction> currentAction = nullptr; 
    bool ShowitemButton = false ; 
    bool ShowPLAYEDPerkButton = false ;
    Hero* currentHero = nullptr ; 
    bool showingHeroInfo = false ; 
    bool showingVillagerInfo = false ;
    bool savegame = false  ;
    bool Backtomenu = false;
    bool ShowHelp = false ;
    Location* selectedLocation = nullptr ; 
    std::vector<ActionButton> actionButtons ;
    Game& game;
    bool fileSaved = false ;
    std::string filename = "" ;
    MonsterType selectedMonsterMat = MonsterType::None;
    Texture2D draculaMat;
    Texture2D invisibleManMat;
    Texture2D coffinTex;
    Texture2D smashedCoffinTex; 
    static const Vector2 terrorLevelPositions[8] ;
};

#endif