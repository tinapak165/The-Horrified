#include "monster.hpp"
#include "Dracula.hpp"

bool Dracula::can_be_defeated() const{}

void Dracula::special_power () {

    std::cout<<" special power ";

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
            Monster* local = monsters[0]; // فرض می‌کنیم فقط یک محلی وجود دارد
            std::cout << get_name() << " destroys the local!\n";
            
            // currentLoc->remove_local(local);
        }
    }
}
