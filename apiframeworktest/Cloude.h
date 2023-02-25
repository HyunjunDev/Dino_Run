#pragma once
#include "Object.h"

class Image;
class Cloude :
    public Object
{
private:
    Image* m_pImage;
    float   m_fSpeed;
    int     m_iDir;
public:
    Cloude();
    //Player(const Player& _origin) 
    //    : Object(_origin)
    //    , m_pImage(_origin.m_pImage)
    //{}
    ~Cloude();
    CLONE(Cloude);
private:
public:
    void Update()       override;
    void Render(HDC _dc) override;
};

