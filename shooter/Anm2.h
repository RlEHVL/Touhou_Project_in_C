#pragma once 
#include "Monster_Bridge.h"

class CAnm2 : public CMonster_Bridge
{
private:
	void Pattern();
	void Shoot(float _angle);
	void ShootSpeed(float _angle, float _speed);
	void Shoot(float _x, float _y);
	void Shoot(float _x, float _y, float _angle);

public:
	virtual void Initialize();
	virtual int Progress(INFO& rInfo);
	virtual void Render(HDC hdc);
	virtual void Release();
	virtual CBridge* Clone() { return new CAnm2(*this); }
public:
	CAnm2();
	~CAnm2();
};
