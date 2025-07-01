#include "Dice.hpp"
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <random>

Dice::Dice(int c) : count(c) {
    faces[0] = {
        DiceFace::Power, 
        DiceFace::empty,
        DiceFace::empty,
        DiceFace::empty,
        DiceFace::empty,
        DiceFace::empty
    };
    faces[1] = {
        DiceFace::Attack,
        DiceFace::empty,
        DiceFace::empty,
        DiceFace::empty,
        DiceFace::empty,
        DiceFace::empty
    };
    faces[2] = {
        DiceFace::Attack,
        DiceFace::empty,
        DiceFace::empty,
        DiceFace::empty,
        DiceFace::empty,
        DiceFace::empty
    };

    // مقداردهی اولیه رندم
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

int Dice::get_count() {
    return count;
}

std::vector<DiceFace> Dice::roll(int numOfDice) {
    std::cout << "Entered roll() with " << numOfDice << " dice.\n";

    if (numOfDice <= 0 || numOfDice > 3) {
        std::cout << "Invalid dice count! Throwing exception...\n";
        throw std::out_of_range("invalid dice count");
    }

    std::vector<int> DiceIndices = {0, 1, 2};
    std::random_shuffle(DiceIndices.begin(), DiceIndices.end());

    std::vector<DiceFace> res;
    for (int i = 0; i < numOfDice; i++) {
        int RandomDice = DiceIndices[i];
        int RandomFace = rand() % 6;
        DiceFace face = faces[RandomDice][RandomFace];
        res.push_back(face);
        std::cout << "Dice " << RandomDice << " rolled: ";
        switch (face) {
            case DiceFace::Power: std::cout << "Power"; break;
            case DiceFace::Attack: std::cout << "Attack"; break;
            case DiceFace::empty: std::cout << "Empty"; break;
            default: std::cout << "Unknown"; break;
        }
        std::cout << "\n";
    }

    return res;
}



// vector<DiceFace> Dice::roll(int numOfDice) {
//     if (numOfDice <= 0 || numOfDice > 3) {
//         throw out_of_range("Invalid number of dice.");
//     }

//     vector<DiceFace> res;

//     for (int i = 0; i < numOfDice; ++i) {
//         int diceIndex = 1 + rand() % 3;    // 1, 2, or 3
//         int faceIndex = rand() % 6;        // 0 to 5

//         DiceFace face = faces[diceIndex][faceIndex];
//         res.push_back(face);

//         cout << "Dice " << diceIndex << " rolled: ";
//         switch (face) {
//             case DiceFace::Power:  cout << "Power"; break;
//             case DiceFace::Attack: cout << "Attack"; break;
//             case DiceFace::empty:  cout << "Empty"; break;
//         }
//         cout << '\n';
//     }

//     return res;
// }