#ifndef INVISIBLEMAN_HPP
#define INVISIBLEMAN_HPP

#include "monster.hpp"

class InvisibleMan : public Monster {
    private:
        


    public:

        InvisibleMan(Location* start);

        void special_power(Hero*) override ; 
        void attack() override ;
        bool is_defeated()const override ;
        bool can_be_defeated()override;

};

#endif