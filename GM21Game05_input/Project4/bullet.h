#pragma once
#include "gameobject.h"

class CBullet :public CGameObject {
private:
	CModel* m_Model;
	D3DXVECTOR3 moveWay;
	bool canUse;//true‚Ì‚Ý•`‰æ
	int Movecount;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void Create(D3DXVECTOR3 playerPos, D3DXVECTOR3 Way);
	void Destroy();
	bool GetCanUse();
};
const int MaxDistance = 10;