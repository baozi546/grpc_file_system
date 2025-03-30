set(CMAKE_TOOLCHAIN_FILE D:/Git/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "") 

find_package(GTest CONFIG REQUIRED)

add_executable(my_tests test_example.cpp)

target_link_libraries(my_tests PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)