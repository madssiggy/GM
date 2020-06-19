#pragma once
#include "gameobject.h"
class CCamera:public  CGameObject{
private:

	D3DXVECTOR3 m_Target;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	D3DXVECTOR3 GetPos();

};