#include "pch.h"
#include "EndScene.h"
#include "Object.h"
#include "Player.h"
#include "Monster.h"
#include "Core.h"
#include "Image.h"
#include "BackGround.h"
#include "PathMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "AniImage.h"
#include "SoundMgr.h"
#include "UIImage.h"

EndScene::EndScene()
{

}

EndScene::~EndScene()
{
}

void EndScene::Enter()
{
	SoundMgr::GetInst()->Stop(SOUND_CHANNEL::SC_BGM);
	SoundMgr::GetInst()->LoadSound(L"Dead", false, L"Sound\\Dead.wav");
	SoundMgr::GetInst()->Play(L"Dead");

	UIImage* Title = new UIImage;
	Title->SetImage(L"GameOver", L"Image\\GameOver.bmp", 550, 50);
	Title->SetScale(100, 100);
	AddObject((Object*)Title, GROUP_TYPE::DEFAULT);

	UIImage* ground = new UIImage;
	ground->SetImage(L"Ground", L"Image\\background.bmp", 550, 285);
	ground->SetScale(100, 100);
	AddObject((Object*)ground, GROUP_TYPE::DEFAULT);

	UIImage* cloude1 = new UIImage;
	cloude1->SetImage(L"Cloud1", L"Image\\cloude.bmp", 300, 175);
	cloude1->SetScale(100, 100);
	AddObject((Object*)cloude1, GROUP_TYPE::DEFAULT);

	UIImage* cloude2 = new UIImage;
	cloude2->SetImage(L"Cloud2", L"Image\\cloude.bmp", 900, 116);
	cloude2->SetScale(100, 100);
	AddObject((Object*)cloude2, GROUP_TYPE::DEFAULT);

	UIImage* pets = new UIImage;
	pets->SetImage(L"pets", L"Image\\PressEnterToStart.bmp", 550, 308);
	pets->SetScale(100, 100);
	AddObject((Object*)pets, GROUP_TYPE::DEFAULT);

	UIImage* dino = new UIImage;
	dino->SetImage(L"dinoDead", L"Image\\DinoDead.bmp", 550, 246);
	dino->SetScale(100, 100);
	AddObject((Object*)dino, GROUP_TYPE::PLAYER);


}

void EndScene::Exit()
{
}

void EndScene::Update()
{
	Scene::Update();
	if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::INGAME);
	}
}
