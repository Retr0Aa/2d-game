//
// Created by Alexander Buchkov on 2.04.26.
//
#pragma once

#include "../Entity.h"

class PlayerEntity : public Entity {
public:
    PlayerEntity(Vector2 position, Vector2 size = {30.0f, 30.0f}, Color color = DARKGRAY);

    ~PlayerEntity() override;

    void render() override;

    void update(float deltaTime) override;

    void onKeyDown(int key) override;
    void onKeyPressed(int key) override;

    void onAddedToWorld() override;

    Vector2 getGunMuzzlePosition() const;
    Vector2 getAimDirection() const;
};
