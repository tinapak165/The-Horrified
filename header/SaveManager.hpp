#ifndef SAVE_H
#define SAVE_H
#include "Game.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

class SaveManager{
    private:
        Game& game ; 
    public:
        SaveManager(Game&);
        void saveGame(const std::string&);
        void loadGame(const std::string&);
        std::string generateNextFile();
        std::vector<std::string> getFiles();
        void registerSaveFiles(const std::string&) ;

};

#endif