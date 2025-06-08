#ifndef ARCHAEOLOGIST_H
#define ARCHAEOLOGIST_H
#include "Hero.hpp"


class Archaeologist : public Hero{
    public:
        Archaeologist() ;
        void DoTheSpecialAction() override ; 
        void DisplayInfo() const override ; 

};


#endif