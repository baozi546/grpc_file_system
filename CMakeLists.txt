cmake_minimum_required(VERSION 3.20)

set(CMAKE_TOOLCHAIN_FILE D:/Git/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "") 

project(Main C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(jwt-cpp CONFIG REQUIRED)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/proto")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src/Service")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src/FileOperation")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src/tools")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src/User")

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/proto SRC_LIST1)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/proto")
file(GLOB HEADER_LIST1 "${CMAKE_CURRENT_SOURCE_DIR}/proto/*.h")


add_executable(Main
    main.cpp
    ${SRC_LIST1}
 "src/Service/FileServer.h" "src/Service/FileServer.cpp" "src/FileOperation/FileDetail.h" "src/FileOperation/FileDetail.cpp" "src/FileOperation/FileOperation.h" "src/FileOperation/FileOperation.cpp" "src/tools/tools.h" "src/tools/tools.cpp" "src/FileOperation/FileDirTree.h" "src/FileOperation/FileDirTree.cpp" "src/Service/AuthServer.cpp" "src/Service/AuthServer.h" "src/User/UserCheck.h" "src/User/UserCheck.cpp" "src/Service/ServiceAwareInterceptorFactory.cpp")

target_link_libraries(Main PRIVATE gRPC::grpc++ gRPC::grpc++_reflection gRPC::gpr gRPC::grpc gRPC::grpc++ protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite)
target_link_libraries(Main PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
target_link_libraries(Main PRIVATE spdlog::spdlog)
target_link_libraries(Main PRIVATE jwt-cpp::jwt-cpp)

add_subdirectory(tests)
#add_test(AllTestsInMain main)