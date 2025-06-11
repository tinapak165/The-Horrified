#ifndef DICE_H
#define DICE_H
#include <array>
#include <vector>
enum class DiceFace{
    empty , 
    Power , 
    Attack 

};

class Dice {
    friend std::ostream& operator<<(std::ostream& os, const Dice& d);

    private:
        int count ; 
        std::array<std::array<DiceFace , 6> , 3> faces ; 
    public:
        Dice(int c) ; 
        int get_count();
        //std::string get_random
        std::vector<DiceFace>  roll(int)  ;
         
        
} ; 
#endif