#include "Itembag.hpp"
#include "iostream"

ItemPool::ItemPool() {
    
   
    allItems.emplace_back("Dart", ItemColor::RED, 2, "Inn");
    allItems.emplace_back("Dart", ItemColor::RED, 2, "Inn");
    allItems.emplace_back("Fire Poker", ItemColor::RED, 3, "Mansion");
    allItems.emplace_back("Fire Poker", ItemColor::RED, 3, "Mansion");
    allItems.emplace_back("Rapier", ItemColor::RED, 5, "Theatre");
    allItems.emplace_back("Rapier", ItemColor::RED, 5, "Theatre");
    allItems.emplace_back("Shovel", ItemColor::RED, 2, "Graveyard");
    allItems.emplace_back("Torch", ItemColor::RED, 5, "Barn");
    allItems.emplace_back("Pistol", ItemColor::RED, 6, "Precinct");
    allItems.emplace_back("Knife", ItemColor::RED, 3, "Docks");
    allItems.emplace_back("Silver Cane", ItemColor::RED, 6, "Shop");
    allItems.emplace_back("Rifle", ItemColor::RED, 6, "Barn");
    allItems.emplace_back("Pitchfork", ItemColor::RED, 4, "Barn");
    allItems.emplace_back("Bear Trap", ItemColor::RED, 4, "Shop");
    allItems.emplace_back("Shovel", ItemColor::RED, 2, "Graveyard");
    allItems.emplace_back("Torch", ItemColor::RED, 5, "Barn");
    allItems.emplace_back("Pistol", ItemColor::RED, 6, "Precinct");
    allItems.emplace_back("Knife", ItemColor::RED, 3, "Docks");
    allItems.emplace_back("Silver Cane", ItemColor::RED, 6, "Shop");
    allItems.emplace_back("Rifle", ItemColor::RED, 6, "Barn");
    allItems.emplace_back("Pitchfork", ItemColor::RED, 4, "Barn");
    allItems.emplace_back("Bear Trap", ItemColor::RED, 4, "Shop");
    allItems.emplace_back("Speargun", ItemColor::RED, 4, "Institute");
    allItems.emplace_back("Speargun", ItemColor::RED, 4, "Institute");

// yellow items
    
    allItems.emplace_back("Flower", ItemColor::YELLOW, 2, "Docks");
    allItems.emplace_back("Tarot Card", ItemColor::YELLOW, 3, "Camp");
    allItems.emplace_back("Garlic", ItemColor::YELLOW, 2, "Inn");
    allItems.emplace_back("Mirrored Box", ItemColor::YELLOW, 3, "Mansion");
    allItems.emplace_back("Stake", ItemColor::YELLOW, 3, "Abbay");
    allItems.emplace_back("Charm", ItemColor::YELLOW, 4, "Camp");
    allItems.emplace_back("Wolfsbane", ItemColor::YELLOW, 4, "Camp");
    allItems.emplace_back("Tablet", ItemColor::YELLOW, 3, "Museum");
    allItems.emplace_back("Violin", ItemColor::YELLOW, 3, "Camp");
    allItems.emplace_back("Scroll of Thoth", ItemColor::YELLOW, 4, "Museum");
    
    allItems.emplace_back("Flower", ItemColor::YELLOW, 2, "Docks");
    allItems.emplace_back("Tarot Card", ItemColor::YELLOW, 3, "Camp");
    allItems.emplace_back("Garlic", ItemColor::YELLOW, 2, "Inn");
    allItems.emplace_back("Mirrored Box", ItemColor::YELLOW, 3, "Mansion");
    allItems.emplace_back("Stake", ItemColor::YELLOW, 3, "Abbey");
    allItems.emplace_back("Charm", ItemColor::YELLOW, 4, "Camp");
    allItems.emplace_back("Wolfsbane", ItemColor::YELLOW, 4, "Camp");
    allItems.emplace_back("Tablet", ItemColor::YELLOW, 3, "Museum");
    allItems.emplace_back("Violin", ItemColor::YELLOW, 3, "Camp");
    allItems.emplace_back("Scroll of Thoth", ItemColor::YELLOW, 4, "Museum");


    
   // blue items
    allItems.emplace_back("Anatomy Text", ItemColor::BLUE, 1, "Institute");
    allItems.emplace_back("Centerfuge", ItemColor::BLUE, 1, "Laboratory");
    allItems.emplace_back("Kite", ItemColor::BLUE, 1, "Tower");
    allItems.emplace_back("Analysis", ItemColor::BLUE, 2, "Institute");
    allItems.emplace_back("Experiment", ItemColor::BLUE, 2, "Laboratory");
    allItems.emplace_back("Searchlight", ItemColor::BLUE, 2, "Precinct");
    allItems.emplace_back("Telescope", ItemColor::BLUE, 2, "Mansion");
    allItems.emplace_back("Cosmic Ray Diffuser", ItemColor::BLUE, 3, "Tower");
    allItems.emplace_back("Rotenone", ItemColor::BLUE, 3, "Institute");
    allItems.emplace_back("Research", ItemColor::BLUE, 2, "Tower");
    allItems.emplace_back("Nebularium", ItemColor::BLUE, 3, "Tower");
    allItems.emplace_back("Monocane Mixture", ItemColor::BLUE, 3, "Inn");
    allItems.emplace_back("Fossil", ItemColor::BLUE, 3, "Camp");
    //////
    allItems.emplace_back("Anatomy Text", ItemColor::BLUE, 1, "Institute");
    allItems.emplace_back("Centerfuge", ItemColor::BLUE, 1, "Laboratory");
    allItems.emplace_back("Kite", ItemColor::BLUE, 1, "Tower");
    allItems.emplace_back("Analysis", ItemColor::BLUE, 2, "Institute");
    allItems.emplace_back("Experiment", ItemColor::BLUE, 2, "Laboratory");
    allItems.emplace_back("Searchlight", ItemColor::BLUE, 2, "Precinct");
    allItems.emplace_back("Telescope", ItemColor::BLUE, 2, "Mansion");
    allItems.emplace_back("Cosmic Ray Diffuser", ItemColor::BLUE, 3, "Tower");
    allItems.emplace_back("Rotenone", ItemColor::BLUE, 3, "Institute");
    allItems.emplace_back("Research", ItemColor::BLUE, 2, "Tower");
    allItems.emplace_back("Nebularium", ItemColor::BLUE, 3, "Tower");
    allItems.emplace_back("Monocane Mixture", ItemColor::BLUE, 3, "Inn");
    allItems.emplace_back("Fossil", ItemColor::BLUE, 3, "Camp");


    // اینجا همه ۶۰ آیتم را کامل می‌کنیم بعداً...
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(allItems.begin(), allItems.end(), g);
}

// std::vector<Item> ItemPool::draw_random_items(int count) {
 
//     if ((int)allItems.size() < count)
//     std::cerr << "Warning: not enough items in pool! Requested: " << count << ", Available: " << allItems.size() << '\n';
//     std::cout<<allItems.size();
//     std::vector<Item> drawn;
//     for (int i = 0; i <= count && !allItems.empty(); ++i) {
//         drawn.push_back(allItems.back());
//         allItems.pop_back();
//     }
//     return drawn;
// }



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
