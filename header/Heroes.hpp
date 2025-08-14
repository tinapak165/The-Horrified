#ifndef HEROES_H
#define HEROES_H
#include "Hero.hpp"
#include "TurnManager.hpp"
#include "Button.hpp"
class Archaeologist : public Hero{
    private:
        bool shouldClose = false ;
        float messageTimer = 0.0f;
        std::string message;
        std::string chosenPlace;
        bool typing = true;
        bool ChoseAnItem = false ;

        GameMap* map = nullptr;
        std::vector<Item>* itemList = nullptr;
        Location* chosenLocation = nullptr ;
        Location* currentTargetLocation = nullptr;
        std::vector<Rectangle> itemHitboxes; 

    public:
        Archaeologist(GameMap&) ;
        void StartSpecial(GameMap&) override ;
        void UpdateSpecial(bool &done) override ;
        void DrawSpecial() override ;
        bool handleShouldClose() ;
        std::string type(std::string) ;
        void DrawTypingText(const std::string &);
        bool drawDoneButton() ;
        bool drawCancelButton() ;

};

class Mayor : public Hero{
    public:
        Mayor(GameMap&) ; 
};

class Courier : public Hero{
    private:
        TurnManager& turn ; 
        std::vector<Hero*> heroes ;
        int hoveredIndex ;
        bool done ; 
    public:
        Courier(GameMap& , TurnManager& ) ; 
        void StartSpecial(GameMap&) override ;
        void UpdateSpecial(bool &done) override ;
        void DrawSpecial() override ;
};

class Scientist : public Hero{
    public:
        Scientist(GameMap&) ; 
        bool HasAbility() override ; 
};


#endif