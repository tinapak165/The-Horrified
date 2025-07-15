#include "Itembag.hpp"
#include "iostream"
#include <ctime>
ItemPool::ItemPool() {
    
   
    allItems.emplace_back("Dart", ItemColor::red, 2, "Inn");
    allItems.emplace_back("Dart", ItemColor::red, 2, "Inn");
    allItems.emplace_back("Fire Poker", ItemColor::red, 3, "Mansion");
    allItems.emplace_back("Fire Poker", ItemColor::red, 3, "Mansion");
    allItems.emplace_back("Rapier", ItemColor::red, 5, "Theatre");
    allItems.emplace_back("Rapier", ItemColor::red, 5, "Theatre");
    allItems.emplace_back("Shovel", ItemColor::red, 2, "Graveyard");
    allItems.emplace_back("Torch", ItemColor::red, 5, "Barn");
    allItems.emplace_back("Pistol", ItemColor::red, 6, "Precinct");
    allItems.emplace_back("Knife", ItemColor::red, 3, "Docks");
    allItems.emplace_back("Silver Cane", ItemColor::red, 6, "Shop");
    allItems.emplace_back("Rifle", ItemColor::red, 6, "Barn");
    allItems.emplace_back("Pitchfork", ItemColor::red, 4, "Barn");
    allItems.emplace_back("Bear Trap", ItemColor::red, 4, "Shop");
    allItems.emplace_back("Shovel", ItemColor::red, 2, "Graveyard");
    allItems.emplace_back("Torch", ItemColor::red, 5, "Barn");
    allItems.emplace_back("Pistol", ItemColor::red, 6, "Precinct");
    allItems.emplace_back("Knife", ItemColor::red, 3, "Docks");
    allItems.emplace_back("Silver Cane", ItemColor::red, 6, "Shop");
    allItems.emplace_back("Rifle", ItemColor::red, 6, "Barn");
    allItems.emplace_back("Pitchfork", ItemColor::red, 4, "Barn");
    allItems.emplace_back("Bear Trap", ItemColor::red, 4, "Shop");
    allItems.emplace_back("Speargun", ItemColor::red, 4, "Institute");
    allItems.emplace_back("Speargun", ItemColor::red, 4, "Institute");

// yellow items
    
    allItems.emplace_back("Flower", ItemColor::yellow, 2, "Docks");
    allItems.emplace_back("Tarot Card", ItemColor::yellow, 3, "Camp");
    allItems.emplace_back("Garlic", ItemColor::yellow, 2, "Inn");
    allItems.emplace_back("Mirrored Box", ItemColor::yellow, 3, "Mansion");
    allItems.emplace_back("Stake", ItemColor::yellow, 3, "Abbey");
    allItems.emplace_back("Charm", ItemColor::yellow, 4, "Camp");
    allItems.emplace_back("Wolfsbane", ItemColor::yellow, 4, "Camp");
    allItems.emplace_back("Tablet", ItemColor::yellow, 3, "Museum");
    allItems.emplace_back("Violin", ItemColor::yellow, 3, "Camp");
    allItems.emplace_back("Scroll of Thoth", ItemColor::yellow, 4, "Museum");
    
    allItems.emplace_back("Flower", ItemColor::yellow, 2, "Docks");
    allItems.emplace_back("Tarot Card", ItemColor::yellow, 3, "Camp");
    allItems.emplace_back("Garlic", ItemColor::yellow, 2, "Inn");
    allItems.emplace_back("Mirrored Box", ItemColor::yellow, 3, "Mansion");
    allItems.emplace_back("Stake", ItemColor::yellow, 3, "Abbey");
    allItems.emplace_back("Charm", ItemColor::yellow, 4, "Camp");
    allItems.emplace_back("Wolfsbane", ItemColor::yellow, 4, "Camp");
    allItems.emplace_back("Tablet", ItemColor::yellow, 3, "Museum");
    allItems.emplace_back("Violin", ItemColor::yellow, 3, "Camp");
    allItems.emplace_back("Scroll of Thoth", ItemColor::yellow, 4, "Museum");


    
   // blue items
    allItems.emplace_back("Anatomy Text", ItemColor::blue, 1, "Institute");
    allItems.emplace_back("Centerfuge", ItemColor::blue, 1, "Laboratory");
    allItems.emplace_back("Kite", ItemColor::blue, 1, "Tower");
    allItems.emplace_back("Analysis", ItemColor::blue, 2, "Institute");
    allItems.emplace_back("Experiment", ItemColor::blue, 2, "Laboratory");
    allItems.emplace_back("Searchlight", ItemColor::blue, 2, "Precinct");
    allItems.emplace_back("Telescope", ItemColor::blue, 2, "Mansion");
    allItems.emplace_back("Cosmic Ray Diffuser", ItemColor::blue, 3, "Tower");
    allItems.emplace_back("Rotenone", ItemColor::blue, 3, "Institute");
    allItems.emplace_back("Research", ItemColor::blue, 2, "Tower");
    allItems.emplace_back("Nebularium", ItemColor::blue, 3, "Tower");
    allItems.emplace_back("Monocane Mixture", ItemColor::blue, 3, "Inn");
    allItems.emplace_back("Fossil", ItemColor::blue, 3, "Camp");
    //////
    allItems.emplace_back("Anatomy Text", ItemColor::blue, 1, "Institute");
    allItems.emplace_back("Centerfuge", ItemColor::blue, 1, "Laboratory");
    allItems.emplace_back("Kite", ItemColor::blue, 1, "Tower");
    allItems.emplace_back("Analysis", ItemColor::blue, 2, "Institute");
    allItems.emplace_back("Experiment", ItemColor::blue, 2, "Laboratory");
    allItems.emplace_back("Searchlight", ItemColor::blue, 2, "Precinct");
    allItems.emplace_back("Telescope", ItemColor::blue, 2, "Mansion");
    allItems.emplace_back("Cosmic Ray Diffuser", ItemColor::blue, 3, "Tower");
    allItems.emplace_back("Rotenone", ItemColor::blue, 3, "Institute");
    allItems.emplace_back("Research", ItemColor::blue, 2, "Tower");
    allItems.emplace_back("Nebularium", ItemColor::blue, 3, "Tower");
    allItems.emplace_back("Monocane Mixture", ItemColor::blue, 3, "Inn");
    allItems.emplace_back("Fossil", ItemColor::blue, 3, "Camp");

}


std::vector<Item> ItemPool::draw_random_items(int count) {
    srand(time(0)) ;
    random_shuffle(allItems.begin(), allItems.end());
    if ((int)allItems.size() < count)
    std::cerr << "Warning: not enough items in pool! Requested: " << count << ", Available: " << allItems.size() << '\n';
  //  std::cout<<allItems.size();
    std::vector<Item> drawn;
    for (int i = 0; i < count && !allItems.empty(); ++i) {
        drawn.push_back(allItems.back());
        allItems.pop_back();
    }
    return drawn;
}

void ItemPool::add_item(const Item& item) {
    allItems.push_back(item);
}

void ItemPool::add_items(const std::vector<Item>& items) {
    for (const auto& item : items) {
        allItems.push_back(item);
    }
}