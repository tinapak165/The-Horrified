#include "InvisibleMan.hpp"
#include "Location.hpp"

InvisibleMan::InvisibleMan(Location* startLocation): Monster("InvisibleMan", startLocation , MonsterType::InvisibleMan , "../Assets/Monsters/InvisibleMan.png"){
    loadTexture() ;   
    required_locations = {
        "Inn", "Barn", "Institute", "Laboratory", "Mansion"
    };


} 
// in game
 void InvisibleMan::special_power(Hero* h) {}

std::pair<Hero*, Villager*> InvisibleMan::attack() {
    Location* loc = get_location();
    const auto& heroes = loc->get_heroes();
    const auto& villagers = loc->get_villagers();

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

bool InvisibleMan::can_be_defeated() {
    return evidence_locations.size() >= 5;
}

bool InvisibleMan::is_defeated() const {
    return defeated;
}

bool InvisibleMan::add_evidence(const std::string& location) {
    if (evidence_locations.count(location))
    return false;

    evidence_locations.insert(location);
    return true;
}
std::unordered_set<std::string> InvisibleMan::get_evidence_locations(){ return evidence_locations; } 


int InvisibleMan::get_evidence_count() const {
    return static_cast<int>(evidence_locations.size());
}