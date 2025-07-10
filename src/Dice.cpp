#include "Dice.hpp"
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <random>
using namespace std ; 
Dice::Dice(int c) : count(c) {
    faces[0] = {
        DiceFace::Power,
        DiceFace::Attack, 
        DiceFace::empty,
        DiceFace::empty,
        DiceFace::empty,
        DiceFace::empty

    };
    faces[1] = {
        DiceFace::Attack,
        DiceFace::Power,
        DiceFace::empty,
        DiceFace::empty,
        DiceFace::empty,
        DiceFace::empty
    };
    faces[2] = {
        DiceFace::Attack,
        DiceFace::Power,
        DiceFace::empty,
        DiceFace::empty,
        DiceFace::empty,
        DiceFace::empty
    };

    srand(time(0));
}


vector<DiceFace> Dice::roll(int numOfDice) {

    cout << "Entered roll() with " << numOfDice << " dice.\n";

    if (numOfDice <= 0 || numOfDice > 3) {
        cout << "Invalid dice count! Throwing exception...\n";
        throw out_of_range("invalid dice count");
    }

    vector<int> DiceIndices = {0, 1, 2};
    random_shuffle(DiceIndices.begin(), DiceIndices.end());

    vector<DiceFace> res;
    for (int i = 0; i < numOfDice; i++) {
        int RandomDice = DiceIndices[i];
        int RandomFace = rand() % 6;
        DiceFace face = faces[RandomDice][RandomFace];
        res.push_back(face);
        cout << "Dice " << RandomDice << " rolled: ";
        switch (face) {
            case DiceFace::Power: cout << "Power"; break;
            case DiceFace::Attack: cout << "Attack"; break;
            case DiceFace::empty: cout << "Empty"; break;
            default: cout << "Unknown"; break;
        }
        cout << "\n";
    }

    return res;
}

