// #include "Game.hpp"
// #include "GameRender.hpp"
// #include "GameStates.hpp"

// GameState::GameState(){}
// void SetupState::update(Menu& menu) {
//     // انجام تنظیمات لازم
//     // وقتی آماده شدیم به HeroPhaseState بریم
//     // مثلا game.changeState باید اینجا اجرا بشه
//     menu.SetState(std::make_unique<HeroPhaseState>());
// }
// void HeroPhaseState::update(Game& game) {
//     // همون hero_phase(hero) رو اینجا بیار
//     game.hero_phase(game.get_turnManager().get_active_hero());
//     game.changeState(std::make_unique<MonsterPhaseState>());
// }
// void SetupState::enter(Game& game) {
//     // اینجا قهرمان‌ها و مانسترها و دک رو ست می‌کنیم
// }
// void SetupState::update(Game& game) {
//     // وقتی آماده شدیم:
//     game.changeState(std::make_unique<HeroPhaseState>());
// }
// void SetupState::render(Game& game) {
//     // "Setting up the board..." متن ساده یا انیمیشن
// }
// void MonsterPhaseState::update(Game& game) {
//     game.monster_phase();
//     // اینجا شرط باخت/برد رو هم می‌تونی چک کنی
//     game.get_turnManager().next_turn();
//     game.changeState(std::make_unique<HeroPhaseState>());
// }
// void HeroPhaseState::render(Game& game) {
//       GameRender renderer(game);
//         renderer.draw_map();
//         renderer.draw_monsters();
//         renderer.draw_heroes();
// }
// void MonsterPhaseState::render(Game& game) {
//     GameRender renderer(game);
//         renderer.draw_map();
//         renderer.draw_monsters();
//         renderer.draw_heroes();
// }