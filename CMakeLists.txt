cmake_minimum_required(VERSION 3.16)

project(SnakeGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB_RECURSE SOURCES
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/*.c"
)

add_executable(SnakeGame ${SOURCES})
add_compile_definitions(SHADERS_DIR="${CMAKE_SOURCE_DIR}/shaders")

target_link_libraries(SnakeGame PRIVATE OpenGL::GL glfw)

include(GNUInstallDirs)
install(TARGETS SnakeGame
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
