//
// Created by Alexander Buchkov on 1.04.26.
//

#pragma once

#include <string>
#include <algorithm>

#include "RenderMaterial.h"
#include "Transform2D.h"

#include <box2d/box2d.h>

struct BoxPhysicsOptions {
    b2BodyType bodyType = b2_staticBody;
    float density = 0.0f;
    float friction = 0.7f;
    float restitution = 0.0f;
    float linearDamping = 0.0f;
    float gravityScale = 1.0f;
    bool fixedRotation = false;
};

class Entity {
public:
    Entity() = default;

    virtual ~Entity();

    virtual void render();

    virtual void update(float deltaTime);

    virtual void onKeyDown(int key);
    virtual void onKeyPressed(int key);

    virtual void onAddedToWorld();

protected:
    void createBoxBody(const BoxPhysicsOptions& options);
    void syncBoxTransformFromBody(float yOffset = 0.0f);

protected:
    const char *tag = nullptr;
    Transform2D transform = {{0.0f, 0.0f}, 0.0f, {0.0f, 0.0f}};
    RenderMaterial material = {WHITE, nullptr};

    b2World* world = nullptr;
    b2Body *body = nullptr;

public:
    const char *getTag() { return tag; }
    void setTag(const char *newTag) { tag = newTag; }

    Transform2D &getTransform() { return transform; }
    void setTransform(const Transform2D &t) { transform = t; }

    RenderMaterial &getMaterial() { return material; }
    void setMaterial(const RenderMaterial &m) { material = m; }

    void setWorld(b2World* w) { world = w; }

    void setBody(b2Body* b) { body = b; }
    b2Body* getBody() { return body; }

    void markForDestroy() { destroyed = true; }
    [[nodiscard]] bool isDestroyed() const { return destroyed; }

private:
    bool destroyed = false;
};

inline Entity::~Entity() = default;

inline void Entity::render() {
}

inline void Entity::update(float deltaTime) {
}

inline void Entity::onKeyDown(int key) {
}

inline void Entity::onKeyPressed(int key) {
}

inline void Entity::onAddedToWorld() {
}

inline void Entity::createBoxBody(const BoxPhysicsOptions& options) {
    if (!world || body) {
        return;
    }

    const float halfWidth = std::max(transform.scale.x * 0.5f, 0.0f);
    const float halfHeight = std::max(transform.scale.y * 0.5f, 0.0f);

    b2BodyDef def;
    def.type = options.bodyType;
    def.position.Set(
        (transform.position.x + halfWidth) / 100.0f,
        (transform.position.y + halfHeight) / 100.0f
    );
    def.fixedRotation = options.fixedRotation;
    def.gravityScale = options.gravityScale;
    def.linearDamping = options.linearDamping;

    b2Body* createdBody = world->CreateBody(&def);

    b2PolygonShape shape;
    shape.SetAsBox(halfWidth / 100.0f, halfHeight / 100.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = options.density;
    fixtureDef.friction = options.friction;
    fixtureDef.restitution = options.restitution;

    createdBody->CreateFixture(&fixtureDef);
    setBody(createdBody);
}

inline void Entity::syncBoxTransformFromBody(float yOffset) {
    if (!body) {
        return;
    }

    const b2Vec2 pos = body->GetPosition();
    transform.position.x = pos.x * 100.0f - transform.scale.x * 0.5f;
    transform.position.y = pos.y * 100.0f - transform.scale.y * 0.5f + yOffset;
}
