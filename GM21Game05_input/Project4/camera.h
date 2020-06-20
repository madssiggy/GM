#pragma once
#include "gameobject.h"
class CCamera:public  CGameObject{
private:

	D3DXVECTOR3 m_Target;
public:
	void Init();
	void Uninit();
	void Update();
	void Update(D3DXVECTOR3 playerPos);
	void Draw();
	D3DXVECTOR3 GetPos();
	void SetPos(D3DXVECTOR3 playerPos);
};