#ifndef HERO_H
#define HERO_H
#include <iostream>
#include <vector>
#include "villager.hpp"
#include "location.hpp"
#include "item.hpp"
#include "perkcardsDeck.hpp"
#include "InvisibleMan.hpp"

class Location ; 
class villager ; 
class InvisibleMan ; 

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
        std::vector<Perkcards> playedCards ; 
        std::vector<Perkcards> availableCards ;  

    public:
        Hero(std::string name , int MaxActions ,  Location* StartingLocation , std::string specialAction) ;
        void MoveTo(Location* new_location , std::vector<villager*>) ;
        void MoveTo(Location*) ; 
        
        bool hasvillagerHere() const ; 
        std::vector<villager*> villagerHere() const ;
        void showvillagersHere()const ; 

        std::string GetName()const ; 
        virtual void DisplayInfo() const = 0 ;

        int getMaxActions() const ; 
        int GetRemainingActions()const ;
        std::string GetSpecialActionInfo() const ;
        Location* GetCurrentLocation() const ; 
        void set_location(Location* new_location);    
        virtual bool HasSpecialAction() const {return true ; } 
        bool PerformTheAction(std::string)  ; 
        void DisplayActions() const ; 
        void resetMaxActions() ; 

        void AddAvailablePerk(Perkcards) ;
        void displayavailblecards() const;
        void displayPlayedCards() const; 
        std::vector<Perkcards> GetAvailablePerkCards() ; 
        void addPlayedCards(Perkcards) ;

        void DisplayItem() ;
        std::string colorItems(const ItemColor&) ; //show items colors 
        void PickupItems() ; 
        void SpecialPickup(Location*) ; 
        std::vector<Item> GetItems() ; 
        void removeItems(const Item&) ; 
        int select_items_to_defeat(ItemColor requiredColor) ;
        bool has_items() const;
        void remove_item_by_index(int index);

        int AdvanceActionForDracula() ; 
        void AdvanceActionForInvisibleMan(InvisibleMan*) ;

        void SetRemainingActions(int newRemaining) ;
        void SetCurrentLocation(Location* location) ;
};
#endif  