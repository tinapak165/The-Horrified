#ifndef HEROS_H
#define HEROS_H

#include "Hero.hpp"
#include <vector>
class Heros : public Hero{
    friend std::ostream& operator << (std::ostream &out , const Heros &heros) ; 
    private:
        std::vector<Hero> heroes ; 
    public:
        Heros() ; 

};
#endif