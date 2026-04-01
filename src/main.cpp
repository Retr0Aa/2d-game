#include "raylib.h"

typedef struct {
    Vector2 position;
    Vector2 velocity;
    float radius;
} Ball;

int main(void)
{
    InitWindow(800, 600, "physics");

    Ball ball = { {400, 100}, {0, 0}, 20 };
    float gravity = 500.0f; // pixels/sec²

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        // physics
        ball.velocity.y += gravity * dt;
        ball.position.x += ball.velocity.x * dt;
        ball.position.y += ball.velocity.y * dt;

        // ground collision
        if (ball.position.y + ball.radius >= 600)
        {
            ball.position.y = 600 - ball.radius;
            ball.velocity.y *= -0.7f; // bounce
        }

        // draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawCircleV(ball.position, ball.radius, RED);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}