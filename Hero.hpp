#ifndef HERO_H
#define HERO_H
#include <iostream>
class Hero{

    private:
        std::string name ; 
        int MaxActions ; 
        int RemainingActions ; 
        std::string specialAction ; 
        std::string StartingLocation ;
        std::string currentLocation;


    public:
        Hero(std::string name , int MaxActions , std::string StartingLocation) ;
        virtual void DoTheSpecialAction() = 0 ; //do the special action
        virtual void DisplayInfo() const = 0 ; //displaying info for each hero
        virtual void MoveTo(std::string Newlocation) ; //change the hero placement

        virtual std::string GetName()const ; 
        virtual int GetMaxAction() const  ; // return the number of action each hero have
        virtual int GetRemainingActions()const ;
        virtual std::string GetSpecialActionInfo() const ;
        virtual std::string GetCurrentLocation() const ; 
        
        virtual void SetName(const std::string& newName) ; 
        virtual void SetMaxActions(int newMax) ; 
        virtual void SetRemainingActions(int newRemaining) ;
        virtual void SetCurrentLocation(const std::string& location) ;
        virtual void SetSpecialActionInfo(const std::string spe) = 0 ;

};






#endif 