//
// Created by Alexander Buchkov on 1.04.26.
//

#include "raylib.h"
#include "Application.h"

#include "framework/scenes/MainScene.h"

typedef struct {
    Vector2 position;
    Vector2 velocity;
    float radius;
} Ball;

Application::Application() {
    InitWindow(800, 600, "2D Engine Test");

    currentScene = new MainScene();
}

Application::~Application() {
    delete currentScene;
}

int Application::run() {
    //Ball ball = { {400, 100}, {0, 0}, 20 };
    //float gravity = 500.0f; // pixels/sec²

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        for (int key = KEY_SPACE; key <= KEY_KP_EQUAL; key++) {
            if (IsKeyDown(key)) {
                currentScene->onKeyDown(key);
            }
            if (IsKeyPressed(key)) {
                currentScene->onKeyPressed(key);
            }
        }

        currentScene->update(dt);

        // draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        currentScene->render();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
