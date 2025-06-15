
#include "GameMap.hpp"

void GameMap::build_map() {
    auto theater = std::make_unique<Location>("Theater");
    auto cave = std::make_unique<Location>("Cave");
    auto tower = std::make_unique<Location>("Tower");
    auto dungeon = std::make_unique<Location>("Dungeon");
    auto camp = std::make_unique<Location>("Camp");
    auto docks = std::make_unique<Location>("Docks"); // اضافه کردم برای شروع قهرمان
    auto barn = std::make_unique<Location>("Barn");

    // اتصال‌ها
    cave->connect(camp.get());
    camp->connect(tower.get());
    theater->connect(barn.get());
    theater->connect(tower.get());

    locations.push_back(std::move(theater));
    locations.push_back(std::move(cave));
    locations.push_back(std::move(tower));
    locations.push_back(std::move(dungeon));
    locations.push_back(std::move(camp));
    locations.push_back(std::move(docks));
    locations.push_back(std::move(barn));
}

Location* GameMap::get_location_by_name(const std::string& name) {
    for (auto& loc : locations) {
        if (loc->get_name() == name)
            return loc.get();
    }
    return nullptr;
}

const std::vector<std::unique_ptr<Location>>& GameMap::get_locations() const {
    return locations;
}


