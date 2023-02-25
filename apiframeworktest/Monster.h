#pragma once
#include "Object.h"
class Image;
class Monster :
    public Object
{
private:
    Image* m_pImage;
    float   m_fSpeed;
    Vec2    m_vCenterPos;
    float   m_fMaxDistance;
    int     m_iDir; // 1, -1
    int     m_iHp;
public:
    float GetSpeed() { return m_fSpeed; }
    void SetSpeed(float _f) { m_fSpeed = _f; }
    void SetCenterPos(Vec2 _vPos) { m_vCenterPos = _vPos; }
    void SetMoveDistance(float _f) { m_fMaxDistance = _f; }
public:
    virtual void Update() override;
    virtual void Render(HDC _dc) override;
    virtual void	EnterCollision(Collider* _pOther);
    //    Monster* Clone() { return new Monster(*this); }
    CLONE(Monster);
public:
    Monster();
    ~Monster();
};

