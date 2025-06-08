#ifndef MAYOR_H
#define MAYOR_H
#include "Hero.hpp"
class Mayor : public Hero{
    private:

    public:
        Mayor() ; 
        void DoTheSpecialAction() override ; 
        void DisplayInfo() const override ; 
};


#endif