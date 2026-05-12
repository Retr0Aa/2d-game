//
// Created by Alexander Buchkov on 21.04.26.
//

#include "MainScene.h"

#include "../entities/BulletEntity.h"
#include "../entities/PlayerEntity.h"
#include "../entities/RectEntity.h"

#include <cmath>

namespace {
constexpr float kBulletSpeed = 520.0f;
constexpr float kAimEpsilon = 0.0001f;
}

MainScene::MainScene() {
    auto* groundEntity = spawnEntity<RectEntity>(Vector2{0.0f, 550.0f}, Vector2{800.0f, 100.0f}, GRAY);
    groundEntity->setTag("Ground");

    auto* platformEntity = spawnEntity<RectEntity>(Vector2{250.0f, 430.0f}, Vector2{150.0f, 20.0f}, LIGHTGRAY);
    platformEntity->setTag("Platform");

    player = spawnEntity<PlayerEntity>(Vector2{80.0f, 0.0f});
    player->setTag("Player");
}

MainScene::~MainScene() {
}

void MainScene::render() {
    Scene::render();

    DrawText("A/D move | SPACE jump | E or LMB shoot", 16, 14, 18, DARKGRAY);
}

void MainScene::update(float deltaTime) {
    Scene::update(deltaTime);

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        shoot();
    }
}

void MainScene::onKeyDown(int key) {
    Scene::onKeyDown(key);
}

void MainScene::onKeyPressed(int key) {
    Scene::onKeyPressed(key);

    if (key == KEY_E) {
        shoot();
    }
}

void MainScene::shoot() {
    if (!player) {
        return;
    }

    const Vector2 muzzlePosition = player->getGunMuzzlePosition();
    const Vector2 mousePosition = GetMousePosition();
    const Vector2 delta = {
        mousePosition.x - muzzlePosition.x,
        mousePosition.y - muzzlePosition.y
    };
    const float lengthSq = delta.x * delta.x + delta.y * delta.y;

    Vector2 direction = {1.0f, 0.0f};
    if (lengthSq > kAimEpsilon) {
        const float invLength = 1.0f / std::sqrt(lengthSq);
        direction = {delta.x * invLength, delta.y * invLength};
    }

    auto* bullet = spawnEntity<BulletEntity>(
        Vector2{muzzlePosition.x - 5.0f, muzzlePosition.y - 2.0f},
        Vector2{10.0f, 4.0f},
        Vector2{direction.x * kBulletSpeed, direction.y * kBulletSpeed},
        2.0f,
        RED
    );
    bullet->setTag("Bullet");
}



