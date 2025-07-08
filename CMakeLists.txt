cmake_minimum_required(VERSION 3.31.5)

project(Horrified)

include_directories(header)

set(SOURCES
    src/Game.cpp
    src/Hero.cpp
    src/Dice.cpp
    src/main.cpp
    src/GameMap.cpp
    src/MonsterCardDeck.cpp
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