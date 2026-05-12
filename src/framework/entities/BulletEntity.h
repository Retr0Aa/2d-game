//
// Created by Alexander Buchkov on 21.04.26.
//

#pragma once

#include "../Entity.h"

class BulletEntity : public Entity {
public:
    BulletEntity(Vector2 position, Vector2 size, Vector2 velocity, float lifetimeSeconds = 1.8f, Color color = RED);
    ~BulletEntity() override;

    void render() override;
    void update(float deltaTime) override;

private:
    Vector2 velocity = {0.0f, 0.0f};
    float lifetimeLeft = 0.0f;
};

