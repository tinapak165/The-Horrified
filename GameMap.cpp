
#include "GameMap.hpp"

void GameMap::build_map() {
auto theater = std::make_unique<Location>("Theater");
    auto cave = std::make_unique<Location>("Cave");
    auto tower = std::make_unique<Location>("Tower");
    auto dungeon = std::make_unique<Location>("Dungeon");
    auto camp = std::make_unique<Location>("Camp");
    auto docks = std::make_unique<Location>("Docks"); // اضافه کردم برای شروع قهرمان
    auto barn = std::make_unique<Location>("Barn");
    auto empty1 = std::make_unique<Location>("empty1");
    auto empty2 = std::make_unique<Location>("empty2");
    auto mansion = std::make_unique<Location>("Mansion");
    auto abbey = std::make_unique<Location>("Abbey");
    auto empty3 = std::make_unique<Location>("empty3");
    auto precinct = std::make_unique<Location>("Precinct");
    auto inn = std::make_unique<Location>("Inn");
    auto crypt = std::make_unique<Location>("Crypt");
    auto shop = std::make_unique<Location>("Shop");
    auto musuem = std::make_unique<Location>("Museum");
    auto church = std::make_unique<Location>("Church");
    auto hospital = std::make_unique<Location>("Hospital");
    auto graveyard = std::make_unique<Location>("Graveyard");
    auto empty4 = std::make_unique<Location>("empty4");
    auto laboratory = std::make_unique<Location>("Laboratory");
    auto institute = std::make_unique<Location>("Institute");


    // وصل شدن
    cave->connect(camp.get());
    camp->connect(empty1.get());
    theater->connect(barn.get());
    theater->connect(tower.get());
    tower->connect(docks.get());
    empty1->connect(empty2.get());
    empty2->connect(precinct.get());
    empty2->connect(inn.get());
    empty2->connect(theater.get());
    empty1->connect(mansion.get());
    mansion->connect(abbey.get());
    mansion->connect(empty3.get());
    abbey->connect(crypt.get());
    empty3->connect(shop.get());
    empty3->connect(church.get());
    empty3->connect(musuem.get());
    empty4->connect(theater.get());
    empty4->connect(shop.get());
    shop->connect(laboratory.get());
    laboratory->connect(institute.get());
    church->connect(graveyard.get());
    church->connect(hospital.get());




    locations.push_back(std::move(theater));
    locations.push_back(std::move(cave));
    locations.push_back(std::move(tower));
    locations.push_back(std::move(dungeon));
    locations.push_back(std::move(camp));
    locations.push_back(std::move(docks));
    locations.push_back(std::move(barn));
    locations.push_back(std::move(inn));
    locations.push_back(std::move(precinct));
    locations.push_back(std::move(empty1));
    locations.push_back(std::move(empty2));
    locations.push_back(std::move(empty3));
    locations.push_back(std::move(empty4));
    locations.push_back(std::move(mansion));
    locations.push_back(std::move(shop));
    locations.push_back(std::move(abbey));
    locations.push_back(std::move(church));
    locations.push_back(std::move(musuem));
    locations.push_back(std::move(crypt));
    locations.push_back(std::move(hospital));
    locations.push_back(std::move(graveyard));
    locations.push_back(std::move(institute));
    locations.push_back(std::move(laboratory));

    

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
