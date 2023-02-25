#pragma once
#include "Object.h"

class Image;
class Background:
	public Object
{
private:
	Image* m_Image;
	float   m_fSpeed;
	int     m_iDir;
public:
	Background();
	~Background();

	void SetSpeed(float _f) { m_fSpeed = _f; }
private:
	CLONE(Background);
public:
	void Update()       override;
	void Render(HDC _dc) override;
};

