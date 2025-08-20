#ifndef FACTORY_H
#define FACTORY_H
#include <memory>
#include "Game.hpp"
#include "Action.hpp"

enum class HeroType{ MAYOR , ARCHAEOLOGIST , COURIER , SCIENTIST};
enum class PerkType {REPEL , LATE_INTO_THE_NIGHT , BREAK_OF_DAWN };

class Factory{
    private:
        Game& game;
    public:
        Factory(Game&);
        std::unique_ptr<Hero> createHero(const std::string) ;
        std::unique_ptr<Perkcard> createPerkcard(const std::string);
        std::unique_ptr<HeroAction> createAction(const std::string , Hero*) ;
};

#endif