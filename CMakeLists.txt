cmake_minimum_required (VERSION 3.8)

project(Doomer CXX)

add_executable(SFML "src/main.cpp"  "src/chara.hpp"  "src/rays.hpp" "src/walls.hpp")

set(CMAKE_CXX_STANDARD 17)
set(SFML_DIR "SFML/lib/cmake/SFML")

find_package(SFML COMPONENTS graphics audio REQUIRED)
target_link_libraries(SFML sfml-graphics sfml-window sfml-system)  
