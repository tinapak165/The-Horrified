#include <iostream>
#include <algorithm>
#include <queue>
#include <unordered_set>
#include <string>
#include "monster.hpp"
#include "location.hpp"
#include "GameMap.hpp"

using namespace std;


Monster::Monster (const string& name, Location* start_location)
: name(name), current_location(start_location) {}



Location* find_nearest_target(Location* start) {
    std::queue<Location*> q;
    std::unordered_set<Location*> visited;

    q.push(start);
    visited.insert(start);

    while (!q.empty()) {
        Location* current = q.front();
        q.pop();

        // شرط هدف
        if (!current->get_heroes().empty() ) {
            return current;
        }

        // بررسی همسایه‌ها
        for (Location* neighbor : current->get_neighbors()) {
            if (visited.count(neighbor) == 0) {
                visited.insert(neighbor);
                q.push(neighbor);
            }
        }
        // if {} //اگه تارگتی پیدا نشد
    }

    return nullptr; // هیچ هدفی
}

void Monster::Monster_move(Location* new_location){

    if (current_location){

        auto& monsters_here = current_location ->get_monster();
        monsters_here.erase(std::remove(monsters_here.begin(), monsters_here.end(), this), monsters_here.end());


    }
    new_location->add_monster(this);
    current_location = new_location;
    std::cout<< this->get_name() << " moved to "<< new_location->get_name()<< "\n";

}