#include "pch.h"
#include "Player.h"
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
#include "SoundMgr.h"
#include "Animation.h"
#include "Core.h"

Player::Player()
{
	// collider 새성
	CreateCollider();
	GetCollider()->SetScale(Vec2(60.f, 70.f));
	GetCollider()->SetOffsetPos(Vec2(10.f, -30.f));

	//SoundMgr::GetInst()->Stop(SOUND_CHANNEL::SC_EFFECT);
	SoundMgr::GetInst()->LoadSound(L"Jump", false, L"Sound\\jump.wav");
	SoundMgr::GetInst()->LoadSound(L"Click", false, L"Sound\\click.wav");

	// image 업로드
	Image* rImage = ResMgr::GetInst()->ImgLoad(L"Player_Run", L"Image\\DinoRun.bmp");
	Image* jImage = ResMgr::GetInst()->ImgLoad(L"Player_Jump", L"Image\\DinoIdle.bmp");
	Image* dImage = ResMgr::GetInst()->ImgLoad(L"Player_Down", L"Image\\bowDown.bmp");

	// animator 생성 및 animation 사용
	CreateAnimator();
	//GetAnimator()->CreateAnimation(L"Jiwoofront", pImg, Vec2(0.f, 150.f), Vec2(50.f, 50.f), Vec2(50.f, 0.f), 5, 0.2f);
	//GetAnimator()->Play(L"Jiwoofront", true);

	GetAnimator()->CreateAnimation(L"Player_Run", rImage, Vec2(0.f, 0.f), Vec2(88.f, 94.f), Vec2(88.f, 0.f), 2, 0.15f);
	GetAnimator()->Play(L"Player_Run", true);
	GetAnimator()->CreateAnimation(L"Player_Jump", jImage, Vec2(0.f, 0.f), Vec2(88.f, 94.f), Vec2(88.f, 0.f), 2, 1.f);
	GetAnimator()->CreateAnimation(L"Player_Down", dImage, Vec2(0.f, 0.f), Vec2(118.f, 60.f), Vec2(118.f, 0.f), 2, 0.15f);
	//GetAnimator()->Play(L"Player_Jump", false);

	jumpPower = 1.75f;
	jumpTime = 4;
	jumpHeight = Core::GetInst()->GetResolution().y - Core::GetInst()->GetResolution().y / 9;

	// animation offset 위로 올리기. 
	Animation* pAnim = GetAnimator()->FindAnimation(L"Player_Run");
	Animation* jAnim = GetAnimator()->FindAnimation(L"Player_Jump");
	Animation* dAnim = GetAnimator()->FindAnimation(L"Player_Down");
	for (size_t i = 0; i < pAnim->GetMaxFrame(); i++) {
		pAnim->GetFrame(i).vOffset = Vec2(50.f, 20.f);
		jAnim->GetFrame(i).vOffset = Vec2(50.f, 20.f);
		dAnim->GetFrame(i).vOffset = Vec2(50.f, 20.f);
	}
}
Player::~Player()
{
	//if(nullptr !=m_pImage)
	//	delete m_pImage;
}
void Player::Update()
{
	Vec2 vPos = GetPos();
	bowDown = false;
	
	if (KEY_TAP(KEY::DOWN))
	{
		if (!isJump) {
			GetAnimator()->Play(L"Player_Down", true);
			SoundMgr::GetInst()->Play(L"Click");
			GetCollider()->SetOffsetPos(Vec2(10.f, -1.f));
			bowDown = true;
		}
	}
	if (KEY_AWAY(KEY::DOWN))
	{
		GetAnimator()->Play(L"Player_Run", true);
		GetCollider()->SetOffsetPos(Vec2(10.f, -30.f));
		bowDown = false;
	}

	if (KEY_TAP(KEY::UP))
	{
		if (!isJump) {
			GetAnimator()->Play(L"Player_Jump", true);
			SoundMgr::GetInst()->Play(L"Jump");
			isJump = true;
			isJumpUp = true;
		}
		//CreateBullet();
	}
	
	Jump();
	vPos.y = jumpHeight;
	SetPos(vPos);
	GetAnimator()->Update();
}

void Player::CreateBullet()
{
	Vec2 vBulletPos = GetPos();
	vBulletPos.y -= GetScale().y / 2.f;

	// 
	Bullet* pBullet = new Bullet;
	pBullet->SetName(L"Bullet_Player");
	pBullet->SetPos(vBulletPos);
	pBullet->SetScale(Vec2(25.f, 25.f));
	pBullet->SetDir(Vec2(0.f, -1.f));
	CreateObject(pBullet, GROUP_TYPE::BULLET_PLAYER);
	//Scene* pCurScene = SceneMgr::GetInst()->GetCurScene();
	//pCurScene->AddObject(pBullet,GROUP_TYPE::BULLET);
}
void Player::Render(HDC _dc)
{
	Component_Render(_dc);
	/*int Width = (int)m_pImage->GetWidth();
	int Height = (int)m_pImage->GetHeight();

	Vec2 vPos = GetPos();*/
	//BitBlt(_dc
	//	,(int)(vPos.x - (float)(Width / 2))
	//	,(int)(vPos.y - (float)(Height / 2))
	//    , Width, Height
	//    , m_pImage->GetDC()
	//    , 0,0, SRCCOPY);

	//마젠타 색상 뺄때 transparent: 투명한
	//TransparentBlt(_dc
	//	, (int)(vPos.x - (float)(Width / 2))
	//	, (int)(vPos.y - (float)(Height / 2))
	//	,Width, Height
	//    , m_pImage->GetDC()
	//    ,0,0, Width, Height
	//    , RGB(255,0,255));

}

void Player::Jump()
{
	if (!isJump) return;

	//integral = jumpPower * (3.f / 2.f);
	//0.1 * 0.1 - 2 * 0.1
	// 시간^2 - 시간*점프력
	if (isJumpUp) {
		jumpTime -= 0.01f * fDT;
		jumpHeight -= (jumpTime * jumpHeight) * fDT;
		//(jumpTime * jumpTime - jumpPower * jumpTime);// / 1.2f;// / integral * 0.02f;
		if (jumpHeight <= (Core::GetInst()->GetResolution().y - Core::GetInst()->GetResolution().y / 9) - 250) {
			isJumpUp = false;
		}
	}
	//(jumpTime * jumpTime - jumpPower * jumpTime);// / 1.2f;// / integral * 0.02f;

	if (!isJumpUp && jumpHeight <= Core::GetInst()->GetResolution().y - Core::GetInst()->GetResolution().y / 9)
	{
		jumpTime += 0.05f * fDT;
		jumpHeight += (jumpTime * jumpHeight) * fDT;
	}

	

	/*if (jumpTime < jumpPower)
	{
		jumpTime += 1.8f * 0.0015f;
	}
	else
	{
		jumpTime += 1.1f * 0.001f;
	}*/

	if (jumpHeight >= Core::GetInst()->GetResolution().y - Core::GetInst()->GetResolution().y / 9)// * 1.5f)
	{
		//jumpHeight = 0;
		jumpTime = 4;
		jumpHeight = Core::GetInst()->GetResolution().y - Core::GetInst()->GetResolution().y / 9;
		isJump = false;
		GetAnimator()->Play(L"Player_Run", true);
	}

	//if (jumpTime > jumpPower * 1.34f)// * 1.5f)
	//{
	//	jumpTime = 0;
	//	jumpHeight = Core::GetInst()->GetResolution().y - Core::GetInst()->GetResolution().y / 9;
	//	isJump = false;
	//	GetAnimator()->Play(L"Player_Run", true);
	//}
}


