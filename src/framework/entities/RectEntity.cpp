//
// Created by Alexander Buchkov on 2.04.26.
//

#include "RectEntity.h"

RectEntity::RectEntity(Vector2 position, Vector2 size, Color color) {
    transform.position = position;
    transform.scale = size;
    material.color = color;
}

void RectEntity::onAddedToWorld() {
    createBoxBody({
        .bodyType = b2_staticBody,
        .friction = 0.9f
    });
}

RectEntity::~RectEntity() {
}

void RectEntity::render() {
    Entity::render();

    DrawRectangle(transform.position.x,
                  transform.position.y,
                  transform.scale.x,
                  transform.scale.y,
                  material.color
    );
}

void RectEntity::update(float deltaTime) {
    Entity::update(deltaTime);
    syncBoxTransformFromBody();
}
