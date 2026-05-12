//
// Created by Alexander Buchkov on 1.04.26.
//

#include "../Scene.h"

class TestScene : public Scene {
public:
    TestScene();
    ~TestScene();

    void render() override;
    void update(float deltaTime) override;

    void onKeyDown(int key) override;
    void onKeyPressed(int key) override;
};
