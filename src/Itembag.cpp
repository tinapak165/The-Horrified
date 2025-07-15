#include "Itembag.hpp"
#include "iostream"
#include <ctime>
ItemPool::ItemPool() {
    
   
    allItems.emplace_back("Dart", ItemColor::Red, 2, "Inn");
    allItems.emplace_back("Dart", ItemColor::Red, 2, "Inn");
    allItems.emplace_back("Fire Poker", ItemColor::Red, 3, "Mansion");
    allItems.emplace_back("Fire Poker", ItemColor::Red, 3, "Mansion");
    allItems.emplace_back("Rapier", ItemColor::Red, 5, "Theatre");
    allItems.emplace_back("Rapier", ItemColor::Red, 5, "Theatre");
    allItems.emplace_back("Shovel", ItemColor::Red, 2, "Graveyard");
    allItems.emplace_back("Torch", ItemColor::Red, 5, "Barn");
    allItems.emplace_back("Pistol", ItemColor::Red, 6, "Precinct");
    allItems.emplace_back("Knife", ItemColor::Red, 3, "Docks");
    allItems.emplace_back("Silver Cane", ItemColor::Red, 6, "Shop");
    allItems.emplace_back("Rifle", ItemColor::Red, 6, "Barn");
    allItems.emplace_back("Pitchfork", ItemColor::Red, 4, "Barn");
    allItems.emplace_back("Bear Trap", ItemColor::Red, 4, "Shop");
    allItems.emplace_back("Shovel", ItemColor::Red, 2, "Graveyard");
    allItems.emplace_back("Torch", ItemColor::Red, 5, "Barn");
    allItems.emplace_back("Pistol", ItemColor::Red, 6, "Precinct");
    allItems.emplace_back("Knife", ItemColor::Red, 3, "Docks");
    allItems.emplace_back("Silver Cane", ItemColor::Red, 6, "Shop");
    allItems.emplace_back("Rifle", ItemColor::Red, 6, "Barn");
    allItems.emplace_back("Pitchfork", ItemColor::Red, 4, "Barn");
    allItems.emplace_back("Bear Trap", ItemColor::Red, 4, "Shop");
    allItems.emplace_back("Speargun", ItemColor::Red, 4, "Institute");
    allItems.emplace_back("Speargun", ItemColor::Red, 4, "Institute");

// Yellow items
    
    allItems.emplace_back("Flower", ItemColor::Yellow, 2, "Docks");
    allItems.emplace_back("Tarot Card", ItemColor::Yellow, 3, "Camp");
    allItems.emplace_back("Garlic", ItemColor::Yellow, 2, "Inn");
    allItems.emplace_back("MirroRed Box", ItemColor::Yellow, 3, "Mansion");
    allItems.emplace_back("Stake", ItemColor::Yellow, 3, "Abbey");
    allItems.emplace_back("Charm", ItemColor::Yellow, 4, "Camp");
    allItems.emplace_back("Wolfsbane", ItemColor::Yellow, 4, "Camp");
    allItems.emplace_back("Tablet", ItemColor::Yellow, 3, "Museum");
    allItems.emplace_back("Violin", ItemColor::Yellow, 3, "Camp");
    allItems.emplace_back("Scroll of Thoth", ItemColor::Yellow, 4, "Museum");
    
    allItems.emplace_back("Flower", ItemColor::Yellow, 2, "Docks");
    allItems.emplace_back("Tarot Card", ItemColor::Yellow, 3, "Camp");
    allItems.emplace_back("Garlic", ItemColor::Yellow, 2, "Inn");
    allItems.emplace_back("MirroRed Box", ItemColor::Yellow, 3, "Mansion");
    allItems.emplace_back("Stake", ItemColor::Yellow, 3, "Abbey");
    allItems.emplace_back("Charm", ItemColor::Yellow, 4, "Camp");
    allItems.emplace_back("Wolfsbane", ItemColor::Yellow, 4, "Camp");
    allItems.emplace_back("Tablet", ItemColor::Yellow, 3, "Museum");
    allItems.emplace_back("Violin", ItemColor::Yellow, 3, "Camp");
    allItems.emplace_back("Scroll of Thoth", ItemColor::Yellow, 4, "Museum");


    
   // Blue items
    allItems.emplace_back("Anatomy Text", ItemColor::Blue, 1, "Institute");
    allItems.emplace_back("Centerfuge", ItemColor::Blue, 1, "Laboratory");
    allItems.emplace_back("Kite", ItemColor::Blue, 1, "Tower");
    allItems.emplace_back("Analysis", ItemColor::Blue, 2, "Institute");
    allItems.emplace_back("Experiment", ItemColor::Blue, 2, "Laboratory");
    allItems.emplace_back("Searchlight", ItemColor::Blue, 2, "Precinct");
    allItems.emplace_back("Telescope", ItemColor::Blue, 2, "Mansion");
    allItems.emplace_back("Cosmic Ray Diffuser", ItemColor::Blue, 3, "Tower");
    allItems.emplace_back("Rotenone", ItemColor::Blue, 3, "Institute");
    allItems.emplace_back("Research", ItemColor::Blue, 2, "Tower");
    allItems.emplace_back("Nebularium", ItemColor::Blue, 3, "Tower");
    allItems.emplace_back("Monocane Mixture", ItemColor::Blue, 3, "Inn");
    allItems.emplace_back("Fossil", ItemColor::Blue, 3, "Camp");
    //////
    allItems.emplace_back("Anatomy Text", ItemColor::Blue, 1, "Institute");
    allItems.emplace_back("Centerfuge", ItemColor::Blue, 1, "Laboratory");
    allItems.emplace_back("Kite", ItemColor::Blue, 1, "Tower");
    allItems.emplace_back("Analysis", ItemColor::Blue, 2, "Institute");
    allItems.emplace_back("Experiment", ItemColor::Blue, 2, "Laboratory");
    allItems.emplace_back("Searchlight", ItemColor::Blue, 2, "Precinct");
    allItems.emplace_back("Telescope", ItemColor::Blue, 2, "Mansion");
    allItems.emplace_back("Cosmic Ray Diffuser", ItemColor::Blue, 3, "Tower");
    allItems.emplace_back("Rotenone", ItemColor::Blue, 3, "Institute");
    allItems.emplace_back("Research", ItemColor::Blue, 2, "Tower");
    allItems.emplace_back("Nebularium", ItemColor::Blue, 3, "Tower");
    allItems.emplace_back("Monocane Mixture", ItemColor::Blue, 3, "Inn");
    allItems.emplace_back("Fossil", ItemColor::Blue, 3, "Camp");

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