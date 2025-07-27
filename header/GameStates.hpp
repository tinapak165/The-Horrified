// #ifndef GAMESTATES_HPP
// #define GAMESTATES_HPP
// #pragma once
// #include <memory>
// class Game;

// class GameState {
// public:
//     GameState();
//     virtual ~GameState() = default;
//     virtual void enter(Game& game) = 0;     // وقتی وارد این State می‌شیم
//     virtual void update(Game& game) = 0;    // آپدیت (منطق)
//     virtual void render(Game& game) = 0;    // رندر (raylib)
//     virtual void exit(Game& game) = 0;      // وقتی خارج می‌شیم
// };

// class SetupState : public GameState {
// public:
//     void enter(Game& game) override;
//     void update(Game& game) override;
//     void render(Game& game) override;
//     void exit(Game& game) override {}
// };

// class HeroPhaseState : public GameState {
// public:
//     void enter(Game& game) override {}
//     void update(Game& game) override;
//     void render(Game& game) override;
//     void exit(Game& game) override {}
// };

// class MonsterPhaseState : public GameState {
// public:
//     void enter(Game& game) override {}
//     void update(Game& game) override;
//     void render(Game& game) override;
//     void exit(Game& game) override {}
// };


// #endif