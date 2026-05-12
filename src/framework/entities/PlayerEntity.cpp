//
// Created by Alexander Buchkov on 2.04.26.
//

#include "PlayerEntity.h"

#include <cmath>

namespace {
constexpr float kGunWidth = 16.0f;
constexpr float kGunHeight = 6.0f;
constexpr float kGunOffsetFromBody = 10.0f;
constexpr float kAimEpsilon = 0.0001f;
}

PlayerEntity::PlayerEntity(Vector2 position, Vector2 size, Color color) {
    transform.position = position;
    transform.scale = size;
    material.color = color;
}

void PlayerEntity::onAddedToWorld() {
    createBoxBody({
        .bodyType = b2_dynamicBody,
        .density = 1.0f,
        .friction = 0.8f,
        .linearDamping = 10.0f,
        .gravityScale = 2.0f,
        .fixedRotation = true
    });
}

PlayerEntity::~PlayerEntity() {
}

void PlayerEntity::render() {
    Entity::render();

    DrawRectangle(transform.position.x,
                  transform.position.y,
                  transform.scale.x,
                  transform.scale.y,
                  material.color
    );

    const Vector2 aimDirection = getAimDirection();
    const Vector2 gunBase = {
        transform.position.x + transform.scale.x * 0.5f + aimDirection.x * kGunOffsetFromBody,
        transform.position.y + transform.scale.y * 0.55f + aimDirection.y * kGunOffsetFromBody
    };

    const Rectangle gunRect = {
        gunBase.x,
        gunBase.y - kGunHeight * 0.5f,
        kGunWidth,
        kGunHeight
    };
    const float gunAngleDegrees = std::atan2(aimDirection.y, aimDirection.x) * RAD2DEG;
    DrawRectanglePro(gunRect, Vector2{0.0f, kGunHeight * 0.5f}, gunAngleDegrees, DARKBROWN);
}

void PlayerEntity::update(float deltaTime) {
    Entity::update(deltaTime);
    syncBoxTransformFromBody(3.0f);

}

void PlayerEntity::onKeyDown(int key) {
    Entity::onKeyDown(key);

    if (!body) {
        return;
    }

    b2Vec2 velocity = body->GetLinearVelocity();

    if (key == KEY_D) {
        velocity.x = 4.4f;
        body->SetLinearVelocity(velocity);
    }
    if (key == KEY_A) {
        velocity.x = -4.4f;
        body->SetLinearVelocity(velocity);
    }
}

void PlayerEntity::onKeyPressed(int key) {
    Entity::onKeyPressed(key);

    if (!body || key != KEY_SPACE) {
        return;
    }

    const float verticalSpeed = body->GetLinearVelocity().y;
    if (std::abs(verticalSpeed) < 0.03f) {
        body->SetLinearVelocity({body->GetLinearVelocity().x, 0.0f});
        body->ApplyLinearImpulseToCenter({0.0f, -1.45f}, true);
    }
}

Vector2 PlayerEntity::getGunMuzzlePosition() const {
    const Vector2 aimDirection = getAimDirection();
    const Vector2 gunBase = {
        transform.position.x + transform.scale.x * 0.5f + aimDirection.x * kGunOffsetFromBody,
        transform.position.y + transform.scale.y * 0.55f + aimDirection.y * kGunOffsetFromBody
    };

    return {
        gunBase.x + aimDirection.x * kGunWidth,
        gunBase.y + aimDirection.y * kGunWidth
    };
}

Vector2 PlayerEntity::getAimDirection() const {
    const Vector2 gunBase = {
        transform.position.x + transform.scale.x * 0.5f,
        transform.position.y + transform.scale.y * 0.55f
    };

    const Vector2 mousePosition = GetMousePosition();
    const Vector2 delta = {
        mousePosition.x - gunBase.x,
        mousePosition.y - gunBase.y
    };
    const float lengthSq = delta.x * delta.x + delta.y * delta.y;

    if (lengthSq <= kAimEpsilon) {
        return {1.0f, 0.0f};
    }

    const float invLength = 1.0f / std::sqrt(lengthSq);
    return {delta.x * invLength, delta.y * invLength};
}

