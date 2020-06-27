#pragma once
#include "gameobject.h"
class CCamera:public  CGameObject{
private:

	D3DXVECTOR3 m_Target;
public:
	void Init();
	void Init(D3DXVECTOR3 pPos,
		D3DXVECTOR3 mPos = D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3 mRot = D3DXVECTOR3(0, 0, 0));
	void Uninit();
	void Update();
	void Update(D3DXVECTOR3 playerPos);
	void Draw();
	void Draw(const D3DXVECTOR3& pPos);
	D3DXVECTOR3 GetPos();
	void SetPos(D3DXVECTOR3 playerPos);
};