//
// Created by Alexander Buchkov on 1.04.26.
//

#pragma once

#include <utility>
#include <vector>
#include <algorithm>

#include "Entity.h"

class Scene {
public:
    Scene() = default;
    virtual ~Scene();

    virtual void render();
    virtual void update(float deltaTime);

    virtual void onKeyDown(int key);
    virtual void onKeyPressed(int key);

    Entity* addEntity(Entity* e) {
        e->setWorld(&world);
        e->onAddedToWorld();
        entities.push_back(e);
        return e;
    }

    template <typename T, typename... Args>
    T* spawnEntity(Args&&... args) {
        auto* entity = new T(std::forward<Args>(args)...);
        return static_cast<T*>(addEntity(entity));
    }

protected:
    std::vector<Entity*> entities;
    b2World world = b2World(b2Vec2(0.0f, 28.0f));
};

inline Scene::~Scene() {
    for (Entity* entity : entities) {
        delete entity;
    }
}

inline void Scene::render() {
    for (Entity* entity : entities) {
        entity->render();
    }
}

inline void Scene::update(float deltaTime) {
    world.Step(deltaTime, 6, 2);

    for (Entity* entity : entities) {
        entity->update(deltaTime);
    }

    entities.erase(std::remove_if(entities.begin(), entities.end(), [](Entity* entity) {
        if (!entity->isDestroyed()) {
            return false;
        }

        delete entity;
        return true;
    }), entities.end());
}

inline void Scene::onKeyDown(int key) {
    for (Entity* entity : entities) {
        entity->onKeyDown(key);
    }
}

inline void Scene::onKeyPressed(int key) {
    for (Entity* entity : entities) {
        entity->onKeyPressed(key);
    }
}
