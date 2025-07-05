#ifndef PERK_HPP
#define PERK_HPP
#include <vector>
#include <iostream>
class Perkcards{
    private:
        std::string Event ; 

    public:
        Perkcards(std::string Event);
        Perkcards() ; 
        std::string get_Event() const ;  
};

#endif