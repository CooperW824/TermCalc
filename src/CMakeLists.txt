cmake_minimum_required(VERSION 3.5)

project(TerminalCalculator LANGUAGES CXX VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Release)


include(FetchContent)

FetchContent_Declare(ftxui
GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
GIT_TAG v5.0.0
)

FetchContent_MakeAvailable(ftxui)

add_executable(calculator main.cpp ) 
target_link_libraries(
    calculator 
    PRIVATE ftxui::screen 
    PRIVATE ftxui::dom
    PRIVATE ftxui::component
)

