#pragma once
#include "Object.h"

class Image;
class Player :
    public Object
{
private:
    Image* m_pImage;
public:
    Player();
    //Player(const Player& _origin) 
    //    : Object(_origin)
    //    , m_pImage(_origin.m_pImage)
    //{}
    ~Player();
private:
    void CreateBullet();
    void Jump();
    //void Down();
//    Player* Clone{ return new Player(*this); }
    CLONE(Player);
public:
    void Update()       override;
    void Render(HDC _dc) override;

public:
    float jumpTime;
    float jumpHeight;
    float jumpPower;
    float integral = jumpPower * (3.f / 2.f);

    bool isJump;
    bool isJumpUp;
    bool bowDown;
};

