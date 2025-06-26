cmake_minimum_required(VERSION 3.16)

project(HorrifiedGame)

# تنظیم زبان
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# همه فایل‌های سورس را تعریف می‌کنیم
set(SOURCES
    
    GameMap.cpp
    Location.cpp
    Monster.cpp
    MonsterCardDeck.cpp
    Monstercards.cpp
    Hero.cpp 
    Dice.cpp 
    Dracula.cpp 
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
# هدف اصلی برنامه
add_executable(Horrified ${SOURCES})

# اگر نیاز به هشدارهای بیشتر حین کامپایل داری (اختیاری ولی توصیه شده)
target_compile_options(Horrified PRIVATE -Wall -Wextra -Wpedantic)
