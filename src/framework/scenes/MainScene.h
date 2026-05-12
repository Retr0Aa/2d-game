//
// Created by Alexander Buchkov on 21.04.26.
//

#pragma once

#include "../Scene.h"

class PlayerEntity;

class MainScene : public Scene {
public:
    MainScene();
    ~MainScene() override;

    void render() override;
    void update(float deltaTime) override;

    void onKeyDown(int key) override;
    void onKeyPressed(int key) override;

private:
    void shoot();

private:
    PlayerEntity* player = nullptr;
};

