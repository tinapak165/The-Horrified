#ifndef PERK_HPP
#define PERK_HPP
#include <iostream>
#include <memory>
#include <vector>
#include "Hero.hpp"
#include "GameMap.hpp"
#include "location.hpp"
#include "monster.hpp"
#include "Itembag.hpp"
#include "item.hpp"
#include "Dracula.hpp"
#include "InvisibleMan.hpp"

class Perkcard{
    private:
        std::string name; 
    public:
        Perkcard(std::string name) ; 
        virtual void play(Hero* hero = nullptr) = 0  ;
        std::string get_name() const ; 
        virtual ~Perkcard() = default ; 
};

class Hurrycard :public Perkcard{
    private:
        Hero* mayor ; 
        Hero* arch ; 
        GameMap& map ; 
    public:
        Hurrycard(Hero* , Hero* , GameMap& map) ; 
        void play(Hero* = nullptr) override ;
};

class Repelcard : public Perkcard{
    private:
    //   Dracula* dracula ; 
        InvisibleMan* invisibleman ; 
        GameMap& map ;
    public:
        Repelcard() ; 
        void play(Hero* = nullptr) override ; 
};

class LateintotheNightCARD : public Perkcard{
   private:
       
    public:
        LateintotheNightCARD() ; 
        void play(Hero*)  ;
};

class BreakofDawnCARD :public Perkcard{
    private:
        ItemPool pool ;
        GameMap& map ;
    public:
        BreakofDawnCARD(ItemPool , GameMap&) ; 
        void play(Hero* = nullptr) override ;       

};

class OverstockCard : public Perkcard {
    private:
        ItemPool pool ;
        GameMap& map ;
    public:
        OverstockCard(ItemPool , GameMap&) ; 
        void play(Hero* = nullptr) override ;       
};

class VisitfromtheDetectiveCARD : public Perkcard{
    private:
    //Monster* invisibleman
        InvisibleMan* invisibleman ; 
        GameMap& map ;
    public:
        VisitfromtheDetectiveCARD(InvisibleMan* , GameMap&) ; 
        void play(Hero* = nullptr) override ; 
};

class PerkDeck{
    private:
        std::vector<std::unique_ptr<Perkcard>> cards;
    public:
        PerkDeck() ; 
        void addCard(std::unique_ptr<Perkcard> card) ; 
        std::unique_ptr<Perkcard> drawcard();
};

#endif