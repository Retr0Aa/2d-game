//
// Created by Alexander Buchkov on 1.04.26.
//
#pragma once
#include "framework/Scene.h"

class Application {
public:
    Application();

    ~Application();

    int run();

private:
    Scene* currentScene;
};
