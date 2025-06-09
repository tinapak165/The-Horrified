#ifndef HERO_H
#define HERO_H
#include <iostream>
#include <vector>
//#include "location.hpp"

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
        std::string name ; 
        int MaxActions ; 
        int RemainingActions ; 
        std::string specialAction ; 
        std::string StartingLocation ;
        std::string currentLocation;
        std::vector<Action> ListOfActions ; 

    public:
        Hero(std::string name , int MaxActions , std::string StartingLocation , std::string specialAction) ;
        void MoveTo(std::string Newlocation) ; 

        std::string GetName()const ; 
        int GetRemainingActions()const ;
        std::string GetSpecialActionInfo() const ;
        std::string GetCurrentLocation() const ; 
        
        virtual bool HasSpecialAction() const {return true ; } 
        void PerformTheAction(std::string)  ; 
        void DisplayActions() ; 

        void SetRemainingActions(int newRemaining) ;
        void SetCurrentLocation(std::string location) ;
};

#endif 