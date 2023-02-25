#pragma once
#include "Object.h"

class Image;
class Button :
    public Object
{
private:
    Image* m_pImage;
public:
    Button();
    //Player(const Player& _origin) 
    //    : Object(_origin)
    //    , m_pImage(_origin.m_pImage)
    //{}
    ~Button();
private:
    //    Player* Clone{ return new Player(*this); }
    CLONE(Button);
public:
    void Update()       override;
    void Render(HDC _dc) override;
};

