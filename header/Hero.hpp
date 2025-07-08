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

class Location ; 
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
        void MoveTo(Location* new_location , std::vector<Villager*>) ;
        void MoveTo(Location*) ; 

        void GuideAction(Hero* , GameMap&) ; 
        
        bool hasvillagerHere() const ; 
        std::vector<Villager*> villagerHere() const ;
        void showvillagersHere()const ; 

        std::string GetName()const ; 
        virtual void DisplayInfo() const = 0 ;

        int getMaxActions() const ; 
        int GetRemainingActions()const ;
        std::string GetSpecialActionInfo() const ;
        Location* GetCurrentLocation() const ;         
    //    virtual bool HasSpecialAction() const = 0 ;
        bool PerformTheAction(std::string)  ; 
        void DisplayActions() const ; 
        void resetMaxActions() ; 

        void AddAvailablePerk(std::unique_ptr<Perkcard>) ;
        void displayavailblecards() const;
        void displayPlayedCards() const; 
        std::vector<std::unique_ptr<Perkcard>>& GetAvailablePerkCards() ; 
        void addPlayedCards(std::unique_ptr<Perkcard>) ;

        void DisplayItem() ;
        std::string colorItems(const ItemColor&) ;
        void PickupItems() ; 
        virtual void SpecialAction(Location*) = 0  ; //arch anc curier
        std::vector<Item> GetItems() ; 
        void removeItems(const Item&) ; 
        int select_items_to_defeat(ItemColor requiredColor) ;
        bool has_items() const;
        void remove_item_by_index(int index); 

        int AdvanceActionForDracula() ; 
        void AdvanceActionForInvisibleMan(InvisibleMan*) ;

        void SetRemainingActions(int newRemaining) ;
        void SetCurrentLocation(Location* location) ;

        std::vector<Item> getUsedItemsForDracula();
        std::vector<Item> getUsedItemsForInvisibleMan();

        virtual ~Hero() = default ; 
};


#endif 