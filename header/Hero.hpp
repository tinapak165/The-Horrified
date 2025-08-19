#ifndef HERO_H
#define HERO_H
#include <iostream>
#include <vector>
#include <memory>
#include "Villager.hpp"
#include "Location.hpp"
#include "Item.hpp"
#include "Perkcards.hpp"
#include "InvisibleMan.hpp"
#include "Dracula.hpp"
#include "Itembag.hpp"
#include "Button.hpp"
class Location ; 
class Dracula ; 
class ItemPool ; 
class Villager ; 
class InvisibleMan ; 
class Perkcard ; 

enum class ActionType{
    Move ,
    Guide ,
    Pickup ,
    Advance , 
    Defeat , 
    SpecialAction ,
};

struct Action{
    ActionType Type ; 
    std::string name ; 
    std::string Description ; 
};

class Hero{ 
    private: 
        std::vector<Item> ListOfitems ; 
        std::string name ; 
        int MaxActions ; 
        int RemainingActions ; 
        std::string specialAction ; 
        Location* StartingLocation ;
        Location* currentLocation;
        std::vector<Action> ListOfActions ;
        std::vector<std::unique_ptr<Perkcard>> playedCards ; 
        std::vector<std::unique_ptr<Perkcard>> availableCards ;
        
        std::vector<Item> usedItemsForDracula;
        std::vector<Item> usedItemsForInvisibleMan;

        Texture2D HeroTex;
        std::string HeroTex_path;

        //special use
        bool done = false;
        bool shown = false ; 
        std::string message ; 
        double messageStartTime = 0.0;

    public:
        Hero(std::string name , int MaxActions ,  Location* StartingLocation , std::string specialAction , std::string HeroTex_path) ;

        void MoveTo(Location*  , std::vector<Villager*>) ;
        void MoveTo(Location*) ; 

        virtual void StartSpecial(GameMap&);
        virtual void UpdateSpecial(bool &done) ;
        virtual void DrawSpecial() ; 
        bool drawCancelButton(); //uses for courier & arch special

        virtual bool HasAbility() ; 

        bool hasvillagerHere() const ; 
        std::vector<Villager*> villagerHere() const ;

        std::string GetName()const ; 
        void DisplayInfo() const;

        int getMaxActions() const ; 
        int GetRemainingActions()const ;
        std::string GetSpecialActionInfo() const ;
        Location* GetCurrentLocation() const ;     
        void DisplayActions() const ; 
        void resetMaxActions() ; 

        void AddAvailablePerk(std::unique_ptr<Perkcard>) ;
        void displayPlayedCards() const; 
        std::vector<std::unique_ptr<Perkcard>>& GetAvailablePerkCards() ; 
        std::vector<std::unique_ptr<Perkcard>>& GetPlayedPerkCards() ; 

        void addPlayedCards(std::unique_ptr<Perkcard>) ;

        void DisplayItem() ;
        std::vector<Item>& GetItems() ;
        void addItems(Item) ; 
        void removeItems(const Item&) ; 
        bool has_items() const;
        void remove_item_by_index(int); 

        void SetRemainingActions(int ) ;
        void SetCurrentLocation(Location*) ;

        std::vector<Item> getUsedItemsForDracula();
        std::vector<Item> getUsedItemsForInvisibleMan();
        virtual ~Hero(); 
        
        Texture2D getTexture();
        void loadTexture();
      
};


#endif 