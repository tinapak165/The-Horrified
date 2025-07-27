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
    public:
        Perkcard(const std::string  , const std::string&) ; 
        virtual void play(Hero* = nullptr) = 0  ;
        virtual void draw() = 0 ;
        virtual bool isDone() const = 0  ; 
        std::string get_name() const ; 
        Texture2D get_texture() const ;
        virtual ~Perkcard() ; 
};

class Hurrycard :public Perkcard{
    private:
        int currentHeroIndex = 0 ; 
        int moveStep = 0 ; // 0 -> first move, 1 -> second move
        bool done = false ;
        std::string message ;
        std::string chosenPlace ; 
        Location* chosenLocation = nullptr ;

        bool typing = true ; 
        bool validInput = false ; 
        bool Finished = false ;

        double messageStartTime = 0.0;
        bool showingMessage = false;


        std::vector<Hero*> heroes ; 
        GameMap& map ; 
    public:
        Hurrycard(const std::vector<Hero*>&, GameMap&) ; 
        void play(Hero* = nullptr) override ;
        void draw() override ; 
        bool isDone() const override ; 
};

class Repelcard : public Perkcard{
    private:
        Dracula* dracula ; 
        InvisibleMan* invisibleman ; 
        GameMap& map ;
        
        int currentMonsterIndex = 0 ; 
        int moveStep = 0 ; // 0 -> first move, 1 -> second move
        bool done = false ;
        std::string message ;
        std::string chosenPlace ; 
        Location* chosenLocation = nullptr ;

        bool typing = true ; 
        bool validInput = false ; 
        bool Finished = false ;

        double messageStartTime = 0.0;
        bool showingMessage = false;

    public:
        Repelcard(Dracula * ,InvisibleMan * , GameMap &) ; 
        void play(Hero* = nullptr) override ; 
        void draw() override ; 
        bool isDone() const override ;
};

class LateintotheNightCARD : public Perkcard{
   private:
        bool done = false ;
        std::string message ;
        float messageTimer = 0.0f;       // زمان شروع نمایش پیام
        const float messageDuration = 2.5f; // چند ثانیه پیام بمونه (مثلاً 2.5 ثانیه)
        bool messageVisible = false;     // آیا پیام باید نشون داده بشه؟
        
        public:
        LateintotheNightCARD() ; 
        void play(Hero*)  ;
        void draw() override ; 
        bool isDone() const override ;
};

class BreakofDawnCARD : public Perkcard{
    private:
        ItemPool& pool ;
        GameMap& map ;
        bool done = false ;
        std::vector<std::string> message ;
        float messageTimer = 0.0f;     
        const float messageDuration = 2.5f; 
        bool messageVisible = false;    
   
    public:
        BreakofDawnCARD(ItemPool& , GameMap&) ; 
        void play(Hero* = nullptr) override ;   
        void draw() override ; 
        bool isDone() const override ;    

};

class OverstockCard : public Perkcard {
    private:
        ItemPool& pool ;
        GameMap& map ;
        std::vector<Hero*> heroes ; 
        bool done = false ;
        std::vector<std::string> message ;
        float messageTimer = 0.0f;     
        const float messageDuration = 2.5f; 
        bool messageVisible = false;  

    public:
        OverstockCard(std::vector<Hero*> , ItemPool& , GameMap&) ; 
        void play(Hero* = nullptr) override ; 
        void draw() override ; 
        bool isDone() const override ;      
};

class VisitfromtheDetectiveCARD : public Perkcard{
    private:
        InvisibleMan* invisibleman ; 
        GameMap& map ;
        
        bool done = false ;
        std::string message ;
        std::string chosenPlace ; 
        Location* chosenLocation = nullptr ;

        bool typing = true ; 
        bool validInput = false ; 
        bool Finished = false ;

        double messageStartTime = 0.0;
        bool showingMessage = false; 

    public:
        VisitfromtheDetectiveCARD(InvisibleMan*, GameMap&) ; 
        void play(Hero* = nullptr) override ; 
        void draw() override ; 
        bool isDone() const override ;
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