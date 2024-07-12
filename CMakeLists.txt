cmake_minimum_required(VERSION 3.5)

project(TerminalCalculator LANGUAGES CXX VERSION 1.0.0)

configure_file(src/versioning.h.in versioning.h)



set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Release)


include(FetchContent)

FetchContent_Declare(ftxui
GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
GIT_TAG v5.0.0
)

FetchContent_MakeAvailable(ftxui)

add_executable(calculator src/main.cpp src/utils.cpp) 
target_include_directories(calculator PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(
    calculator 
    PRIVATE ftxui::screen 
    PRIVATE ftxui::dom
    PRIVATE ftxui::component
)

# Installation rules
install(TARGETS calculator
    RUNTIME DESTINATION bin  # For executable
    LIBRARY DESTINATION lib  # For shared libraries
    ARCHIVE DESTINATION lib  # For static libraries
)


# Symbolic link to the executable
install(CODE "execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_INSTALL_PREFIX}/bin/calculator ${CMAKE_INSTALL_PREFIX}/bin/calc)")
install(CODE "execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_INSTALL_PREFIX}/bin/calculator ${CMAKE_INSTALL_PREFIX}/bin/termcalc)")

