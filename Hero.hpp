#ifndef HERO_H
#define HERO_H
#include <iostream>
#include <vector>
#include "villager.hpp"
#include "location.hpp"
#include "item.hpp"

class Location ; 
class villager ; 

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

    public:
        Hero(std::string name , int MaxActions ,  Location* StartingLocation , std::string specialAction) ;
        void MoveTo(Location* new_location , std::vector<villager*>) ;
        void MoveTo(Location*) ; 
        
        bool hasvillagerHere() const ; 
        std::vector<villager*> villagerHere() const ;
        void showvillagersHere()const ; 

        std::string GetName()const ; 

        int GetRemainingActions()const ;
        std::string GetSpecialActionInfo() const ;
        Location* GetCurrentLocation() const ;         
        virtual bool HasSpecialAction() const {return true ; } 
        bool PerformTheAction(std::string)  ; 
        void DisplayActions() ; 


        void DisplayItem() ;
        std::string colorItems(const ItemColor&) ; //show items colors 
        void PickupItems() ; 
        void SpecialPickup(Location*) ; 
        std::vector<Item> GetItems() ; 
        void removeItems(const Item&) ; 
        void AdvanceAction() ; 

        void SetRemainingActions(int newRemaining) ;
        void SetCurrentLocation(Location* location) ;
};
#endif 