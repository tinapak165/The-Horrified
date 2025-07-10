#include "monster.hpp"
#include <algorithm>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include "location.hpp"
#include "GameMap.hpp"
#include "Hero.hpp"

using namespace std;


Monster::Monster (const string& name, Location* start_location) : name(name), current_location(start_location) {}

const std::string& Monster::get_name() const { return name; }
Location* Monster::get_location() const { return current_location; }

void Monster::set_location(Location* new_location) {
 
    if (current_location) {
        auto& monsters_here = current_location->get_monsters();
        monsters_here.erase(std::remove(monsters_here.begin(), monsters_here.end(), this), monsters_here.end());
    }

    current_location = new_location;
    if (current_location) {
        current_location->add_monster(this);
    }
}

Location* Monster::find_nearest_target(Location* start) {
   
    std::queue<Location*> q;
    std::unordered_set<Location*> visited;

    q.push(start);
    visited.insert(start);

    while (!q.empty()) {
        Location* current = q.front();
        q.pop();

        if (!current->get_heroes().empty() || !current->get_villagers().empty() ) {
            return current;
        }

        for (Location* neighbor : current->get_neighbors()) {
            if (visited.count(neighbor) == 0) {
                visited.insert(neighbor);
                q.push(neighbor);
            }
        }

    }
    cout<<"end of find nearest target \n";
    return nullptr; 
}

Location* Monster::find_nearest_hero(Location* start) {
    std::cout<<"in fine nearest target ";
    std::queue<Location*> q;
    std::unordered_set<Location*> visited;

    q.push(start);
    visited.insert(start);

    while (!q.empty()) {
        Location* current = q.front();
        q.pop();

        if (!current->get_heroes().empty() ) {
            cout<<"Monster won't move from strike because hero is at"<<current <<"too !";
            return current;
        }

        for (Location* neighbor : current->get_neighbors()) {
            if (visited.count(neighbor) == 0) {
                visited.insert(neighbor);
                q.push(neighbor);
            }
        }
    }

    return nullptr;
}
Location* Monster::find_nearest_villager(Location* start) {
    std::cout<<"in fine nearest target ";
    std::queue<Location*> q;
    std::unordered_set<Location*> visited;

    q.push(start);
    visited.insert(start);

    while (!q.empty()) {
        Location* current = q.front();
        q.pop();

        if (!current->get_villagers().empty() ) {
            return current;
        }

        for (Location* neighbor : current->get_neighbors()) {
            if (visited.count(neighbor) == 0) {
                visited.insert(neighbor);
                q.push(neighbor);
            }
        }
    }

    return nullptr; 
}
void Monster::Monster_move_event(Location* new_location){

    if (current_location){

        auto& monsters_here = current_location ->get_monsters();
        monsters_here.erase(std::remove(monsters_here.begin(), monsters_here.end(), this), monsters_here.end());

    }
    new_location->add_monster(this);
    current_location = new_location;
    std::cout<< this->get_name() << " moved to "<< new_location->get_name()<< "\n";

}

Location* Monster::find_next_step(Location* target) {
    if (current_location == target) return nullptr;

    std::unordered_map<Location*, Location*> parent;
    std::queue<Location*> q;

    q.push(current_location);
    parent[current_location] = nullptr;

    while (!q.empty()) {
        Location* curr = q.front();
        q.pop();

        if (curr == target) break;

        for (Location* neighbor : curr->get_neighbors()) {
            if (parent.find(neighbor) == parent.end()) {
                parent[neighbor] = curr;
                q.push(neighbor);
            }
        }
    }

    if (parent.find(target) == parent.end()) return nullptr;

    Location* step = target;
    while (parent[step] != current_location) {
        step = parent[step];
    }
    return step;
}




void Monster::move_towards(int max_steps) {

    std::queue<Location*> q;
    std::unordered_map<Location*, Location*> parent;
    std::unordered_set<Location*> visited;

    q.push(current_location);
    visited.insert(current_location);

    Location* target = nullptr;

    while (!q.empty()) {
        Location* curr = q.front();
        q.pop();

        if (!curr->get_heroes().empty() ) {
            target = curr;
            break;
        }

        for (Location* neighbor : curr->get_neighbors()) {
            if (visited.count(neighbor) == 0) {
                visited.insert(neighbor);
                parent[neighbor] = curr;
                q.push(neighbor);
            }
        }
    }

    if (!target) {
        std::cout << name << " found no target.\n";
        return;
    }

    std::vector<Location*> path;
    for (Location* loc = target; loc != current_location; loc = parent[loc]) {
        path.push_back(loc);
    }
    std::reverse(path.begin(), path.end());

    int steps = std::min(max_steps, (int)path.size());

    for (int i = 0; i < steps; ++i) {
        auto& monsters_here = current_location->get_monsters();
        monsters_here.erase(std::remove(monsters_here.begin(), monsters_here.end(), this), monsters_here.end());

        current_location = path[i];
        current_location->add_monster(this);

        std::cout << name << " moved to " << current_location->get_name() << "\n";
    }
   
}

std::ostream operator<<(std::ostream &output, Monster &m){
    output<<m.get_name();
 }

bool Monster::is_alive() const { return get_location() != nullptr; }