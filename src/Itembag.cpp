#include "Itembag.hpp"
#include "iostream"
#include <ctime>
ItemPool::ItemPool() {
    
   // Red items
allItems.emplace_back("Dart", ItemColor::Red, 2, "Inn", ".../Assest/Items/Red/Dart.png");
allItems.emplace_back("Dart", ItemColor::Red, 2, "Inn", ".../Assest/Items/Red/Dart.png");
allItems.emplace_back("Fire Poker", ItemColor::Red, 3, "Mansion", ".../Assest/Items/Red/FirePoker.png");
allItems.emplace_back("Fire Poker", ItemColor::Red, 3, "Mansion", ".../Assest/Items/Red/FirePoker.png");
allItems.emplace_back("Rapier", ItemColor::Red, 5, "Theatre", ".../Assest/Items/Red/Rapier.png");
allItems.emplace_back("Rapier", ItemColor::Red, 5, "Theatre", ".../Assest/Items/Red/Rapier.png");
allItems.emplace_back("Shovel", ItemColor::Red, 2, "Graveyard", ".../Assest/Items/Red/Shovel.png");
allItems.emplace_back("Shovel", ItemColor::Red, 2, "Graveyard", ".../Assest/Items/Red/Shovel.png");
allItems.emplace_back("Torch", ItemColor::Red, 5, "Barn", ".../Assest/Items/Red/Torch.png");
allItems.emplace_back("Torch", ItemColor::Red, 5, "Barn", ".../Assest/Items/Red/Torch.png");
allItems.emplace_back("Pistol", ItemColor::Red, 6, "Precinct", ".../Assest/Items/Red/Pistol.png");
allItems.emplace_back("Pistol", ItemColor::Red, 6, "Precinct", ".../Assest/Items/Red/Pistol.png");
allItems.emplace_back("Knife", ItemColor::Red, 3, "Docks", ".../Assest/Items/Red/Knife.png");
allItems.emplace_back("Knife", ItemColor::Red, 3, "Docks", ".../Assest/Items/Red/Knife.png");
allItems.emplace_back("Silver Cane", ItemColor::Red, 6, "Shop", ".../Assest/Items/Red/SilverCane.png");
allItems.emplace_back("Silver Cane", ItemColor::Red, 6, "Shop", ".../Assest/Items/Red/SilverCane.png");
allItems.emplace_back("Rifle", ItemColor::Red, 6, "Barn", ".../Assest/Items/Red/Rifle.png");
allItems.emplace_back("Rifle", ItemColor::Red, 6, "Barn", ".../Assest/Items/Red/Rifle.png");
allItems.emplace_back("Pitchfork", ItemColor::Red, 4, "Barn", ".../Assest/Items/Red/Pitchfork.png");
allItems.emplace_back("Pitchfork", ItemColor::Red, 4, "Barn", ".../Assest/Items/Red/Pitchfork.png");
allItems.emplace_back("Bear Trap", ItemColor::Red, 4, "Shop", ".../Assest/Items/Red/BearTrap.png");
allItems.emplace_back("Bear Trap", ItemColor::Red, 4, "Shop", ".../Assest/Items/Red/BearTrap.png");
allItems.emplace_back("Speargun", ItemColor::Red, 4, "Institute", ".../Assest/Items/Red/Speargun.png");
allItems.emplace_back("Speargun", ItemColor::Red, 4, "Institute", ".../Assest/Items/Red/Speargun.png");

// Yellow items
allItems.emplace_back("Flower", ItemColor::Yellow, 2, "Docks", ".../Assest/Items/Yellow/Flower.png");
allItems.emplace_back("Flower", ItemColor::Yellow, 2, "Docks", ".../Assest/Items/Yellow/Flower.png");
allItems.emplace_back("Tarot Card", ItemColor::Yellow, 3, "Camp", ".../Assest/Items/Yellow/TarotCard.png");
allItems.emplace_back("Tarot Card", ItemColor::Yellow, 3, "Camp", ".../Assest/Items/Yellow/TarotCard.png");
allItems.emplace_back("Garlic", ItemColor::Yellow, 2, "Inn", ".../Assest/Items/Yellow/Garlic.png");
allItems.emplace_back("Garlic", ItemColor::Yellow, 2, "Inn", ".../Assest/Items/Yellow/Garlic.png");
allItems.emplace_back("MirroRed Box", ItemColor::Yellow, 3, "Mansion", ".../Assest/Items/Yellow/MirroRedBox.png");
allItems.emplace_back("MirroRed Box", ItemColor::Yellow, 3, "Mansion", ".../Assest/Items/Yellow/MirroRedBox.png");
allItems.emplace_back("Stake", ItemColor::Yellow, 3, "Abbey", ".../Assest/Items/Yellow/Stake.png");
allItems.emplace_back("Stake", ItemColor::Yellow, 3, "Abbey", ".../Assest/Items/Yellow/Stake.png");
allItems.emplace_back("Charm", ItemColor::Yellow, 4, "Camp", ".../Assest/Items/Yellow/Charm.png");
allItems.emplace_back("Charm", ItemColor::Yellow, 4, "Camp", ".../Assest/Items/Yellow/Charm.png");
allItems.emplace_back("Wolfsbane", ItemColor::Yellow, 4, "Camp", ".../Assest/Items/Yellow/Wolfsbane.png");
allItems.emplace_back("Wolfsbane", ItemColor::Yellow, 4, "Camp", ".../Assest/Items/Yellow/Wolfsbane.png");
allItems.emplace_back("Tablet", ItemColor::Yellow, 3, "Museum", ".../Assest/Items/Yellow/Tablet.png");
allItems.emplace_back("Tablet", ItemColor::Yellow, 3, "Museum", ".../Assest/Items/Yellow/Tablet.png");
allItems.emplace_back("Violin", ItemColor::Yellow, 3, "Camp", ".../Assest/Items/Yellow/Violin.png");
allItems.emplace_back("Violin", ItemColor::Yellow, 3, "Camp", ".../Assest/Items/Yellow/Violin.png");
allItems.emplace_back("Scroll of Thoth", ItemColor::Yellow, 4, "Museum", ".../Assest/Items/Yellow/ScrollofThoth.png");
allItems.emplace_back("Scroll of Thoth", ItemColor::Yellow, 4, "Museum", ".../Assest/Items/Yellow/ScrollofThoth.png");

// Blue items
allItems.emplace_back("Anatomy Text", ItemColor::Blue, 1, "Institute", ".../Assest/Items/Blue/AnatomyText.png");
allItems.emplace_back("Anatomy Text", ItemColor::Blue, 1, "Institute", ".../Assest/Items/Blue/AnatomyText.png");
allItems.emplace_back("Centerfuge", ItemColor::Blue, 1, "Laboratory", ".../Assest/Items/Blue/Centerfuge.png");
allItems.emplace_back("Centerfuge", ItemColor::Blue, 1, "Laboratory", ".../Assest/Items/Blue/Centerfuge.png");
allItems.emplace_back("Kite", ItemColor::Blue, 1, "Tower", ".../Assest/Items/Blue/Kite.png");
allItems.emplace_back("Kite", ItemColor::Blue, 1, "Tower", ".../Assest/Items/Blue/Kite.png");
allItems.emplace_back("Analysis", ItemColor::Blue, 2, "Institute", ".../Assest/Items/Blue/Analysis.png");
allItems.emplace_back("Analysis", ItemColor::Blue, 2, "Institute", ".../Assest/Items/Blue/Analysis.png");
allItems.emplace_back("Experiment", ItemColor::Blue, 2, "Laboratory", ".../Assest/Items/Blue/Experiment.png");
allItems.emplace_back("Experiment", ItemColor::Blue, 2, "Laboratory", ".../Assest/Items/Blue/Experiment.png");
allItems.emplace_back("Searchlight", ItemColor::Blue, 2, "Precinct", ".../Assest/Items/Blue/Searchlight.png");
allItems.emplace_back("Searchlight", ItemColor::Blue, 2, "Precinct", ".../Assest/Items/Blue/Searchlight.png");
allItems.emplace_back("Telescope", ItemColor::Blue, 2, "Mansion", ".../Assest/Items/Blue/Telescope.png");
allItems.emplace_back("Telescope", ItemColor::Blue, 2, "Mansion", ".../Assest/Items/Blue/Telescope.png");
allItems.emplace_back("Cosmic Ray Diffuser", ItemColor::Blue, 3, "Tower", ".../Assest/Items/Blue/CosmicRayDiffuser.png");
allItems.emplace_back("Cosmic Ray Diffuser", ItemColor::Blue, 3, "Tower", ".../Assest/Items/Blue/CosmicRayDiffuser.png");
allItems.emplace_back("Rotenone", ItemColor::Blue, 3, "Institute", ".../Assest/Items/Blue/Rotenone.png");
allItems.emplace_back("Rotenone", ItemColor::Blue, 3, "Institute", ".../Assest/Items/Blue/Rotenone.png");
allItems.emplace_back("Research", ItemColor::Blue, 2, "Tower", ".../Assest/Items/Blue/Research.png");
allItems.emplace_back("Research", ItemColor::Blue, 2, "Tower", ".../Assest/Items/Blue/Research.png");
allItems.emplace_back("Nebularium", ItemColor::Blue, 3, "Tower", ".../Assest/Items/Blue/Nebularium.png");
allItems.emplace_back("Nebularium", ItemColor::Blue, 3, "Tower", ".../Assest/Items/Blue/Nebularium.png");
allItems.emplace_back("Monocane Mixture", ItemColor::Blue, 3, "Inn", ".../Assest/Items/Blue/MonocaneMixture.png");
allItems.emplace_back("Monocane Mixture", ItemColor::Blue, 3, "Inn", ".../Assest/Items/Blue/MonocaneMixture.png");
allItems.emplace_back("Fossil", ItemColor::Blue, 3, "Camp", ".../Assest/Items/Blue/Fossil.png");
allItems.emplace_back("Fossil", ItemColor::Blue, 3, "Camp", ".../Assest/Items/Blue/Fossil.png");


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
void ItemPool::unload_item_textures() {
    for (Item& item : allItems) {
        item.unloadTexture();
    }
}
void ItemPool::load_item_textures(){
    for (Item& item : allItems) {
        item.loadTexture();
    }
}