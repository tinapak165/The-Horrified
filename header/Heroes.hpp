#ifndef HEROES_H
#define HEROES_H
#include "Hero.hpp"

class Archaeologist : public Hero{
    public:
        Archaeologist(GameMap& Map) ;
        void DisplayInfo() const ;
        void SpecialAction(Location*) override ; 
         
};

class Mayor : public Hero{

    public:
        Mayor(GameMap& Map) ; 
        void DisplayInfo() const  ; 
        void SpecialAction(Location*) override ; 

};




#endif