#include "Itembag.hpp"

ItemPool::ItemPool() {
    // نمونه فقط بخشی از آیتم‌ها — بعداً همه ۶۰ آیتم را کامل می‌کنیم
    allItems.emplace_back("Garlic", ItemColor::RED, 2, "Barn");
    allItems.emplace_back("Crucifix", ItemColor::RED, 3, "Church");
    allItems.emplace_back("Stake", ItemColor::RED, 1, "Barn");

    allItems.emplace_back("Journal", ItemColor::YELLOW, 2, "Institute");
    allItems.emplace_back("Tarot Card", ItemColor::YELLOW, 3, "Theater");

    allItems.emplace_back("Flower", ItemColor::BLUE, 1, "Cave");
    allItems.emplace_back("Map", ItemColor::BLUE, 2, "Docks");
    allItems.emplace_back("Lantern", ItemColor::BLUE, 3, "Camp");

    // اینجا همه ۶۰ آیتم را کامل می‌کنیم بعداً...
}

std::vector<Item> ItemPool::draw_random_items(int count) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(allItems.begin(), allItems.end(), g);

    std::vector<Item> drawn;
    for (int i = 0; i < count && !allItems.empty(); ++i) {
        drawn.push_back(allItems.back());
        allItems.pop_back();
    }
    return drawn;
}
