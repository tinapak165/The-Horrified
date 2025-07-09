
#include "GameMap.hpp"


void GameMap::build_map() {
    auto theatre = std::make_unique<Location>("Theatre"); 
    auto cave = std::make_unique<Location>("Cave");
    auto tower = std::make_unique<Location>("Tower");
    auto dungeon = std::make_unique<Location>("Dungeon");
    auto camp = std::make_unique<Location>("Camp");
    auto docks = std::make_unique<Location>("Docks"); 
    auto barn = std::make_unique<Location>("Barn");
     auto mansion = std::make_unique<Location>("Mansion");
    auto abbey = std::make_unique<Location>("Abbey");
    auto precinct = std::make_unique<Location>("Precinct");
     auto inn = std::make_unique<Location>("Inn");
    auto crypt = std::make_unique<Location>("Crypt");
    auto shop = std::make_unique<Location>("Shop");
    auto museum = std::make_unique<Location>("Museum");
    auto church = std::make_unique<Location>("Church");
    auto hospital = std::make_unique<Location>("Hospital");
    auto graveyard = std::make_unique<Location>("Graveyard");
    auto laboratory = std::make_unique<Location>("Laboratory");
    auto institute = std::make_unique<Location>("Institute");
 
 
     // وصل شدن
     cave->connect(camp.get());
     camp->connect(mansion.get()) ; 
     theatre->connect(barn.get());
     theatre->connect(tower.get());
     theatre->connect(precinct.get()) ; 
     theatre->connect(inn.get()) ; 
     tower->connect(docks.get());
     theatre->connect(mansion.get());
     inn->connect(precinct.get()) ; 
     theatre->connect(shop.get()) ; 
     mansion->connect(abbey.get());
     abbey->connect(crypt.get());
     shop->connect(laboratory.get());
     shop->connect(museum.get()) ; 
     mansion->connect(church.get()) ;
     laboratory->connect(institute.get());
     church->connect(graveyard.get());
     church->connect(hospital.get());
     tower->connect(dungeon.get()) ; 
     camp->connect(mansion.get()) ; 
     camp->connect(precinct.get()) ; 
      
     mansion->connect(shop.get());
     mansion->connect(museum.get()) ; 
      


   
 
     locations.push_back(std::move(theatre));
     locations.push_back(std::move(cave));
     locations.push_back(std::move(tower));
     locations.push_back(std::move(dungeon));
     locations.push_back(std::move(camp));
     locations.push_back(std::move(docks));
     locations.push_back(std::move(barn));
     locations.push_back(std::move(inn));
     locations.push_back(std::move(precinct));
     locations.push_back(std::move(mansion));
     locations.push_back(std::move(shop));
     locations.push_back(std::move(abbey));
     locations.push_back(std::move(church));
     locations.push_back(std::move(museum));
     locations.push_back(std::move(crypt));
     locations.push_back(std::move(hospital));
     locations.push_back(std::move(graveyard));
     locations.push_back(std::move(institute));
     locations.push_back(std::move(laboratory));
 
     
 
 }
// در یسری از کانستراکتو ها استفاده شد برای مکان اولیه
Location* GameMap::get_location_by_name(const std::string& name) {
    for (auto& loc : locations) {
        if (loc->get_name() == name)
            return loc.get();
    }
    return nullptr;
}

Villager* GameMap::find_villager_by_name(const std::string& name) {
    for (const auto& loc : locations) { // loc: std::unique_ptr<Location>
        for (Villager* v : loc->get_villagers()) {
            if (v->get_name() == name) return v;
        }
    }
    return nullptr;
}


const std::vector<std::unique_ptr<Location>>& GameMap::get_locations() const {
    return locations;
}


