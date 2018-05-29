cmake_minimum_required(VERSION 3.11)
set (target_name so2)

find_package(Threads REQUIRED)

add_executable(${target_name}
                include/App.hpp
                include/Car.hpp
                include/CarSquare.hpp
                include/Screen.hpp
                include/Texture.hpp
                include/Timer.hpp
                src/App.cpp
                src/CarSquare.cpp
                src/Screen.cpp
                src/Texture.cpp
                src/Timer.cpp
                src/Main.cpp)

target_include_directories(${target_name} PRIVATE 
                        include)
target_link_libraries(${target_name} SDL2 SDL2_image SDL2_mixer SDL2_ttf Threads::Threads)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/data/ DESTINATION ${CMAKE_BINARY_DIR}/data)
