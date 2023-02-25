#include "pch.h"
#include "StartScene.h"
#include "Object.h"
#include "Player.h"
#include "Monster.h"
#include "Core.h"
#include "Image.h"
#include "BackGround.h"
#include "PathMgr.h"
#include "CollisionMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "AniImage.h"
#include "SoundMgr.h"
#include "UIImage.h"

StartScene::StartScene()
{
}

StartScene::~StartScene()
{
}
void StartScene::Enter()
{
	
	//SoundMgr::GetInst()->Stop(SOUND_CHANNEL::SC_BGM);
	//SoundMgr::GetInst()->LoadSound(L"BGM", true, L"Sound\\StartBgm.wav");
	//SoundMgr::GetInst()->Play(L"BGM");
	// Object 추가
	/*Object* pObj = new Player;
	pObj->SetPos(Vec2(Core::GetInst()->GetResolution().x / 12, Core::GetInst()->GetResolution().y - Core::GetInst()->GetResolution().y / 9));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);*/

	//BackGround


	UIImage* Title = new UIImage;
	Title->SetImage(L"Title", L"Image\\DinoTitle.bmp", 550, 50);
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

	//AniImage* d = new AniImage;
	//d->SetPos(Vec2(0, 0));
	//d->SetScale(Vec2(1.f, 1.f));
	//d->SetAniImage(L"Dino", L"Image\\DinoRun.bmp", 88.f, 94.f, 2);

	//AddObject((Object*)d, GROUP_TYPE::DEFAULT);

	AniImage* playerImage = new AniImage;
	playerImage->SetPos(Vec2(Core::GetInst()->GetResolution().x / 2 + 50, Core::GetInst()->GetResolution().y - Core::GetInst()->GetResolution().y / 9));
	playerImage->SetScale(Vec2(1.f, 1.f));
	playerImage->SetAniImage(L"PlayerIdle", L"Image\\DinoIdle.bmp", 88.f, 94.f, 2);

	AddObject((Object*)playerImage, GROUP_TYPE::ANIIMAGE);

	/*BackGround* backGround = new BackGround;
	backGround->SetImage(L"Background_Tower", L"Image\\BackGroundTower.bmp");
	backGround->SetPos(Vec2(Core::GetInst()->GetResolution().x / 2, Core::GetInst()->GetResolution().y - Core::GetInst()->GetResolution().y / 2));
	backGround->SetScale(Vec2(10.f, 10.f));*/
	//backGround->downSpeed = 0.5f;
	//backGround->
	//AddObject(backGround, GROUP_TYPE::BACKGROUND);
	//	Object* pOtherPlayer = new Player(*(Player*)pObj);
		/*Object* pOtherPlayer = pObj->Clone();
		pOtherPlayer->SetPos(Vec2(Core::GetInst()->GetResolution().x / 2.f + 100.f, Core::GetInst()->GetResolution().y / 2.f));
		AddObject(pOtherPlayer, GROUP_TYPE::PLAYER);*/

		//m_vecObj[(UINT)GROUP_TYPE::DEFAULT].push_back(pObj); 

		// Monster Object 추가
		//Monster* pMonsterObj = new Monster;
		//pMonsterObj->SetPos(Vec2(640.f, 50.f));
		//pMonsterObj->SetScale(Vec2(50.f, 50.f));
		//pMonsterObj->SetCenterPos(pMonsterObj->GetPos());
		//AddObject(pMonsterObj, GROUP_TYPE::MONSTER);

		// 몬스터 배치
	Vec2 vResolution(Vec2(Core::GetInst()->GetResolution()));
	int iMonster = 16;
	float fMoveDist = 25.f;
	float fObjScale = 50.f;
	float fTerm = (vResolution.x - ((fMoveDist + fObjScale / 2.f) * 2)) / (float)(iMonster - 1);
	/*Monster* pMonsterObj = nullptr;
	for (int i = 0; i < iMonster; i++)
	{
		pMonsterObj = new Monster;
		pMonsterObj->SetName(L"Monster");
		pMonsterObj->SetPos(Vec2((fMoveDist + fObjScale / 2.f) + (float)i * fTerm, 50.f));
		pMonsterObj->SetScale(Vec2(fObjScale, fObjScale));
		pMonsterObj->SetCenterPos(pMonsterObj->GetPos());
		pMonsterObj->SetMoveDistance(fMoveDist);
		AddObject(pMonsterObj, GROUP_TYPE::MONSTER);
	}*/
	//pObj = new Object;

	//pObj->SetPos(Vec2(640.f, 384.f));
	//pObj->SetScale(Vec2(100.f, 100.f));

	//AddObject(pObj, GROUP_TYPE::DEFAULT);
	// 충돌 지정 
	// Player - Monster 그룹 간의 충돌 체크
	/*CollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::BULLET_PLAYER, GROUP_TYPE::MONSTER)*/
}

void StartScene::Exit()
{
	DeleteAll();
	CollisionMgr::GetInst()->CheckReset();
}

void StartScene::Update()
{
	Scene::Update();

	

	if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::INGAME);
	}
}
