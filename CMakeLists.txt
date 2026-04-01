cmake_minimum_required(VERSION 4.2)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(libs/raylib)

add_executable(untitled src/main.cpp
        src/framework/Entity.h
        src/framework/RenderMaterial.h
        src/framework/entities/DebugEntity.cpp
        src/framework/entities/DebugEntity.h
        src/framework/Transform2D.h)

target_link_libraries(untitled raylib)

# macOS frameworks (required)
target_link_libraries(untitled
        "-framework IOKit"
        "-framework Cocoa"
        "-framework OpenGL"
)
