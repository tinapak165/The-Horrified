#ifndef ARCHAEOLOGIST_H
#define ARCHAEOLOGIST_H
#include "Hero.hpp"
#include "location.hpp"
#include "GameMap.hpp"

class Archaeologist : public Hero{
    public:
        Archaeologist(GameMap& Map) ;
        void DisplayInfo() const  ; 
};

#endif