#ifndef ACTIONS_H
#define ACTIONS_H
#include "Hero.hpp"
#include "GameMap.hpp"
#include "item.hpp"
#include "Game.hpp"
#include <vector>
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

class PickUpAction : public HeroAction{
    private:
        Hero* hero ;
        bool done = false;
        int frameCounter = 0 ; 
        std::string message = "Click an item to pick up ( to cancel)";
        Vector2 mousePos;
    public:
        PickUpAction(Hero*) ;
        bool update() override ;
        void draw() override ;

};

class ChoosePerkCardAction : public HeroAction{
    private:
        Hero* hero;
        Vector2 mousePos;
        std::string message;
        bool done = false;
        int frameCounter = 0 ; 
        Game& game ; 
        std::unique_ptr<Perkcard> currentCard = nullptr ;

    public:
        ChoosePerkCardAction(Hero* , Game&);
        bool update() override;   
        void draw()override;     
};

class SpecialAction : public HeroAction{
    private:
        Hero* hero ;
        GameMap & map ; 

        std::string message;
        std::string chosenPlace = "";
        bool typing = true;
        bool validInput = false;
        bool specialFinished = false;
        Location* chosenLocation = nullptr;

        double messageStartTime = 0.0;
        bool showingMessage = false;

    public:
        SpecialAction(Hero* , GameMap&);
        bool update() override;   
        void draw()override;  

};

class AdvanceAction : public HeroAction{
    private:

        Hero* hero;
        Dracula* dracula;
        ItemPool& pool;
        GameMap& map;
        InvisibleMan* invisibleman;
        Item pendingAbilityItem;
        float messageTimer = 0.0f;
        bool shouldClose = false;
        bool waitingForAbility = false ; 
        bool waitingForAbilityInput = false ; 


        enum class Mode { None, ForDracula, ForInvisibleMan } mode = Mode::None;

        // برای حالت دراکولا
        std::vector<Item> availableRedItems;
        std::vector<Item> selectedItems;
        int totalStrength = 0;
        int hoveredIndex = -1;

        // برای حالت نامرئی
        std::vector<Item> evidenceItems;
        int hoveredEvidenceIndex = -1;
        bool evidencePlaced = false;

        std::string message;
    public:
        AdvanceAction(Hero*, Dracula* , ItemPool& , GameMap& ,InvisibleMan*);
        bool update() override;   
        void draw()override; 
};

#endif