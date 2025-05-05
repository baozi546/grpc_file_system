find_package(GTest CONFIG REQUIRED)
if (MSVC)
    add_compile_options("/utf-8")
endif()
include_directories(${GTEST_INCLUDE_DIRS})
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC_TEST)

add_executable(my_tests ${SRC_TEST} ${SRC_LIST1} "../src/tools/tools.cpp")

target_link_libraries(my_tests PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
target_link_libraries(my_tests PRIVATE gRPC::grpc++ gRPC::grpc++_reflection gRPC::gpr gRPC::grpc gRPC::grpc++ protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite)
target_link_libraries(my_tests PRIVATE spdlog::spdlog)
target_link_libraries(my_tests PRIVATE jwt-cpp::jwt-cpp)