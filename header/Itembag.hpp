#pragma once
#include "Item.hpp"
#include <vector>
#include <random>
#include <algorithm>

class ItemPool {
private:
    std::vector<Item> allItems;

public:
    ItemPool();
    void add_item(const Item& item);
    void add_items(const std::vector<Item>& items);
    std::vector<Item> draw_random_items(int );
    void load_item_textures();
    void unload_item_textures();
};