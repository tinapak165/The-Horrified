#ifndef HEROES_H
#define HEROES_H
#include "Hero.hpp"
#include "TurnManager.hpp"

class Archaeologist : public Hero{
    private:
        std::string message;
        std::string chosenPlace;
        bool typing = true;
        bool validInput = false;
        bool showingMessage = false;
        double messageStartTime = 0.0;
        Location* chosenLocation = nullptr;
        GameMap* map = nullptr;
        std::vector<Item>* itemList = nullptr;
        int selectedItemIndex = 0;
        Location* currentTargetLocation = nullptr;
        bool pickingItems = false;
        std::vector<Rectangle> itemHitboxes; 
        Rectangle doneButtonBox = { 740.0f, 460.0f, 70.0f, 30.0f }; 
        bool autoCompleteWithoutItems = false;


    public:
        Archaeologist(GameMap&) ;
        void StartSpecial(GameMap&) override ;
        void UpdateSpecial(bool &done) override ;
        void DrawSpecial() override ;
        void DisplayInfo() const ;
        void Special(Location*) override ;        
};

class Mayor : public Hero{

    private:
        bool shown = false ; 
        std::string message ; 
        double messageStartTime = 0.0;

    public:

        Mayor(GameMap&) ; 
        void DisplayInfo() const  ; 
        void StartSpecial(GameMap&) override ;
        void Special(Location*) override ; 
        void UpdateSpecial(bool& done) override ;
        void DrawSpecial() override ;
};

class Courier : public Hero{
    private:
        TurnManager& turn ; 
    public:
        Courier(GameMap& , TurnManager&) ; 
        void DisplayInfo() const  ; 
        void Special(Location*) override ;
};

class Scientist : public Hero{
    private:
        bool shown = false ; 
        std::string message ; 
        double messageStartTime = 0.0;
    public:
        Scientist(GameMap&) ; 
        void DisplayInfo() const  ; 
        int Ability(Item& item) override ; 
        void StartSpecial(GameMap&) override ;
        void Special(Location*) override ; 
        void UpdateSpecial(bool& done) override ;
        void DrawSpecial() override ;
};


#endif