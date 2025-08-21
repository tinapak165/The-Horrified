#include "Dracula.hpp"

Dracula::Dracula(Location* startLocation): Monster("Dracula", startLocation , MonsterType::Dracula ,"../Assets/Monsters/Dracula.png" )
{
    loadTexture() ; 
    coffinsDestroyed["Cave"] = false;
    coffinsDestroyed["Dungeon"] = false;
    coffinsDestroyed["Crypt"] = false;
    coffinsDestroyed["Graveyard"] = false;
}

void Dracula::destroy_coffin_at(const std::string& locationName) {
    if (coffinsDestroyed.count(locationName) && !coffinsDestroyed[locationName]) {
        coffinsDestroyed[locationName] = true;
        //Coffin destroyed!
    } else {
        //No coffin to destroy or already destroyed.
    }
}



const std::map<std::string, bool>& Dracula::get_coffins_map() const {
    return coffinsDestroyed;
}


bool Dracula::is_defeated() const {
    return defeated;
   
}

bool Dracula::can_be_defeated(){
    for (const auto& keyvalue : coffinsDestroyed) {
        if (!keyvalue.second) return false;
    }
    return true;
}

void Dracula::special_power(Hero* active_hero) {
    
        Location* dracula_location = get_location();
    
        Location* current_hero_location = active_hero->GetCurrentLocation();
        if (current_hero_location) {
            auto& heroes_here = current_hero_location->get_heroes();
            heroes_here.erase(std::remove(heroes_here.begin(), heroes_here.end(), active_hero), heroes_here.end());
        }
    
        dracula_location->add_hero(active_hero , active_hero ->getTexture());
        active_hero->SetCurrentLocation(dracula_location);

    }
    
std::pair<Hero*, Villager*> Dracula::attack() {
        Location* currentLoc = get_location();
        const auto& heroes = currentLoc->get_heroes();
        const auto& villagers = currentLoc->get_villagers();
    
        Hero* chosenHero = nullptr;
        Villager* chosenVillager = nullptr;
    
            
        if (!heroes.empty()) {
            if (heroes.size() == 1) {
                chosenHero = heroes[0];
            } else {
                size_t index = rand() % heroes.size();
                chosenHero = heroes[index];
                
            }
        }
        if (!villagers.empty()) {
            if (villagers.size() == 1)
                chosenVillager = villagers[0];
            else {
                size_t index = rand() % villagers.size();
                chosenVillager = villagers[index];
            }
        }
    
        return {chosenHero, chosenVillager};
    }