# cmake_minimum_required(VERSION 3.10)

# project(Horrified)

# include_directories(header)

# set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_EXTENSIONS OFF)
# set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")  # فعال کردن اطلاعات دیباگ
# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# # استفاده از pkg-config برای پیدا کردن Raylib
# find_package(PkgConfig REQUIRED)
# pkg_check_modules(RAYLIB REQUIRED raylib)

# include_directories(${RAYLIB_INCLUDE_DIRS})
# link_directories(${RAYLIB_LIBRARY_DIRS})

# set(SOURCES
#     src/Game.cpp
#     src/Hero.cpp
#     src/Dice.cpp
#     src/Main.cpp
#     src/GameMap.cpp
#     src/Monstercards.cpp
#     src/Perkcards.cpp
#     src/TurnManager.cpp
#     src/Monster.cpp
#     src/Dracula.cpp
#     src/InvisibleMan.cpp
#     src/Item.cpp
#     src/Itembag.cpp
#     src/Location.cpp
#     src/Villager.cpp
#     src/Heroes.cpp
#     src/State.cpp
#     src/Menu.cpp
#     src/Button.cpp
#     src/GameRender.cpp
#     src/Action.cpp
#     src/GameState.cpp
# )

# add_executable(Horrified ${SOURCES})

# # لینک کردن Raylib
# target_link_libraries(${PROJECT_NAME} ${RAYLIB_LIBRARIES})
cmake_minimum_required(VERSION 3.10)

project(Horrified LANGUAGES CXX)

# Enforce C++20 everywhere
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)  # prevents gnu++ fallback

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g") 
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(header)

# Find Raylib
find_package(PkgConfig REQUIRED)
pkg_check_modules(RAYLIB REQUIRED raylib)
include_directories(${RAYLIB_INCLUDE_DIRS})
link_directories(${RAYLIB_LIBRARY_DIRS})

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
    src/SaveManager.cpp
    src/Factory.cpp

)

add_executable(Horrified ${SOURCES})

target_link_libraries(Horrified ${RAYLIB_LIBRARIES})
