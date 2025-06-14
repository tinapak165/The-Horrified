#ifndef MAYOR_H
#define MAYOR_H
#include "Hero.hpp"
class Mayor : public Hero{
    private:

    public:
        Mayor() ; 
        void DisplayInfo() const  ; 
        bool HasSpecialAction() const override {return false ; }
};


#endif