#include "Dice.hpp"
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
using namespace std ; 
Dice::Dice(int c) : count(c){
    
    faces[1] = {
        DiceFace::Power , 
        DiceFace::empty ,
        DiceFace::empty ,
        DiceFace::empty ,
        DiceFace::empty ,
        DiceFace::empty 
    }; 
    faces[2] = {
        DiceFace::Attack , 
        DiceFace::empty ,
        DiceFace::empty ,
        DiceFace::empty ,
        DiceFace::empty ,
        DiceFace::empty 

    };
    faces[3] = {
        DiceFace::Attack , 
        DiceFace::empty ,
        DiceFace::empty ,
        DiceFace::empty ,
        DiceFace::empty ,
        DiceFace::empty 

    };
}
int Dice::get_count(){
    return count ; 
}

vector<DiceFace> Dice::roll(int numOfDice){ //انتخاب index تاس رندوم
    if(numOfDice <= 0 || numOfDice >= 4){
        throw out_of_range("invalid") ; 
    }
    vector<int>DiceIndices = {1,2,3} ; 
    random_shuffle(DiceIndices.begin() , DiceIndices.end()) ; 
    vector<DiceFace> res ; 


    for(int i = 0 ; i < numOfDice ; i++){
        int RandomDice = DiceIndices[i] ;
        int RandomFace = rand() % 6 ; 
        res.push_back(faces[RandomDice][RandomFace]) ; 
        cout << "Dice " << RandomDice << " rolled: " ;
        switch (faces[RandomDice][RandomFace])
        {
        case DiceFace::Power : 
            
            break;
        
        case DiceFace::Attack :
            
            break ;
        case DiceFace::empty:
                     
        }
        cout << '\n' ; 
    }
    return res ; 
}
