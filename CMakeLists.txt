cmake_minimum_required (VERSION 3.8)
project(Doomer CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set( doomer_src
    src/main.cpp
  )
add_executable(Doomer ${doomer_src})

set(SFML_DIR "SFML/lib/cmake/SFML")

find_package(SFML COMPONENTS graphics audio REQUIRED)
target_link_libraries(Doomer sfml-graphics sfml-window sfml-system)
