//
// Created by Alexander Buchkov on 2.04.26.
//

#pragma once

#include "../Entity.h"

class RectEntity : public Entity {
public:
    RectEntity(Vector2 position = {0.0f, 0.0f}, Vector2 size = {0.0f, 0.0f}, Color color = WHITE);
    ~RectEntity();

    void render() override;
    void update(float deltaTime) override;

    void onAddedToWorld() override;
};
