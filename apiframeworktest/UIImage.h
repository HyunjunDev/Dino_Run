#pragma once
#include "Object.h"

class Image;
class UIImage:
	public Object
{
public:
    Image* image;

    float scaleX;
    float scaleY;
public :
    void SetImage(wstring name, wstring path, float x, float y);
    void SetScale(float x, float y);
public:
    virtual void Update() override;
    virtual void Render(HDC _dc) override;
    //    Monster* Clone() { return new Monster(*this); }
    CLONE(UIImage);

public:
    UIImage();
    ~UIImage();
};

