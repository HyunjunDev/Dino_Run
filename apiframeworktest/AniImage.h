#pragma once
#include "Object.h"

class Image;
class AniImage :
	public Object
{
private:
    Image* m_pImage;
public:
    AniImage();
    //Player(const Player& _origin) 
    //    : Object(_origin)
    //    , m_pImage(_origin.m_pImage)
    //{}
    ~AniImage();
public:
    void SetAniImage(wstring name, wstring path, float x, float y, int frame);

private:
    //    Player* Clone{ return new Player(*this); }
    CLONE(AniImage);
public:
    void Update()       override;
    void Render(HDC _dc) override;
};

