cmake_minimum_required(VERSION 4.2)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BOX2D_BUILD_TESTBED OFF CACHE BOOL "" FORCE)
set(BOX2D_BUILD_UNIT_TESTS OFF CACHE BOOL "" FORCE)
set(BOX2D_BUILD_SAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(libs/raylib)
add_subdirectory(libs/box2d)

add_executable(untitled src/main.cpp
        src/framework/Entity.h
        src/framework/RenderMaterial.h
        src/framework/entities/DebugEntity.cpp
        src/framework/entities/DebugEntity.h
        src/framework/Transform2D.h
        src/framework/Scene.h
        src/framework/scenes/TestScene.cpp
        src/framework/scenes/TestScene.h
        src/framework/scenes/MainScene.cpp
        src/framework/scenes/MainScene.h
        src/Application.cpp
        src/Application.h
        src/framework/entities/RectEntity.cpp
        src/framework/entities/RectEntity.h
        src/framework/entities/PlayerEntity.cpp
        src/framework/entities/PlayerEntity.h
        src/framework/entities/BulletEntity.cpp
        src/framework/entities/BulletEntity.h)

target_link_libraries(untitled raylib box2d)

# macOS frameworks (required)
target_link_libraries(untitled
        "-framework IOKit"
        "-framework Cocoa"
        "-framework OpenGL"
)
