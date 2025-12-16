cmake_minimum_required(VERSION 3.14)
project(NPCGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(npc_game
    main.cpp
    game.cpp
    npc.cpp
    visitor.cpp
    npc_factory.cpp
)

target_include_directories(npc_game PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

find_package(GTest REQUIRED)
add_executable(npc_tests
    test_npc.cpp
    npc.cpp
    visitor.cpp
    npc_factory.cpp
)

target_include_directories(npc_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(npc_tests GTest::gtest GTest::gtest_main)