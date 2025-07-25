#ifndef ACTIONS_H
#define ACTIONS_H
#include "Hero.hpp"
#include "GameMap.hpp"


class HeroAction{
    public:
        virtual ~HeroAction() = default ;
        virtual bool update() = 0 ;
        virtual void draw() = 0 ; 
};

class MoveAction : public HeroAction{
    private:
    GameMap& map ; 
    Hero* hero ;
    std::string chosenPlace = "";
    bool typing = true;
    bool validInput = false;
    bool askVillager = false;
    bool moveWithVillager = false;
    bool moveFinished = false;
    Location* chosenLocation = nullptr;
    std::string message = "Which neighboring place do you want to move to?";

    public:
        MoveAction(GameMap& map , Hero* hero) ;
        bool update() override;
        void draw() override ; 

};

class HelpAction : public HeroAction {
    private:
        Hero* hero ; 
    public:
        HelpAction(Hero*) ;
        bool update() override ;
        void draw() override ;

};

#endif