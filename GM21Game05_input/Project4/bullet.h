#pragma once
#include "gameobject.h"
#include "collision.h"
class CBullet :public CGameObject {
private:
	CModel* m_Model;
	D3DXVECTOR3 moveWay;
	bool canUse;//true‚Ì‚Ý•`‰æ
	int Movecount;
	CCollision m_Col;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void Create(D3DXVECTOR3 playerPos, D3DXVECTOR3 Way);
	void Destroy();
	bool GetCanUse();
	CCollision GetCollision() { return m_Col; }

};
const int MaxDistance = 10;