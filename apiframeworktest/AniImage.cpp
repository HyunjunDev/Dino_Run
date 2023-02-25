#include "pch.h"
#include "AniImage.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Image.h"
#include "PathMgr.h"
#include "ResMgr.h"
#include "Collider.h"
#include "Animator.h"
#include "Animation.h"
#include "Core.h"

AniImage::AniImage():
	m_pImage()
{
}

AniImage::~AniImage()
{
}

void AniImage::Update()
{
}

void AniImage::Render(HDC _dc)
{
	Component_Render(_dc);
}

void AniImage::SetAniImage(wstring name, wstring path, float x, float y, int frame)
{
	Image* image = ResMgr::GetInst()->ImgLoad(name, path);
	CreateAnimator();

	GetAnimator()->CreateAnimation(name, image, Vec2(0.f, 0.f), Vec2(x, y), Vec2(x, 0.f), frame, 1.f);
	GetAnimator()->Play(name, true);

	Animation* Anim = GetAnimator()->FindAnimation(name);

	for (size_t i = 0; i < Anim->GetMaxFrame(); i++) {
		Anim->GetFrame(i).vOffset = Vec2(0.f, 0.f);
	}
}