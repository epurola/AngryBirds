add_subdirectory(${CMAKE_SOURCE_DIR}/external/googletest googletest-build)

add_executable(AngryBirdsTests
    test_main.cpp
    test_game.cpp
)

target_link_libraries(AngryBirdsTests PRIVATE gtest gtest_main AngryBirds)
add_test(NAME AngryBirdsTests COMMAND AngryBirdsTests)
