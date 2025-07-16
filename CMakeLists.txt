cmake_minimum_required(VERSION 3.15)
project(Horrified)

# فایل‌های پروژه
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

# فولدر هدرهای خودت
include_directories(header)

# ساختن executable
add_executable(Horrified ${SOURCES})

# مسیر به raylib
target_include_directories(Horrified PRIVATE "C:/Users/Tina/Downloads/w64devkit/bin/include")
target_link_directories(Horrified PRIVATE "C:/Users/Tina/Downloads/w64devkit/bin")

# لینک به raylib و کتابخونه‌های لازم ویندوز
target_link_libraries(Horrified
    raylib
    opengl32
    gdi32
    winmm
)
