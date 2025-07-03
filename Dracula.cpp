#include "monster.hpp"
#include "Dracula.hpp"

Dracula::Dracula(Location* startLocation): Monster("Dracula", startLocation)
 { // key value
    // coffinsDestroyed["Cave"] = false;
    coffinsDestroyed["Dungeon"] = false;
    // coffinsDestroyed["Crypt"] = false;
    // coffinsDestroyed["Graveyard"] = false;
}

// remmember first word is capital 
void Dracula::destroy_coffin_at(std::string locationName) {
    if (coffinsDestroyed.count(locationName) && !coffinsDestroyed[locationName]) {
        coffinsDestroyed[locationName] = true;
        std::cout << "Coffin at " << locationName << " destroyed!\n";
    } else {
        std::cout << "No coffin to destroy at " << locationName << " or already destroyed.\n";
    }
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
    
    
       // برداشتن هیرو از لوکیشن فعلی
        Location* current_hero_location = active_hero->GetCurrentLocation();
        if (current_hero_location) {
            auto& heroes_here = current_hero_location->get_heroes();
            heroes_here.erase(std::remove(heroes_here.begin(), heroes_here.end(), active_hero), heroes_here.end());
        }
    
        // انتقال به لوکیشن دراکولا
        dracula_location->add_hero(active_hero);
        active_hero->SetCurrentLocation(dracula_location);
        std::cout << "Dracula uses Dark Charm! Pulling " << active_hero->GetName() 
        << " to " << dracula_location->get_name() << "!" << std::endl;
    }
    

    std::pair<Hero*, villager*> Dracula::attack() {
        Location* currentLoc = get_location();
        const auto& heroes = currentLoc->get_heroes();
        const auto& villagers = currentLoc->get_villagers();
    
        Hero* chosenHero = nullptr;
        villager* chosenVillager = nullptr;
    
        if (!heroes.empty()) {
            if (heroes.size() == 1)
                chosenHero = heroes[0];
            else {
                std::cout << "Choose a hero to attack:\n";
                for (size_t i = 0; i < heroes.size(); ++i)
                    std::cout << i << ": " << heroes[i]->GetName() << '\n';
                int index;
                std::cin >> index;
                chosenHero = heroes[index];
            }
        }
    
        if (!villagers.empty()) {
            if (villagers.size() == 1)
                chosenVillager = villagers[0];
            else {
                std::cout << "Choose a villager to destroy:\n";
                for (size_t i = 0; i < villagers.size(); ++i)
                    std::cout << i << ": " << villagers[i]->get_name() << '\n';
                int index;
                std::cin >> index;
                chosenVillager = villagers[index];
            }
        }
    
        return {chosenHero, chosenVillager};
    }
    