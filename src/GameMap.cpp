#include "GameMap.hpp"
void GameMap::unload() {
    if (mapTexture.id != 0) {
        UnloadTexture(mapTexture);
        mapTexture.id = 0;
    }

    for (auto& loc : locations) {
        loc->unload(); // آیکون هر لوکیشن
    }
}

void GameMap::build_map() {

    mapTexture = LoadTexture("../Assets/Menu/map.png");
if (mapTexture.id == 0) {
    std::cerr << "[ERROR] map.png not loaded!\n";
}

    add_location("Inn", {500, 170, 50, 50}, "../Assets/Icons/InnIcon.png");
    add_location("Cave" , {10,240,50,50} , "../Assets/Icons/CaveIcon.png") ; 
    add_location("Camp" , {150,240,50,50} , "../Assets/Icons/CampIcon.png") ; 
    add_location("Precinct" , {400,200,50,50} , "../Assets/Icons/PrecinctIcon.png") ; 
    add_location("Mansion" , {500,200,50,50} , "../Assets/Icons/MansionIcon.png") ; 
    add_location("Abbey" , {250,200,50,50} , "../Assets/Icons/AbbeyIcon.png") ; 
    add_location("Crypt" , {350,200,50,50} , "../Assets/Icons/CryptIcon.png") ; 
    add_location("Museum" , {700,200,50,50} , "../Assets/Icons/MuseumIcon.png") ; 
    add_location("Hospital" , {800,200,50,50} , "../Assets/Icons/HospitalIcon.png") ; 
    add_location("Church" , {290,200,50,50} , "../Assets/Icons/ChurchIcon.png") ; 
    add_location("Graveyard" , {150,200,50,50} , "../Assets/Icons/GraveyardIcon.png") ; 
    add_location("Institute" , {110,200,50,50} , "../Assets/Icons/InstituteIcon.png") ; 
    add_location("Laboratory" , {380,200,50,50} , "../Assets/Icons/LaboratoryIcon.png") ; 
    add_location("Shop" , {660,200,50,50} , "../Assets/Icons/ShopIcon.png") ; 
    add_location("Theatre" , {650,200,50,50} , "../Assets/Icons/TheatreIcon.png") ; 
    add_location("Docks" , {880,200,50,50} , "../Assets/Icons/DocksIcon.png") ; 
    add_location("Tower" , {200,200,50,50} , "../Assets/Icons/TowerIcon.png") ; 
    add_location("Barn" , {200,200,50,50} , "../Assets/Icons/BarnIcon.png") ; 
    add_location("Dungeon" , {200,200,50,50} , "../Assets/Icons/DungeonIcon.png") ; 


    Location* cave = get_location_by_name("Cave");
    Location* camp = get_location_by_name("Camp");
    Location* mansion = get_location_by_name("Mansion");
    Location* inn = get_location_by_name("Inn");
    Location* precinct = get_location_by_name("Precinct");
    Location* abbey = get_location_by_name("Abbey");
    Location* crypt = get_location_by_name("Crypt");
    Location* museum = get_location_by_name("Museum");
    Location* church = get_location_by_name("Church");
    Location* hospital = get_location_by_name("Hospital");   
    Location* graveyard = get_location_by_name("Graveyard");
    Location* institute = get_location_by_name("Institute");
    Location* laboratory = get_location_by_name("Laboratory");
    Location* shop = get_location_by_name("Shop");
    Location* theatre = get_location_by_name("Theatre");
    Location* docks = get_location_by_name("Docks");
    Location* tower = get_location_by_name("Tower");
    Location* barn = get_location_by_name("Barn");
    Location* dungeon = get_location_by_name("Dungeon");


    cave->connect(camp);
    camp->connect(mansion) ; 
    theatre->connect(barn );
    theatre->connect(tower );
    theatre->connect(precinct ) ; 
    theatre->connect(inn ) ; 
    tower->connect(docks );
    theatre->connect(mansion );
    inn->connect(precinct ) ; 
    theatre->connect(shop ) ; 
    mansion->connect(abbey );
    abbey->connect(crypt );
    // shop->connect(museum ) ; توی نقشه نبود
    shop->connect(laboratory ) ; //اضافه شد بخاطر نقشه
    mansion->connect(church ) ;
    laboratory->connect(institute );
    church->connect(graveyard );
    church->connect(hospital );
    tower->connect(dungeon ) ; 
    camp->connect(mansion ) ; 
    camp->connect(precinct ) ;   
    mansion->connect(shop );
    mansion->connect(museum ) ; 


 
 
}

void GameMap::add_location(const std::string& name, Rectangle area, const std::string& iconPath) {
    Texture2D icon = LoadTexture(iconPath.c_str());
    locations.push_back(std::make_unique<Location>(name, area, icon));
}
Location* GameMap::get_location_by_name(const std::string& name) {
    for (auto& loc : locations) {
        if (loc->get_name() == name)
            return loc.get();   
    }
    return nullptr;
}

void GameMap::draw_map() {
   
    if (mapTexture.id == 0) {
        std::cerr << "[ERROR] map.png not loaded properly!\n";
        return;
    }

    // محاسبه scale مناسب برای حفظ نسبت تصویر و وسط‌چین کردن
    float scale = std::min(
        (float)GetScreenWidth() / mapTexture.width,
        (float)GetScreenHeight() / mapTexture.height
    );

    // محاسبه موقعیت برای رسم وسط‌چین
    float drawX = (GetScreenWidth() - mapTexture.width * scale) / 2.0f;
    float drawY = (GetScreenHeight() - mapTexture.height * scale) / 2.0f;

    // رسم نقشه با scale
    DrawTextureEx(mapTexture, {drawX, drawY}, 0.0f, scale, WHITE);
}
Location* GameMap::check_click(Vector2 mousePos) {
    for (const auto& loc : locations) {
        if (CheckCollisionPointRec(mousePos, loc->get_clickable_area())) {
            return loc.get();
        }
    }
    return nullptr;
}

Villager* GameMap::find_villager_by_name(const std::string& name) {
    for (const auto& loc : locations) {
        for (Villager* v : loc->get_villagers()) {
            if (v->get_name() == name) 
            return v;
        }
    }
    return nullptr;
}

const std::vector<std::unique_ptr<Location>>& GameMap::get_locations() const {
    return locations;
}


Location* GameMap::find_next_step(Location* start, Location* goal) {
    if (!start || !goal || start == goal)
        return nullptr;

    std::unordered_map<Location*, Location*> came_from;
    std::queue<Location*> q;
    q.push(start);
    came_from[start] = nullptr;

    while (!q.empty()) {
        Location* current = q.front();
        q.pop();

        for (Location* neighbor : current->get_neighbors()) {
            if (came_from.count(neighbor)) continue;

            came_from[neighbor] = current;
            q.push(neighbor);

            if (neighbor == goal) {
                // مسیر کامل ساخته شد، حالا مسیر رو از goal به عقب دنبال می‌کنیم
                Location* step = neighbor;
                Location* prev = came_from[step];

                while (prev != start && prev != nullptr) {
                    step = prev;
                    prev = came_from[step];
                }

                return step;  // این همون همسایهٔ مستقیم start هست که به سمت goal می‌ره
            }
        }
    }

    return nullptr;  // مسیر پیدا نشد
}

