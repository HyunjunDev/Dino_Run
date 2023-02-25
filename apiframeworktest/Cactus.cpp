#include "pch.h"
#include "Cactus.h"
#include "TimeMgr.h"
#include "Image.h"
#include "PathMgr.h"
#include "ResMgr.h"
#include "Collider.h"

Cactus::Cactus()
    : m_fSpeed(100.f)
    , m_fMaxDistance(50.f)
    , m_vCenterPos(Vec2(0.f, 0.f))
    , m_iDir(1)
    , m_iHp(5)
{
    m_pImage = ResMgr::GetInst()->ImgLoad(L"obstacle2Img", L"Image\\obstacle2.bmp");
    CreateCollider();
    GetCollider()->SetScale(Vec2(144.f, 90.f));
}

Cactus::~Cactus()
{
}

void Cactus::Update()
{
    Vec2 vCurPos = GetPos();
    // 진행방향으로 시간당 m_fSpeed만큼 이동
//    vCurPos.x += m_fSpeed * fDT * m_iDir;
    vCurPos.x += fDT * m_fSpeed * -m_iDir;

    // 배회 거리 기준량을 넘어섰는지 확인
    if (-100 > vCurPos.x)
    {
        DeleteObject(this);
    }
    /*float fDist = abs(m_vCenterPos.x - vCurPos.x) - m_fMaxDistance;
    if (fDist > 0.f)
    {
        m_iDir *= -1;
        vCurPos.x += fDist * m_iDir;
    }*/
    SetPos(vCurPos);
}

void Cactus::Render(HDC _dc)
{
    int Width = (int)m_pImage->GetWidth();
    int Height = (int)m_pImage->GetHeight();

    Vec2 vPos = GetPos();
    //마젠타 색상 뺄때 transparent: 투명한
    TransparentBlt(_dc
        , (int)(vPos.x - (float)(Width / 2))
        , (int)(vPos.y - (float)(Height / 2))
        , Width, Height
        , m_pImage->GetDC()
        , 0, 0, Width, Height
        , RGB(255, 0, 255));
    Component_Render(_dc);
}

void Cactus::EnterCollision(Collider* _pOther)
{
    Object* pOtherObj = _pOther->GetObj();
    if (pOtherObj->GetName() == L"Player")
    {
        ChangeScene(SCENE_TYPE::GAMEOVER);
    }
}

