#pragma once
#include "item.hpp"
#include <vector>
#include <random>
#include <algorithm>

class ItemPool {
private:
    std::vector<Item> allItems;
    std::vector<Item> inUseItems ; 

public:
    ItemPool();
    void add_item(const Item& item);
    void add_items(const std::vector<Item>& items);
    std::vector<Item> draw_random_items(int );
    void unload_in_use_items() ;
    // void load_item_textures();
    // void unload_item_textures();
};