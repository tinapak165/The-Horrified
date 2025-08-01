cmake_minimum_required(VERSION 3.10)

project(Horrified)

include_directories(header)
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g") 
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
    src/State.cpp
    src/menu.cpp
    src/button.cpp
    src/GameRender.cpp
    src/Action.cpp
)
add_executable(Horrified ${SOURCES})
target_link_libraries(Horrified PRIVATE raylib GL m pthread dl X11)