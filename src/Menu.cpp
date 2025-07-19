#include "menu.hpp"

Menu::Menu() : current_state(nullptr) {}

void Menu::SetState(std::unique_ptr<State> s) {
    current_state = std::move(s);
}

void Menu::renderCurrentState() {
    if (current_state) {
        current_state->playState(*this);
    } else {
        DrawText("No State Selected!", 100, 100, 20, RED);
    }
}
// void Menu::StartGame(const std::string& p1Name, const std::string& p1Hero,
//                     const std::string& p2Name, const std::string& p2Hero) {
//     SetState(nullptr); // Close menu
//  //   game.StartGame(p1Name, p1Hero, p2Name, p2Hero); // Delegate to Game
// }
