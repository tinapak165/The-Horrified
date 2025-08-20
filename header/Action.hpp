#ifndef ACTIONS_H
#define ACTIONS_H
#include "Game.hpp"

class HeroAction{
    private:
        std::string message; 
        bool shouldClose = false;
        float messageTimer = 0.0f;
    public:
        virtual bool update() = 0 ;
        virtual void draw() = 0 ; 
        void DrawPanel() ; 
        bool drawCancelButton() ;
        bool drawDoneButton() ;
        void DrawMessage(int y , Color) ;
        void set_message(std::string) ; 
        std::string get_message() ;
        std::string type(std::string) ;
        bool handleShouldClose() ; 
        void set_ShouldClose(bool) ;
        bool get_shouldClose() ;
        void DrawTypingText(const std::string &) ; 
        virtual ~HeroAction() = default ;

};

class MoveAction : public HeroAction{
    private:
        GameMap& map ; 
        Hero* hero ;
        std::string chosenPlace;
        bool askVillager = false;
        bool moveWithVillager = false;
        bool moveFinished = false;
        Location* chosenLocation = nullptr;
        bool typing = true;

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
        std::vector<Item>* itemList = nullptr;
        std::vector<Rectangle> itemHitboxes; 
        bool ChoseAnItem = false ;
    public:
        PickUpAction(Hero*) ;
        bool update() override ;
        void draw() override ;

};

class ChoosePerkCardAction : public HeroAction{
    private:
        Hero* hero;
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
        bool specialFinished = false;

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
        bool waitingForAbility = false ; 

        enum class Mode { None, ForDracula, ForInvisibleMan } mode = Mode::None;

        //dracula
        std::vector<Item> availableRedItems;
        std::vector<Item> selectedItems;
        int totalStrength = 0;
        int hoveredIndex = -1;

        //invisible man
        std::vector<Item> evidenceItems;
        int hoveredEvidenceIndex = -1;
        bool evidencePlaced = false;

    public:
        AdvanceAction(Hero*, Dracula* , ItemPool& , GameMap& ,InvisibleMan*);
        void checkforDestroyingCoffin() ;
        bool update() override;   
        void draw()override; 
};

class DefeatAction : public HeroAction{

    private:
        Hero* hero;
        InvisibleMan*  invisibleMan;
        Dracula* dracula;
        std::vector<Item> availableItems;
        int totalStrength = 0;
        int hoveredIndex = -1 ; 
        enum class Mode { None, ForDracula, ForInvisibleMan } mode ;
        Item pendingAbilityItem;
        bool waitingForAbility = false ; 

    public:
        DefeatAction(Hero* , InvisibleMan* , Dracula*) ;
        void checkForStrength(int, std::string);
        bool update() override;   
        void draw()override;

};


class GuideAction : public HeroAction{
    private:
        enum class GuideStep { ChooseMode, ChooseVillager, ChoosePlace };
        GuideStep step  ; 
        GameMap& map ; 
        Hero* hero ;
        std::string mode; 
        std::string input;
        std::string chosenPlace;
        std::string chosenVillager;
        bool typing = true ; 
    public: 
        GuideAction(GameMap&  ,Hero*) ;
        bool update() override;   
        void draw()override;
};

#endif