#ifndef MAYOR_H
#define MAYOR_H
#include "Hero.hpp"
#include "location.hpp"
#include "GameMap.hpp"

class Mayor : public Hero{

    public:
        Mayor(GameMap& Map) ; 
        void DisplayInfo() const  ; 
        bool HasSpecialAction() const override {return false ; }
};


#endif