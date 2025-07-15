cmake_minimum_required(VERSION 3.15)
project(Horrified)

include_directories(header)

set(SOURCES
    src/Game.cpp
    src/Hero.cpp
    src/Dice.cpp
    src/main.cpp
    src/GameMap.cpp
    src/monstercards.cpp
    src/perkcards.cpp
    src/TurnManager.cpp
    src/monster.cpp
    src/Dracula.cpp
    src/InvisibleMan.cpp
    src/item.cpp
    src/Itembag.cpp
    src/Location.cpp
    src/villager.cpp
    src/Heroes.cpp
)

add_executable(Horrified ${SOURCES})

# مسیر به raylib
target_include_directories(Horrified PRIVATE "C:/w64devkit/include")
target_link_directories(Horrified PRIVATE "C:/w64devkit/lib")

# لینک کتابخانه‌ها
target_link_libraries(Horrified
    raylib
    opengl32
    gdi32
    winmm
)
