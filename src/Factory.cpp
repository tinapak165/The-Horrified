#include "Factory.hpp"

Factory::Factory(Game& game) : game(game){}

std::unique_ptr<Hero> Factory::createHero(const std::string type){
    if(type == "mayor")
        return std::make_unique<Mayor>(game.get_map()) ;
    else if ( type == "archaeologist") 
        return std::make_unique<Archaeologist>(game.get_map());
    else if (type == "courier") 
        return std::make_unique<Courier>(game.get_map() , game.get_turnManager()) ;
    else if (type == "scientist") 
        return std::make_unique<Scientist>(game.get_map()) ;

    return nullptr;
}

std::unique_ptr<Perkcard> Factory::createPerkcard(const std::string type){
    if (type == "Repel") return std::make_unique<Repelcard>(game.get_dracula(), game.get_invisibleMan(), game.get_map());
    if (type == "Hurry") return std::make_unique<Hurrycard>(game.get_turnManager().get_heroes(), game.get_map());
    if (type == "Late into the Night") return std::make_unique<LateintotheNightCARD>();
    if (type == "Break of Dawn") return std::make_unique<BreakofDawnCARD>(game.get_pool() , game.get_map());
    if (type == "Overstock") return std::make_unique<OverstockCard>( game.get_pool() , game.get_map());
    if (type == "Visit from the Detective") return std::make_unique<VisitfromtheDetectiveCARD>(game.get_invisibleMan(), game.get_map());

    return nullptr;
}

std::unique_ptr<HeroAction> Factory::createAction(const std::string type , Hero* currentHero){
    if (type == "Help") 
        return std::make_unique<HelpAction>(currentHero) ;
    else if(type == "Quit") { 
        game.set_currentPhase(Phase::MonsterPhase) ; 
        game.set_HeroTurnInProgress(false) ; 
        game.get_turnManager().next_turn() ; 
    }
    else if (type == "Perk") 
        return std::make_unique<ChoosePerkCardAction>(currentHero , game) ;
    else if (type == "Move") 
        return std::make_unique<MoveAction>(game.get_map() , currentHero) ;
    else if (type == "Guide") 
        return std::make_unique<GuideAction>(game.get_map() , currentHero) ;
    else if (type == "Pickup") 
        return std::make_unique<PickUpAction>(currentHero) ;
    else if (type == "Special")   
        return std::make_unique<SpecialAction>(currentHero , game.get_map()) ;
    else if (type == "Advance") 
        return std::make_unique<AdvanceAction>(currentHero , game.get_dracula() , game.get_pool() , game.get_map() ,game.get_invisibleMan());
    else if (type == "Defeat") 
        return std::make_unique<DefeatAction>(currentHero, game.get_invisibleMan(), game.get_dracula());
    
    return nullptr;
}