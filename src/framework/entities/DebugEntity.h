//
// Created by Alexander Buchkov on 1.04.26.
//
#pragma once
#include "../Entity.h"

class DebugEntity : public Entity {
public:
    DebugEntity();
    ~DebugEntity();

    void Render() override;
};
