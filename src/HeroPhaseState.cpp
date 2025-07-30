#include "HeroPhaseState.hpp"
#include "Game.hpp"
#include "GameRender.hpp"
#include "Menu.hpp"

HeroPhaseState::HeroPhaseState(Game& g) 
    : State("../Assets/Menu/Background.png") , game(g) , renderer(std::make_unique<GameRender>(g))
{
     actionButtons = {
            {"Move", {50, 500, 120, 40}},
            {"Special", {190, 500, 120, 40}},
            {"Guide", {330, 500, 120, 40}},
            {"Pickup", {50, 550, 120, 40}},
            {"Advance", {190, 550, 120, 40}},
            {"Defeat", {330, 550, 120, 40}},
            {"Perk", {50, 600, 120, 40}},
            {"Help", {190, 600, 120, 40}},
            {"Quit", {330, 600, 120, 40}},
        };
}

// HeroPhaseState.cpp

void HeroPhaseState::update(Menu& menu) {
    std::cout << "[HeroPhaseState] update called" << std::endl;

   Game& game = menu.getGame();
    Hero* activeHero = game.get_turnManager().get_active_hero();
    std::cout << "[HeroPhaseState] Active hero: " << activeHero->GetName() 
              << " Remaining actions: " << activeHero->GetRemainingActions() << std::endl;

   // Track hover & click states
    static std::string lastHoverButton;
    static std::string lastClickButton;
    static bool wasMouseOverButton = false;

    Vector2 mousePos = GetMousePosition();
    bool mousePressed = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    bool mouseReleased = IsMouseButtonReleased(MOUSE_LEFT_BUTTON);

    bool hoveringAny = false;

    for (const auto& button : actionButtons) {
        if (CheckCollisionPointRec(mousePos, button.bounds)) {
            hoveringAny = true;

            if (lastHoverButton != button.label) { 
                std::cout << "[DEBUG] Hover start: " << button.label << " at (" 
                        << (int)mousePos.x << "," << (int)mousePos.y << ")\n";
                lastHoverButton = button.label;
            }

            if (mousePressed) {
                std::cout << "[DEBUG] Mouse down on: " << button.label << "\n";
            }

            if (mouseReleased) {
                std::cout << "[DEBUG] Mouse clicked: " << button.label << "\n";
                lastClickButton = button.label;

                std::cout << "[DEBUG] renderer is " << (renderer ? "NOT NULL" : "NULL") << std::endl;

                renderer->handle_action(button.label, activeHero);
                std::cout << "[DEBUG] Finished handle_action for: " << button.label << "\n";
            }
    }
}

// Detect hover exit
if (!hoveringAny && !lastHoverButton.empty()) {
    std::cout << "[DEBUG] Hover end: " << lastHoverButton << "\n";
    lastHoverButton.clear();
}

}

void HeroPhaseState::render(Menu& menu) {
    DrawTexture(get_background(), 0, 0, WHITE);

 
    renderer->draw();
    renderer->draw_action_panel();
}
