#include "pch.h"
#include "Pterosaur.h"
#include "TimeMgr.h"
#include "Image.h"
#include "PathMgr.h"
#include "ResMgr.h"
#include "Collider.h"
#include "Animator.h"
#include "Animation.h"
Pterosaur::Pterosaur()
    : m_fSpeed(100.f)
    , m_fMaxDistance(50.f)
    , m_vCenterPos(Vec2(0.f, 0.f))
    , m_iDir(1)
    , m_iHp(5)
{
    //m_pImage = ResMgr::GetInst()->ImgLoad(L"birdImg", L"Image\\bird.bmp");
    Image* pImg = ResMgr::GetInst()->ImgLoad(L"BirdFly", L"Image\\bird.bmp");

    // animator 생성 및 animation 사용
    CreateAnimator();
    GetAnimator()->CreateAnimation(L"BirdFly", pImg, Vec2(0.f, 0.f), Vec2(46.f, 40.f), Vec2(46.f, 0.f), 2, 0.4f);
    GetAnimator()->Play(L"BirdFly", true);

    Animation* Anim = GetAnimator()->FindAnimation(L"BirdFly");
    for (size_t i = 0; i < Anim->GetMaxFrame(); i++) {
        Anim->GetFrame(i).vOffset = Vec2(0.f, 0.f);
    }
    //// animation offset 위로 올리기. 
    //Animation* pAnim = GetAnimator()->FindAnimation(L"BirdFly");
    //for (size_t i = 0; i < pAnim->GetMaxFrame(); i++)
    //    pAnim->GetFrame(i).vOffset = Vec2(10.f, -50.f);

    CreateCollider();
    GetCollider()->SetScale(Vec2(40.f, 30.f));
    GetCollider()->SetOffsetPos(Vec2(-15.f, -20.f));
}

Pterosaur::~Pterosaur()
{
}

void Pterosaur::Update()
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
    //GetAnimator()->Update();
}

void Pterosaur::Render(HDC _dc)
{
    //int Width = (int)m_pImage->GetWidth();
    //int Height = (int)m_pImage->GetHeight();

    //Vec2 vPos = GetPos();
    ////마젠타 색상 뺄때 transparent: 투명한
    //TransparentBlt(_dc
    //    , (int)(vPos.x - (float)(Width / 2))
    //    , (int)(vPos.y - (float)(Height / 2))
    //    , Width, Height
    //    , m_pImage->GetDC()
    //    , 0, 0, Width, Height
    //    , RGB(255, 0, 255));
    Component_Render(_dc);
}

//여기서 게임 종료 시켜야함
void Pterosaur::EnterCollision(Collider* _pOther)
{
    Object* pOtherObj = _pOther->GetObj();
    if (pOtherObj->GetName() == L"Player")
    {
        ChangeScene(SCENE_TYPE::GAMEOVER);
    }
}

