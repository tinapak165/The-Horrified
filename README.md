# 🎮 The Horrified

## 📖 About the Game  
**Horrified Game** is a cooperative digital adaptation inspired by the popular *Horrified* board game. Players team up as unique heroes to defend a haunted town from terrifying monsters like Dracula and the Invisible Man.  

Each monster has distinct abilities and requires different strategies to defeat. This digital version captures the suspense and teamwork of the board game while introducing immersive visuals, smooth gameplay, and a spooky atmosphere.  

![Game Preview](/Assets/screen.png)


## ✨ Features  
- 🚀 **Cooperative Gameplay**: Work together with friends or play solo to defeat monsters.  
- 🧩 **Unique Heroes**: Choose from multiple heroes, each with their own abilities.  
- 🎨 **Immersive Atmosphere**: Eerie visuals and chilling sound effects enhance the horror vibe.  
- 💻 **Cross-Platform**: Playable on Linux, Windows, and macOS.  
- 🧑‍💻 **Clean Modular Design**: Graphics, game logic, and assets are separated for easy maintenance.  

---

📂 Project Structure  

```plaintext
── CMakeLists.txt
├── header/
│   ├── Action.hpp
│   ├── ActionButton.hpp
│   ├── Factory.hpp
│   ├── Itembag.hpp
│   ├── Heroes.hpp
│   ├── Dice.hpp
│   ├── Dracula.hpp
│   ├── Game.hpp
│   ├── Hero.hpp
│   ├── InvisibleMan.hpp
│   ├── Item.hpp
│   ├── Location.hpp
│   ├── Menu.hpp
│   ├── Monster.hpp
│   ├── Monstercards.hpp
│   ├── Perkcards.hpp
│   ├── GameRender.hpp
│   ├── GameMap.hpp
│   ├── SaveManager.hpp
│   ├── State.hpp
│   ├── Tools.hpp
│   ├── TurnManager.hpp
│   └── Villager.hpp
├── src/
│   ├── Action.cpp
│   ├── Factory.cpp
│   ├── Itembag.cpp
│   ├── Heroes.cpp
│   ├── Dice.cpp
│   ├── Dracula.cpp
│   ├── Game.cpp
│   ├── Hero.cpp
│   ├── InvisibleMan.cpp
│   ├── Item.cpp
│   ├── Location.cpp
│   ├── Menu.cpp
│   ├── Monster.cpp
│   ├── Monstercards.cpp
│   ├── Perkcards.cpp
│   ├── GameRender.cpp
│   ├── GameMap.cpp
│   ├── SaveManager.cpp
│   ├── State.cpp
│   ├── Tools.cpp
│   ├── TurnManager.cpp
│   ├── Villager.cpp
│   └── Main.cpp
└── README.md

```

## 🛠️ How to Build  
```bash
git clone https://github.com/tinapak165/The-Horrified.git
cd The-Horrified
cmake -S . -B build "Makefiles"
cd build
make
./Horrified
```
