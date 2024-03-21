cmake_minimum_required(VERSION 3.27)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_PREFIX_PATH "/opt/homebrew")

project(weatherapp)
find_package(nlohmann_json 3.11.2 REQUIRED)

find_package(Wt REQUIRED)
find_package(Boost REQUIRED)

add_executable(weatherapp main.cpp)

add_custom_command(TARGET weatherapp POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E create_symlink
                   ${CMAKE_SOURCE_DIR}/resources
                   ${CMAKE_BINARY_DIR}/resources)

target_link_libraries(weatherapp PUBLIC Wt::Wt Wt::HTTP)
target_link_libraries(weatherapp PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(weatherapp PRIVATE Boost::boost)