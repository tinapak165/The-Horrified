#include "monster.hpp"
#include "Dracula.hpp"

Dracula::Dracula(Location* startLocation): Monster("Dracula", startLocation)
 { // key value
    coffinsDestroyed["Cave"] = false;
    coffinsDestroyed["Dungeon"] = false;
    coffinsDestroyed["Crypt"] = false;
    coffinsDestroyed["Graveyard"] = false;
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


Dracula::Dracula(Location* startLocation)
    : Monster("Dracula", startLocation) {
    coffinsDestroyed["Cave"] = false;
    coffinsDestroyed["Dungeon"] = false;
    coffinsDestroyed["Crypt"] = false;
    coffinsDestroyed["Graveyard"] = false;
}

void Dracula::destroy_coffin_at(std::string locationName) {
    if (coffinsDestroyed.count(locationName) && !coffinsDestroyed[locationName]) {
        coffinsDestroyed[locationName] = true;
        std::cout << "Coffin at " << locationName << " destroyed!\n";
    } else {
        std::cout << "No coffin to destroy at " << locationName << " or already destroyed.\n";
    }
}

bool Dracula::is_defeated() const {
   
}

void Dracula::print_remaining_coffins() const {
    std::cout << "Remaining coffins:\n";
    for (const auto& [loc, destroyed] : coffinsDestroyed) {
        if (!destroyed)
            std::cout << "- " << loc << '\n';
    }
}

bool Dracula::can_be_defeated(){
    for (const auto& [loc, destroyed] : coffinsDestroyed) {
        if (!destroyed) return false;
    }
    return true;
}



 void Dracula::special_power(Hero* active_hero) {
    
        Location* dracula_location = get_location();
    
        std::cout << "Dracula uses Dark Charm! Pulling " << active_hero->GetName() 
                  << " to " << dracula_location->get_name() << "!" << std::endl;
    
        // برداشتن هیرو از لوکیشن فعلی
        // Location* current_hero_location = active_hero->get_location();
        // if (current_hero_location) {
        //     auto& heroes_here = current_hero_location->get_heroes();
        //     heroes_here.erase(std::remove(heroes_here.begin(), heroes_here.end(), active_hero), heroes_here.end());
        // }
    
        // انتقال به لوکیشن دراکولا
        dracula_location->add_hero(active_hero);
        // active_hero->set_location(dracula_location);
    }
    


void Dracula::attack() {
    Location* currentLoc = get_location();
   const std::vector<Hero*>& heroes = currentLoc->get_heroes();
    const std::vector<Monster*>& monsters = currentLoc->get_monsters();

    // بررسی وجود قهرمان یا محلی در مکان فعلی
    if (!heroes.empty() || !monsters.empty()) {
        //  تابع قهرمان رو بنویسسس
        if (!heroes.empty()) {
            Hero* hero = heroes[0]; // فرض می‌کنیم فقط یک قهرمان وجود دارد
            std::cout << get_name() << " attacks " << hero->GetName() << "!\n";
            // قهرمان زخمی می‌شود و به بیمارستان می‌رود
            // اینجا باید تابعی برای انتقال قهرمان به بیمارستان بنویسید
            // hero->move_to_hospital();
        }

        // اگر محلی وجود دارد رو بعدااااا بنویس
        if (!monsters.empty()) {
            // Monster* local = monsters[0]; // فرض می‌کنیم فقط یک محلی وجود دارد
            std::cout << get_name() << " destroys the local!\n";
            
            // currentLoc->remove_local(local);
        }
    }
}
