#ifndef HERO_H
#define HERO_H
#include <iostream>
//#include "location.hpp"
class Hero{
    friend std::ostream& operator << (std::ostream &out , const Hero &hero) ; 

    private:
        std::string name ; 
        int MaxActions ; 
        int RemainingActions ; 
        std::string specialAction ; 
        std::string StartingLocation ;
        std::string currentLocation;

    public:
        Hero(std::string name , int MaxActions , std::string StartingLocation , std::string specialAction) ;
        Hero() ; 
        //virtual void DoTheSpecialAction() = 0 ; //do the special action
        //virtual void DisplayInfo() const = 0 ; //displaying info for each hero
        void MoveTo(std::string Newlocation) ; //change the hero placement

        std::string GetName()const ; 
        int GetMaxAction() const  ; // return the number of action each hero have
        int GetRemainingActions()const ;
        std::string GetSpecialActionInfo() const ;
        std::string GetCurrentLocation() const ; 
        

        void SetMaxActions(int newMax) ; 
        void SetRemainingActions(int newRemaining) ;
        void SetCurrentLocation(std::string location) ;
        //virtual void SetSpecialActionInfo(const std::string spe) = 0 ;
};

#endif 