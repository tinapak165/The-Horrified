#include "GameMap.hpp"

void GameMap::build_map() {

    mapTexture = LoadTexture("../Assets/map.png");
    if (mapTexture.id == 0) {
        std::cerr << "[ERROR] map.png not loaded!\n";
    }
    add_location("Cave", {50 - 200, 405 , 150, 30}, "../Assets/Icons/CaveIcon.png");  
    add_location("Camp", {310 - 200, 400 , 150, 30}, "../Assets/Icons/CampIcon.png"); 
    add_location("Precinct", {596 - 200, 350,150, 30}, "../Assets/Icons/PrecinctIcon.png"); 
    add_location("Inn", {870 - 200, 295, 150, 30}, "../Assets/Icons/InnIcon.png");  
    add_location("Barn", {1179 - 200, 333, 150, 30}, "../Assets/Icons/BarnIcon.png"); 
    add_location("Dungeon", {1455 - 200, 338, 150, 30}, "../Assets/Icons/DungeonIcon.png"); 
    add_location("Tower", {1322 - 200, 629, 150, 30}, "../Assets/Icons/TowerIcon.png"); 
    add_location("Theatre", {990 - 200, 655, 150, 30}, "../Assets/Icons/TheatreIcon.png"); 
    add_location("Mansion", {300 - 200, 700, 150, 30}, "../Assets/Icons/MansionIcon.png");
    add_location("Abbey", {50 - 200, 700, 150, 30}, "../Assets/Icons/AbbeyIcon.png");
    add_location("Crypt", {52 -200, 1303, 150, 30}, "../Assets/Icons/CryptIcon.png"); 
    add_location("Museum", {302-200, 1299, 150, 30}, "../Assets/Icons/MuseumIcon.png"); 
    add_location("Hospital", {555-200, 1539, 150, 30}, "../Assets/Icons/HospitalIcon.png"); 
    add_location("Church", {680-200, 1351, 150, 30}, "../Assets/Icons/ChurchIcon.png"); 
    add_location("Graveyard", {930-200, 1539, 150, 30}, "../Assets/Icons/GraveyardIcon.png"); 
    add_location("Institute", {1270-200, 1535, 150, 30}, "../Assets/Icons/InstituteIcon.png"); 
    add_location("Laboratory", {1073-200, 1288,150, 30}, "../Assets/Icons/LaboratoryIcon.png");  
    add_location("Shop", {840-200, 1088, 150, 30}, "../Assets/Icons/ShopIcon.png"); 
    add_location("Docks", {1415-200, 915, 150, 30}, "../Assets/Icons/DocksIcon.png");


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
    shop->connect(laboratory ) ; 
    shop->connect(museum) ; //
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
std::string GameMap::checkString(std::string str){
    for (char &c : str) 
        c = tolower(c); 
    str[0] = toupper(str[0]);
    return str;
}
void GameMap::add_location(const std::string& name, Rectangle area, const std::string& iconPath) {
    Texture2D icon = LoadTexture(iconPath.c_str());
    locations.push_back(std::make_unique<Location>(name, area, icon));
}
Location* GameMap::get_location_by_name(const std::string& name) {
    std::string input = checkString(name) ;
    for (auto& loc : locations) {
        if (loc->get_name() == input)
            return loc.get();   
    }
    return nullptr;
}

Rectangle GameMap::get_drawn_rect() const {
        return { drawX, drawY, mapTexture.width * scale, mapTexture.height * scale };
    }

void GameMap::draw_map() {
   
    if (mapTexture.id == 0) {
        std::cerr << "[ERROR] map.png not loaded properly!\n";
        return;
    }

    // محاسبه scale مناسب برای حفظ نسبت تصویر و وسط‌چین کردن
     scale = std::min(
        (float)GetScreenWidth() / mapTexture.width,
        (float)GetScreenHeight() / mapTexture.height
    );

    // محاسبه موقعیت برای رسم وسط‌چین
     drawX = (GetScreenWidth() - mapTexture.width * scale) / 1/5.0f;
     drawY = (GetScreenHeight() - mapTexture.height * scale) / 2.0f;

    // رسم نقشه با scale
    DrawTextureEx(mapTexture, {drawX, drawY}, 0.0f, scale, WHITE);
}
const Texture2D &GameMap::get_mapTexture() const{
    return mapTexture ;
}
Location *GameMap::check_click(Vector2 mousePos)
{
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

GameMap::~GameMap(){
    UnloadTexture(mapTexture);
}