#include "Menu.hpp"

Menu::Menu(Game& gameRef) : current_state(nullptr) , game(gameRef){}

void Menu::SetState(std::unique_ptr<State> s) {
    current_state = std::move(s);
}
void Menu::renderCurrentState() {
    if (current_state) 
        current_state->playState(*this);
}
State* Menu::getState(){
    return current_state.get();
}
void Menu::startGame(const PlayerSelection &p1, const PlayerSelection &p2){
    game.initialize(p1,p2) ;
    SetState(nullptr);
}