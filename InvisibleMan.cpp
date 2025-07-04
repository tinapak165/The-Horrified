#include "InvisibleMan.hpp"
#include "item.hpp"
#include "location.hpp"
#include "monster.hpp"

InvisibleMan::InvisibleMan(Location* startLocation): Monster("InvisibleMan", startLocation){
    
    required_locations = {
        "Inn", "Barn", "Institute", "Laboratory", "Mansion"
    };


} 
// in game
 void InvisibleMan::special_power(Hero* h) {}

std::pair<Hero*, villager*> InvisibleMan::attack() {
    Location* loc = get_location();
    const auto& heroes = loc->get_heroes();
    const auto& villagers = loc->get_villagers();

    Hero* targetHero = nullptr;
    villager* targetVillager = nullptr;

    if (!heroes.empty()) {
        if (heroes.size() == 1)
            targetHero = heroes[0];
        else {
            std::cout << "Choose hero to attack:\n";
            for (size_t i = 0; i < heroes.size(); ++i)
                std::cout << i << ": " << heroes[i]->GetName() << '\n';
            int choice; std::cin >> choice;
            targetHero = heroes[choice];
        }
    }

    if (!villagers.empty()) {
        if (villagers.size() == 1)
            targetVillager = villagers[0];
        else {
            std::cout << "Choose villager to destroy:\n";
            for (size_t i = 0; i < villagers.size(); ++i)
                std::cout << i << ": " << villagers[i]->get_name() << '\n';
            int choice; std::cin >> choice;
            targetVillager = villagers[choice];
        }
    }

    return {targetHero, targetVillager};
}

bool InvisibleMan::can_be_defeated() {
    return evidence_locations.size() >= 5;
}

bool InvisibleMan::is_defeated() const {
    return defeated;
}

bool InvisibleMan::try_place_evidence(Item item) {
    std::string loc = item.getLocationName();

    
    if (required_locations.count(loc)) {
        
        if (evidence_locations.count(loc)) {
            std::cout << "You already used an item from " << loc << " as evidence.\n";
            return false;
        }

        
        evidence_locations.insert(loc);
        std::cout << "Evidence placed from " << loc << " (" 
                  << evidence_locations.size() << "/5)\n";
        return true;
    }

    std::cout << loc << " is not a valid evidence location.\n";
    return false;
}

bool InvisibleMan::add_evidence(const std::string& location) {
    if (evidence_locations.count(location))
    return false;

evidence_locations.insert(location);
return true;
}
int InvisibleMan::get_evidence_count() const {
    return static_cast<int>(evidence_locations.size());
}
