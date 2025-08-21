#include "Dice.hpp"

Dice::Dice(int c) : count(c) {
    faces[0] = {
        DiceFace::Attack,
        DiceFace::Power, 
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


std::vector<DiceFace> Dice::roll(int numOfDice) {

    if (numOfDice <= 0 || numOfDice > 3) {
        throw std::out_of_range("invalid dice count");
    }

    std::vector<int> DiceIndices = {0, 1, 2};
    std::shuffle(DiceIndices.begin(), DiceIndices.end(), std::default_random_engine(std::random_device{}()));

    std::vector<DiceFace> res;
    for (int i = 0; i < numOfDice; i++) {
        int RandomDice = DiceIndices[i];
        int RandomFace = rand() % 6;
        DiceFace face = faces[RandomDice][RandomFace];
        res.push_back(face);
    }

    return res;
}

