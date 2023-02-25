#include "pch.h"
#include "Background.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "Bullet.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Image.h"
#include "PathMgr.h"
#include "ResMgr.h"
#include "Collider.h"
#include "Animator.h"
#include "Animation.h"
Background::Background() : m_fSpeed(100.f), m_iDir(1)
{
	m_Image = ResMgr::GetInst()->ImgLoad(L"BackgroundImg", L"Image\\background.bmp");
}
Background::~Background()
{
	//if(nullptr !=m_pImage)
	//	delete m_pImage;
}
void Background::Update()
{
	Vec2 vCurPos = GetPos();
	// 진행방향으로 시간당 m_fSpeed만큼 이동
//    vCurPos.x += m_fSpeed * fDT * m_iDir;
	vCurPos.x += fDT * m_fSpeed * -m_iDir;

	// 배회 거리 기준량을 넘어섰는지 확인
	if (-1000 >= vCurPos.x)
	{
		vCurPos.x = 2000;
	}
	/*float fDist = abs(m_vCenterPos.x - vCurPos.x) - m_fMaxDistance;
	if (fDist > 0.f)
	{
		m_iDir *= -1;
		vCurPos.x += fDist * m_iDir;
	}*/
	SetPos(vCurPos);
}

void Background::Render(HDC _dc)
{
	int Width = (int)m_Image->GetWidth();
	int Height = (int)m_Image->GetHeight();

	Vec2 vPos = GetPos();
	//마젠타 색상 뺄때 transparent: 투명한
	TransparentBlt(_dc
		, (int)(vPos.x - (float)(Width / 2))
		, (int)(vPos.y - (float)(Height / 2))
		, Width, Height
		, m_Image->GetDC()
		, 0, 0, Width, Height
		, RGB(255, 0, 255));
	Component_Render(_dc);
}
