#pragma once
#include "Scene.h"
class StartScene :
    public Scene
{
public:
    virtual void Enter() override;
    virtual void Exit() override;
    virtual void Update() override;
public:
    StartScene();
    virtual ~StartScene();
};