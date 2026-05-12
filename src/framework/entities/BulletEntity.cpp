//
// Created by Alexander Buchkov on 21.04.26.
//

#include "BulletEntity.h"

BulletEntity::BulletEntity(Vector2 position, Vector2 size, Vector2 velocity, float lifetimeSeconds, Color color)
    : velocity(velocity), lifetimeLeft(lifetimeSeconds) {
    transform.position = position;
    transform.scale = size;
    material.color = color;
}

BulletEntity::~BulletEntity() {
}

void BulletEntity::render() {
    Entity::render();

    DrawRectangle(
        static_cast<int>(transform.position.x),
        static_cast<int>(transform.position.y),
        static_cast<int>(transform.scale.x),
        static_cast<int>(transform.scale.y),
        material.color
    );
}

void BulletEntity::update(float deltaTime) {
    Entity::update(deltaTime);

    transform.position.x += velocity.x * deltaTime;
    transform.position.y += velocity.y * deltaTime;
    lifetimeLeft -= deltaTime;

    if (lifetimeLeft <= 0.0f || transform.position.x < -80.0f || transform.position.x > 900.0f ||
        transform.position.y < -80.0f || transform.position.y > 700.0f) {
        markForDestroy();
    }
}


