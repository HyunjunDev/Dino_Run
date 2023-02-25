#pragma once
#include "Scene.h"
class EndScene :
    public Scene
{
private:
public:
    EndScene();
    virtual ~EndScene();
public:
    virtual void Enter() override;
    virtual void Exit() override;
    virtual void Update() override;
};

