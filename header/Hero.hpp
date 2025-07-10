#ifndef HERO_H
#define HERO_H
#include <iostream>
#include <vector>
#include <memory>
#include "villager.hpp"
#include "location.hpp"
#include "item.hpp"
#include "perkcards.hpp"
#include "InvisibleMan.hpp"
#include "Dracula.hpp"
#include "Itembag.hpp"

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

    public:
        Hero(std::string name , int MaxActions ,  Location* StartingLocation , std::string specialAction) ;
        //actions
        void MoveAction(GameMap& , Hero*) ;
        void MoveTo(Location*  , std::vector<Villager*>) ;
        void MoveTo(Location*) ; 

        void GuideAction(Hero* , GameMap&) ; 

        virtual void SpecialAction(Location*) = 0  ; //arch and curier
        void Special(Hero *, GameMap& )  ;

        void AdvanceAction(Hero* , Dracula* , ItemPool , GameMap& , InvisibleMan*) ; 
        int select_items_to_defeat(ItemColor) ;
        
        int AdvanceActionForDracula() ; 
        void AdvanceActionForInvisibleMan(InvisibleMan*) ;

        void DefeatAction(Hero*, InvisibleMan* , Dracula*) ; 

        bool hasvillagerHere() const ; 
        std::vector<Villager*> villagerHere() const ;
        void showvillagersHere()const ; 

        std::string GetName()const ; 
        virtual void DisplayInfo() const = 0 ;

        int getMaxActions() const ; 
        int GetRemainingActions()const ;
        std::string GetSpecialActionInfo() const ;
        Location* GetCurrentLocation() const ;         
        bool PerformTheAction(std::string)  ; 
        void DisplayActions() const ; 
        void resetMaxActions() ; 

        void AddAvailablePerk(std::unique_ptr<Perkcard>) ;
        void displayavailblecards() const;
        void displayPlayedCards() const; 
        std::vector<std::unique_ptr<Perkcard>>& GetAvailablePerkCards() ; 
        void addPlayedCards(std::unique_ptr<Perkcard>) ;

        void DisplayItem() ;
        void PickupItems() ; 
        std::vector<Item> GetItems() ; 
        void removeItems(const Item&) ; 
        bool has_items() const;
        void remove_item_by_index(int); 

        void SetRemainingActions(int ) ;
        void SetCurrentLocation(Location*) ;

        std::vector<Item> getUsedItemsForDracula();
        std::vector<Item> getUsedItemsForInvisibleMan();

        virtual ~Hero() = default ; 
};


#endif 