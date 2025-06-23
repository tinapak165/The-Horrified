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

    std::vector<Item> draw_random_items(int count);
};
