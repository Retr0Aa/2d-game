//
// Created by Alexander Buchkov on 1.04.26.
//

#include "TestScene.h"

#include "../entities/DebugEntity.h"
#include "../entities/PlayerEntity.h"
#include "../entities/RectEntity.h"

TestScene::TestScene() {
    auto *groundEntity = spawnEntity<RectEntity>(Vector2{0.0f, 550.0f}, Vector2{800.0f, 100.0f}, GRAY);
    groundEntity->setTag("Ground");

    constexpr float debugSize = 36.0f;
    constexpr float debugStartX = 380.0f;
    constexpr float debugBaseY = 60.0f;
    constexpr float debugSpacing = 2.0f;

    for (int index = 0; index < 3; ++index) {
        auto *debugEntity = spawnEntity<DebugEntity>(
            Vector2{debugStartX, debugBaseY + index * (debugSize + debugSpacing)},
            debugSize,
            Color(
                GetRandomValue(0, 255),
                GetRandomValue(0, 255),
                GetRandomValue(0, 255),
                255)
        );
        debugEntity->setTag(("Debug Entity_" + std::to_string(index)).c_str());
    }

    auto *playerEntity = spawnEntity<PlayerEntity>(Vector2{80.0f, 0.0f});
    playerEntity->setTag("Player");
}

TestScene::~TestScene() {

}

void TestScene::update(float deltaTime) {
    Scene::update(deltaTime);
}

void TestScene::onKeyDown(int key) {
    Scene::onKeyDown(key);
}

void TestScene::onKeyPressed(int key) {
    Scene::onKeyPressed(key);
}

void TestScene::render() {
    Scene::render();
}
