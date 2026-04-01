//
// Created by Alexander Buchkov on 1.04.26.
//

#include "raylib.h"
#include "RenderMaterial.h"
#include "Transform2D.h"

class Entity {
public:
    Entity();
    virtual ~Entity();

    virtual void Render();
private:
    Transform2D transform;

    RenderMaterial* material;
public:
    Transform2D getTransform() { return transform; }
    void setTransform(Transform2D transform) { this->transform = transform; }
};
