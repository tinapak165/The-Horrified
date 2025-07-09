cmake_minimum_required(VERSION 3.16)

project(HorrifiedGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Horrified
    GameMap.cpp
    Location.cpp
    Monster.cpp
    
    Monstercards.cpp
    Hero.cpp 
    Dice.cpp 
    Dracula.cpp 
    InvisibleMan.cpp
    item.cpp 
    Game.cpp 
    itembag.cpp 
    TurnManager.cpp 
    Villager.cpp 
    Mayor.cpp 
    Archaeologist.cpp
    main.cpp
    perkcards.cpp 
    perkcardsDeck.cpp
)

target_compile_options(Horrified PRIVATE -Wall -Wextra -Wpedantic)
