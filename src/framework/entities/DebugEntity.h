//
// Created by Alexander Buchkov on 1.04.26.
//
#pragma once

#include "../Entity.h"

class DebugEntity : public Entity {
public:
    DebugEntity(Vector2 position = {400.0f, 100.0f}, float size = 40.0f, Color color = RED);
    ~DebugEntity();

    void render() override;
    void update(float deltaTime) override;
    void onAddedToWorld() override;
};
