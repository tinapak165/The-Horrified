#ifndef DICE_H
#define DICE_H
#include <array>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <random>

enum class DiceFace{
    empty , 
    Power , 
    Attack 

};

class Dice {

    private:
        int count ; 
        std::array<std::array<DiceFace , 6> , 3> faces ; 
    public:
        Dice(int c) ; 
        std::vector<DiceFace> roll(int)  ;
         
} ; 
#endif