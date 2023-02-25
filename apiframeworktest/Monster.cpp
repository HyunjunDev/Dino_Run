#include "pch.h"
#include "Monster.h"
#include "TimeMgr.h"
#include "Image.h"
#include "PathMgr.h"
#include "ResMgr.h"
#include "Collider.h"

Monster::Monster()
    : m_fSpeed(100.f)
    , m_fMaxDistance(50.f)
    , m_vCenterPos(Vec2(0.f, 0.f))
    , m_iDir(1)
    , m_iHp(5)
{
    m_pImage = ResMgr::GetInst()->ImgLoad(L"obstacle1Img", L"Image\\obstacle1.bmp");
    CreateCollider();
    GetCollider()->SetScale(Vec2(100.f, 60.f));
}

Monster::~Monster()
{
}

void Monster::Update()
{
    Vec2 vCurPos = GetPos();
    // ����������� �ð��� m_fSpeed��ŭ �̵�
//    vCurPos.x += m_fSpeed * fDT * m_iDir;
    vCurPos.x += fDT * m_fSpeed * -m_iDir;

    // ��ȸ �Ÿ� ���ط��� �Ѿ���� Ȯ��
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

void Monster::Render(HDC _dc)
{
    int Width = (int)m_pImage->GetWidth();
    int Height = (int)m_pImage->GetHeight();

    Vec2 vPos = GetPos();
    //����Ÿ ���� ���� transparent: ������
    TransparentBlt(_dc
        , (int)(vPos.x - (float)(Width / 2))
        , (int)(vPos.y - (float)(Height / 2))
        , Width, Height
        , m_pImage->GetDC()
        , 0, 0, Width, Height
        , RGB(255, 0, 255));
    Component_Render(_dc);
}

//���⼭ ���� ���� ���Ѿ���
void Monster::EnterCollision(Collider* _pOther)
{
    Object* pOtherObj = _pOther->GetObj();
    if (pOtherObj->GetName() == L"Player")
    {
        ChangeScene(SCENE_TYPE::GAMEOVER);
    }
}