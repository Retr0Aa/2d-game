//
// Created by Alexander Buchkov on 1.04.26.
//

#include "DebugEntity.h"

DebugEntity::DebugEntity(Vector2 position, float size, Color color) {
    transform.position = position;
    transform.scale = {size, size};
    material.color = color;
}

DebugEntity::~DebugEntity() {
}

void DebugEntity::onAddedToWorld() {
    createBoxBody({
        .bodyType = b2_dynamicBody,
        .density = 1.0f,
        .friction = 0.7f,
        .restitution = 0.15f,
        .linearDamping = 0.4f
    });
}

void DebugEntity::render() {
    Entity::render();

    DrawRectangleV(transform.position, transform.scale, material.color);
}

void DebugEntity::update(float deltaTime) {
    Entity::update(deltaTime);
    syncBoxTransformFromBody();
}
