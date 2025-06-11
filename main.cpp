#include "Dice.hpp"
#include <iostream>
#include <stdexcept>
#include <ctime>
using namespace std ; 

int main(){

    srand(time(0)) ;

    Dice d(3) ; 
    vector<DiceFace> res =  d.roll(3); 
    //how to use:
    for(DiceFace e : res){
        switch (e)
        {
        case DiceFace::Attack :
            cout << "Attack!!!" ; //do the DiceFace
            break;
        
        default:
            break;
        }
    }
         

}