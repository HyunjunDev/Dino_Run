#pragma once
#include "Scene.h"
class Scene_InGame :
    public Scene
{
public:
    float time = 0;
    float cTime = 0;
    float m_time = 0;
    float r_time = 0;
    float w = 250;
    virtual void Enter() override;
    virtual void Exit() override;
    virtual void Update() override;
public:
    Scene_InGame();
    virtual ~Scene_InGame();
};

