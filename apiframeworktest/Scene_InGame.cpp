#include "pch.h"
#include "Scene_InGame.h"
#include "Object.h"
#include "Player.h"
#include "Monster.h"
#include "Core.h"
#include "Image.h"
#include "PathMgr.h"
#include "CollisionMgr.h"
#include "Cloude.h"
#include "Cactus.h"
#include "Background.h"
#include "TimeMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"
#include "Pterosaur.h"
#include <random>

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> dis(0, 3);
std::random_device cl;
std::mt19937 cen(cl());
std::uniform_int_distribution<int> clt(2, 6);
std::random_device cPos;
std::mt19937 ken(cPos());
std::uniform_int_distribution<int> cp(30, 115);
std::random_device pPos;
std::mt19937 hen(pPos());
std::uniform_int_distribution<int> gp(180, 240);
std::random_device cnt;
std::mt19937 ten(cnt());
std::uniform_int_distribution<int> ct(3, 4);

Scene_InGame::Scene_InGame()
{
}

Scene_InGame::~Scene_InGame()
{
}
void Scene_InGame::Enter()
{
	SoundMgr::GetInst()->Stop(SOUND_CHANNEL::SC_BGM);
	SoundMgr::GetInst()->LoadSound(L"BGM", true, L"Sound\\InGame_Sound.wav");
	SoundMgr::GetInst()->Play(L"BGM");
	// Object 추가
	Object* pObj = new Player;
	pObj->SetName(L"Player");
	pObj->SetPos(Vec2((float)(Core::GetInst()->GetResolution().x / 20), 270.f));
	pObj->SetScale(Vec2(1.f,1.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);

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
	/*Vec2 vResolution(Vec2(Core::GetInst()->GetResolution()));
	int iMonster = 16;
	float fMoveDist = 25.f;
	float fObjScale = 50.f;
	float fTerm = (vResolution.x - ((fMoveDist + fObjScale /2.f) * 2)) / (float)(iMonster-1);
	Monster* pMonsterObj = nullptr;
	for (int i = 0; i < iMonster; i++)
	{
		pMonsterObj = new Monster;
		pMonsterObj->SetName(L"Monster");
		pMonsterObj->SetPos(Vec2((fMoveDist + fObjScale / 2.f) + (float)i*fTerm, 50.f));
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

	Background* background = new Background;
	background->SetPos(Vec2(1000.f, 300.f));
	background->SetScale(Vec2(100.f, 100.f));
	background->SetSpeed(w);
	AddObject(background, GROUP_TYPE::BACKGROUND);
	Background* background2 = new Background;
	background2->SetPos(Vec2(3000.f, 300.f));
	background2->SetSpeed(w);
	background2->SetScale(Vec2(100.f, 100.f));
	AddObject(background2, GROUP_TYPE::BACKGROUND);
	time = 0;
	cTime = 3;

	CollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::BULLET_PLAYER, GROUP_TYPE::MONSTER);
}

void Scene_InGame::Exit()
{
	DeleteAll();
	CollisionMgr::GetInst()->CheckReset();
}

void Scene_InGame::Update()
{  
	SetScore(fDT);
	time += fDT;
	cTime -= fDT;
	r_time += fDT;
	w += fDT * 2;
	if (cTime <= 0)
	{
		float randPos = cp(ken);
		Cloude* background = new Cloude;
		background->SetPos(Vec2(1300.f, randPos));
		background->SetScale(Vec2(100.f, 100.f));
		AddObject(background, GROUP_TYPE::BACKGROUND);
		cTime = clt(cen);
	}

	if (time >= m_time)
	{
		int rand = dis(gen);
		if (rand == 0)
		{
			Vec2 vResolution(Vec2(Core::GetInst()->GetResolution()));
			float fMoveDist = 25.f;
			float fObjScale = 110.f;
			Monster* pMonsterObj = nullptr;
			pMonsterObj = new Monster;
			pMonsterObj->SetName(L"Monster");
			pMonsterObj->SetPos(Vec2(1500.f, 270.f));
			pMonsterObj->SetSpeed(w);
			pMonsterObj->SetScale(Vec2(fObjScale, fObjScale));
			pMonsterObj->SetCenterPos(pMonsterObj->GetPos());
			pMonsterObj->SetMoveDistance(fMoveDist);
			AddObject(pMonsterObj, GROUP_TYPE::MONSTER);
			time = 0;
		}
		else if (rand == 1)
		{
			Vec2 vResolution(Vec2(Core::GetInst()->GetResolution()));
			float fMoveDist = 25.f;
			float fObjScale = 110.f;
			Cactus* pMonsterObj = nullptr;
			pMonsterObj = new Cactus;
			pMonsterObj->SetName(L"Monster2");
			pMonsterObj->SetPos(Vec2(1500.f, 255.f));
			pMonsterObj->SetSpeed(w);
			pMonsterObj->SetScale(Vec2(fObjScale, fObjScale));
			pMonsterObj->SetCenterPos(pMonsterObj->GetPos());
			pMonsterObj->SetMoveDistance(fMoveDist);
			AddObject(pMonsterObj, GROUP_TYPE::MONSTER);
			time = 0;
		}
		else if (rand == 2)
		{
			float randY = gp(hen);
			Vec2 vResolution(Vec2(Core::GetInst()->GetResolution()));
			float fMoveDist = 25.f;
			float fObjScale = 1.f;
			Pterosaur* pMonsterObj = nullptr;
			pMonsterObj = new Pterosaur;
			pMonsterObj->SetName(L"Monster3");
			pMonsterObj->SetPos(Vec2(1500.f, randY));
			pMonsterObj->SetSpeed(w * 1.3);
			pMonsterObj->SetScale(Vec2(fObjScale, fObjScale));
			pMonsterObj->SetCenterPos(pMonsterObj->GetPos());
			pMonsterObj->SetMoveDistance(fMoveDist);
			AddObject(pMonsterObj, GROUP_TYPE::MONSTER);
			time = 0;
		}
		m_time = ct(ten) - (r_time * 0.01);
	}
	Scene::Update();
	/*if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::INGAME);
	}*/
}
