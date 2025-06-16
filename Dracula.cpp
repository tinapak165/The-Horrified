#include "monster.hpp"
#include "Dracula.hpp"

bool Dracula::can_be_defeated() const{ return false;}



 void Dracula::special_power(Hero* active_hero) {
        Location* dracula_location = get_location();
    
        std::cout << "Dracula uses Dark Charm! Pulling " << active_hero->GetName() 
                  << " to " << dracula_location->get_name() << "!" << std::endl;
    
        // برداشتن هیرو از لوکیشن فعلی
        Location* current_hero_location = active_hero->get_location();
        if (current_hero_location) {
            auto& heroes_here = current_hero_location->get_heroes();
            heroes_here.erase(std::remove(heroes_here.begin(), heroes_here.end(), active_hero), heroes_here.end());
        }
    
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
