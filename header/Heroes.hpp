#ifndef HEROES_H
#define HEROES_H
#include "Hero.hpp"
#include "TurnManager.hpp"
class Archaeologist : public Hero{
    public:
        Archaeologist(GameMap&) ;
        void DisplayInfo() const ;
        void SpecialAction(Location*) override ;        
};

class Mayor : public Hero{
    public:
        Mayor(GameMap&) ; 
        void DisplayInfo() const  ; 
        void SpecialAction(Location*) override ; 
};

class Courier : public Hero{
    private:
        TurnManager& turn ; 
    public:
        Courier(GameMap& , TurnManager&) ; 
        void DisplayInfo() const  ; 
        void SpecialAction(Location*) override ;
};

class Scientist : public Hero{
    public:
        Scientist(GameMap&) ; 
        void DisplayInfo() const  ; 
        void SpecialAction(Location*) override ;
        int Ability(Item& item) override ; 
};


#endif