#include "pch.h"
#include "Monster.h"
#include "TimeMgr.h"
#include "Image.h"
#include "PathMgr.h"
#include "ResMgr.h"
#include "UIImage.h"

void UIImage::SetImage(wstring name, wstring path, float _x, float _y)
{
	image = ResMgr::GetInst()->ImgLoad(name, path);
    SetPos(Vec2(_x, _y));
}

void UIImage::SetScale(float x, float y)
{
    scaleX = x / 100.f;
    scaleY = y / 100.f;
}

void UIImage::Update()
{
}

void UIImage::Render(HDC _dc)
{
    int Width = (int)image->GetWidth() * scaleX;
    int Height = (int)image->GetHeight() * scaleY;

    Vec2 vPos = GetPos();
    //¸¶Á¨Å¸ »ö»ó »¬¶§ transparent: Åõ¸íÇÑ
    TransparentBlt(_dc
        , (int)(vPos.x - (float)(Width / 2))
        , (int)(vPos.y - (float)(Height / 2))
        , Width, Height
        , image->GetDC()
        , 0, 0, Width, Height
        , RGB(255, 0, 255));
    Component_Render(_dc);
}

UIImage::UIImage()
{
}

UIImage::~UIImage()
{
}
