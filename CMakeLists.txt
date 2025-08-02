cmake_minimum_required(VERSION 3.10)

project(Horrified)

include_directories(header)
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g") 
set(SOURCES
    src/Game.cpp
    src/Hero.cpp
    src/Dice.cpp
    src/Main.cpp
    src/GameMap.cpp
    src/Monstercards.cpp
    src/Perkcards.cpp
    src/TurnManager.cpp
    src/Monster.cpp
    src/Dracula.cpp
    src/InvisibleMan.cpp
    src/Item.cpp
    src/Itembag.cpp
    src/Location.cpp
    src/Villager.cpp
    src/Heroes.cpp
    src/State.cpp
    src/Menu.cpp
    src/Button.cpp
    src/GameRender.cpp
    src/Action.cpp
)
add_executable(Horrified ${SOURCES})
target_link_libraries(Horrified PRIVATE raylib GL m pthread dl X11)