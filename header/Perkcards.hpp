#ifndef PERK_HPP
#define PERK_HPP
#include <iostream>
#include <memory>
#include <vector>
#include "Hero.hpp"
#include "GameMap.hpp"
#include "Location.hpp"
#include "Itembag.hpp"
#include "Item.hpp"
#include "Dracula.hpp"
#include "InvisibleMan.hpp"

class Dracula ;

class Perkcard{
    private:
        std::string name; 
        Texture2D texture ;
        std::string message; 
        bool shouldClose = false;
        float messageTimer = 0.0f;
    public:
        Perkcard(const std::string  , const std::string&) ; 
        virtual void play(Hero* = nullptr) = 0  ;
        virtual void draw() = 0 ;
        virtual bool isDone() const = 0  ; 
        virtual void Reset() = 0 ;
        std::string get_name() const ; 
        Texture2D get_texture() const ;
        void DrawInfoPanel() ;
        void Drawtexture();
        std::string type(std::string);
        bool handleShouldClose() ; 
        void set_ShouldClose(bool) ;
        void Drawmessage(int , Color) ;
        void Setmessage(std::string) ; 
        virtual ~Perkcard() ; 
};

class Hurrycard :public Perkcard{
    private:
        int currentHeroIndex = 0 ; 
        int moveStep = 0 ;
        bool done = false ;
        std::string chosenPlace ; 
        Location* chosenLocation = nullptr ;

        bool typing = true ; 
        bool Finished = false ;

        std::vector<Hero*> heroes ; 
        GameMap& map ; 
    public:
        Hurrycard(const std::vector<Hero*>&, GameMap&) ; 
        void play(Hero* = nullptr) override ;
        void draw() override ; 
        bool isDone() const override ; 
        void Reset() override ;
};

class Repelcard : public Perkcard{
    private:
        Dracula* dracula ; 
        InvisibleMan* invisibleman ; 
        GameMap& map ;
        
        int currentMonsterIndex = 0 ; 
        int moveStep = 0 ; 
        bool done = false ;
        std::string chosenPlace ; 
        Location* chosenLocation = nullptr ;

        bool typing = true ; 
        bool Finished = false ;

    public:
        Repelcard(Dracula * ,InvisibleMan * , GameMap &) ; 
        void play(Hero* = nullptr) override ; 
        void draw() override ; 
        bool isDone() const override ;
        void Reset() override ;

};

class LateintotheNightCARD : public Perkcard{
   private:
        bool done = false ;
        bool messageVisible = false;
        
        public:
        LateintotheNightCARD() ; 
        void play(Hero*)  ;
        void draw() override ; 
        bool isDone() const override ;
        void Reset(){} ;
};

class BreakofDawnCARD : public Perkcard{
    private:
        ItemPool& pool ;
        GameMap& map ;
        bool done = false ;
        bool messageVisible = false;    
   
    public:
        BreakofDawnCARD(ItemPool& , GameMap&) ; 
        void play(Hero* = nullptr) override ;   
        void draw() override ; 
        bool isDone() const override ; 
        void Reset() {} ;

};

class OverstockCard : public Perkcard {
    private:
        ItemPool& pool ;
        GameMap& map ;
        bool done = false ;
        bool messageVisible = false;  

    public:
        OverstockCard(ItemPool& , GameMap&) ; 
        void play(Hero* = nullptr) override ; 
        void draw() override ; 
        bool isDone() const override ;  
        void Reset() {} ;
};

class VisitfromtheDetectiveCARD : public Perkcard{
    private:
        InvisibleMan* invisibleman ; 
        GameMap& map ;
        
        bool done = false ;
        std::string chosenPlace ; 
        bool typing = true ; 

    public:
        VisitfromtheDetectiveCARD(InvisibleMan*, GameMap&) ; 
        void play(Hero* = nullptr) override ; 
        void draw() override ; 
        bool isDone() const override ;
        void Reset(){};

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